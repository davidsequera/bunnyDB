#pragma once
#include <string>


namespace JSON{
    struct Object {
        int n;
        char** field;
        char** value;
        int start;
        int end;
    };
    struct ObjectArray {
        int n;
        Object* object;
    };
    Object StoO(char*);
    char* OtoS(Object);
    Object getObject(std::string path, std::string id);
    ObjectArray getObjectsByTable(std::string path, std::string tableName);
    ObjectArray getObjectsByKey(std::string path, std::string field, std::string value);
    void printObject(Object);
    void printObjectArray(ObjectArray );
    Object templateObject(std::string fields);
    bool insertNewObject(std::string path, std::string tableName, Object object);
    bool createObject(std::string path, std::string tableName, std::string fields);
    bool insertObject(std::string path, Object object);
    bool changeField(Object &object, std::string field, std::string value);
    bool insertField(Object &object,int p, std::string field, std::string value);
     bool updateObject(string path, string id, string field, string value);
    bool deleteObject(std::string path, std::string id);
    bool fileEdit(std::string path,int position = 0, int delay = 0, char* token = "");
    std::string genID();
    std::string tabletoString(std::string path, std::string tableName,int &tstart,int &tend );//deveulve las posiciones
}
char* stoc(string);

