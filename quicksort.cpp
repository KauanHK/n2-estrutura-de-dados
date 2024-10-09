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

bool verificarVetor(int *vet, int n){

    int elementosErrados = 0;
    bool ordenado = true;

    for (int j = 1; j < n; j++){
        if (vet[j-1] > vet[j]){
            // printf("Erro: %d antes de %d\n", vet[j-1], vet[j]);
            elementosErrados++;
            ordenado = false;
        }
    }
    if (!ordenado){
        printf("\nFalha ao ordenar vetor: %d elementos errados\n\n", elementosErrados);
        return false;
    }
    return true;
}

// Função para testes para validar se o vetor está 100% ordenado
bool validar(int *vet, int n, int opcao, int numTestes){

    bool ordenado;
    int i;
	for (i = 0; i < numTestes; i++){

		printf("%d\r", i);

        geraVetor(vet, n, opcao);
		quickSort(vet, 0, n-1);
        ordenado = verificarVetor(vet, n);
        if (!ordenado){
            break;
        }
        
    }
    printf("Foram ordenados %d vetores com sucesso\n", i);
    return true;
}

int main(){

    // Gerar um vetor com 50000 n?meros
    int n = 50000;
    int vet[n];
    // gera_vetor_aleatorio(vet, n);
    // gera_vetor_ordenado_ASC(vet, n);
    // gera_vetor_ordenado_DESC(vet, n);
    // imprime_vetor(vet,n);

    // Tempo inicial da execu??o
    float t = clock();

    // Ordenar vetor
    // Do ?ndice 0 at? o ?ltimo para ordenar todo o vetor
    geraVetor(vet, n, 1);
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execu??o
    t = clock() - t;

    // Exibir tempo de execu??o, n?mero de compara??es e de trocas
    printf("Tempo de execucao: %.3f ms\n", t/1000);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n\n", quantTrocas);
    // imprime_vetor(vet, n);
    // validar(vet, n, 2, 10000);


    return 0;
}