#include <iostream>

using namespace std ;

int main(int argc , char *argv[])
{
    int num ;
    cin >> num ;
    int list[num] ;
    int input_num ;
    int items_num = 0 ;
    while(cin >> input_num)
    {
        if(input_num < 0) break ;
        items_num ++ ;
        list[(items_num - 1) % num] = input_num ;
    }
    if(num > items_num) cout << "NULL" << endl ;
    else
    {
        cout << list[(items_num - num)%num] << endl ;
    }
    return 0 ;
}
