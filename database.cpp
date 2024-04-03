#include <string>
#include <iostream>
using namespace std;

#define DATABASE_H

enum Type
{
    INT,
    DOUBLE,
    STRING,
    ARRAY
};

struct Array
{
    int size;
    Type type;
    void *items;
};

struct Entry
{
    Type type;
    std::string key;
    void *value;
};

struct Database
{
    int datasize;
    Entry *entry;
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value)
{
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;
    return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database)
{
    database.datasize = 0;
    database.entry = new Entry[1];
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry)
{
    int count = -1;
    database.datasize++;
    Entry *newData = new Entry[database.datasize];
    for (int i = 0; i < database.datasize - 1; i++)
    {
        newData[i] = database.entry[i];
        if (database.entry[i].key == entry->key)
            count = i;
    }

    if (count == -1)
    {
        *(newData + database.datasize - 1) = *entry;
    }
    else
    {
        *(newData + count) = *entry;
        database.datasize--;
    }

    delete[] database.entry;
    database.entry = newData;
    delete entry;
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key)
{
    for (int i = 0; i < database.datasize; i++)
    {
        if (database.entry[i].key == key)
        {
            return &database.entry[i];
        }
    }
    string n = "none";
    Entry *none = create(STRING, "none", &n);
    return none;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key)
{

    int check = 0, count = 0;
     Entry *data;
    for (int i = 0; i < database.datasize; i++)
    {
        if (database.entry[i].key == key)
        {
            check++;
            database.datasize -= 1;
            if (database.datasize != 0)
            {
                data = new Entry[database.datasize];
                for (int j = 0; j < database.datasize+1; j++)
                {
                    if (i != j)
                    {
                        data[count] = database.entry[j];
                        count++;
                    }
                }
            }
            else{
                data = new Entry[1];
            }
            delete[] database.entry;
            database.entry = data;
            break;
        }
    }
    if (check == 0)
        cout << "not found";
}

// 데이터베이스를 해제한다.
void destroy(Database &database)
{
    delete[] &database;
}
