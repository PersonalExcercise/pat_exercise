#include <iostream>

using namespace std ;

class Stack_int
{
    private :
    int size ;
    int top_pos ;
    int *data ;

    public :
    Stack_int(int size)
    {
        this->size = size ;
        data = new int[size] ;
        top_pos = -1 ;
    }
    ~Stack_int()
    {
        delete [] data ;
    }
    bool is_full()
    {
        return top_pos == size -1 ;
    }
    bool is_empty()
    {
        return top_pos == -1 ;
    }
    bool push(int item)
    {
        if(is_full()) return false ;
        else 
        {
            data[++top_pos] = item ;
            return true ;
        }
    }
    bool pop(int &item)
    {
        if(is_empty()) return false ;
        else
        {
            item = data[top_pos] ;
            top_pos -- ;
            return true ;
        }
    }

} ;


int main(int argc , char *argv[])
{
    int small_size , big_size ;
    cin >> small_size >> big_size ;
    if(small_size > big_size)
    {
        int tmp = small_size ;
        small_size = big_size ;
        big_size = tmp ;
    }
    // init stack
    Stack_int small_stack(small_size) ;
    Stack_int big_stack(big_size) ;
    
    char op ;
    while(cin >> op)
    {
        if(op == 'A')
        {
            int num ;
            cin >> num ;
            // small stack is full ?
            if(!small_stack.is_full())
            {
                small_stack.push(num) ;
            }
            else
            {
                // big_stack is empty ?
                if(big_stack.is_empty())
                {
                    // move the small to big stack . GET the max capacity : 2*small_size
                    int tmp ;
                    while(!small_stack.is_empty())
                    {
                        small_stack.pop(tmp) ;
                        big_stack.push(tmp) ;
                    }
                    //push
                    small_stack.push(num) ;
                }
                else
                {
                    // can not put any more
                    cout << "ERROR:Full" << endl ;
                }
            }

        }
        else if(op == 'D')
        {
            // is the big_stack empty ?
            if(big_stack.is_empty())
            {
                // is the small_stack empty ?
                if(small_stack.is_empty())
                {
                    // EMPTY
                    cout << "ERROR:Empty" << endl ;
                }
                else
                {
                    // move the small_stack to the big stack
                    int tmp ;
                    while(!small_stack.is_empty())
                    {
                        small_stack.pop(tmp) ;
                        big_stack.push(tmp) ;
                    }
                    big_stack.pop(tmp) ;
                    cout << tmp << endl ;
                }
            }
            else
            {
                int tmp ;
                big_stack.pop(tmp) ;
                cout << tmp << endl ;
            }
        }
        else if(op == 'T')
        {
            break ;
        }

    }
    
    return 0 ;
}
