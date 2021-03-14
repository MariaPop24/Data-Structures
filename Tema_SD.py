import time
import random
import sys


def partitie(array1, st1, dr1):
    pivot = array1[st1]
    limita_inf = st1 + 1
    limita_sup = dr1

    while True:

        while limita_inf <= limita_sup and array1[limita_sup] >= pivot:
            limita_sup = limita_sup - 1

        while limita_inf <= limita_sup and array1[limita_inf] <= pivot:
            limita_inf = limita_inf + 1

        if limita_inf <= limita_sup:
            array1[limita_inf], array1[limita_sup] = array1[limita_sup], array1[limita_inf]
        else:
            break

    array1[st1], array1[limita_sup] = array1[limita_sup], array1[st1]

    return limita_sup


def quicksort(array, st, dr):
    if st >= dr:
        return

    pozitie_partitie = partitie(array, st, dr)
    quicksort(array, st, pozitie_partitie - 1)
    quicksort(array, pozitie_partitie + 1, dr)



def interclasare(array, st, mij, dr):
    g = st
    u = mij + 1
    array_auxiliar = []
    while g <= mij and u <= dr:
        if array[g] <= array[u]:
            array_auxiliar.append(array[g])
            g += 1
        else:
            array_auxiliar.append(array[u])
            u += 1

    array_auxiliar.extend(array[g:mij+1])
    array_auxiliar.extend(array[u:dr+1])

    array[st:dr+1] = array_auxiliar[:]


def mergesort(array1, st1, dr1):
    if st1 < dr1:
        mij = (st1 + dr1) // 2
        mergesort(array1, st1, mij)
        mergesort(array1, mij+1, dr1)
        interclasare(array1, st1, mij, dr1)


def functie(array, x):
    nr_elemente = len(array)
    array_pentru_sortare = [0] * nr_elemente
    vector_frecventa = [0] * 10

    for i in range(nr_elemente):
        nr_ordine = array[i] // x
        vector_frecventa[nr_ordine % 10] += 1

    for i in range(1, 10):
        vector_frecventa[i] += vector_frecventa[i - 1]

    i = nr_elemente - 1
    while i >= 0:
        nr_ordine = (array[i] // x) % 10
        array_pentru_sortare[vector_frecventa[nr_ordine] - 1] = array[i]
        vector_frecventa[nr_ordine] -= 1
        i -= 1

    for i in range(nr_elemente):
        array[i] = array_pentru_sortare[i]


def radixsort(array1):
    maxim_array1 = max(array1)
    putere = 1

    while maxim_array1 // putere:
        functie(array1, putere)
        putere *= 10


def test_sort(v):
    for c in range(len(v)-1):
        if v[c] > v[c+1]:
            return "Vectorul nu este corect sortat!"
    return "Vectorul este corect sortat!"


f = open("exemplu.txt")
nr_teste = int(f.readline())

for i in range(nr_teste):
    s = f.readline()
    x = [int(y) for y in s.split()]
    lista = [random.randint(0, x[1]) for j in range(x[0])]
    print("Numarul de elemente ce trebuie sortate este:", x[0])
    print("Cel mai mare numar care poate fi generat este:", x[1], "\n")
    print("Primul algoritm de sortare va fi Bubble Sort\n")
    if x[0] >= 50000:
        print("Bubble Sort nu poate fi aplicat in acest caz!\n")
    else:
        start = time.time()
        ok = 1
        m = len(lista)

        while ok:
            p = m
            ok = 0
            for k in range(p - 1):
                if lista[k] > lista[k + 1]:
                    lista[k], lista[k + 1] = lista[k + 1], lista[k]
                    ok = 1
                    m = k + 1

        stop = time.time()
        print("Bubble Sort a sortat numerele in", stop - start, "secunde!")
        print(test_sort(lista), "\n")


    print("Al doilea algoritm de sortare va fi Counting Sort!")
    if x[0] >= 50000000 and x[1] >= 150:
        print("Counting Sort nu poate fi aplicat in acest caz!")
    else:
        start = time.time()

        vector_frecventa = [0] * (x[1] + 1)

        for d in lista:
            vector_frecventa[d] += 1

        index = 0
        nr_elemente = len(vector_frecventa)
        for h in range(nr_elemente):
            for z in range(vector_frecventa[h]):
                lista[index] = h
                index += 1

        stop = time.time()
        print("Counting Sort a sortat numerele in", stop - start, "secunde!")
        print(test_sort(lista), "\n")


    print("Al treilea algoritm de sortare va fi Radix Sort!")
    if x[0] >= 50000000:
        print("Radix Sort nu poate fi aplicat in acest caz!")
    else:
        start = time.time()

        radixsort(lista)

        stop = time.time()
        print("Radix Sort a sortat numerele in", stop - start, "secunde!")
        print(test_sort(lista), "\n")

    print("Al patrulea algoritm de sortare este Merge Sort!")

    if x[0] >= 50000000:
        print("Merge Sort nu poate fi aplicat in acest caz!")
    else:
        start = time.time()

        mergesort(lista, 0, len(lista) - 1)

        stop = time.time()
        print("Merge Sort a sortat numerele in", stop - start, "secunde!")
        print(test_sort(lista), "\n")

    print("Al cincilea algoritm de sortare este Quick Sort!")

    if (x[0] >= 50000000) or (x[0] >= 5000000 and x[1] <= 100000) or (x[0] >= 500000 and x[1] < 500) or (x[0] >= 50000 and x[1] <= 100):
        print("Quick Sort nu poate fi aplicat in acest caz!")
        print(lista)
    else:
        if x[0] >= 50000:
            sys.setrecursionlimit(x[0])

        start = time.time()

        quicksort(lista, 0, len(lista) - 1)

        stop = time.time()
        print("Quick Sort a sortat numerele in", stop - start, "secunde!")
        print(test_sort(lista), "\n")