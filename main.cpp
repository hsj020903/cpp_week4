#include "database.h"
#include <string>
#include <iostream>
using namespace std;
#define typepic "type (int, double, string, array) : "
// 끝없이 값을 받을 수 있는 배열선언 함수
int arrays(Array &arr)
{
    string s, sval;
    int size, ival;
    double dval;
    cout << typepic;
    cin >> s;
    if (s != "int" && s != "double" && s != "string" && s != "array")
    {
        cout << "invalid type" << endl;
        return 0;
        ;
    }
    cout << "size: ";
    if (!(cin >> size))
    {
        cin.clear();
        while (std::cin.get() == '\n')
            continue;
        cout << "invalid size" << endl;
        return 0;
    }
    arr.size = size;
    if (s == "int")
    {
        arr.type = INT;
        int *item = new int[size];
        for (int i = 0; i < size; i++)
        {
            cout << "item[" << i << "]: ";
            if (!(cin >> ival))
            {
                cin.clear();
                while (std::cin.get() == '\n')
                    continue;
                cout << "invalid int" << endl;
                return 0;
            }
            item[i] = ival;
        }
        arr.items = item;
    }
    if (s == "double")
    {
        arr.type = DOUBLE;
        double *item = new double[size];
        for (int i = 0; i < size; i++)
        {
            cout << "item[" << i << "]: ";
            if (!(cin >> dval))
            {
                cin.clear();
                while (std::cin.get() == '\n')
                    continue;
                cout << "invalid int" << endl;
                return 0;
            }
            item[i] = dval;
        }
        arr.items = item;
    }
    if (s == "string")
    {
        arr.type = STRING;
        string *item = new string[size];
        for (int i = 0; i < size; i++)
        {
            cout << "item[" << i << "]: ";
            cin.ignore();
            getline(cin, sval);
            item[i] = sval;
        }
        arr.items = item;
    }
    if (s == "array")
    {
        arr.type = ARRAY;
        Array *item = new Array[size];
        for (int i = 0; i < size; i++)
        {
            cout << "item[" << i << "]: ";
            int k = arrays(item[i]);
            if (k == 0)
                return 0;
        }
        arr.items = item;
    }
    return 1;
}

// 배열 출력기
void arrPrint(Array &arr, int n)
{
    cout << "[";
    for (int i = 0; i < arr.size; i++)
    {
        switch (arr.type)
        {
        case INT:
            cout << static_cast<int *>(arr.items)[i];
            if (i + 1 != arr.size)
                cout << ", ";
            break;
        case DOUBLE:
            cout << static_cast<double *>(arr.items)[i];
            if (i + 1 != arr.size)
                cout << ", ";
            break;
        case STRING:
            cout << "\"";
            cout << static_cast<string *>(arr.items)[i];
            cout << "\"";
            if (i + 1 != arr.size)
                cout << ", ";
            break;
        case ARRAY:
            arrPrint(static_cast<Array *>(arr.items)[i], arr.size - i - 1);
            break;
        default:
            break;
        }
    }
    cout << "]";
    if (n != 0)
        cout << ", ";
}

int main()
{
    string s, key;
    string sval;
    int ival;
    double dval;
    Type type;
    bool end = false;
    Database database;
    init(database);
    while (!end)
    {
    
        cout << "command (list, add, get, del, exit): ";
        cin >> s;
        if (s == "exit")
        {
            break;
        }
        else if (s == "list")
        {
            for (int i = 0; i < database.datasize; i++)
            {
                
                switch (database.entry[i].type)
                {
                case INT:
                    cout << database.entry[i].key << ": " << *static_cast<int *>(database.entry[i].value) << endl;
                    break;
                case DOUBLE:
                    cout << database.entry[i].key << ": " << *static_cast<double *>(database.entry[i].value) << endl;
                    break;
                case STRING:
                    cout << database.entry[i].key << ": "
                         << "\"" << *static_cast<string *>(database.entry[i].value) << "\"" << endl;
                    break;
                case ARRAY:
                    cout << database.entry[i].key << ": ";
                    arrPrint(*static_cast<Array *>(database.entry[i].value), 0);
                    cout << endl;
                    break;
                default:
                    break;
                }
                ((database.entry + i)->type);
            }
        }
        else if (s == "add")
        { // 엔트리 추가 입력
            cout << "key: ";
            cin >> key;
            cout << typepic;
            cin >> s;
            if (s != "int" && s != "double" && s != "string" && s != "array")
            {
                cout << "invalid type" << endl;
                continue;
            }
            cout << "value: ";
            if (s == "int")
            {
                type = INT;
                if (!(cin >> ival))
                {
                    cin.clear();
                    while (std::cin.get() == '\n')
                        continue;
                    cout << "invalid int" << endl;
                    continue;
                }
                Entry *entry = create(type, key, &ival);
                add(database, entry);
            }
            else if (s == "double")
            {
                type = DOUBLE;
                int dval = 0;
                if (!(cin >> dval))
                {
                    cin.clear();
                    while (std::cin.get() == '\n')
                        continue;
                    cout << "invalid double" << endl;
                    continue;
                }
                Entry *entry = create(type, key, &dval);
                add(database, entry);
            }
            else if (s == "string")
            {
                type = STRING;
                cin.ignore();
                getline(cin, sval);
                Entry *entry = create(type, key, &sval);
                add(database, entry);
            }
            else if (s == "array")
            {
                Array arr;
                type = ARRAY;
                int k = arrays(arr);
                if (k == 0)
                {
                    continue;
                }
                Entry *entry = create(type, key, &arr);
                add(database, entry);
            }
        }

        else if (s == "get") // 데이터베이스에서 엔트리를 찾는다
        {
            cout << "key: ";
            cin >> key;
            Entry *entry = get(database, key);
            if (entry->key != "none")
            {
                switch (entry->type)
                {
                case INT:
                    cout << (entry->key) << ": " << *static_cast<int *>(entry->value) << endl;
                    break;
                case DOUBLE:
                    cout << (entry->key) << ": " << *static_cast<double *>(entry->value) << endl;
                    break;
                case STRING:
                    cout << (entry->key) << ": " << *static_cast<string *>(entry->value) << endl;
                    break;
                case ARRAY:
                    cout << entry->key << ": ";
                    arrPrint(*static_cast<Array *>(entry->value), 0);
                    cout << endl;
                    break;
                default:
                    break;
                }
            }
            else
                cout << "not found" << endl;
        }

        else if (s == "del") // 데이터베이스에서 엔트리를 삭제한다
        {
            cout << "key: ";
            cin >> key;
            remove(database, key);
        }
        else
        {
            cout << "invalid command" << endl;
        }
        cout << endl;
    }
    return 0;
}
