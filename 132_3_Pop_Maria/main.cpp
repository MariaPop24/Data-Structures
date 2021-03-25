#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
stack <int> stiva;
void traseu()
{
    while(!stiva.empty())
    {
        int stare = stiva.top();
        stiva.pop();
        traseu();
        cout << stare << " ";
    }
}


int lambda_NFA(int st, int dr, int poz, int nr_stari2, string cuvant2, char matrix[100][100])
{
    int i;
    bool k = false;
    stiva.push(st);
    for(i = 0; i < nr_stari2; i++)
    {
        if(matrix[st][i] == cuvant2[poz])
        {
            lambda_NFA(i, dr, poz + 1, nr_stari2, cuvant2, matrix);
            k = true;
        }
        else if(matrix[st][i] == '#')
        {
            lambda_NFA(i, dr, poz, nr_stari2, cuvant2, matrix);
            k = true;

        }
    }

    if(k)
    {
        if(stiva.size() == cuvant2.length() + 1)
            return 1;
        else
            stiva.pop();
    }
    else
    {
        stiva.pop();
    }

    if(stiva.empty())
        return 0;
}

int main()
{
    ///declarari de variabile
    int i, j, k;
    int nr_stari;
    int nr_muchii;
    char matrice[100][100];
    int stanga, dreapta, nr_cuvinte, stare_initiala, nr_stari_finale;
    char drum, cuvant[100];


    ifstream fin("data.in");

    fin >> nr_stari >> nr_muchii; /// citim prima linie a fisierului

    for(i = 0; i < nr_stari; i++)           /// declarare matrice de adiacenta si initializare cu '0'
    for(j = 0; j < nr_stari; j++)
        matrice[i][j] = '0';

    for(i = 0; i < nr_muchii; i++)
    {
        fin >> stanga >> dreapta >> drum;   /// citim muchiile grafului pentru matricea de adiacenta
        matrice[stanga][dreapta] = drum;
    }

    fin >> stare_initiala;                  /// citim starea initiala

    fin >> nr_stari_finale;                 /// citim numarul de stari finale

    vector <int> stari_finale(nr_stari_finale);
    for(i = 0; i < nr_stari_finale; i++)    /// declaram un vector de stari finale pe care le citim
        fin >> stari_finale[i];

    fin >> nr_cuvinte;                      /// citim numarul de cuvinte

    ///verificam pentru fiecare cuvant proprietatea ceruta
    for(i = 0; i < nr_cuvinte; i++)
    {
        fin >> cuvant;
        bool ok = false;


        for(j = 0; j < nr_stari_finale; j++)
        {
            k = j;
            if(lambda_NFA(stare_initiala, stari_finale[j], 0, nr_stari, cuvant, matrice))
                ok = true;
        }

        if(ok)
        {
            cout << "DA" << '\n' << "Traseu: ";
            traseu();
            cout << stari_finale[k] << '\n';
        }
        else
            cout << "NU" << '\n';

    }

    return 0;

}
