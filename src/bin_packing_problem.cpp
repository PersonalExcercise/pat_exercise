#include <iostream>

using namespace std ;

struct Bin_t{
    int volume ;
    int bin_num ;

} ;

int main(int argc , char *argv[])
{
    int bin_num ;
    cin >> bin_num ;
    // MAX use bin_num bins
    int bin_capaty[bin_num] ;
    for(int i = 0 ; i < bin_num ; i++)
    {
        bin_capaty[i] = 100 ;
    }
    int needed_num = 0 ;
    // init the bins
    struct Bin_t bins[bin_num] ;
    for(int i = 0 ; i < bin_num ; i++)
    {
        cin >> bins[i].volume ;
    }
    
    // start 
    for(int i = 0 ; i < bin_num ; i++)
    {
        // find the box from the current
        bool has_found = false ;
        for(int j = 0 ; j < needed_num ; j++)
        {
            if(bin_capaty[j] >= bins[i].volume)
            {
                bins[i].bin_num = j + 1 ;
                bin_capaty[j] -= bins[i].volume ;
                has_found = true ;
                break ;
            }
        }
        if(! has_found)
        {
            needed_num += 1 ;
            bins[i].bin_num = needed_num  ;
            bin_capaty[needed_num -1] -= bins[i].volume ;
        }
    }
    //output
    for(int i = 0 ; i < bin_num ; i++)
    {
        cout << bins[i].volume << " " << bins[i].bin_num << endl ;
    }
    cout << needed_num ;

    return 0 ;
}
