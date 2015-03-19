#include <iostream>

using namespace std ;

struct NumLink_t{
    int num ;
    struct NumLink_t * next ;

} ;

void build_link(NumLink_t * & head)
{
   int input_num = 0 ;
   NumLink_t *rear = NULL ;
   while(cin >> input_num)
   {
        if(input_num == -1) break ;
        NumLink_t * tmp = new NumLink_t ;
        tmp->num = input_num ;
        tmp->next = NULL ;
        if(head == NULL)
        {
            head = tmp ;
            rear = head ;
        }
        else
        {
            rear->next = tmp ;
            rear = tmp ;
        }
   }
    

}

void free_list(NumLink_t *list_head)
{
    NumLink_t * pos ;
    while(list_head != NULL)
    {
        pos = list_head ;
        list_head = list_head->next ;
        delete pos ;
    }
}

int main(int argc , char *argv[]){
   NumLink_t *link_1 = NULL ;
   NumLink_t *link_2 = NULL ;
   NumLink_t *rst = NULL ;
   build_link(link_1) ;
   build_link(link_2) ;
   NumLink_t *pos1 , *pos2 , *pos_rst , *pos_rear = NULL ;
   pos1 = link_1 ;
   pos2 = link_2 ;
   while(pos1 != NULL && pos2 != NULL)
   {
        if(pos1->num <= pos2->num)
        {
            pos_rst = pos1 ;
            pos1 = pos1->next ;
        }
        else
        {
            pos_rst = pos2 ;
            pos2 = pos2->next ;
        }
        if(rst == NULL)
        {
            rst = pos_rst ;
            pos_rear = rst ;
        }
        else
        {
            pos_rear->next = pos_rst ;
            pos_rear = pos_rear->next ;
        }
   }
   if(pos1 != NULL)
   {
       if(pos_rear == NULL) 
       {
            rst = pos1 ;
       }
       else
       {
            pos_rear->next = pos1 ;
       }
   }
   else if(pos2 != NULL )
   {
       if(pos_rear == NULL)
       {
            rst = pos2 ;
       }
       else
       {
            pos_rear->next = pos2 ;
       }
   }
   
    pos_rst = rst ;
    if(pos_rst == NULL)
    {
        cout << "NULL" ;
    }
    else
    {
        while(pos_rst != NULL)
        {
            if(pos_rst != rst) cout << " " ;
            cout << pos_rst->num ;
            pos_rst = pos_rst->next ;
        }
    }
   free_list(rst) ;
   return 0 ; 

}
