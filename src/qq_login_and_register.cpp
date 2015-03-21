#include <iostream>
#include <string>
#include <map>

using namespace std ;

int main(int argc , char *argv[])
{
    int req_num ;
    cin >> req_num ;

    map<string , string> qq_db ;
    qq_db.clear() ;

    string op ;
    string user ;
    string passwd ;
    map<string , string>::iterator it ;
    for(int i = 0 ;  i < req_num ; ++i)
    {
        cin >> op >> user >> passwd ;
        if(op == "L")
        {
            it = qq_db.find(user) ;
            if(it == qq_db.end())
            {
                cout << "ERROR: Not Exist" ;
            }
            else if(it->second != passwd)
            {
                cout << "ERROR: Wrong PW" ;
            }
            else
            {
                cout << "Login: OK" ;
            }
        }
        else
        {
            pair<map<string,string>::iterator,bool> insert_rst = qq_db.insert(pair<string,string>(user,passwd)) ;
            if(insert_rst.second)
            {
                cout << "New: OK" ;
            }
            else
            {
                cout << "ERROR: Exist" ;
            }
        }
        cout << endl ;
    }
}
