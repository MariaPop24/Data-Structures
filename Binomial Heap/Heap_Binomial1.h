
#include <iostream>
#include <list>

using namespace std;

struct nod
{
    int grad;
    long cheie;
    nod *nod_parinte, *nod_copil, *nod_frate;
};

class Heap_Binomial
{
    list <nod*> lista;
    list <nod*> :: iterator gasire_radacina()
    {
        list <nod*> :: iterator iterator1, iterator_maxim;

        nod* maxim = creare_nod(-2000000000);

        for(iterator1 = lista.begin(); iterator1 != lista.end(); iterator1++)
            if(maxim-> cheie < (*iterator1)-> cheie)
        {
            maxim = *iterator1;
            iterator_maxim = iterator1;
        }

        return iterator_maxim;
    }

    void uneste_arbori(nod* primul_arbore, nod* al_doilea_arbore);
    void reglare();
    void stergere_radacina(nod* arbore, Heap_Binomial& heap);
    nod* creare_nod(long valoare);

public:

    void push(int valoare);
    void pop();
    void heap_union(Heap_Binomial& heap2);
    int top() { return (*gasire_radacina()) -> cheie;}

};
