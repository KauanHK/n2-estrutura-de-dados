/*
PROCESSO AVALIATIVO N2 ? ESTRUTURA DE DADOS

EQUIPE
NOMES:
    Kauan Henrique Kaestner
    Luis Gabriel
    Ricardo Cardoso

CONSEGUIU CHEGAR NO RESULTADO?
R: Sim, conseguimos chegar ao resultado dos gr?ficos
   e inclusive tornar o c?digo mais eficiente, 
   principalmente para vetores j? ordenados ou semi ordenados.

*/


#include <stdio.h>
#include <stdlib.h>
#include "time.h"


void imprime_vetor(int *vetor, int total){
	for(int i = 0; i < total; i++){
		printf("\nVetor[%d] = %d", i, vetor[i]);
	}
	printf("\n");
}

//gera um vetor ordenado de forma crescente e sem repeti??o [MELHOR CASO]
void gera_vetor_ordenado_ASC(int *vetor, int n) {
	for(int i = 0; i < n; i++){
		vetor[i] = i;
	}
}

//gera um vetor ordenado de forma DEcrescente e sem repeti??o [PIOR CASO]
void gera_vetor_ordenado_DESC(int *vetor, int n) {
	int j = n - 1;
	for(int i = 0; i < n; i++){
		vetor[i] = j--;
	}
}

//gera um vetor ordenado de forma aleat?ria e sem repeti??o [CASO M?DIO]
void gera_vetor_aleatorio(int *vetor, int n) {
	int j, aux;
	
	for(int i = 0; i < n; i++){
		vetor[i] = i;
	}
	
	srand(time(0));
	
	//aplica o algoritmo de Fisher-Yates
	for(int i = 0; i < n; i++){
		// gera um n?mero randomico de 0 a n -1
		j = rand() % n;
		// troca de posi??o
		aux = vetor[i];
		vetor[i] = vetor[j];
		vetor[j] = aux;
	}
}

const int ORDENADO = 1;
const int ALEATORIO = 2;
const int INVERTIDO = 3;

void geraVetor(int *vet, int n, int opcao){
    switch (opcao){
        case 1:
            gera_vetor_ordenado_ASC(vet, n);
            break;
        case 2:
            gera_vetor_aleatorio(vet, n);
            break;
        case 3:
            gera_vetor_ordenado_DESC(vet, n);
            break;
    }
}


// Declarando as vari?veis globais que armazenar?o
// o n?mero de comapara??es e de trocas feitas durante a ordena??o
int quantComparacoes = 0;
int quantTrocas = 0;

// Fun??o que ordena um vetor com o algoritmo quick sort
// Recebe como par?metro o vetor que ser? ordenado
// o ?ndice do in?cio e do fim da parte do vetor que ser? ordenada
void quickSort(int vet[], int ini, int fim){

    int pivo =  vet[ini + (fim - ini) / 2];
    int i = ini;
    int j = fim;

    while (i <= j){

        while (vet[i] < pivo){
            quantComparacoes++;  // Adiciona mais uma compara??o ? contagem
            i++;  // Avan?a para o pr?ximo n?mero ? direita
        }

        while (vet[j] > pivo){
            quantComparacoes++;  // Adiciona mais uma compara??o ? contagem
            j--;  // Avan?a para o pr?ximo n?mero ? esquerda
        }

        if (i == j){
            break;
        }

        quantTrocas++;
        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        
    }

    if (i > ini){
        quickSort(vet, ini, i);
    }

    if (i+1 < fim){
        quickSort(vet, i+1, fim);
    }
}


int main(){

    // Gerar um vetor com 50000 n?meros
    int n = 50000;
    int vet[n];

    geraVetor(vet, n, ALEATORIO);

    // Tempo inicial da execu??o
    float t = clock();

    // Ordenar vetor
    // Do indice 0 ate o ultimo para ordenar todo o vetor
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execu??o
    t = clock() - t;

    // Exibir tempo de execu??o, n?mero de compara??es e de trocas
    printf("Tempo de execucao: %.3f ms\n", t/1000);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n\n", quantTrocas);
    // imprime_vetor(vet, n);


    return 0;
}