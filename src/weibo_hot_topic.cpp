#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <cassert>

using namespace std ;

struct Node
{
    char topic[41] ;
    int freq ;
    int next_pos ;
} ;

// FOR HASH

const int SIZE = 100003 ;
Node memory[SIZE] ;
int data_head_index[SIZE] ;
int malloc_index = 0 ;

// FOR inverse rank

vector<int> inverse_rank[SIZE] ;
int cur_max_time = 0 ;

unsigned int get_hash_code(char *arKey)
{
    unsigned int h = 0, g; 
    while (*arKey != '\0')
    { 
        h = (h << 4) + *arKey++; 
        if ((g = (h & 0xF0000000))) 
        { 
            h = h ^ (g >> 24); 
            h = h ^ g; 
        } 
    } 
    return h % SIZE ; 

}


int main(int argc , char *argv[])
{
    memset(memory,0,sizeof(memory)) ;
    memset(data_head_index,-1,sizeof(data_head_index)) ;
    for(int i = 0 ; i < SIZE ; ++i) 
    {
        inverse_rank[i].clear() ;
    }
    int input_num ;
    cin >> input_num ;
    cin.ignore() ;
    char weibo[142] ;
    for(int i = 0 ; i < input_num ; ++i)
    {
        cin.getline(weibo , 141 ) ;
        //abstract the topic
        char *topics[80] ;
        int topic_num = 0 ;
        char *topic_start = weibo ;
        char *topic_end = weibo ;
        while(true)
        {
            topic_start = strchr(topic_end ,'#') ;
            if(topic_start == NULL) break ;
            ++topic_start ; // ahead from '#'
            topic_end = strchr(topic_start ,'#') ;
            *(topic_end) = '\0' ;
            ++topic_end ;
            // fix the topic
            // first , replace the punc to the blank
            for(char * pos = topic_start ; pos < topic_end -1 ; ++pos )
            {
                if(ispunct(*pos)) *pos = ' ' ;
            }
            // clear the head blank
            while(topic_start < topic_end)
            {
                if((*topic_start) == ' ') ++topic_start ;
                else break ;
            }
            // clear the rear blank
            char *pos = topic_end - 2 ; // From the inverse 1 char start
            while(pos > topic_start)
            {
                if((*pos) == ' ') *pos = '\0' ;
                else break ;
            }
            if(strlen(topic_start) == 0) continue ;
            // UP case the first char
            *(topic_start) = toupper(*(topic_start)) ;
            // substr str letting it less than 40
            if(strlen(topic_start) > 40)
            {
                *(topic_start + 40) = '\0' ;
            }
            bool has_same = false ;
            for(int k = 0 ; k < topic_num ; ++k)
            {
                if(strcmp(topics[k],topic_start) == 0) 
                {
                    has_same = true ;
                    break ;
                }
            }
            if(!has_same)
            {
                topics[topic_num] = topic_start ;
                ++topic_num ;
            }
        }
        for(int j = 0 ; j < topic_num ; ++j)
        {
            // add to the hash memory
            unsigned hash_code = get_hash_code(topics[j]) ;
            //cout << hash_code << endl ;
            //NO node ? 
            int pos = data_head_index[hash_code] ;
            bool has_added = false ;
            while(pos != -1)
            {
                if(strcmp(memory[pos].topic,topics[j]) == 0)
                {
                    has_added = true ;
                    ++memory[pos].freq ;
                    break ;
                }
                pos =  memory[pos].next_pos ;
            }
            if(!has_added)
            {
                // add it 
                strcpy(memory[malloc_index].topic , topics[j]) ;
                memory[malloc_index].freq = 1 ;
                memory[malloc_index].next_pos = data_head_index[hash_code] ;
                data_head_index[hash_code] = malloc_index ;
                ++malloc_index ;
                pos = data_head_index[hash_code] ;
            }
            //cout << memory[pos].topic << " length is " << strlen(memory[pos].topic) << " " << memory[pos].freq << endl ;
            // --check the freq 
            if(cur_max_time == memory[pos].freq)
            {
                inverse_rank[cur_max_time - 1].push_back(pos) ;                
            }
            else if(memory[pos].freq > cur_max_time)
            {
                cur_max_time = memory[pos].freq ;
                inverse_rank[cur_max_time - 1].push_back(pos) ;
            }
        }
        
    }
    // find the min topic by compare the topic
    vector<int>::size_type hot_topic_size = inverse_rank[cur_max_time - 1].size() ;
    assert(hot_topic_size > 0) ;
    vector<int> *v_p = & inverse_rank[cur_max_time -1] ;
    char *topic = memory[(*v_p)[0]].topic ;
    if(hot_topic_size == 1)
    {
        cout << topic << endl << memory[(*v_p)[0]].freq << endl ;
    }
    else
    {
        int rank_first_pos = (*v_p)[0] ;
        for(vector<int>::iterator it = v_p->begin() + 1 ; it != v_p->end() ; ++it)
        {
            if(strcmp(topic , memory[(*it)].topic) > 0 )
            {
                topic = memory[(*it)].topic ;
                rank_first_pos = *it ;
            }
        }
        cout << topic << endl << memory[rank_first_pos].freq << endl 
             << "And " << hot_topic_size -1 << " more ..." << endl ;
    }
    return 0 ;
}
