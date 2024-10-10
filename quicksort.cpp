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

MELHORIAS:
R: Nós aplicamos algumas melhorias, como a escolha do elemento do meio
   do vetor como pivô, o que evita o caso O(n2).
   Também melhoramos a eficiência para vetores já ordenados e invertidos
   percorrendo o vetor com i e j.

   Outras possíveis melhorias seriam:
   - Escolher dois pivôs, dividindo o vetor em 3 partes
   - Como o quicksort não é eficiente para ordenar pequenos vetores, usar um outro algoritmo, 
   como o insertion sort, para vetores menores do 17, por exemplo

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

// Função que determina um pivô para a subseção de um vetor e
// desloca os números maiores do que ele para a sua direita e
// os menores para a sua esquerda
// Retorna o índice da posição final do pivô no vetor
int partition(int vet[], int ini, int fim){

    // Escolha do pivô
    // O elemento do meio da subseção do vetor é selecionado
    // Isso evita o caso O(n2) para vetores já ordenados ou invertidos
    int pivo =  vet[ini + (fim - ini) / 2];

    // Índices que percorrerão a subseção do vetor
    // i percorre da esquerda para a direita, iniciando no início da subseção
    // j percorre da direita para a esquerda, iniciando do fim da subseção
    int i = ini;
    int j = fim;

    // Loop while que fará a partição
    // Deve ser interrompido caso i seja igual a j
    while (true){

        // i percorre o vetor até encontrar um elemento que seja maior do que o pivô
        // Não é necessário verificar se i é menor do que fim,
        // porque em algum momento i será igual a j
        while (vet[i] < pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            i++;  // Avança para o próximo número à direita
        }

        // j percorre o vetor até encontrar um elemento menor do que o pivô
        // Não é necessário verificar se j é maior do que ini,
        // porque em algum momento i será igual a j
        while (vet[j] > pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            j--;  // Avança para o próximo número à esquerda
        }

        // Caso i seja igual a j, o loop já pode ser interrompido
        // Neste algoritmo, é impossível i ser maior do que j,
        // pois em algum momento, i e j estarão sobre um elemento
        // que não é maior nem menor do que o pivô, ou seja, o próprio pivô
        // Isso significa que toda a subseção foi percorrida
        if (i == j){
            break;
        }

        quantTrocas++;  // Adiciona uma troca à contagem

        // Inverte os valores do vetor em i e j usando uma variável auxiliar
        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        
    }

    // Retorna a partição, que é a posição final do pivô no vetor
    // Poderia ser retornado o valor de j também, pois i e j têm o mesmo valor
    return i;
}

// Organiza um vetor em ordem crescente usando o algoritmo quicksort
void quickSort(int *vet, int ini, int fim){

    // Condição de parada da função recursiva
    // Se ini for igual ou maior do j, então a subseção do vetor já está ordenada
    if (ini < fim){

        // A função da partição é executada
        // Um elemento é escolhido como pivô, 
        // os números maiores do que ele são deslocados para a sua direita
        // e os menores para sua esquerda
        // A variável 'p' armazena o índice final do pivô
        int p = partition(vet, ini, fim);

        // Chama a função recursivamente
        // Primeiro ordena a parte à esquerda da partição, incluindo a partição
        quickSort(vet, ini, p);

        // Depois ordena a parte à direita da partição
        quickSort(vet, p+1, fim);
    }
}

int main(){

    // Gerar um vetor com 50000 números
    int n = 50000;
    int vet[n];
    // gera_vetor_ordenado_ASC(vet, n);
    gera_vetor_aleatorio(vet, n);
    // gera_vetor_ordenado_DESC(vet, n);

    // Tempo inicial da execução
    float t = clock();

    // Ordenar vetor
    // Do índice 0 até o último para ordenar todo o vetor
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execução
    t = clock() - t;

    // Exibir tempo de execução, número de comparações e de trocas
    printf("Tempo de execucao: %.3f ms\n", t/1000);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n", quantTrocas);
    // imprime_vetor(vet, n);


    return 0;
}