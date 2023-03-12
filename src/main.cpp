#include <iostream>
#include "./Lib/JSON.h"
#include <string>
#include <fstream>
#include <time.h>
#include <regex>
#include <ctime>
#include <sstream>

#define PATH "web\\db.js"

using namespace std;

string generarFecha(){
    time_t t = time(NULL);
	tm* punteroTiempo = localtime(&t);
    stringstream ss_year;
    ss_year << punteroTiempo->tm_year+1900;
    string anio = ss_year.str();
    stringstream ss_month;
    ss_month << punteroTiempo->tm_mon+1;
    string mes = ss_month.str();
    if(atoi(mes.c_str()) < 10){
        mes = "0"+mes;
    }
    stringstream ss_day;
    ss_day << punteroTiempo->tm_mday;
    string dia = ss_day.str();
    if(atoi(dia.c_str()) < 10){
        dia = "0"+dia;
    }
    stringstream ss_hour;
    ss_hour << punteroTiempo->tm_hour;
    string hora = ss_hour.str();
    if(atoi(hora.c_str()) < 10){
        hora = "0"+hora;
    }

    stringstream ss_min;
    ss_min << punteroTiempo->tm_min;
    string minutos = ss_min.str();
    if(atoi(minutos.c_str()) < 10){
        minutos = "0"+minutos;
    }
    stringstream ss_sec;
    ss_sec << punteroTiempo->tm_sec;
    string segundos = ss_sec.str();
    if(atoi(segundos.c_str()) < 10){
        segundos = "0"+segundos;
    }
    string Fecha = dia+"/"+mes+"/"+anio+"_"+hora+":"+minutos;
    return Fecha;
}

void changePrice(string &general,string &preferencial){
    string opcion="";
    do{
        cout<<"Que precio desea cambiar? (g=general/p=preferencial/s=salir): "<<endl;
        getline(cin,opcion);
        if(opcion=="g"){
            cout<<"A que valor desea cambiar el precio?: ";
            getline(cin,general);
        }else if(opcion=="p"){
            cout<<"A que valor desea cambiar el precio?: ";
            getline(cin,preferencial);
        }
        system("cls");
    }while(opcion!="s");
}

void header();

void cleanMemoryObject(JSON::Object);
void cleanMemoryArray(JSON::ObjectArray);

//principal functions
void showMovies();

void addMovie();
void addRoom();
void addShowtime();
void addSeat();
void addSeatsToShowroom(string);

void deleteMovie(string);
void deleteShowtime(string);
void deleteRoom(string);
void deleteSeat(string );
void deleteSeatByMovie();
void deleteShowtimeByMovie(string);
bool sellSeats(string,string);
void generateTicket(string,string,string,string,string);

