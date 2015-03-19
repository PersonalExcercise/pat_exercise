#include <iostream>
#include <string>
#include <queue>
#include <cassert>

using namespace std ;

struct Node
{
    string name ;
    Node *firstchild  ;
    Node *sibling ;  
    Node *parent ;
    Node():firstchild(NULL) , sibling(NULL) , parent(NULL) , name("") {} ;  
} ;

class Genealogy
{
    private :
        Node *root ;
        Node *pre_ele ;
        int pre_abs_relation ;
    public :
        Genealogy()
        {
            root = new Node ;
            pre_ele = NULL ;
            pre_abs_relation = -1 ;
        }
        ~Genealogy()
        {
            queue<Node *> q ;
            q.push(root) ;
            while(!q.empty())       
            {
                Node * cur = q.front() ;
                q.pop() ;
                if(cur != NULL && cur->sibling != NULL) q.push(cur->sibling) ;
                if(cur != NULL && cur->firstchild != NULL) q.push(cur->firstchild) ;
                if(cur != NULL) delete cur ;
            } 
        }
        void ordered_insert(const string &name , int abs_relation)
        {
            Node *tmp = new Node ;
            tmp->name = name ;
            if(abs_relation == 0)
            {
                assert(root->firstchild == NULL) ;
                root->firstchild = tmp ;
            }
            else
            {
                int relation = (abs_relation - pre_abs_relation) / 2  ;
                if(relation == 1 )
                {
                    // child 
                    tmp->parent = pre_ele ;
                    pre_ele->firstchild = tmp ;
                    
                }
                else if(relation == 0)
                {
                    // sibling 
                    tmp->parent = pre_ele->parent ;
                    pre_ele->sibling = tmp ;
                }
                else if(relation < 0)
                {
                    // parent * n 's sibling
                    Node *parent_node = pre_ele ;
                    int tmp_relation = relation ;
                    while(tmp_relation < 0)
                    {
                        parent_node = parent_node->parent ;
                        ++tmp_relation ;
                    }
                    tmp->parent = parent_node->parent ;
                    parent_node->sibling = tmp ;

                }
                else
                {
                    cerr << "READ ERROR" << endl ;
                    delete tmp ;
                    return ;
                }

            }
            pre_ele = tmp ;
            pre_abs_relation = abs_relation ;
        }
        bool is_child_relation(const string &child_name , const string &parent_name)
        {
            // first found the child Node
            Node * child_node = find_node(root->firstchild , child_name) ;
            if(child_node == NULL) return false ;
            if(child_node->parent == NULL) return false ;
            return child_node->parent->name == parent_name ;
        }
        bool is_sibling_relation(const string &name1 , const string &name2)
        {
            if(name1 == name2) return false ;
            Node *node1 = find_node(root->firstchild , name1) ;
            Node *pos = node1 ;
            while(pos != NULL)
            {
                if(pos->name == name2) return true ;
                pos = pos->sibling ;
            }
            Node *node2 = find_node(root->firstchild , name2) ;
            pos = node2 ;
            while(pos != NULL)
            {
                if(pos->name == name1) return true ;
                pos = pos->sibling ;
            }
            return false ;
        }
        bool is_descendant_relation(const string &descendant_name , const string &ancestor_name)
        {
            Node * descendant_node = find_node(root->firstchild , descendant_name) ;
            if(descendant_node == NULL ) return false ;
            Node *pos = descendant_node ;
            while(pos->parent != NULL)
            {
                if(pos->parent->name == ancestor_name) return true ;
                pos = pos->parent ;
            }
            return false ;
        }
        Node * find_node(Node *cur_node , const string &name)
        {
            if(cur_node == NULL) return NULL ;
            else if(cur_node->name == name) return cur_node ;
            else
            {
                Node * sibling_rst = find_node(cur_node->sibling , name) ;
                if(sibling_rst == NULL) 
                {
                    return find_node(cur_node->firstchild , name) ;
                }
                else
                {
                    return sibling_rst ;
                }
            }
        }
} ;



int main(int argc , char *argv[])
{
    int name_cnt , statement_cnt ;
    cin >> name_cnt >> statement_cnt ;
    cin.ignore() ;

    Genealogy genealogy ;

    string input_line ;
    string name ;
    int abs_relation ;
    for(int i = 0 ; i < name_cnt ; ++i)
    {
        getline(cin , input_line) ;
        for(string::iterator it = input_line.begin() ; it != input_line.end() ; ++it)
        {
            if((*it) == ' ') continue ;
            else
            {
                abs_relation = it - input_line.begin() ;
                name = input_line.substr(abs_relation) ;
                break ;
            }
        }
        //cout << name << "\t" << abs_relation << endl ;
        genealogy.ordered_insert(name , abs_relation) ;  
    }
    
    string statement ;
    for(int i = 0 ; i < statement_cnt ; ++i)
    {
        getline(cin , statement) ;
        // get x , y , relation
        string x , y , relation ;
        string::iterator pos ;
        int blank_cnt = 0 ;
        for(string::iterator it = statement.begin() ; it != statement.end() ; ++it)
        {
            if((*it) != ' ') continue ;
            else
            {
                ++blank_cnt ;
                if(blank_cnt == 1)
                {
                    x = statement.substr(0, it - statement.begin()) ;
                } 
                else if(blank_cnt == 4)
                {
                    relation = statement.substr(pos - statement.begin() , it - pos ) ;
                }
                else if(blank_cnt == 5)
                {
                    y = statement.substr(it - statement.begin() + 1 ) ;
                    break ;
                }
                pos = it + 1 ;
            }
        }
        //cout <<  x << "\t" << y << "\t" << relation << endl ;
        
        //find
        bool find_rst ;
        if(relation == "child")
        {
            find_rst = genealogy.is_child_relation(x,y) ;
        }
        else if(relation == "parent")
        {
            find_rst = genealogy.is_child_relation(y,x) ;
        }
        else if(relation == "descendant")
        {
            find_rst = genealogy.is_descendant_relation(x,y) ;
        }
        else if(relation == "ancestor")
        {
            find_rst = genealogy.is_descendant_relation(y,x) ;
        }
        else if(relation == "sibling")
        {
            find_rst = genealogy.is_sibling_relation(x,y) ;
        }
        else
        {
            find_rst = false ;
            cerr << "INVALID RELATION : " << relation << endl ;
        }
        if(find_rst) cout << "True" ;
        else cout << "False" ;
        cout << endl ;
    }
    return 0 ;
}
