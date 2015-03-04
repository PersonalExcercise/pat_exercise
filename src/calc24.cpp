#include <iostream>
#include <iomanip>

using namespace std ;

/**
*IF it is valid , it should return a no-negative number
* ie : if return num >= 0 , it is valid ; else , return -1
*/
int process_calc(int a , int b , char op)
{
    int ret = 0 ;
    switch(op)
    {
        case '+' :
        {
            ret = a + b ;
            break ;
        }
        case '-' :
        {
            ret = a - b ;
            if(ret < 0) ret = -1 ;
            break ;
        }
        case '*' :
        {
            ret = a * b ;
            break ;
        }
        case '/' :
        {
            if(b == 0 ) ret = -1 ;
            else if (a % b != 0) ret = -1 ;
            else ret = a / b ;
            break ;
        }
        default :
        ret = -1 ;
    }
    return ret ;
}

/**
*mode : 0  
        1  ((a op b)op c) op d
        2
        3
        4
*/
void print_rst(int nums_seq[4] , char ops_seq[3] , int mode)
{
    switch(mode)
    {
        case 0 :
        {
            cout << "(" << nums_seq[0] << ops_seq[0] << nums_seq[1] << ")"
                 << ops_seq[1] << "(" << nums_seq[2] << ops_seq[2] 
                 << nums_seq[3] << ")" << endl ;
            break ;
        }
        case 1 :
        {
            cout << "((" << nums_seq[0] << ops_seq[0] << nums_seq[1] << ")"
                 << ops_seq[1]  << nums_seq[2] << ")" << ops_seq[2] << nums_seq[3] << endl ;
            break ;
        }
        case 2 :
        {
            cout << nums_seq[0] << ops_seq[0]<< "((" << nums_seq[1] 
                 << ops_seq[1] << nums_seq[2] << ")" << ops_seq[2]
                 << nums_seq[3] << ")" << endl ;
            break ;
        }
        case 3 :
        {
            cout << "(" << nums_seq[0] << ops_seq[0] << "(" << nums_seq[1] 
                 << ops_seq[1] << nums_seq[2] << "))" << ops_seq[2] 
                 << nums_seq[3] << endl ;
            break ;
        }
        case 4 :
        {
            cout << nums_seq[0] << ops_seq[0] << "(" << nums_seq[1]
                 << ops_seq[1] << "(" << nums_seq[2] << ops_seq[2] 
                 << nums_seq[3] << "))" << endl ;
            break ;
        }
        default :
            break ;
    }
}

/**
*IF find the case can get 24 , return 1
*   else return 0
*if find , it will output it !
*/
int test_calc24(int nums_seq[4] , char ops_seq[3])
{
    // it should be 5 cases 
    for(int i = 0 ; i < 5 ; i ++)
    {
        switch(i)
        {
            case 0 :
                {
                    // 0 , (a op b )op (c op d )
                    int tmp_1 = process_calc(nums_seq[0] , nums_seq[1] , ops_seq[0]) ;
                    if(tmp_1 == -1) break ;
                    int tmp_2 = process_calc(nums_seq[2] , nums_seq[3] , ops_seq[2]) ;
                    if(tmp_2 == -1) break ;
                    int rst = process_calc(tmp_1 , tmp_2 , ops_seq[1]) ;
                    if(rst == 24)
                    {
                        print_rst(nums_seq , ops_seq , i) ;
                        return 1 ;
                    }
                    break ;
                }
            case 1 :
                {
                    // 1 , ((a op b)op c) op d
                    int tmp_1 = process_calc(nums_seq[0] , nums_seq[1] , ops_seq[0]) ;
                    if(tmp_1 == -1) break ;
                    int tmp_2 = process_calc(tmp_1 , nums_seq[2] , ops_seq[1]) ;
                    if(tmp_2 == -1) break ;
                    int rst = process_calc(tmp_2 , nums_seq[3] , ops_seq[2]) ;
                    if(rst == 24)
                    {
                        print_rst(nums_seq,ops_seq , i) ;
                        return 1 ;
                    }
                    break ;
                }
            case 2 :
                {
                    // 2 , a op ((b op c)op d)
                    int tmp_1 = process_calc(nums_seq[1] , nums_seq[2] , ops_seq[1]) ;
                    if(tmp_1 == -1) break ;
                    int tmp_2 = process_calc(tmp_1 , nums_seq[3] , ops_seq[2]) ;
                    if(tmp_2 == -1) break ;
                    int rst = process_calc(nums_seq[0] , tmp_2 , ops_seq[0]) ;
                    if(rst == 24) 
                    {
                        print_rst(nums_seq , ops_seq , i) ;
                        return 1 ;
                    }
                    break ;
                }
            case 3 :
                {
                    //3 , (a op (b op c)) op d 
                    int tmp_1 = process_calc(nums_seq[1] , nums_seq[2] , ops_seq[1]) ;
                    if(tmp_1 == -1) break ;
                    int tmp_2 = process_calc( nums_seq[0] , tmp_1 , ops_seq[0]) ;
                    if(tmp_2 == -1) break ;
                    int rst = process_calc(tmp_2 , nums_seq[3] , ops_seq[2] ) ;
                    if(rst == 24 )
                    {
                        print_rst(nums_seq , ops_seq , i) ;
                        return 1 ;
                    }
                    break ;
                }
            case 4 :
                {
                    //4 , a op (b op (c op d))
                    int tmp_1 = process_calc(nums_seq[2] , nums_seq[3] , ops_seq[2]) ;
                    if(tmp_1 == -1) break ;
                    int tmp_2 = process_calc(nums_seq[1] , tmp_1 , ops_seq[1]) ;
                    if(tmp_2 == -1) break ;
                    int rst = process_calc(nums_seq[0] , tmp_2 , ops_seq[0]) ;
                    if(rst == 24)
                    {
                        print_rst(nums_seq , ops_seq , i) ;
                        return 1 ;
                    }
                    break ;
                }
        }
    }
    return 0 ;

}
int main(int argc , char *argv[])
{
    int nums[4] ;
    for(int i = 0 ; i < 4 ; i ++)
    {
        cin >> nums[i] ;
    }
    char ops[4] = {'+' , '-' , '*' , '/'} ;
    int nums_seq[4] ;
    char ops_seq[3] ;
    
    // circulation and enumerate
    for(int fir = 0 ; fir < 4 ; fir++ )
    {
        for(int sec = 0 ; sec < 4 ; sec++)
        {
            if(sec == fir) continue ;
            for(int thi = 0 ; thi < 4 ; thi++)
            {
                if(thi == fir || thi == sec) continue ;
                int forth = 0 + 1 + 2 + 3 - fir - sec - thi ;
                //cout <<setw(10)<< fir << sec << thi << forth << endl ;
                nums_seq[0] = nums[fir] ;
                nums_seq[1] = nums[sec] ;
                nums_seq[2] = nums[thi] ;
                nums_seq[3] = nums[forth] ;
                for(int i = 0 ; i < 4 ; i ++)
                {
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        for(int k = 0 ; k < 4 ; k++)
                        {
                            ops_seq[0] = ops[i] ;
                            ops_seq[1] = ops[j] ;
                            ops_seq[2] = ops[k] ;
                            int ret = test_calc24(nums_seq , ops_seq) ;
                            if(ret == 1) return 0 ;
                        }
                    }
                }
            }
        }

    }
    // NO solution
    cout << "-1" << endl ;
    return 0 ;
}