int main(){
    string valGeneral="5.000",valPreferencial="8.000";
    srand(time(NULL));
    int option = 0, edit = 0, add_delete; string  sad;
    do
    {
        system("cls");
        header();
        cout << "Welcome to CineApp" << endl;
        cout <<"  1. Cosult Movies/Show Times/Rooms/Seats"<<endl;
        cout <<"  2. Edit Movies/Show Times/Rooms/Seats"<<endl;
        cout <<"  3. Sell Ticket"<<endl;
        cout <<"  4. Change price"<<endl;
        cout <<"  5. Exit"<<endl;
        cout <<"\n  Choose an option: ";
        cin>>option;
        switch(option)
        {
        case 1:
            system("cls");
            showMovies();
            break;
        case 2:
            cout<<"\n 1.Add \n 2.delete ";
            do
            {
                cout<<"\n  Choose an edit: ";
                cin >> add_delete;
            }
            while( add_delete != 1 && add_delete != 2);
            system("cls");
            cout<<"\n Edit a:"<<endl;
            cout<<"   1.movie"<<endl;
            cout<<"   2.room"<<endl;
            cout<<"   3.seat"<<endl;
            cout<<"   4.showtime"<<endl;
            do
            {
                cout<<"\n  Choose an type: ";
                cin>>edit;
            }
            while( edit != 1 && edit != 2 && edit != 3 && edit != 4);
            sad = add_delete==1? "Add":"Delete";
            if(edit == 1){
                cout<< sad <<" movie:"<<endl;
                if(add_delete==1){
                    cin.ignore(1);
                    addMovie();
                }else{
                    cin.ignore(1);
                    cout<<"Que pelicula desea eliminar: ";
                    string name="";
                    getline(cin,name);
                    deleteMovie(name);
                }

            }
            else if (edit == 2)
            {
                cout<< sad <<" room"<<endl;
                if(add_delete==1){
                    cin.ignore(1);
                    addRoom();
                }else{
                    cin.ignore(1);
                    cout<<"Que sala desea eliminar: ";
                    string name="";
                    getline(cin,name);
                    deleteRoom(name);
                }

            }else if(edit == 3)
            {
                cout<< sad <<" seat"<<endl;
                if(add_delete==1){
                    cin.ignore(1);
                    addSeat();
                }else{
                    cin.ignore(1);
                    deleteSeatByMovie();
                }
            }else if(edit == 4)
            {
                cout<< sad <<" show room"<<endl;
                if(add_delete==1){
                    cin.ignore(1);
                    addShowtime();
                }else{
                    cin.ignore(1);
                    cout<<"A que pelicula pertenece la funcion: ";
                    string name="";
                    getline(cin,name);
                    deleteShowtimeByMovie(name);
                }
            }
            break;
        case 3:
            system("cls");
            cin.ignore(1);
            sellSeats(valGeneral,valPreferencial);
            break;
        case 4:
            system("cls");
            cin.ignore(1);
            changePrice(valGeneral,valPreferencial);
            break;
        case 5:
            cout <<"  Have a good day :)"<<endl;
            option = 6;
            break;
        default:
            cout << "  Invalid option !!\n" << endl;
            break;
        }
    }
    while(option!=6);
    return 0;
}

void header(){
    cout<<"  -------------------------------"<<"  -------------------------------"<<endl;
    cout<<"  |                              "<<" |                               |"<<endl;
    cout<<"  |                              "<<" |           CREATED BY          |"<<endl;
    cout<<"  |                              "<<" |    Jhoseph Samirt Lizarazo    |"<<endl;
    cout<<"  |            CineApp           "<<" |    Jaider David Daza Pardo    |"<<endl;
    cout<<"  |                              "<<" |    David Alejandro Sequera    |"<<endl;
    cout<<"  |                              "<<" |  Kevin Leonardo Lopez Garcia  |"<<endl;
    cout<<"  |                              "<<" |                               |"<<endl;
    cout<<"  -------------------------------"<<"  -------------------------------" <<endl;
}

void showMovies(){
    system("start web\\index.html");
}

void addMovie(){
    string id=JSON::genID();
    cout<<"Digite el nombre de la pelicula: ";
    string nombre="";
    getline(cin,nombre);

    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", nombre);

    if(arrmovie.n!=0){
        cout<<"Ya existe esa pelicula."<<endl;
    }else{
        cout<<"Digite el link de la imagen: ";
        string imagen="";
        getline(cin,imagen);
        string peliculaa="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"name\":\""+nombre+"\",\n\t\t\"img\":\""+imagen+"\",\n\t},\n";
        char* moviee=new char[100];
        moviee=stoc(peliculaa);
        JSON::Object x=JSON::StoO(moviee);
        insertNewObject(PATH,"MOVIE",x);
    }
}

void addRoom(){
    string id=JSON::genID();
    cout<<"Digite el nombre de la nueva sala: ";
    string nombre="";
    getline(cin,nombre);

    JSON::ObjectArray arrroom = JSON::getObjectsByKey(PATH,"name", nombre);

    if(arrroom.n!=0){
        cout<<"Ya existe esa sala."<<endl;
    }else{
        cout<<" ¡Recuerde que cada sala nueva se crea inicialmente con 16 sillas! "<<endl;
        string sala="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"name\":\""+nombre+"\",\n\t\t\"seats\":\"16\",\n\t},\n";
        char* cuartoC=new char[100];
        cuartoC=stoc(sala);
        JSON::Object x=JSON::StoO(cuartoC);
        insertNewObject(PATH,"ROOM",x);
    }
}

