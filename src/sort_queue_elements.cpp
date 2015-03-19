#include <iostream>
#include <algorithm>

using namespace std ;

class Queue_int
{
    private :
        int size ;
        int *data ;
        int front ;
        int rear ;

    public :
        Queue_int(int size)
        {
            this->size = size ;
            data = new int[size] ;
            front = -1 ;
            rear = -1 ;
        } 
        ~Queue_int()
        {
            delete [] data ;
        }
        bool is_empty()
        {
            if(front == -1 && rear == -1) return true ;
            else return false ;
        }
        bool is_full()
        {
            if((rear + 1)%size == front)
            {
                return true ;
            }
            else return false ;
        }
        bool add_queue(int item)
        {

            if(is_full()) return false ;
            else if(is_empty())
            {
                front = 0 ;
                rear = 0 ;
                data[rear] = item ; 
            }
            else
            {
                ++rear;
                rear %= size ;
                data[rear] = item ;
            }
            return true ;
        }
        bool delete_queue(int &item)
        {
            if(is_empty()) return false ;
            else
            {
                item = data[front] ;
                ++front ;
                front %= size ;
                if((rear + 1)%size == front)
                {       
                    //empty
                    front = -1 ;
                    rear = -1 ;
                }
                return true ;
            }
        }
        void insert_sort()
        {
            Queue_int q_tmp(size) ;
            int tmp_size = 0 ;
            while(!is_empty())
            {
                int add_item ;
                delete_queue(add_item) ;
                if(q_tmp.is_empty())
                {
                    q_tmp.add_queue(add_item) ;
                }
                else
                {
                    int cnt = 0 ;
                    bool has_added = false ;
                    // add the add_item to the right position
                    while(cnt < tmp_size)
                    {
                        int tmp_item ;
                        q_tmp.delete_queue(tmp_item) ;
                        if(!has_added)
                        {
                            if(tmp_item > add_item)
                            {
                                q_tmp.add_queue(add_item) ;
                                has_added = true ;
                            }
                            q_tmp.add_queue(tmp_item) ;
                        }
                        else
                        {
                            q_tmp.add_queue(tmp_item) ;
                        }
                        ++cnt ;
                    }
                    if(!has_added)
                    {
                        q_tmp.add_queue(add_item) ;
                        has_added = true ;
                    }
                }
                ++tmp_size ; 
            }
            // now q_tmp is full while q is empty
            while(!q_tmp.is_empty())
            {
                int tmp_item ;
                q_tmp.delete_queue(tmp_item) ;
                add_queue(tmp_item) ;
            }
        }

        void merge_sort()
        {
            int merge_block_size = 1 ;
            Queue_int q_tmp(size) ;

            while(merge_block_size < size)
            {
                int left_to_sort_size = size ;
                while(left_to_sort_size > 0)
                {
                    int block_one_size = min( merge_block_size , left_to_sort_size) ;
                    // copy the block_one_size 's elements to the q_tmp
                    for(int i = 0 ; i < block_one_size ; i++)
                    {
                        int tmp ;
                        delete_queue(tmp) ;
                        q_tmp.add_queue(tmp) ;
                    }
                    left_to_sort_size -= block_one_size ;
                    int block_two_size = min(merge_block_size , left_to_sort_size) ;
                    left_to_sort_size -= block_two_size ;

                    // merge sort 
                    // because there is no method 'front' to  get front element while not pop it . so make a flag do it
                    int item , item_tmp ;
                    if(block_two_size > 0)
                    {
                        delete_queue(item) ;
                    }
                    if(block_one_size > 0)
                    {
                        q_tmp.delete_queue(item_tmp) ;
                    }
                    while(block_one_size > 0 && block_two_size > 0)
                    {
                        if(item > item_tmp) // small -> big . so first make the small to the queue
                        {
                            add_queue(item_tmp) ;
                            --block_one_size ; // at here minus 1 , because only here to add it !
                            if(block_one_size > 0) q_tmp.delete_queue(item_tmp) ;
                        }
                        else
                        {
                            add_queue(item) ;
                            --block_two_size ;
                            if(block_two_size > 0) delete_queue(item) ;
                        }

                    }
                    if(block_one_size > 0)
                    {
                        // it means that block_two_size = 0 , so the `item_tmp` has not been push to the q
                        add_queue(item_tmp) ;
                        --block_one_size ;
                        while(block_one_size > 0)
                        {
                            q_tmp.delete_queue(item_tmp) ;
                            add_queue(item_tmp) ;
                            --block_one_size ;
                        }
                    }
                    if(block_two_size > 0)
                    {
                        add_queue(item) ;
                        --block_two_size ;
                        while(block_two_size > 0)
                        {
                            delete_queue(item) ;
                            add_queue(item) ;
                            --block_two_size ;
                        }
                    }
                }
                merge_block_size *= 2 ;
            }

        }
} ;

int main(int argc , char *argv[])
{
    int size ;
    cin >> size ;
    Queue_int q(size) ;
    int input_num ;
    int input_cnt = 0 ;
    while(input_cnt < size)
    {
        cin >> input_num ;
        q.add_queue(input_num) ;
        ++input_cnt ;
    }
    q.merge_sort() ;

    // dump
    bool need_a_blank = false ;
    while(!q.is_empty())
    {
        int tmp ;
        q.delete_queue(tmp) ;
        if(need_a_blank) cout << " " ;
        cout << tmp ;
        need_a_blank = true ;
    }
    cout << endl ;
}
