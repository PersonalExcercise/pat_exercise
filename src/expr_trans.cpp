#include <iostream>
#include <string>
#include <cctype>
#include <stack>
using namespace std ;

const int NUM_TYPE = 1 ;
const int OP_TYPE = 2 ;

/**
*   GET next item of the infix expression
*   if ok , return True , else reutrn false 
*   if true , out_type make the type , while the item store the item
 */
bool get_next_item(const string & expr , int start_pos , int & out_type , string & item)
{
    int expr_len = expr.length() ;
    if(start_pos >= expr_len) return false ;
    int pos = start_pos ;
    if(isdigit(expr.at(pos)) || expr.at(pos) == '.' )
    {
        while(pos < expr_len && (isdigit(expr.at(pos)) || (expr.at(pos) == '.')))
        {
            pos ++ ;
        }
        item = expr.substr(start_pos , pos - start_pos) ;
        out_type = NUM_TYPE ;
    }
    else
    {
        char cur_char = expr.at(start_pos) ;
        if(cur_char == '+' || cur_char == '-')
        {
            // is the sign of a num ?
            if(start_pos == 0 || expr.at(start_pos -1) == '(')
            {
                // a num
                int pos = start_pos + 1 ;
                while(pos < expr_len && (isdigit(expr.at(pos)) || (expr.at(pos) == '.')))
                {
                    pos ++ ;
                }
                out_type = NUM_TYPE ;
                item = expr.substr(start_pos , pos - start_pos) ;
            }
            else
            {
                out_type = OP_TYPE ;
                item = expr.substr(start_pos , 1) ;
            }

        }
        else
        {
            out_type = OP_TYPE ;
            item = expr.substr(start_pos , 1) ;
        }
    }
    return true ;
}
int get_priority(const string & op)
{
    if(op == "+" || op == "-") return 1 ;
    else if(op == "*" || op == "/") return 2 ;
    else return -1 ;
}

int main(int argc , char *argv[])
{
    string input_str = "" ;
    cin >> input_str ;
    int start_pos = 0 ;
    string item = "" ;
    int item_type ;
    stack<string> op_stack ;
    bool need_a_blank = false ;

    while(get_next_item(input_str , start_pos , item_type , item))
    {
        /*
        cout << " item : " << item 
             << " start_pos: " << start_pos 
             << " item_type: " << item_type <<endl ;
        */
        if(item_type == NUM_TYPE)
        {
            if(need_a_blank) cout << " " ;
            if(item.at(0) == '+') cout << item.substr(1) ;
            else cout << item ;
            need_a_blank = true ;
        }
        else
        {
            if(op_stack.empty())
            {
                op_stack.push(item) ;
            }
            else
            {
                // push or output
                if(item == "(")
                {
                    op_stack.push(item) ;
                }
                else if(item == ")")
                {
                    while(!op_stack.empty() && op_stack.top() != "(")
                    {
                        if(need_a_blank) cout << " " ;
                        cout << op_stack.top() ;
                        need_a_blank = true ;
                        op_stack.pop() ;
                    }
                    if(!op_stack.empty()) op_stack.pop() ;
                }
                else if(get_priority(item) > get_priority(op_stack.top()))
                {
                    op_stack.push(item) ;
                }
                else
                {
                    while(!op_stack.empty() && get_priority(item) <= get_priority(op_stack.top()))
                    {
                        if(need_a_blank) cout << " " ;
                        cout << op_stack.top() ;
                        need_a_blank = true ;
                        op_stack.pop() ;
                    }
                    op_stack.push(item) ;
                }
            }
        }
        start_pos += item.length() ;
    }
    while(!op_stack.empty())
    {   
        if(need_a_blank) cout << " " ;
        cout << op_stack.top() ;
        op_stack.pop() ;

    }
    cout << endl ;
    return 0 ;
}