void addShowtime(){

    string id=JSON::genID();
    cout<<"Digite el nombre de la pelicula: ";
    string nombrePelicula="";
    getline(cin,nombrePelicula);

    cout<<"Digite el nombre de la sala que va a asignar a esta funcion: ";
    string nombreSala="";//nombre de la sala
    getline(cin,nombreSala);

    cout<<"Digite a que hora quiere la nueva funcion: ";
    string tiempo="";//00:00
    getline(cin,tiempo);

    //Sacar Id pelicula
    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", nombrePelicula);
    JSON::Object movie = *(arrmovie.object);
    string idMovie = *(movie.value);

    //Sacar Id room
    JSON::ObjectArray arrsala = JSON::getObjectsByKey(PATH,"name", nombreSala);
    JSON::Object sala = *(arrsala.object);
    string idSala = *(sala.value);

    //crear horario
    string sShowRoom="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"time\":\""+tiempo+"\",\n\t\t\"room_id\":\""+idSala+"\"\n\t\t\"movie_id\":\""+idMovie+"\",\n\t},\n";
    JSON::Object x=JSON::StoO(stoc(sShowRoom));
    JSON::insertNewObject(PATH,"SHOWTIME",x);
    addSeatsToShowroom(id);
}

void addSeat(){

    string id=JSON::genID();
    cout<<"Ingrese el nombre de la pelicula: ";
    string nombrePelicula="";
    getline(cin,nombrePelicula);
    cout<<"Digite el tipo de silla (G-general/P-preferencial): ";
    string tipoSilla="";
    getline(cin,tipoSilla);
    cout<<"Ingrese la posicion de la silla: ";
    string posSilla="";
    getline(cin,posSilla);
    cout<<"Digite la hora de la funcion: ";
    string horario="";
    getline(cin,horario);
    cout<<"Ingrese el nombre de la sala:";
    string nSala="";
    getline(cin,nSala);


    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", nombrePelicula);
    JSON::Object movie = *(arrmovie.object);
    string movie_id = *(movie.value);
    string showtime_id="";

    JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"movie_id", movie_id);

    for (size_t i = 0; i < arrshowtime.n; i++){
        if(strcmp(stoc(movie_id),*((*(arrshowtime.object+i)).value+3))==0  &&strcmp(stoc(horario),*((*(arrshowtime.object+i)).value+1))==0){
            showtime_id=*((*(arrshowtime.object+i)).value);
        }
    }

    string sSilla="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"type\":\""+tipoSilla+"\",\n\t\t\"state\":\"A\",\n\t\t\"postion\":\""+posSilla+"\",\n\t\t\"showtime_id\":\""+showtime_id+"\",\n\t},\n";
    JSON::Object x=JSON::StoO(stoc(sSilla));
    insertNewObject(PATH,"SEAT",x);

}

void addSeatsToShowroom(string showTimeId){
    string id;
    for(int nSilla=1;nSilla<=16;nSilla++){
        id=JSON::genID();
        char *intStr = itoa(nSilla,intStr,10);
        string str = string(intStr);
        string sSilla="";
        if(nSilla<=9){
            sSilla="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"type\":\"G\",\n\t\t\"state\":\"A\",\n\t\t\"postion\":\""+str+"\",\n\t\t\"showtime_id\":\""+showTimeId+"\",\n\t},\n";

        }else{
            sSilla="\t{\n\t\t\"id\":\""+id+"\",\n\t\t\"type\":\"P\",\n\t\t\"state\":\"A\",\n\t\t\"postion\":\""+str+"\",\n\t\t\"showtime_id\":\""+showTimeId+"\",\n\t},\n";
        }
        JSON::Object x=JSON::StoO(stoc(sSilla));
        insertNewObject(PATH,"SEAT",x);
    }


}

