#include <iostream>

using namespace std ;

bool is_cartesian_tree(int **data , int node_num)
{
    // neighbor nodes check
    for(int i = 0 ; i < node_num ; ++i)
    {
        int k1 = data[i][0] ;
        int k2 = data[i][1] ;
        int leftchild = data[i][2] ;
        int rightchild = data[i][3] ;
        if(leftchild != -1 && ! (data[leftchild][0] < k1 && data[leftchild][1] > k2))
        {
            return false ;
        }
        if(rightchild != -1 && !(data[rightchild][0] > k1 && data[rightchild][1] > k2))
        {
            return false ;
        }
    }
    // inflection node check
        // first , build a inverted index for child -> parent , recode the child type , so data type [node_idx][2]
        // [0] stands for parent , [1] reprent the child type : left , or right
    const int LEFT_CHILD = 0 ;
    const int RIGHT_CHILD = 1 ;
    const int ROOT = -1 ;
    int **inverted_index ;
    inverted_index = new int*[node_num] ;
    for(int i = 0 ; i < node_num ; ++i)
    {
        inverted_index[i] = new int[2] ;
        inverted_index[i][0] = -1 ;
        inverted_index[i][1] = ROOT ; // init
    }   // build the inverted index
    
    for(int i = 0 ; i < node_num ; ++i)
    {
        int leftchild = data[i][2] ;
        int rightchild = data[i][3] ;
        if(leftchild != -1)
        {
            inverted_index[leftchild][0] = i ;
            inverted_index[leftchild][1] = LEFT_CHILD ;
        }
        if(rightchild != -1)
        {
            inverted_index[rightchild][0] = i ;
            inverted_index[rightchild][1] = RIGHT_CHILD ;
        }
    }
    bool check_rst = true ;
    for(int i = 0 ; i < node_num ; ++i)
    {
        int parent_idx = inverted_index[i][0] ;
        int self_type = inverted_index[i][1] ;
        if(parent_idx != -1)
        {
            if(self_type == LEFT_CHILD)
            {
                // find the first right acestor 's parent
                while(parent_idx != -1 && inverted_index[parent_idx][1] == LEFT_CHILD)
                {
                    parent_idx = inverted_index[parent_idx][0] ;
                }
                if(parent_idx != -1 && inverted_index[parent_idx][1] != ROOT)
                {
                    // that is the inverted_index[parent_idx][1] == RIGHT_CHILD
                    // to get it's parent
                    parent_idx = inverted_index[parent_idx][0] ;
                    if(data[i][0] < data[parent_idx][0])
                    {
                        check_rst = false ;
                        break ;
                    }
                }
            }
            else
            {
                while(parent_idx != -1 && inverted_index[parent_idx][1] == RIGHT_CHILD)
                {
                    parent_idx = inverted_index[parent_idx][0] ;
                }
                if(parent_idx != -1 && inverted_index[parent_idx][1] != ROOT)
                {
                    parent_idx = inverted_index[parent_idx][0] ;
                    if(data[i][0] > data[parent_idx][0]) 
                    {
                        check_rst = false ;
                        break ;
                    }
                    
                }
            }
        }
    }
    for(int i = 0 ; i < node_num ; ++i) delete inverted_index[i] ;
    delete inverted_index ;
    return check_rst ;
}

int main(int argc , char *argv[])
{
    int node_num ;
    cin >> node_num ;
    int **datas ;
    datas = new int*[node_num] ;
    for(int i = 0 ; i < node_num ; ++i)
    {
        datas[i] = new int[4] ;
    }
    for(int i = 0 ; i < node_num ; ++i)
    {
        for(int j = 0 ; j < 4 ; ++j) cin >> datas[i][j] ;
    }
    if(is_cartesian_tree(datas , node_num))
    {
        cout << "YES" << endl ;
    }
    else 
    {
        cout << "NO" << endl ;
    }
    for(int i = 0 ; i < node_num ; ++i)
    {
        delete [] datas[i] ;
    }
    delete [] datas ;
}
