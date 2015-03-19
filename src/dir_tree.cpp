#include <iostream>
#include <queue>
#include <string>
#include <cassert>

using namespace std ;

const int FILE_TYPE = 0 ;
const int DIR_TYPE = 1 ;
struct Node
{
    string name ;
    int type ;
    Node *firstchild ;
    Node *rightsibling ;
    Node():name(""),type(FILE_TYPE),firstchild(NULL),rightsibling(NULL){} ;
} ;

class DirTree
{
    private :
        Node * root ;
    public :
        DirTree()
        {
            root = new Node ;
            root->name = "root" ;
            root->type = DIR_TYPE ;
        }
        ~DirTree()
        {
            queue<Node *> q ;
            q.push(root) ;
            while(!q.empty())
            {
                Node *tmp = q.front() ;
                q.pop() ;
                if(tmp->rightsibling) q.push(tmp->rightsibling) ;
                if(tmp->firstchild) q.push(tmp->firstchild) ;
                delete tmp ;
            }
        }
        void mk_dir_or_file(const string &path)
        {
            _mk_dir_or_file(root , path) ;
        }
        void _mk_dir_or_file(Node *parent_node , const string &path)
        {
            if(path == "") return ;
            int backslash_pos = path.find('\\') ;
            string cur_name ;
            string left_path ;
            int cur_type ;
            Node *cur_node = NULL ;
            if(backslash_pos == string::npos)
            {
                cur_name = path ;
                left_path = "" ;
                cur_type = FILE_TYPE ;
            }
            else
            {
                cur_name = path.substr(0,backslash_pos) ;
                left_path = path.substr(backslash_pos + 1) ;
                cur_type = DIR_TYPE ;
            }

            // mk

            //cout <<"mk" << cur_name <<" " << cur_type << endl ;
            if(cur_type == DIR_TYPE)
            {
                Node *pos = parent_node->firstchild ;
                Node *pre_pos = NULL ;
                // find the right pos for the cur_name
                while(pos != NULL && pos->type == DIR_TYPE && cur_name > pos->name)
                {
                    pre_pos = pos ;
                    pos = pos->rightsibling ;
                }
                // if pre_pos == NULL , it means it quits at once
                if(pre_pos == NULL)
                {
                    if(pos != NULL && cur_name == pos->name)
                    {
                        cur_node = pos ;
                    }
                    else
                    {
                        // new a node
                        cur_node = new Node ;
                        cur_node->name = cur_name ;
                        cur_node->type = cur_type ;
                        cur_node->rightsibling = pos ;
                        parent_node->firstchild = cur_node ;
                    }
                }
                else
                {
                    if(pos != NULL && pos->name == cur_name)
                    {
                        cur_node = pos ;
                    }
                    else
                    {
                        cur_node = new Node ;
                        cur_node->name = cur_name ;
                        cur_node->type = cur_type ;
                        cur_node->rightsibling = pos ;
                        pre_pos->rightsibling = cur_node ;
                    }
                }

            }
            else
            {
                // the FILE_TYPE node . so it should impossible that the cur_name = pos->name
                // first , find the head of the FILE_TYPE Node
                cur_node = new Node ;
                cur_node->name = cur_name ;
                cur_node->type = cur_type ;
                Node *pos = parent_node->firstchild ;
                Node *pre_pos = NULL ;
                while(pos != NULL && pos->type != FILE_TYPE)
                {
                    pre_pos = pos ;
                    pos = pos->rightsibling ;
                }
                // pos == NULL or pos->type == FILE_TYPE
                if(pos == NULL)
                {
                    if(pre_pos == NULL)
                    {
                        // means nothing
                        parent_node->firstchild = cur_node ;
                    }
                    else
                    {
                        // no file (all is the dir)
                        pre_pos->rightsibling = cur_node ;
                    }
                }
                else
                {
                    // pos is the head of the FILE_TYPE
                    // find the right pos to insert
                    while(pos != NULL && cur_name > pos->name)
                    {
                        pre_pos = pos ;
                        pos = pos->rightsibling ;
                    }
                    if(pre_pos == NULL)
                    {
                        // be the first child
                        parent_node->firstchild = cur_node ;
                        cur_node->rightsibling = pos ;
                    }
                    else
                    {
                        cur_node->rightsibling = pos ;
                        pre_pos->rightsibling = cur_node ;
                    }
                }
            }

            // recursive process the left
            if(left_path != "")
            {
                _mk_dir_or_file(cur_node,left_path) ;
            }
        }
        void tree_traversal()
        {
            _tree_traversal(root , 0) ;
        }
        void _tree_traversal(Node *node , int indent)
        {
            if(node == NULL) return ;
            string indent_str(2*indent,' ') ;
            cout << indent_str << node->name << endl ;
            if(node->firstchild != NULL) _tree_traversal(node->firstchild , indent+1) ;
            if(node->rightsibling != NULL) _tree_traversal(node->rightsibling , indent) ;
        }
} ;


int main(int argc ,char *argv[])
{
    int node_num  ;
    DirTree dt ;
    cin >> node_num ;
    for(int i = 0 ; i < node_num ; ++i)
    {
        string path ;
        cin >> path ;
        dt.mk_dir_or_file(path) ;
    }
    dt.tree_traversal() ;
    return 0 ;
}
