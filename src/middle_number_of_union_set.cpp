#include <iostream>

using namespace std ;

int main(int argc , char *argv[])
{
    int num ;
    cin >> num ;
    int * set1 = new int[num] ;
    int * set2 = new int[num] ;
    int * set_rst = new int[num*2] ;
    int union_set_num = 0 ;
    for(int i = 0 ; i < num ; i++) cin >> set1[i] ;
    for(int i = 0 ; i < num ; i++) cin >> set2[i] ;
    int idx1 = 0 ;
    int idx2 = 0 ;
    while(idx1 < num && idx2 < num)
    {
        if(set1[idx1] < set2[idx2])
        {
            set_rst[union_set_num++] = set1[idx1] ;
            idx1++ ;
        }
        else if(set1[idx1] > set2[idx2])
        {
            set_rst[union_set_num++] =set2[idx2] ;
            idx2++ ;
        }
        else
        {
            set_rst[union_set_num++] = set1[idx1] ;
            set_rst[union_set_num++] = set2[idx2] ;
            idx1++ ;
            idx2++ ;
        }

    }
    while(idx1 < num)
    {
        set_rst[union_set_num++] = set1[idx1] ;
        idx1++ ;
    }
    while(idx2 < num)
    {
        set_rst[union_set_num++] = set2[idx2] ;
        idx2++ ;
    }
    int middle = ( union_set_num - 1 ) / 2 ;

    cout << set_rst[middle] << endl ;
    delete [] set1 ;
    delete [] set2 ;
    delete [] set_rst ;
    return 0 ;
}
