#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

using namespace std ;

const int OP_TYPE = 1 ;
const int NUM_TYPE = 2 ;

const int INVALID = -1 ;
const int INIT = 1 ;
const int ONE = 2 ;
const int TWO = 3 ;
struct Node
{
    float val ;
    char op ;
    int node_type ;
} ;

void build_prefix_expr(vector<Node*> &expr , char str[])
{
    char *pos = str ;
    char *start_pos = str ;
    while(*pos != '\0')
    {
        if(*pos == ' ')
        {
            if((int(pos - start_pos)  == 1 )&& (*start_pos == '+' || *start_pos == '-' || *start_pos == '/' || *start_pos == '*'))
            {
                // op
                Node *tmp = new Node ;
                tmp->node_type = OP_TYPE ;
                tmp->op = *(pos -1) ;
                expr.push_back(tmp) ;
                *pos = '\0' ;
            }
            else
            {
                // num
                *pos = '\0' ;
                Node * tmp = new Node ;
                tmp->node_type = NUM_TYPE ;
                sscanf(start_pos , "%f" , &tmp->val) ;
                expr.push_back(tmp) ;
            }
            start_pos = pos + 1 ;
        }
        pos++ ;
    }
    if( (int(pos - start_pos) == 1) && (*start_pos == '+' || *start_pos == '-' || *start_pos == '/' || *start_pos == '*'))
    {
        Node* tmp = new Node ;
        tmp->node_type = OP_TYPE ;
        tmp->op = *start_pos ;
        expr.push_back(tmp) ;
    }
    else
    {
        Node *tmp = new Node ;
        tmp->node_type = NUM_TYPE ;
        sscanf(start_pos , "%f" , &tmp->val) ;
        expr.push_back(tmp) ;
    }

}

int main(int argc , char *argv[])
{
    const int MAX_INPUT_NUM = 30 ;
    char input_str[MAX_INPUT_NUM + 1] ;
    cin.getline(input_str , MAX_INPUT_NUM) ;
    vector<Node *> prefix_expr ;
    prefix_expr.clear() ;
    build_prefix_expr(prefix_expr , input_str) ;

    int calc_state_ok = true ;
    while(prefix_expr.size() > 1)
    {
        int state = INVALID ;
        for(int i = 0 ; i < prefix_expr.size() ; i++)
        {
            Node * cur = prefix_expr[i] ;
            if(cur->node_type == OP_TYPE) state = INIT ;
            else
            {
                if(state == INIT) state = ONE ;
                else if(state == ONE) state = TWO ;
            }
            if(state == TWO)
            {
                float result ;
                assert(i>1) ;
                char op = prefix_expr[i-2]->op ;
                switch(op)
                {
                    case '+' :
                        result = cur->val + prefix_expr[i-1]->val ;
                        break ;
                    case '-' :
                        result = prefix_expr[i-1]->val - cur->val ;
                        break ;
                    case '*' :
                        result = prefix_expr[i-1]->val * cur->val ;
                        break ;
                    case '/' :
                        if(cur->val == 0)
                        {
                            calc_state_ok = false ;
                            break ;
                        }
                        result = prefix_expr[i-1]->val / cur->val ;
                        break ;
                    default :
                        calc_state_ok = false ;
                }
                if(calc_state_ok)
                {
                    delete prefix_expr[i-2] ;
                    delete prefix_expr[i-1] ;
                    prefix_expr.erase(prefix_expr.begin() + i -2 , prefix_expr.begin() + i ) ;
                    // i -> i-2
                    prefix_expr[i-2]->val = result ;
                }
                break ;
            }

        }
        if(state != TWO) calc_state_ok = false ;
        if(!calc_state_ok) break ;
        
    }
   if(!calc_state_ok || prefix_expr.size() < 1) 
   {
        cout << "ERROR" << endl ;
   }
   else
   {
        cout <<setiosflags(ios::fixed)<< setprecision(1) <<prefix_expr[0]->val << endl ;
   }

    //release
    for(vector<Node*>::iterator it = prefix_expr.begin() ; it != prefix_expr.end() ; ++it)
    {
        delete (*it) ;
    }
    return 0 ; 
}
