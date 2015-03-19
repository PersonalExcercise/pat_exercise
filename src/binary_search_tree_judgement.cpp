#include <iostream>
#include <cassert>

using namespace std ;

struct Node
{
    int val ;
    Node *lchild ;
    Node *rchild ;
    Node():val(0),lchild(NULL),rchild(NULL){} ;
} ;
class BinarySearchTree_int
{
    private :
        Node * root ;
        int node_num ;
    public:
     BinarySearchTree_int()
    {
        root = NULL ;
        node_num = 0 ;
    }
    void insert(int ele)
    {
        _insert(root , ele) ;
        ++node_num ;
    }
    void _insert(Node *&cur_node , int ele)
    {
        if(cur_node == NULL)
        {
            cur_node = new Node ;
            cur_node->val = ele ;
        }
        else if(ele >= cur_node->val)
        {
            _insert(cur_node->rchild , ele) ;
        }
        else
        {
            _insert(cur_node->lchild , ele) ;
        }

    }
    int* preorder_traversal()
    {
        if(root == NULL) return NULL ;
        int *ret_val = new int[node_num] ;
        int pos = 0 ;
        _preorder_traversal(root , ret_val , pos) ;
        return ret_val ; // should be free outer
    }
    void _preorder_traversal(Node *node , int ret_val[] , int &pos)
    {
        if(node == NULL) return ;
        assert(pos < node_num) ;
        ret_val[pos] = node->val ;
        ++pos ;
        _preorder_traversal(node->lchild , ret_val , pos) ;
        _preorder_traversal(node->rchild , ret_val , pos) ;
    }

    int* reverse_preorder_traversal()
    {
        if(root == NULL) return NULL ;
        int *ret_val = new int[node_num] ;
        int pos = 0 ;
        _reverse_preorder_traversal(root , ret_val , pos) ;
        return ret_val ; // should be free outer
    }
    void _reverse_preorder_traversal(Node *node , int ret_val[] , int &pos)
    {
        if(node == NULL) return ;
        assert(pos < node_num) ;
        ret_val[pos] = node->val ;
        ++pos ;
        _reverse_preorder_traversal(node->rchild , ret_val , pos) ;
        _reverse_preorder_traversal(node->lchild , ret_val , pos) ;
    }

    int* postorder_traversal()
    {
        if(root == NULL) return NULL ;
        int *ret_val = new int[node_num] ;
        int pos = 0 ;
        _postorder_traversal(root , ret_val , pos) ;
        return ret_val ; // should be free outer
    }
    void _postorder_traversal(Node *node , int ret_val[] ,int &pos)
    {
        if(node == NULL ) return ;
        _postorder_traversal(node->lchild , ret_val , pos) ;
        _postorder_traversal(node->rchild , ret_val , pos) ;
        assert(pos < node_num) ;
        ret_val[pos] = node->val ;
        ++pos ;
    }
    
    int* reverse_postorder_traversal()
    {
        if(root == NULL) return NULL ;
        int *ret_val = new int[node_num] ;
        int pos = 0 ;
        _reverse_postorder_traversal(root , ret_val , pos) ;
        return ret_val ; // should be free outer
    }
    void _reverse_postorder_traversal(Node *node , int ret_val[] ,int &pos)
    {
        if(node == NULL ) return ;
        _reverse_postorder_traversal(node->rchild , ret_val , pos) ;
        _reverse_postorder_traversal(node->lchild , ret_val , pos) ;
        assert(pos < node_num) ;
        ret_val[pos] = node->val ;
        ++pos ;
    }
} ;

bool is_array_same(int a[] , int b[] , int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        if(a[i] != b[i]) return false ;
    }
    return true ;
}

void output_array(int a[] , int size)
{
    if(size <= 0) return ;
    cout << a[0] ;
    for(int i = 1 ; i < size ; ++i)
    {
        cout << " " << a[i] ;
    }
    cout << endl ;
}

int main(int argc , char *argv[])
{
    int node_num ;
    cin >> node_num ;

    int *input_list = new int[node_num] ;
    BinarySearchTree_int bts ;
    for(int i = 0 ; i < node_num ; ++i)
    {
        cin >> input_list[i] ;
        bts.insert(input_list[i]) ;
    }
    int *preorder_rst = bts.preorder_traversal() ;
    
    bool is_same = is_array_same(input_list , preorder_rst , node_num) ;
    if(is_same)
    {
        cout << "YES" << endl ;
        int *postorder_rst = bts.postorder_traversal() ;
        output_array(postorder_rst , node_num) ;   
        delete [] preorder_rst ;
        delete [] input_list ;
        delete [] postorder_rst ;
    }
    else
    {
        delete [] preorder_rst ;
        preorder_rst = bts.reverse_preorder_traversal() ;
        is_same = is_array_same(preorder_rst , input_list , node_num) ;
        if(is_same)
        {
            cout << "YES" << endl ;
            int *postorder_rst = bts.reverse_postorder_traversal() ;
            output_array(postorder_rst , node_num) ;
            delete [] postorder_rst ;
        }
        else
        {
            cout << "NO" << endl ;
        }
        delete [] preorder_rst ;
        delete [] input_list ;
    }
    
    /*
    for(int i = 0 ; i < node_num ; ++i)
    {
        cout << preorder_rst[i] << " " ;
    }
    cout << endl ;
    */

    return 0 ;
}
