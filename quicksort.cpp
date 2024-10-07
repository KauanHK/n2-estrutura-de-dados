/*
PROCESSO AVALIATIVO N2 – ESTRUTURA DE DADOS

EQUIPE
NOMES:
    Kauan Henrique Kaestner
    Luis Gabriel
    Ricardo Cardoso

CONSEGUIU CHEGAR NO RESULTADO?
R: Sim, conseguimos chegar ao resultado dos gráficos
   e inclusive tornar o código mais eficiente.

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

//gera um vetor ordenado de forma crescente e sem repetição [MELHOR CASO]
void gera_vetor_ordenado_ASC(int *vetor, int n) {
	for(int i = 0; i < n; i++){
		vetor[i] = i;
	}
}

//gera um vetor ordenado de forma DEcrescente e sem repetição [PIOR CASO]
void gera_vetor_ordenado_DESC(int *vetor, int n) {
	int j = n - 1;
	for(int i = 0; i < n; i++){
		vetor[i] = j--;
	}
}

//gera um vetor ordenado de forma aleatória e sem repetição [CASO MÉDIO]
void gera_vetor_aleatorio(int *vetor, int n) {
	int j, aux;
	
	for(int i = 0; i < n; i++){
		vetor[i] = i;
	}
	
	srand(time(0));
	
	//aplica o algoritmo de Fisher-Yates
	for(int i = 0; i < n; i++){
		// gera um número randomico de 0 a n -1
		j = rand() % n;
		// troca de posição
		aux = vetor[i];
		vetor[i] = vetor[j];
		vetor[j] = aux;
	}
}



int quantComparacoes = 0;
int quantTrocas = 0;

void quickSort(int vet[], int ini, int fim){

    int pivo = vet[ini + (fim-ini) / 2];
    int i = ini;
    int j = fim;

    while (true){

        while (vet[i] < pivo && i < fim){
            quantComparacoes++;
            i++;
        }
        while (vet[j] > pivo && j > ini){
            quantComparacoes++;
            j--;
        }

        if (i > j){
            break;
        } else if (i == j){
            i++;
            j--;
            break;
        }

        quantTrocas++;
        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;

    }

    if (i < fim){
        quickSort(vet, i, fim);
    }
    if (j > ini){
        quickSort(vet, ini, j);
    }
}


int main(){

    // Gerar um vetor com n números
    int n = 50000;
    int vet[n];
    gera_vetor_aleatorio(vet, n);
    // gera_vetor_ordenado_ASC(vet, n);
    // gera_vetor_ordenado_DESC(vet, n);


    float t = clock();
    quickSort(vet, 0, n-1);
    t = (clock() - t) / 1000;

    printf("Tempo de execução: %.3f ms\n", t);
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n", quantTrocas);


    return 0;
}