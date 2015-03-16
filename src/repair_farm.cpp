#include <iostream>
#include <vector>
#include <queue>
#include <functional> // greater

using namespace std ;

int main(int argc , char *argv[])
{
    priority_queue<int , vector<int> , greater<int> > pq ;
    int pice_num ;
    cin >> pice_num ;
    for(int i = 0 ; i < pice_num ; ++i)
    {
        int input_tmp ;
        cin >> input_tmp ;
        pq.push(input_tmp) ;
    }
    int total_sum = 0 ;
    while(pq.size() != 1)
    {
        int min = pq.top() ;
        pq.pop() ;
        int second_min = pq.top() ;
        pq.pop() ;
        int sum = min + second_min ;
        pq.push(sum) ;
        total_sum += sum ;
    }
    cout << total_sum << endl ;

    return 0 ;
}
