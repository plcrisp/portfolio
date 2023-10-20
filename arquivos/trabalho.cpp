#include <bits/stdc++.h>

#define N 15000 // tamanho do vetor que foi sendo variado para cada teste

using namespace std;


// Bubble sort para vetor de strings
// método simples, porém ineficiente
// compara elementos adjacentes e os troca 
void bubble(string *vet, int n){ 
    string aux;
    
    for(int i =0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(vet[j+1] < vet[j]){
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }
}


// Selection sort para vetor de strings
// encontra o menor e o coloca no ínicio (se atentando aos elementos ja ordenados)
void selection(string *vet, int n){
    string aux;
    int menor;

    for(int i=0;i<n-1;i++){
        menor = i;

        for(int j=(i+1); j < n; j++){
            if(vet[j] < vet[menor]){
                menor = j;
            }
        }

        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}


// Insertion sort para vetor de strings
// Comparação com elementos adjacentes (ordenação comum no âmbito das cartas)
void insertion(string vet[], int n){
    string aux;
    int j;
    for(int i=1; i<n;i++){
        aux = vet[i];

        for(j=i-1;(j>=0) && (vet[j] > aux);j--){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}


// Shell sort para vetor de strings
// insertion sort com comparação de elementos equidistantes 
void shell(string *vet, int n){
    string aux;
    int j, h;
    h = n/2;

    while(h >= 1){
        for(int i=1;i<n;i++){
            aux = vet[i];

            for(j = i-h; (j>=0) && (vet[j] > aux); j = j-h){
                vet[j+h] = vet[j];
            }
            vet[j+h] = aux;
        }
        h=h/2;
    }
}


// Merge intercala para vetor de strings
// Intercala os subvetores os ordenando
void mergeIntercala(string *vet, string *aux, int ini, int meio, int fin){
    int atual, fimEsq, n;
    atual = ini;
    fimEsq = meio-1;
    n = fin - ini + 1;

    while((ini <= fimEsq) && (meio <= fin)){
        if(vet[ini] <= vet[meio]){
            aux[atual++] = vet[ini++];
        }else{
            aux[atual++] = vet[meio++];
        }
    }

    while(ini <= fimEsq){
        aux[atual++] = vet[ini++];
    }

    while(meio <= fin){
        aux[atual++] = vet[meio++];
    }

    for(int i =0;i<n;i++){
        vet[fin] = aux[fin];
        fin--;
    }
}


// Merge divide para vetor de strings
// Divide o vetor recursivamente e depois os intercala ordenando
void mergeDivide(string *vet, string *aux, int ini, int fin){
    int meio;

    if(fin > ini){
        meio = (fin+ini) / 2;

        mergeDivide(vet,aux,ini,meio);
        mergeDivide(vet,aux,meio+1,fin);

        mergeIntercala(vet,aux,ini,meio+1,fin);
    }
}


// Merge sort para vetor de strings
void merge(string *vet, int n){
    string aux[n];

    mergeDivide(vet, aux, 0, n-1);
}


// Método particiona para vetor de strings
// retorna um novo pivo a cada chamada
int particiona(string *vet, int esq, int dir){
    int i, j;
    string aux, pivo;
    i=esq;
    j=dir;
    pivo = vet[esq];

    while(i < j){
        while((vet[i] <= pivo) && (i < dir)){
            i++;
        }
        while((vet[j] >= pivo) && (j > esq)){
            j--;
        }
        if(i < j){
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;
        }
    }
    vet[esq] = vet[j];
    vet[j] = pivo;
    return j;
}


// Quick sort para vetor de strings
// Chama recursivamente para a esquerda do pivo e para direita do pivo
void quick(string *vet, int esq, int dir){
    if(esq < dir){
        int pivo = particiona(vet,esq,dir);
        quick(vet, esq, pivo-1);
        quick(vet, pivo+1, dir);
    }
}

int main(){
    int tempoInicio, tempoFim, tempoMs;

    string vet[N];

    // leitura dos elemenetos do dicionário até a posição N
    for(int i=0;i<N;i++){
        cin >> vet[i];
    }

    tempoInicio = (int) clock(); // tempo de inicio

    quick(vet, 0, N-1); // invocação do método que foi sendo variado

    tempoFim = (int) clock(); // tempo final

    

    tempoMs = ((tempoFim - tempoInicio) * 1000 / CLOCKS_PER_SEC); // medição do tempo em ms

    cout << tempoMs << " ms" << endl;

    return 0;
}