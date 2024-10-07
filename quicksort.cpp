/*
PROCESSO AVALIATIVO N2 – ESTRUTURA DE DADOS

EQUIPE
NOMES:
    Kauan Henrique Kaestner
    Luis Gabriel
    Ricardo Cardoso

CONSEGUIU CHEGAR NO RESULTADO?
R: Sim, conseguimos chegar ao resultado dos gráficos
   e inclusive tornar o código mais eficiente, 
   principalmente para vetores já ordenados ou semi ordenados.

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


// Declarando as variáveis globais que armazenarão
// o número de comaparações e de trocas feitas durante a ordenação
int quantComparacoes = 0;
int quantTrocas = 0;

// Função que ordena um vetor com o algoritmo quick sort
// Recebe como parâmetro o vetor que será ordenado
// o índice do início e do fim da parte do vetor que será ordenada
int partition(int vet[], int ini, int fim){

    // Escolha de um pivô para fazer as comparações
    // A escolha do pivô como o elemento do meio é vantajosa
    // porque tende a evitar que o pivô seja o maior ou menor número do vetor
    // minimizando a chance de cair no caso O(n²)
    int pivo =  vet[ini + (fim - ini) / 2];

    // Variáveis i e j para percorrer o vetor
    // i começa no primeiro elemento da parte do vetor a ser ordenada
    // j começa no último elemento da parte do vetor a ser ordenada
    int i = ini;
    int j = fim;

    // Este loop while controla a partição
    // Ao final do loop, os números que são maiores do que o pivô
    // estarão à sua esquerda, e os maiores à sua direita
    // A condição de parada é quando i for maior ou igual a j
    while (true){

        // Loop para encontrar um elemento que seja
        // maior do que o pivô
        // i percorre o vetor do início em direção ao fim
        while (vet[i] < pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            i++;  // Avança para o próximo número à direita
        }

        // Loop para encontrar um elemento que seja
        // menor do que o pivô
        // j percorre o vetor do fim em direção ao início
        while (vet[j] > pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            j--;  // Avança para o próximo número à esquerda
        }

        // Neste ponto, vet[i] é um número maior do que o pivô
        // e vet[j] um número menor do que o pivô
        // O loop deve ser interrompido caso i seja maior ou igual a j

        // Caso i seja maior ou igual a j, então todo o vetor já foi percorrido
        if (i >= j){
			break;
		}

        // Se o código chegou aqui, então i e j ainda não se cruzaram
        // vet[i] é um número maior do que o pivô e que está à esquerda dele
        // vet[j] é um número menor do que o pivô e que está à direita dele
        // Os valores de vet[i] e vet[j] devem ser trocados
        int aux = vet[i];  // Uso de uma variável auxiliar para fazer a troca
        vet[i] = vet[j];
        vet[j] = aux;
        quantTrocas++;  // Adiciona mais uma troca à contagem
        i++;
        j--;
    }

    // Neste ponto, todos os números menores do que o pivô estão à sua esquerda
    // e os maiores à sua direita

    // O algoritmo então é chamado recursivamente para ordenar a parte à direita e à esquerda da partição
    // A partição pode ser tanto i quanto j, pois tem o mesmo valor
    // A parte à esquerda é do início até a partição (inclusa)
    // A parte à direita é de partição+1 até o fim

    // Retornar a partição
    return i;
}


void quickSort(int vet[], int ini, int fim){

    // Condição de para é se início for igual ou menor ao fim,
    // o que significa que essa parte do vetor já está ordenada
    if (ini < fim){

        // Pega a partição
        int p = partition(vet, ini, fim);

        // Ordena a parte à esquerda da partição, de início até a partição (inclusa)
        quickSort(vet, ini, p);

        // Ordena a parte à direita da partição, da partição+1 até fim
        quickSort(vet, p+1, fim);
    }

}


int main(){

    // Gerar um vetor com 50000 números
    int n = 50000;
    int vet[n];
    gera_vetor_aleatorio(vet, n);
//     gera_vetor_ordenado_ASC(vet, n);
//     gera_vetor_ordenado_DESC(vet, n);
//     imprime_vetor(vet,n);

    // Tempo inicial da execução
    clock_t t = clock();

    // Ordenar vetor
    // Do índice 0 até o último para ordenar todo o vetor
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execução
    t = clock() - t;

    // Exibir tempo de execução, número de comparações e de trocas
//    imprime_vetor(vet, n);
    printf("Tempo de execucao: %li ms\n", t);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n", quantTrocas);


    return 0;
}