void deleteMovie(string name){
    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", name);
    if(arrmovie.n==0){
        cout<<"No existe esa pelicula."<<endl;
        system("pause");
    }else{
        JSON::Object movie = *(arrmovie.object);
        string id = *(movie.value);
        JSON::deleteObject(PATH, id);
        JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"movie_id", id);
        for (size_t i = 0; i < arrshowtime.n; i++)
        {
            deleteShowtime(*((arrshowtime.object+i)->value));
        }
    }
}
void deleteRoom(string name){
    JSON::ObjectArray arrroom = JSON::getObjectsByKey(PATH,"name", name);
    JSON::Object room = *(arrroom.object);
    string id = *(room.value);
    JSON::deleteObject(PATH, id);
    JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"room_id", id);
    for (size_t i = 0; i < arrshowtime.n; i++)
    {
        deleteShowtime(*((arrshowtime.object+i)->value));
    }
}
void deleteShowtime(string id){
    JSON::deleteObject(PATH, id);
    JSON::ObjectArray arrseats;
    arrseats = JSON::getObjectsByKey(PATH,"showtime_id", id);
    for (size_t j = 0; j < arrseats.n; j++)
    {
        deleteSeat(*((arrseats.object+j)->value));
    }
}

void deleteShowtimeByMovie(string name){
    cout<<"Ingrese la sala de la funcion a eliminar: ";
    string nombreSala="";
    getline(cin,nombreSala);
    cout<<"Ingrese el horario de la funcion a eliminar: ";
    string horaFuncion="";
    getline(cin,horaFuncion);

    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", name);
    JSON::Object movie = *(arrmovie.object);
    string movie_id = *(movie.value);
    string showtime_id="";
    JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"movie_id", movie_id);

    JSON::ObjectArray arrSalas=JSON::getObjectsByKey(PATH,"name",nombreSala);
    JSON::Object sSala = *(arrSalas.object);
    string room_id= *(sSala.value);

    for (size_t i = 0; i < arrshowtime.n; i++){
        if(strcmp(stoc(movie_id),*((*(arrshowtime.object+i)).value+3))==0 && (strcmp((stoc(horaFuncion)),*((*(arrshowtime.object+i)).value+1))==0) && strcmp(stoc(room_id),*((*(arrshowtime.object+i)).value+2))==0){
            showtime_id=*((*(arrshowtime.object+i)).value);
            JSON::deleteObject(PATH,showtime_id);
        }
    }
    if (showtime_id!=""){
        JSON::ObjectArray arrSillas = JSON::getObjectsByKey(PATH,"showtime_id", showtime_id);
        for (size_t i = 0; i < arrSillas.n; i++){
            JSON::deleteObject(PATH,*((*(arrSillas.object+i)).value));
        }
    }else{
        cout<<"No se encontro esa funcion."<<endl;
    }
}


void deleteSeat(string id){
    JSON::deleteObject(PATH, id);
}

void deleteSeatByMovie(){

    cout<<"Ingrese el nombre de la pelicula: ";
    string nombrePelicula="";
    getline(cin,nombrePelicula);
    cout<<"Hora: ";
    string horario="";
    getline(cin,horario);
    cout<<"Sala:";
    string nSala="";
    getline(cin,nSala);
    cout<<"Silla: "<<endl;;
    string posSilla="";
    getline(cin,posSilla);

    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", nombrePelicula);
    JSON::Object movie = *(arrmovie.object);
    string movie_id = *(movie.value);
    string showtime_id="";

    JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"movie_id", movie_id);

    for (size_t i = 0; i < arrshowtime.n; i++){
        if(strcmp(stoc(movie_id),*((*(arrshowtime.object+i)).value+3))==0  &&strcmp(stoc(horario),*((*(arrshowtime.object+i)).value+1))==0){
            showtime_id=*((*(arrshowtime.object+i)).value);
        }
    }
    JSON::ObjectArray arrSillas = JSON::getObjectsByKey(PATH,"showtime_id", showtime_id);
    for (size_t i = 0; i < arrSillas.n; i++){
        if(strcmp(stoc(posSilla),*((*(arrSillas.object+i)).value+3))==0){
            JSON::deleteObject(PATH,*((*(arrSillas.object+i)).value));
        }
    }
}

