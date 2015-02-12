#include <iostream>

using namespace std ;

int main(int argc , char * argv[])
{
    int A , N ;
    cin >> A ;
    cin >> N ;
    int rst_bits[N+1] ;
    for(int i = 0 ; i < N+1 ; i ++ )
        rst_bits[i] = 0 ;
    for(int i = N ; i >= 1 ; i--)
    {
        int cur_bit_pos = N - i ;
        int cur_add_val = A * i ;
        while(cur_add_val > 0)
        {
            int cur_bit = cur_add_val % 10 ;
            rst_bits[cur_bit_pos] += cur_bit ;
            // process the carry bit
            int tmp = rst_bits[cur_bit_pos] ;
            int tmp_pos = cur_bit_pos ;
            while(tmp >= 10 )
            {
                rst_bits[tmp_pos] = tmp % 10 ;
                tmp_pos ++ ;
                rst_bits[tmp_pos] += 1 ;
                tmp = rst_bits[tmp_pos] ;
            }
            cur_bit_pos ++ ;
            cur_add_val /= 10 ;
        }
    }
    if(N == 0) 
    {
        cout << 0 ;
    }
    else if(rst_bits[N] != 0) 
    {
        cout << rst_bits[N] ;
    }
    for(int i = N-1 ; i >= 0 ; i--)
    {
        cout << rst_bits[i] ;
    }
    return 0 ; 
}
