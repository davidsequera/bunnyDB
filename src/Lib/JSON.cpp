#include "JSON.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <regex>


using namespace std;

//JSON parse Library

//strign to char
char* stoc(string a){
    char* b = new char[(a.length()+1)];
    for (size_t i = 0; i <= a.length(); i++)
    {
     *(b+i) = i!=a.length()? a[i] : (char)0;
    }
    return b;
}

//depreciated due to regex implementation

//matrix management
char **createMatrix(int f, int c) {
    char** m = new char* [f];
    for (int i = 0; i < f; i++) {
        //m[i]= new int[c];
        *(m + i) = new char[c+1];
    }
    return m;
}

void fillMatrix(char** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            *(*(m + i) + j) = j==c ?(char)0: '0'; // m[i][j]
        }
    }
}

// not suitalble for unitialized char*;
void resizing(char*& m, int p) {
    //aumenta un espacio de mas
    char* aux = new char[p+2];
    for (size_t i = 0; i < (p+2); i++)
    {
        if(i < strlen(m)){
            *(aux + i) = i!=(p+1)? *(m + i) : (char)0 ;
        }else{
            *(aux + i) = i!=(p+1)? '0': (char)0;
        }
    }
    delete[] m;
    m = aux;
}



//file management
// bool fileEdit(string path,int position, int delay, char* token){
//         char* s1 = new char[1], * s2 = new char[1];
//         fstream file(path, ios::in| ios::out | ios::binary);
//         if(file.fail()){
//             cout << "[fileEdit] Unable to open File" <<endl;
//             return false;
//         }
//         int end; 
//         file.seekg(0, ios::end);
//         end = file.tellg();
//         file.seekg(0, ios::beg);
//         if(end > (position+delay) && delay >= 0 && position >= 0 && !file.fail()){
//             s1= new char[(position)+1];
//             s1[(position)] = (char)0;//define el final de la linea
//             s2 = new char[(end - delay - position)+1];
//             s2[(end - delay - position)] = (char)0;
//             file.read((char*)s1,position);
//             file.seekg(delay, ios::cur);
//             file.read((char*)s2,(end - delay - position));
//             file.close();
//             ofstream ofile(path, ios::trunc);
//             if(ofile.fail()){
//                 cout << "[fileEdit] Fatal Error" << endl;
//                 return false;
//             }
//             ofile.close();
//             ofile.clear();
//             file.open(path, ios::out| ios::in | ios::binary );
//             if(file.fail()){
//                 cout << "[fileEdit] Opening Error" << endl;
//                 return false;
//             }else{
//                 file.write((char*)s1,position);
//                 file.write((char*)token,strlen(token));
//                 file.write((char*)s2,strlen(s2));        
//             }     
//         }else if(!file.fail()){
//             cout << "[fileEdit] Invalid Params" <<endl;
//             file.close();
//             file.clear();
//             return false;
//         }
//         file.close();
//         file.clear();
//         return true;
//         delete s1;
//         delete s2;
//     }

//keword

