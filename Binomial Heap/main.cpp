#include <iostream>
#include <fstream>
#include <list>
#include "Heap_Binomial1.h"

using namespace std;


/// functia membra din clasa Heap_Binomial folosita pentru crearea unui nod
nod* Heap_Binomial:: creare_nod(long valoare)
{
    nod* n = new nod;
    n->cheie = valoare;
    n->grad = 0;
    n->nod_copil = NULL;
    n->nod_parinte = NULL;
    n->nod_frate = NULL;
    return n;
}

/// functia membra stergere_radacina
void Heap_Binomial :: stergere_radacina(nod* arbore, Heap_Binomial& heap)
{
    if(!arbore -> grad)
    {
        delete arbore;
        return;
    }

    arbore -> nod_copil -> nod_parinte = NULL;
    heap.lista.push_front(arbore -> nod_copil);

    arbore = arbore -> nod_copil;
    while(arbore -> nod_frate)
    {
        arbore -> nod_frate -> nod_parinte = NULL;
        heap.lista.push_front(arbore -> nod_frate);
        arbore = arbore -> nod_frate;
    }

}

/// functia membra uneste arbori
void Heap_Binomial :: uneste_arbori(nod* primul_arbore, nod* al_doilea_arbore)
{
    if(primul_arbore -> cheie < al_doilea_arbore -> cheie)
        swap(*primul_arbore, *al_doilea_arbore);

    al_doilea_arbore -> nod_frate = primul_arbore -> nod_copil;

    al_doilea_arbore -> nod_parinte = primul_arbore;
    primul_arbore -> nod_copil = al_doilea_arbore;

    primul_arbore -> grad++;
}

/// rearanjeaza heap-ul astfel incat sa se pastreze ordinea crescatoare a gradelor si
/// sa nu existe 2 arbori binomiali cu acelasi grad in heap
void Heap_Binomial :: reglare()
{
    if(lista.size() <= 1)
        return;

    list <nod*> :: iterator element_anterior, element_urmator, element_curent, element;

    element_anterior = element_curent = lista.begin();
    element_curent++;
    element_urmator = element_curent;
    element_urmator++;

    while(element_curent != lista.end())
    {
        while((element_urmator == lista.end() || (*element_urmator) -> grad > (*element_curent) -> grad)
              && element_curent != lista.end() && (*element_anterior) -> grad == (*element_curent) -> grad)
        {
            uneste_arbori(*element_curent, *element_anterior);

            element = element_anterior;

            if(element_anterior == lista.begin())
            {
                element_anterior++;
                element_curent++;
                if(element_urmator != lista.end())
                    element_urmator++;
            }
            else
                element_anterior--;

            lista.erase(element);
        }
        element_anterior++;
        if(element_curent != lista.end())
            element_curent++;
        if(element_urmator != lista.end())
            element_urmator++;
    }

}

/// functia membra pop
void Heap_Binomial :: pop()
{
    list <nod*> :: iterator radacina = gasire_radacina();

    Heap_Binomial heap_nou;
    stergere_radacina((*radacina), heap_nou);

    lista.erase(radacina);

    heap_union(heap_nou);
}

/// funtia membra heap_union
void Heap_Binomial :: heap_union(Heap_Binomial& heap2)
{
    list <nod*> :: iterator iterator1 = lista.begin();
    list <nod*> :: iterator iterator2 = heap2.lista.begin();
    list <nod*> heap_nou;

    while(iterator1 != lista.end() && iterator2 != heap2.lista.end())
        if((*iterator1) -> grad <= (*iterator2) -> grad)
        {
            heap_nou.push_back(*iterator1);
            iterator1++;
        }
        else
        {
            heap_nou.push_back(*iterator2);
            iterator2++;
        }

    while(iterator1 != lista.end())
    {
        heap_nou.push_back(*iterator1);
        iterator1++;
    }

    while(iterator2 != heap2.lista.end())
    {
        heap_nou.push_back(*iterator2);
        iterator2++;
    }

    heap2.lista.clear();

    lista = heap_nou;
    reglare();
}

/// functia membra push
void Heap_Binomial :: push(int valoare)
{
    nod* arbore = creare_nod(valoare);
    lista.push_front(arbore);
    reglare();
}

int numar_multimi, numar_operatii;
int tip_operatie, valoare1, valoare2;
Heap_Binomial heap[101];

int main()
{
    ifstream fin("mergeheap1.in");
    ofstream fout("mergeheap1.out");

    fin >> numar_multimi >> numar_operatii;

    for(int i = 0; i < numar_operatii; i++)
    {
        fin >> tip_operatie;

        if(tip_operatie == 1)
        {
            /// in multimea valoare1 se insereaza elementul valoare2
            fin >> valoare1 >> valoare2;
            heap[valoare1].push(valoare2);

        }
        else if(tip_operatie == 2)
        {
            /// se afiseaza elem. max din m. valoare2, apoi se elimina din aceasta
            fin >> valoare1;
            fout << heap[valoare1].top() << '\n';
            heap[valoare1].pop();

        }
        else if(tip_operatie == 3)
        {
            /// se reunesc cele 2 multimi (multimea valoare1 preia elem. m. valoare2 care ramane vida)
            fin >> valoare1 >> valoare2;
            heap[valoare1].heap_union(heap[valoare2]);
        }
    }

    return 0;
}
