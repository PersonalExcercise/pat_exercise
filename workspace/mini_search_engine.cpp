#include <iostream>
#include <cstring>
#include <vector>

using namespace std ;

const int HASH_SIZE = 100003 ;
const int DOC_SIZE = 100 ;
const int LINE_NUM = 100 ;
const int LINE_CHAR_NUM = 50 ;
const int WORD_CHAR_NUM = 10 ;
const int WORD_NUM = 10 ;
// hash
struct InverseRankNode
{
    int doc_id ;
    vector<int> line_ids ;
} ;
struct HashNode
{
    char word[WORD_CHAR_NUM + 1] ;
    vector<struct InverseRankNode> inverse_rank_nodes ;
    int next_pos ;
} ;

struct HashNode memory[HASH_SIZE] ;
int malloc_num = 0 ;
int inverse_head_index[HASH_SIZE] ;
// doc sets

struct DOC
{
    char title[LINE_CHAR_NUM] ;
    char content[LINE_NUM][LINE_CHAR_NUM + 1] ;
    int line_num ;
} ;

struct DOC docs[DOC_SIZE] ;
int doc_num = 0 ;

// str processing function
void split(const char *str , char words[WORD_NUM][WORD_CHAR_NUM + 1] , int &word_num)
{
    word_num = 0 ;
    unsigned int begin_pos = 0 ;
    unsigned int len = strlen(str) ;
    int word_idx = 0 ;
    for(unsigned i = 0 ; i < len ; ++i)
    {
        if(str[i] == ' ')
        {
            words[word_num][word_idx] = '\0' ;
            ++word_num ;
            word_idx = 0 ; 
        }
        else
        {
            words[word_num][word_idx] = str[i] ;
            ++word_idx ;
        }
    }
    // last word
    words[word_num][word_idx] = '\0' ;
    ++word_num ;
}


inline void capitalize_word( char *word)
{
    // attention : WILL CHANGE the origin word
    for(int i = 0 ; i < strlen(word) ; ++i)
    {
        word[i] = toupper(word[i]) ;
    }
}

// hash function
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
    return h % HASH_SIZE ; 

}

// DEBUG : dump a hahs_node
void dump_hash_node(int memory_pos)
{
    cout << "memory pos : "  << memory_pos << endl ;
    cout << "word : " << memory[memory_pos].word << endl ;
    cout << "inverse rank : " << endl ;
   for(vector<InverseRankNode>::iterator it = memory[memory_pos].inverse_rank_nodes.begin() ; it != memory[memory_pos].inverse_rank_nodes.end() ; ++it )
   {
        cout << "doc id : " << it->doc_id << endl ;
        cout << "lines id : " << endl ;
        for(vector<int>::iterator iti = (it->line_ids).begin() ; iti != (it->line_ids).end() ; ++iti)
        {
            cout << "\t" << *iti << endl ;
        }
   } 
}

// the inverse node need : doc_id , line_id !
int put_to_hash_memory(char *word , int doc_id , int line_id)
{
    //cout << word << " " << doc_id << " " << line_id << endl ;
    
    // because ignore the case , so always up it !
    capitalize_word(word) ;
    unsigned hash_code = get_hash_code(word) ;
    int pos = inverse_head_index[hash_code] ;
    
    bool has_found = false ;
    while(pos != -1)
    {
        if(strcmp(word , memory[pos].word) == 0)
        {
            has_found = true ;
            break ;
        }
        pos = memory[pos].next_pos ;        
    }
    if(!has_found)
    {
        // new a hash_node
        strcpy(memory[malloc_num].word,word) ;
        memory[malloc_num].next_pos = inverse_head_index[hash_code] ;
        inverse_head_index[hash_code] = malloc_num ;
        pos = malloc_num ;
        ++malloc_num ;
    }
    HashNode *cur_node = &memory[pos] ;
    vector<struct InverseRankNode> * cur_rank_node = &(cur_node->inverse_rank_nodes) ;
    // add the doc_id , line_id info To the hash_node
        // if need to new a InverseRankNode
    if(cur_rank_node->size() != 0 && (*cur_rank_node)[cur_rank_node->size() - 1 ].doc_id == doc_id)
    {
        // no need to new a InverseRankNode , just push the line_id to the line_ids vector
        // check
        vector<int> *cur_line_ids = &(*cur_rank_node)[cur_rank_node->size() -1 ].line_ids ;
        if(cur_line_ids->size() == 0 || (*cur_line_ids)[cur_line_ids->size() -1 ] != line_id)
        {
            // should push the line_id
            cur_line_ids->push_back(line_id) ;
        }
    }
    else
    {
        InverseRankNode irnode ;
        irnode.doc_id = doc_id ;
        irnode.line_ids.push_back(line_id) ;
        // add to the rank_node
        cur_rank_node->push_back(irnode) ;
    }
    //dump_hash_node(pos) ;
}

int main(int argc , char *argv[])
{
    memset(inverse_head_index , -1 , sizeof(inverse_head_index)) ;
    int doc_num ;
    cin >> doc_num ;
    cin.ignore() ;
    char line[LINE_CHAR_NUM + 1] ;
    char words[WORD_NUM][WORD_CHAR_NUM + 1 ] ;
    int words_num ;    
    for(int i = 0 ; i < doc_num ; ++i)
    {
        int doc_id = i ;
        DOC *cur_doc = &docs[doc_id] ;
        // title
        cin.getline(cur_doc->title , LINE_CHAR_NUM + 1) ;
        
        // process title invser rank
        split(cur_doc->title , words , words_num) ;

        int line_id = -1 ; // -1 indicates to the title
        for(int k = 0 ; k < words_num ; ++k)
        {
            put_to_hash_memory(words[k],doc_id,line_id) ;
        }

        //content
        cur_doc->line_num = 0 ;
        while(cin.getline(line, LINE_CHAR_NUM + 1))
        {
            if(strlen(line) == 1 && line[0] == '#')
            {
                break ;
            }
            // add to the doc->content
            strcpy(cur_doc->content[cur_doc->line_num] , line) ;
            ++(cur_doc->line_num) ;
            // process the line
            split(line , words , words_num) ;
            line_id = cur_doc->line_num -1 ;
            for(int k = 0 ; k < words_num ; ++k)
            {
                put_to_hash_memory(words[k] , doc_id , line_id) ;
            }
        }
    }
}
