#include <iostream>
#include <cassert>
using namespace std ;

struct Fact 
{
    long base ;
    int pow ;
    Fact * next ;
} ;
int main(int argc , char * argv[])
{
    Fact * root = NULL ;
    Fact * rear = NULL ;
    long x ;
    cin >> x ;
    if(x == 1) 
    {
        cout << "1=1" ;
        return 0 ;
    }
    long remain_val = x ;
    while(remain_val % 2 == 0)
    {
        if(rear == NULL)
        {
            root = new Fact ;
            rear = root ;
            rear->base = 2 ;
            rear->pow = 0 ;
            rear->next = NULL ;
        }
        rear->pow ++ ;
        remain_val /= 2 ;
    }
    for(long i = 3 ; i <= remain_val ; i += 2)
    {
        if(remain_val %i != 0)continue ;
        if(rear == NULL)
        {
            root = new Fact ;
            rear = root ;
        }
        else
        {
            rear->next = new Fact ;
            rear = rear->next ;
        }
        rear->next = NULL ;
        rear->base = i ;
        rear->pow = 0 ; 
        while(remain_val % i == 0 )
        {
            rear->pow ++ ;
            remain_val /= i ;
        }
    }
    assert(remain_val == 1) ;
    //output
    Fact * pos = root ;
    cout << x << "=" ;
    while(pos != NULL)
    {
        if(pos != root)
        {
            cout << "*" ;
        }
        cout << pos->base ;
        if(pos->pow != 1)
        {
            cout << "^" << pos->pow ;
        } 
        pos = pos->next ;
    }
    return 0 ;
}
