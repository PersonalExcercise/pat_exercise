#include <iostream>

using namespace std ;

struct Term_t
{
    int exp ;
    int factor ;
    Term_t * next ;
} ;

void build_poly(Term_t * &poly , int term_num)
{
    if(term_num == 0)
    {
        poly = NULL ;
        return ;
    }
    else
    {
        poly = new Term_t[term_num] ;
    }
    for(int i = 0 ; i < term_num ; i++)
    {
        cin >> poly[i].factor >> poly[i].exp ;
    }
}

void add_to_multi_poly(Term_t * & poly , int factor , int exp)
{
    if(poly == NULL)
    {
        Term_t * tmp = new Term_t ;
        tmp->factor = factor ;
        tmp->exp = exp ;
        tmp->next = NULL ;
        poly = tmp ;
    }
    else
    {
        Term_t * pos = poly ;
        Term_t * pre_pos = NULL ;
        while(pos!= NULL && exp < pos->exp)
        {
            pre_pos = pos ;
            pos = pos->next ;
        }
        if(pos == poly)
        {
            // that means exp is bigger than or equal to the the header
            if(exp ==  poly->exp)
            {
                poly->factor += factor ;
            }
            else
            {
                Term_t * tmp = new Term_t ;
                tmp->factor = factor ;
                tmp->exp = exp ;
                tmp->next = poly ;
                poly = tmp ;
            }
        }
        else
        {
            if(pos != NULL && exp == pos->exp) // !!! pos may be NULL
            {
                pos->factor += factor ;
            }
            else
            {   
                Term_t * tmp = new Term_t ;
                tmp->factor = factor ;
                tmp->exp = exp ;
                tmp->next = pos ;
                pre_pos->next = tmp ;
            }
        }

    }

}
int main(int argc , char *argv[])
{
    int term1_num ;
    cin >> term1_num ;
    Term_t * poly1 ;
    build_poly(poly1 , term1_num) ;
    int term2_num ;
    cin >> term2_num ;
    Term_t * poly2 ;
    build_poly(poly2 , term2_num) ;
    //multi
    /* there max has term1_num * term2_num terms for the result */
    Term_t * poly_mul  = NULL ;
    for(int i = 0 ; i < term1_num ; i++)
    {
        for(int j = 0 ; j < term2_num ; j++)
        {
            int factor = poly1[i].factor * poly2[j].factor ;
            int exp = poly1[i].exp + poly2[j].exp ;
            add_to_multi_poly(poly_mul , factor , exp) ;
        }
    }
    //add
    /* it is ordered !*/
    Term_t poly_add[term1_num+term2_num] ;
    int idx1 = 0 , idx2 = 0 , idx_rst = 0  ;
    while(idx1 < term1_num && idx2 < term2_num)
    {
        if(poly1[idx1].exp > poly2[idx2].exp)
        {
            poly_add[idx_rst].factor = poly1[idx1].factor ;
            poly_add[idx_rst].exp = poly1[idx1].exp ;
            idx1++ ;
            idx_rst++ ;
        }
        else if(poly1[idx1].exp < poly2[idx2].exp)
        {
            poly_add[idx_rst].factor = poly2[idx2].factor ;
            poly_add[idx_rst].exp = poly2[idx2].exp ;
            idx2++ ;
            idx_rst++ ;
        }
        else
        {
            int factor = poly1[idx1].factor + poly2[idx2].factor ;
            if(factor != 0)
            {
                poly_add[idx_rst].factor = factor ;
                poly_add[idx_rst].exp = poly1[idx1].exp ;
                idx_rst++ ;
            }
            idx1++ ;
            idx2++ ;
        }

    }
    while(idx1 < term1_num)
    {
        poly_add[idx_rst].factor = poly1[idx1].factor ;
        poly_add[idx_rst].exp = poly1[idx1].exp ;
        idx_rst++ ;
        idx1++ ;
    }
    while(idx2 < term2_num)
    {
        poly_add[idx_rst].factor = poly2[idx2].factor ;
        poly_add[idx_rst].exp = poly2[idx2].exp ;
        idx_rst++ ;
        idx2++ ;
    }
    //output
    Term_t * pos = poly_mul ;
    if(pos == NULL) 
    {
        cout << "0 0" ;
    }
    else
    {
        while(pos != NULL)
        {
            if(pos->factor != 0)
            {
                if(pos != poly_mul)
                {
                    cout << " " ;
                }
                cout << pos->factor << " " << pos->exp ;
            }
            Term_t * pre_pos = pos ;
            pos = pos->next ;
            delete pre_pos ;
        }
    }
    cout << endl ;
    if(idx_rst == 0)
    {
        cout <<"0 0" ;
    }
    else
    {
        for(int i = 0 ; i < idx_rst ; i++)
        {
            if(i != 0) cout << " " ;
            if(poly_add[i].factor != 0)
            {
                cout << poly_add[i].factor << " " << poly_add[i].exp ;
            }
        }
    }
    cout << endl ;
    return 0 ;
}