int avaibleSeats(string name){
    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", name);
    JSON::Object movie = *(arrmovie.object);
    string id = *(movie.value);
    JSON::ObjectArray arrshowtimes = JSON::getObjectsByKey(PATH,"movie_id", id);
    int count = 0;
    for (size_t i = 0; i < arrshowtimes.n; i++)
    {
        if(false){
            count++;
        }
    }
    return count;
}

bool sellSeats(string valGeneral,string valPreferencial){

    cout<<"Ingrese el nombre de la pelicula: ";
    string nombrePelicula="";
    getline(cin,nombrePelicula);
    cout<<"Hora: ";
    string horario="";
    getline(cin,horario);
    cout<<"Sala:";
    string nSala="";
    getline(cin,nSala);
    cout<<"Silla: ";
    string posSilla="";
    getline(cin,posSilla);

    JSON::ObjectArray arrmovie = JSON::getObjectsByKey(PATH,"name", nombrePelicula);
    JSON::Object movie = *(arrmovie.object);
    string movie_id = *(movie.value);
    string showtime_id="";

    JSON::ObjectArray arrshowtime = JSON::getObjectsByKey(PATH,"movie_id", movie_id);

    for (size_t i = 0; i < arrshowtime.n; i++){
        if(strcmp(stoc(movie_id),*((*(arrshowtime.object+i)).value+3))==0  &&strcmp(stoc(horario),*((*(arrshowtime.object+i)).value+1))==0){
            showtime_id=*((*(arrshowtime.object+i)).value);
        }
    }
    JSON::ObjectArray arrSillas = JSON::getObjectsByKey(PATH,"showtime_id", showtime_id);
    for (size_t i = 0; i < arrSillas.n; i++)
    {
        if(strcmp(stoc(posSilla),*((*(arrSillas.object+i)).value+3))==0){
            JSON::Object seat = JSON::getObject(PATH,*((*(arrSillas.object+i)).value));
            //validar
            if(*(*(seat.value+2)) == 'A'){
                if(*(*(seat.value+ 1)) == 'P'){
                    JSON::updateObject(PATH,*((*(arrSillas.object+i)).value),"state","B");
                    generateTicket(nombrePelicula,horario,nSala,posSilla,valPreferencial);
                    return true;
                }else{
                    JSON::updateObject(PATH,*((*(arrSillas.object+i)).value),"state","B");
                    generateTicket(nombrePelicula,horario,nSala,posSilla,valGeneral);
                    return true;
                }
            }else
                cout<<"Esta silla ya esta vendida."<<endl;
                return false;
            }
        }
    return false;
}

void generateTicket(string movie,string sala,string hora,string silla,string precio){
    string date=generarFecha();
    ofstream tiquete;
    tiquete.open("TIQUETE.txt",ios::out);
    tiquete<<"Dia y Hora: "<<date<<endl;
    tiquete<<"Pelicula: "<<movie<<endl;
    tiquete<<"Sala: "<<sala<<endl;
    tiquete<<"Hora de la funcion: "<<hora<<endl;
    tiquete<<"Numero de silla: "<<silla<<endl;
    tiquete<<"-------------------"<<endl;
    tiquete<<"VALOR TOTAL: $"<<precio<<endl;
    tiquete.close();
    cout<<"-----EL TICKET SE GENERO EN LA CARPETA DONDE ESTA UBICADO EL ARCHIVO!-----"<<endl;
}

void cleanMemoryObject(JSON::Object obj){
    for (int i = 0; i < obj.n; i++) {
        delete *(obj.field+i);
        delete *(obj.value+i);
    }
    delete[] obj.field;
    delete[] obj.value;
}
void cleanMemoryArray(JSON::ObjectArray arr){
    for (int i = 0; i < arr.n; i++) {
        cleanMemoryObject(*(arr.object+i));
    }
    delete arr.object;
}