namespace JSON {
    Object StoO(char* token) {
        string s = token;
        smatch sm;//smatch a inicialization sm[0]
        regex e ("\"[^:].*?\"");
        int f = 0, c= 2, j=0, v=0;//j is a counter of number of matches
        while (regex_search (s,sm,e)) {
            for (auto x:sm) f++;
            s = sm.suffix().str();
        }
        s = token;
        char** field = createMatrix((f/2), c);
        fillMatrix(field, (f / 2), c);
        char** value = createMatrix((f/2), c);
        fillMatrix(value, (f / 2), c);
        while (regex_search (s,sm,e)) {
            for (auto x:sm){
            string z = x.str();
                for(char i:z){
                if(i != '\"'){
                    if (j % 2 == 0) {
                        resizing(*(field + (j / 2)), v);
                        *(*(field + (j / 2)) + v) = i;
                        }
                    else {
                    int aux = (j - 1) / 2;
                        resizing(*(value + aux), v);
                        *(*(value + aux) + v) = i;
                        }
                    v++;
                    }else{
                    v = 0;
                    }
                }
            }
        j++;
        s = sm.suffix().str();
      }
        Object object;
        object.n = f / 2;
        object.field = field;
        object.value = value;
        object.start = 0;
        object.end = 0;
        return object;
    }
    char* OtoS(Object object) {
        char* a = new char[1];//"{\",:\n }";
        int p = 0;
        *a = '{';
        for (size_t i = 0; i < object.n; i++)
        {
            resizing(a,++p);
            *(a+p) = '\r';
            resizing(a,++p);
            *(a+p) = '\n';
            resizing(a,++p);
            *(a+p) = '\t';
            resizing(a,++p);
            *(a+p) = '\t';
            resizing(a,++p);
            *(a+p) = '\"';
            for (size_t u = 0; *(*(object.field+i)+u) != (char)0; u++)
            {
                resizing(a,++p);
                *(a + p) = *(*(object.field + i) + u);
            }
            resizing(a,++p);
            *(a + p) = '\"';
            resizing(a,++p);
            *(a + p) = ':';
            resizing(a,++p);
            *(a + p) = '\"';
            for (size_t v = 0; *(*(object.value + i) + v) != (char)0; v++)
            {
                resizing(a,++p);
                *(a + p) = *(*(object.value + i) + v);
            }
            resizing(a,++p);
            *(a + p) = '\"';
            if(i+1 != object.n){
                resizing(a,++p);
                *(a + p) = ',';
            }
        }
        resizing(a,++p);
        *(a + p) = '\r';
        resizing(a,++p);
        *(a + p) = '\n';
        resizing(a,++p);
        *(a + p) = '\t';
        resizing(a,++p);
        *(a + p) = '}';
        resizing(a,++p);
        *(a + p) = (char)0;
        return a;
    }
    Object getObject(string path, string id) {
    int start, end;
    ifstream file(path, ios::in | ios::binary);
    if(file.fail()){
        cout << "[getObject] Unable to open File" <<endl;
    }
    string regexId;
    regexId.append("(.*)(\"id\" ?: ?\"");
    regexId.append(id);
    regexId.append("\"),?");
    string line;
    int initial = -1;//line where id was found
    while ( initial ==-1 && !file.eof() ) {
        getline(file, line);
        if (line.find(id) != string::npos && regex_search(line, regex(regexId))) {
            initial = file.tellg();
        }
    }
    file.close();
    file.clear();
    file.open(path, ios::in | ios::binary);//reopen to avoid
    if(file.fail()){
        cout << "[getObject] Unable to reopen the file" <<endl;
    }
    file.seekg(initial, ios::beg);
    char* aux= new char[1];
    while(file.tellg() > 1 && *aux != '{'){
        file.seekg(-2, ios::cur);
        file.read(aux, 1);
    }
    start = (int)file.tellg() - 1;
    file.seekg(start, ios::beg);
    getline(file, line, '}');
    line.append("}");
    end = file.tellg();
    file.close();
    file.clear();
    Object object = StoO(stoc(line));
    object.start = start;
    object.end = end;
    return object;
    }
    ObjectArray getObjectsByTable(string path, string tableName){
        int tstart, tend, initial = -1;//line where regex is found
        ifstream file(path, ios::in | ios::binary);
        if(file.fail()){
            cout << "[getObjectsByTable] Unable to open File" <<endl;
        }
        string regexTable;
        string line;
        regexTable.append("(.*)\"");
        regexTable.append(tableName);
        regexTable.append("\" *: *\\[");
        while ( initial ==-1 && !file.eof() ) {
            getline(file, line);
            if (line.find(tableName) != string::npos && regex_search(line, regex(regexTable))) {
                initial = file.tellg();
            }
        }
        file.close();
        file.clear();
        file.open(path, ios::in | ios::binary);//reopen to avoid
        if(file.fail()){
            cout << "[getObjectsByTable] Unable to reopen the file" <<endl;
        }
        file.seekg(initial, ios::beg);
        char* aux= new char[1];
        while(file.tellg() > 1 && *aux != '['){
            if(file.tellg() > 1){
                file.seekg(-2, ios::cur);
            }
            file.read(aux, 1);
        }
        tstart = (int)file.tellg() - 1;
        file.seekg(tstart, ios::beg);
        getline(file, line, ']');
        line.append("]");
        tend = file.tellg();
        file.close();
        file.clear();
        Object* objects = new Object[1];
        int relativePostion = tstart,start, end, ne = -1; bool notfound = true;
        do{
            notfound = true;
            ifstream file(path, ios::in | ios::binary);
            if(file.fail()){
                cout << "[getObjectByKey] Unable to open File after table" <<endl;
            }
            file.seekg(relativePostion, ios::beg);
            string regexS = "(.*)(\"id\" *: *\"(.*)\"),?";
            initial = -1;//line where id was found
            while ( initial ==-1 && file.tellg() < tend ) {
                getline(file, line);
                if (regex_search(line, regex(regexS))) {
                    initial = file.tellg();
                    relativePostion = initial;
                    notfound= false;
                    ne++;
                }
            }
            file.clear();
            file.close();
            if(!notfound){
                file.open(path, ios::in | ios::binary);//reopen to avoid
                if(file.fail()){
                    cout << "[getObjectByKey] Unable to reopen the file after table" <<endl;
                }
                file.seekg(initial, ios::beg);
                char* aux = new char[1];
                while(file.tellg() > 1 && *aux != '{'){
                    if(file.tellg() > 1){
                        file.seekg(-2, ios::cur);
                    }
                    file.read(aux, 1);
                }
                start = (int)file.tellg() - 1;
                file.seekg(start, ios::beg);
                getline(file, line, '}');
                line.append("}");
                end = file.tellg();
                file.close();
                file.clear();
                if(ne >= 1){
                    //resize objects
                    Object* arr = new Object[ne+1];
                    for(int i = 0 ; i < ne; i++){
                        *(arr+i) = *(objects+i);
                    }
                    delete[] objects;
                    objects = arr;
                }
                *(objects+ne) = StoO(stoc(line));
                (objects+ne)->start = start;
                (objects+ne)->end = end;
            }
        }while(!notfound);
        ObjectArray Array;
        Array.n = ne+1;
        Array.object = objects;
        return Array;
    }
    ObjectArray getObjectsByKey(string path, string field, string value){
        Object* objects = new Object[1];
        int relativePostion = 0,start, end, ne = -1; bool notfound = true;
        do{
            notfound = true;
            ifstream file(path, ios::in | ios::binary);
            if(file.fail()){
                cout << "[getObjectByKey] Unable to open File" <<endl;
            }
            file.seekg(relativePostion, ios::beg);
            string regexS;
            regexS.append("(.*)(\"");
            regexS.append(field);
            regexS.append("\" ?: ?\"");
            regexS.append(value);
            regexS.append("\"),?\n?");
            string line;
            int initial = -1;//line where id was found
            while ( initial ==-1 && !file.eof() ) {
                getline(file, line);
                if (line.find(value) != string::npos && regex_search(line, regex(regexS))) {
                    initial = file.tellg();
                    relativePostion = initial;
                    notfound= false;
                    ne++;
                }
            }
            file.clear();
            file.close();
            if(!notfound){
                file.open(path, ios::in | ios::binary);//reopen to avoid
                if(file.fail()){
                    cout << "[getObjectByKey] Unable to reopen the file" <<endl;
                }
                file.seekg(initial, ios::beg);
                char* aux = new char[1];
                while(file.tellg() > 1 && *aux != '{'){
                    if(file.tellg() > 1){
                        file.seekg(-2, ios::cur);
                    }
                    file.read(aux, 1);
                }
                start = (int)file.tellg() - 1;
                file.seekg(start, ios::beg);
                getline(file, line, '}');
                line.append("}");
                end = file.tellg();
                file.close();
                file.clear();
                if(ne >= 1){
                    //resize objects
                    Object* arr = new Object[ne+1];
                    for(int i = 0 ; i < ne; i++){
                        *(arr+i) = *(objects+i);
                    }
                    delete[] objects;
                    objects = arr;
                }
                *(objects+ne) = StoO(stoc(line));
                (objects+ne)->start = start;
                (objects+ne)->end = end;
            }
        }while(!notfound);
        ObjectArray Array;
        Array.n = ne+1;
        Array.object = objects;
        return Array;
    }
    void printObject(Object object) {
        cout << '{' << '\n';
        for (size_t i = 0; i < object.n; i++) {
            cout << '\t' << '\"' << *(object.field + i) << '\"' << ':' << '\"' << *(object.value + i) << '\"';
            if (i+1 != object.n)
                cout << ',';
            cout << '\n';
        }
        cout << '}' << endl;
    }
    void printObjectArray(ObjectArray ObjectArray) {
        for (size_t i = 0; i < ObjectArray.n; i++)
        {
            printObject(*(ObjectArray.object+i));
        }

    }
    Object templateObject(string fields){
    int n = 0, v =0;
    char** fieldArray = new char*[1];
    regex e ("(\"[^\"]*\")");
    smatch sm;
    string z;
    while (regex_search (fields,sm,e)) {
        if(n >= 1){
            char** aux = new char*[n+1];
            for(int i = 0 ; i < n; i++){
                *(aux+i) = *(fieldArray+i);
            }
            *(aux+n) = new char[1];
            delete[] fieldArray;
            fieldArray = aux;
        }else{
            *(fieldArray+n) = new char[1];
        }
        for (auto x:sm){
            z = x.str();
        }
        for(char i:z){
            if(i != '\"'){
                resizing(*(fieldArray+n), v);
                *(*(fieldArray+n) + v) = i;
                v++;
            }else{
                v = 0;
            }
        }
        n++;
        fields = sm.suffix().str();
    }
    Object object;
    object.n = n;object.start = 0;object.end = 0;
    object.field= new char*[n];
    object.value= new char*[n];
    string value;
    for (size_t i = 0; i < n; i++)
    {
        *(object.field+i) = *(fieldArray+i);
        if(strcmp(*(object.field+i), "id") == 0){
         *(object.value+i) = stoc(genID());
        }else{
         cout << *(object.field+i) <<':';
         getline(cin,value);
         *(object.value+i) = stoc(value);
        }
    }
    return object;
}
    bool insertNewObject(string path, string tableName, Object object){
        bool a = true;
        int tstart, tend, point;//point of reference
        int postion, delay;
        tabletoString(path, tableName,tstart, tend);
        fstream file;
        file.open(path, ios::in | ios::binary);//reopen to avoid problems
        if(file.fail()){
            cout << "[insertNewObject] Unable to reopen the file" <<endl;
        }
        file.seekg(tend, ios::beg);
        char* aux= new char[1];
        while(file.tellg() > 1 && *aux != ',' && *aux != '}' ){
            if(file.tellg() > 1){
                file.seekg(-2, ios::cur);
            }
            file.read(aux, 1);
        }
        point = (int)file.tellg();
        file.clear();
        file.close();
        if((char)*aux != ','){
            fileEdit(path,point, 0, ",\r\n\t");
            point+=4;
        }else{
            fileEdit(path,point, 0, "\r\n\t");
            point+=3;
        }
        a = fileEdit(path, point, 0, OtoS(object));
        return a;
    }
    bool insertObject(string path, Object object){
        bool a = true;
        fstream file;
        if(object.end == 0 && object.start == 0){
            cout << "[insertObject] Non Defined position Object" <<endl;
            a= false;
        }else{
            fileEdit(path, object.start, 0, OtoS(object));
            object = getObject(path, *(object.value));//id
            file.open(path, ios::in | ios::binary);//open to bool if its last
            if(file.fail()){
                cout << "[insertObject] Unable to open the file" <<endl;
                a= false;
            }
            file.seekg(object.start+1, ios::beg);
            char* aux= new char[1];
            while (!file.eof() && *aux != ']' && *aux != '{'  )
            {
                file.read(aux, 1);
                cout << aux;
            }
            cout <<endl;
            file.clear();
            file.close();
            if(*aux == '{'){
                fileEdit(path, object.end, 0, ",\r\n\t" );
            }else if (*aux == ']'){
                fileEdit(path, object.end, 0, "\r\n\t" );
            }
        }
        return a;
}
    bool updateObject(string path, string id, string field, string value){
        Object object = getObject(path, id);
        changeField(object, field, value);
        deleteObject(path, id);
        insertObject(path, object);
        return true;
    }
    bool createObject(string path, string tableName, string fields){
        Object obj= templateObject(fields);
        bool a = insertNewObject(path, tableName, obj);
        return a;
    }
    bool changeField(Object &object, string field, string value){
        int n= 0;
        while(strcmp(stoc(field),  *(object.field+n)) != 0 && n<= object.n){
            n++;
        }
        if(strcmp(stoc(field),  *(object.field+n)) == 0){
            delete *(object.value+n);
            *(object.value+n) = new char[value.length()+1];//count backslash
            strcpy(*(object.value+n), stoc(value));
            return true;
        }
        return false;
    }
    bool insertField(Object &object,int p, string field, string value){
    if(object.n > p){
        char** fields = new char*[object.n];
        char** values = new char*[object.n];
        for (size_t i = 0; i < object.n; i++)
        {
           *(fields+i) = new char[strlen(*(object.field+i))+1];
           *(values+i) = new char[strlen(*(object.value+i))+1];
           strcpy(*(fields+i), *(object.field+i));
           strcpy(*(values+i), *(object.value+i));
        }
        cout << endl;
        object.n+=1;
        object.field = new char*[object.n];
        object.value = new char*[object.n];
        int j = 0;
        for (size_t i = 0; i < object.n; i++)
        {
          if(i == p){
            *(object.field+i) = new char[(field.length())+1];
            *(object.value+i) = new char[(value.length())+1];
            strcpy(*(object.field+i), stoc(field));
            strcpy(*(object.value+i), stoc(value));
            j-=1;
          }else{
          *(object.field+i) = new char[strlen(*(fields+j))+1];
          *(object.value+i) = new char[strlen(*(values+j))+1];
           strcpy(*(object.field+i), *(fields+j));
           strcpy(*(object.value+i), *(values+j));
          }
          j++;
        }
        return true;
    }else{
        cout << "[insertField] Fatal Error" <<endl;
    }
    //llenar la copia con el espacio p en blanco
    //llenar p con los parametros
    //borrar matrices object.field y object.value y remplazarlas
    //borrar tamanno y contenido de la poscion p en ambos arreglos y repmlazar
    return false;
    }
//  temporal for testing [fileEdit]
    string genID(){
    //rangos ASCII 0-1 (48-57)10 a-z(97-122)26 A-Z(65-90)26
    const int w = 11, z = 20;
    int n;
    char* s = new char[w];//random first
    char* e = new char[z];//finale random
    string t = to_string(time(NULL));//time
    for (size_t i = 0; i < w; i++)
    {
        int a = rand() % 3;
        if(a==0){
            n = rand() % 10 + 48;
        }else if(a==1){
            n = rand() % 26 + 97;
        }else{
            n = rand() % 26 + 65;
        }
        *(s+i)= i==(w-1)? (char)0 : (char)n;
    }
    for (size_t i = 0; i < z; i++)
    {
        if(i%2 == 0){
            *(e+i)= *(s+(i/2)) ;
        }else{
            *(e+i)= i==(z-1)? (char)0 :t[((i-1)/2)] ;
        }
    }
    string ID(e);
    delete s;
    delete e;
    return ID;
    }
    string tabletoString(string path, string tableName,int &tstart,int &tend ){
        int initial = -1;//line where regex is found
        ifstream file(path, ios::in | ios::binary);
        if(file.fail()){
            cout << "[tabletoString] Unable to open File" <<endl;
        }
        string regexTable;
        string line;
        regexTable.append("(.*)\"");
        regexTable.append(tableName);
        regexTable.append("\" *: *\\[");
        while ( initial ==-1 && !file.eof() ) {
            getline(file, line);
            if (line.find(tableName) != string::npos && regex_search(line, regex(regexTable))) {
                initial = file.tellg();
            }
        }
        file.close();
        file.clear();
        file.open(path, ios::in | ios::binary);//reopen to avoid problems
        if(file.fail()){
            cout << "[tabletoString] Unable to reopen the file" <<endl;
        }
        file.seekg(initial, ios::beg);
        char* aux= new char[1];
        while(file.tellg() > 1 && *aux != '['){
            if(file.tellg() > 1){
                file.seekg(-2, ios::cur);
            }
            file.read(aux, 1);
        }
        tstart = (int)file.tellg() - 1;
        file.seekg(tstart, ios::beg);
        getline(file, line, ']');
        line.append("]");
        tend = file.tellg();
        file.close();
        file.clear();
        return line;
    }
    bool fileEdit(string path,int position, int delay, char* token){
        char* s1 = new char[1], * s2 = new char[1];
        fstream file(path, ios::in| ios::out | ios::binary);
        if(file.fail()){
            cout << "[fileEdit] Unable to open File" <<endl;
            return false;
        }
        int end;
        file.seekg(0, ios::end);
        end = file.tellg();
        file.seekg(0, ios::beg);
        if(end > (position+delay) && delay >= 0 && position >= 0 && !file.fail()){
            s1= new char[(position)+1];
            s1[(position)] = (char)0;//define el final de la linea
            s2 = new char[(end - delay - position)+1];
            s2[(end - delay - position)] = (char)0;
            file.read((char*)s1,position);
            file.seekg(delay, ios::cur);
            file.read((char*)s2,(end - delay - position));
            file.close();
            ofstream ofile(path, ios::trunc);
            if(ofile.fail()){
                cout << "[fileEdit] Fatal Error" << endl;
                return false;
            }
            ofile.close();
            ofile.clear();
            file.open(path, ios::out| ios::in | ios::binary );
            if(file.fail()){
                cout << "[fileEdit] Opening Error" << endl;
                return false;
            }else{
                file.write((char*)s1,position);
                file.write((char*)token,strlen(token));
                file.write((char*)s2,strlen(s2));
            }
        }else if(!file.fail()){
            if(end <= (position+delay)){
                // cout << "[fileEdit] Invalid Params End " <<endl;
            }else if(delay < 0 || position < 0){
                if(delay < 0){
                    // cout << "[fileEdit] Invalid Params Delay" <<endl;
                }else{
                    // cout << "[fileEdit] Invalid Params Position" <<endl;
                }
            }
            file.close();
            file.clear();
            return false;
        }
        file.close();
        file.clear();
        return true;
        delete s1;
        delete s2;
    }
    bool deleteObject(string path, string id){
        Object object (getObject(path, id));
        int length = object.end - object.start;
        bool a = fileEdit(path,object.start, length);
        //correct if it has a ',' or/and  '\n'
        if(a){
            fstream file(path, ios::in| ios::out | ios::binary);
            if(file.fail()){
                cout << "[deleteObject] Unable to open File" <<endl;
                a = false;
            }else{
                file.seekg(object.start, ios::beg);
                int nd =0;
                char* aux= new char[2];
                while(file.tellg() > 1 && *aux != '{' && *aux != ']' ){
                    file.read(aux, 1);
                    nd++;
                }
                if(*aux == '{' || *aux == ']'){
                    bool final = false;
                    int pf = 0;
                    if(*aux == ']'){
                        final = false;
                        file.seekg(object.start, ios::beg);
                        while(file.tellg() > 1 && *aux != ',' && *aux != '}' ){
                            file.seekg(-2, ios::cur);
                            file.read(aux, 1);
                        }
                        if(*aux == ','){
                            file.read(aux, 1);
                            if(*aux == '}'){//condition to avoid ] when end
                                final = true;
                                pf = (int)file.tellg()-2;
                            }
                        }
                    }
                    file.clear();
                    file.close();
                    nd-=1;
                    a = fileEdit(path,object.start, nd);
                    if(final){
                        a = fileEdit(path,pf, 1);
                    }
                }else{

                file.clear();
                file.close();
                }
                delete aux;
            }

        }
        return a;
    }
};
