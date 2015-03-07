#include <iostream>

using namespace std ;

struct Link_t
{
    int num ;
    Link_t *next ;
} ;

void build_link(Link_t * &head)
{
    int input ;
    Link_t *rear = NULL ;
    while(cin >> input)
    {
        if(input == -1) return ;
        Link_t * tmp = new Link_t ;
        tmp->num = input ;
        tmp->next = NULL ;
        if(head == NULL)
        {
            head = tmp ;
            rear = head ;
        }
        else
        {
            rear->next = tmp ;
            rear = rear->next ;
        }
    }

}
void free_link(Link_t * head)
{
    Link_t *pos = head ;
    while(head != NULL)
    {
        pos = head ;
        head = head->next ;
        delete pos ;
    }

}
int main(int argc , char *argv[])
{
    Link_t * link1 = NULL , *link2 = NULL , *link_rst = NULL ;
    build_link(link1) ;
    build_link(link2) ;

    Link_t *pos1 , *pos2 , *rst_rear ;
    pos1 = link1 ;
    pos2 = link2 ;

    // union
    while(pos1 != NULL && pos2 != NULL)
    {
        if(pos1->num < pos2->num) pos1 = pos1->next ;
        else if(pos1->num > pos2->num) pos2 = pos2->next ;
        else
        {
            Link_t *tmp = new Link_t ;
            tmp->num = pos1->num ;
            tmp->next = NULL ;
            if(link_rst  == NULL)
            {
                link_rst = tmp ;
                rst_rear = link_rst ;
            }
            else
            {
                rst_rear->next = tmp ;
                rst_rear = rst_rear->next ;
            }
            pos1 = pos1->next ;
            pos2 = pos2->next ;
        }

    }
    if(link_rst == NULL) cout << "NULL" ;
    else
    {
        Link_t *pos = link_rst ;
        cout << pos->num ;
        pos = pos->next ;
        while(pos != NULL)
        {
            cout << " " << pos->num ;
            pos = pos->next ;
        }
    }
    cout << endl ;
    free_link(link1) ;
    free_link(link2) ;
    free_link(link_rst) ;    
    return 0 ;
}
