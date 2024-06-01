#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Pair {
    char * name;
    int val;
};

const int LARGE = 1024;
static Pair vec[LARGE];

Pair* find (const char *p){
    int i;
    for (i = 0; i <LARGE && vec[i].name !=NULL; i++){
        if(strcmp(p, vec[i].name)== 0)
            return &vec[i];
    }
    if(i == LARGE)
        return &vec[LARGE-1];
    return &vec[i];
}

int & value (const char *p){
    Pair * res = find(p);
    if (res->name == 0){
        res->name = new char[strlen(p)+1];
        strcpy (res->name, p);
        res->val = 0;
    }
    return res->val;
}
int main(){
    const int MAX = 256;
    char buf[MAX];

    while( cin >> buf)
        value(buf)++;
    for (int i = 0; i < LARGE && vec[i].name != NULL; i++)
        cout << vec[i].name << ": " << vec[i].val << '\n';
    int a = value("example");
    cout << "a=" << a << endl;

    value("example") = 513;
    cout << "a=" << a << endl;

    --value("example");
    cout << "a=" << a << endl;

    return 0;
}
