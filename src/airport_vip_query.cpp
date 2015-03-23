#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std ;

struct DBNode
{
    unsigned int key1 ;
    unsigned int key2 ;
    unsigned char key3 ;
    int kilometer ;
    int next_pos ;
} ;

DBNode g_data[110000] ;

class VIPDB
{
    private :
        int *data ;
        const int DATA_SIZE ;
        DBNode *memory_data ;
        int memory_pos ;
    public :
        VIPDB(int size):DATA_SIZE(size)
    {
        data = new int[DATA_SIZE] ;
        for(int i = 0 ; i < DATA_SIZE ; ++i)
        {
            data[i] = -1 ;
        }
        memory_data =  g_data ;
        memory_pos = 0 ;
    }
        ~VIPDB()
        {
            delete [] data ;
        }
        inline unsigned int hashCode(unsigned int k1 , unsigned int k2 , unsigned char k3)
        {
            unsigned sum = k1%DATA_SIZE + k2%DATA_SIZE + k3 ;
            return sum % DATA_SIZE ;
        }
        unsigned int get_hash_code(char *ID , unsigned &k1 , unsigned &k2 , unsigned char &k3)
        {
            k1 = 0 ; 
            k2 = 0 ;
            k3 = 0 ;
            unsigned hash_val = 0 ;
            unsigned tmp ;
            for(int i = 0 ; i < 9 ; ++i)
            {
                tmp = ID[i] - '0' ;
                k1 = k1 * 10 + tmp ;
                hash_val = (hash_val * 10 + tmp) % DATA_SIZE ;
            }
            for(int i = 9 ; i < 17 ; ++i)
            {
                tmp = ID[i] - '0' ;
                k2 = k2 * 10 + tmp ;
                hash_val = (hash_val * 10 + tmp) % DATA_SIZE ;
            }
            k3 = ID[17] == 'x' ? 10 : ID[17] - '0' ;
            hash_val = (hash_val * 100 + k3 ) % DATA_SIZE ;
            return hash_val ;
        }
        inline void ID_2key(const string & ID , unsigned int & k1 , unsigned &k2 , unsigned char &k3) 
        {
            sscanf(ID.c_str(),"%9u%8u%c",&k1,&k2,&k3) ;
            /*
               sscanf(ID.substr(0,9).c_str() , "%u" , &k1) ;
               sscanf(ID.substr(9,8).c_str() , "%u" , &k2) ;
               sscanf(ID.substr(17).c_str() , "%c" , &k3) ;
             */
        }

        bool find_db(char *ID , int &kilometer)
        {
            unsigned int k1 , k2 ;
            unsigned char k3 ;
            //ID_2key(ID,k1,k2,k3) ;
            //unsigned int hash_val = hashCode(k1,k2,k3) ;
            unsigned hash_val = get_hash_code(ID,k1,k2,k3) ;
            int next_pos = data[hash_val] ;
            while(next_pos != -1)
            {
                if(g_data[next_pos].key1 == k1 && g_data[next_pos].key2 == k2 && g_data[next_pos].key3 == k3)
                {        
                    kilometer = g_data[next_pos].kilometer ;
                    return true ;
                }
                next_pos = g_data[next_pos].next_pos ;
            }
            return false ;
        }
        void update_db(char *ID , int kilometer)
        {
            unsigned int k1 , k2 ;
            unsigned char k3 ;
            //ID_2key(ID , k1 , k2 , k3) ;
            //unsigned int hash_val = hashCode(k1 , k2, k3) ;
            unsigned hash_val = get_hash_code(ID,k1,k2,k3) ;

            int pos = data[hash_val] ;
            // first find
            while(pos != -1)
            {
                if(g_data[pos].key1 == k1 && g_data[pos].key2 == k2 && g_data[pos].key3 == k3)
                {
                    g_data[pos].kilometer += kilometer ;
                    return ;
                }
                pos = g_data[pos].next_pos ;
            }

            // NOT FOUND !
            // ADD
            // DBNode *tmp = new DBNode(k1,k2,k3) ; -> change it
            /*
               DBNode *tmp = & memory_data[memory_pos++] ;
               tmp->key1 = k1 ;
               tmp->key2 = k2 ;
               tmp->key3 = k3 ;
               tmp->kilometer = kilometer ;
               tmp->next = data[hash_val] ;
               data[hash_val] = tmp ;
             */

            g_data[memory_pos].key1 = k1 ;
            g_data[memory_pos].key2 = k2 ;
            g_data[memory_pos].key3 = k3 ;
            g_data[memory_pos].next_pos = data[hash_val] ;
            g_data[memory_pos].kilometer = kilometer ;
            data[hash_val] = memory_pos ;
            ++memory_pos ;

        }
} ;

int main(int argc , char *argv[])
{
    VIPDB db(100003) ;
    int input_num , min_kilometer ;
    cin >> input_num >> min_kilometer ;
    char ID[19] ;
    int kilometer ;
    for(int i = 0 ; i < input_num ; ++i)
    {

        scanf("%s%d",ID,&kilometer) ;
        if(kilometer < min_kilometer) kilometer = min_kilometer ;
        db.update_db(ID,kilometer) ;
    }

    int query_num ;
    cin >> query_num ;
    for(int i = 0 ; i < query_num ; ++i)
    {
        cin >> ID ;

        bool is_found_ok = db.find_db(ID,kilometer) ;
        if(is_found_ok)
        {
            cout << kilometer << endl ;
        }
        else
        {
            cout << "No Info" << endl ;
        } 
    }

    return 0 ;
}
