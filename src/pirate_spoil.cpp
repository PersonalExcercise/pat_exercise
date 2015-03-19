#include <iostream>

using namespace std ;

int main(int argc , char *argv[]){
    
    int diamonds_num , pirate_num ;
    cin >> diamonds_num >> pirate_num ;
    int content_num = pirate_num / 2 + 1 ;
    if(content_num == 2)
    {
        cout << diamonds_num -1 ;
    }
    else
    {
        cout << diamonds_num - 2 - ( content_num -2 ) ;
    }
    return 0 ;
}
