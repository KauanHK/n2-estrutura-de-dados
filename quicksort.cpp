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


// Declarando as variáveis globais que armazenarão
// o número de comaparações e de trocas feitas durante a ordenação
int quantComparacoes = 0;
int quantTrocas = 0;

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int median3(int vet[], int ini, int fim){
    int meio = ini + (fim - ini) / 2;

    if (vet[ini] > vet[meio])
        swap(&vet[ini], &vet[meio]);

    if (vet[ini] > vet[fim])
        swap(&vet[ini], &vet[fim]);

    if (vet[meio] > vet[fim])
        swap(&vet[meio], &vet[fim]);

    return vet[meio];
}


// Função que ordena um vetor com o algoritmo quick sort
// Recebe como parâmetro o vetor que será ordenado
// o índice do início e do fim da parte do vetor que será ordenada
void quickSort(int vet[], int ini, int fim){

    // Escolha de um pivô para fazer as comparações
    // A escolha do pivô como o elemento do meio é vantajosa
    // porque tende a evitar que o pivô seja o maior ou menor número do vetor
    // int pivo = vet[ini + (fim-ini) / 2];
    // int pivo = median3(vet, ini, fim);
    int pivo =  ini + rand() % (fim - ini + 1);

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
        // maior do que o pivô e que esteja antes do pivô
        // i percorre o vetor do início em direção ao fim
        // i não pode ultrapassar o índice do fim
        while (vet[i] < pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            i++;  // Avança para o próximo número à direita
        }

        if (i >= fim){
            break;
        }

        // Loop para encontrar um elemento que seja
        // menor do que o pivô e que esteja depois do pivô
        // j percorre o vetor do fim em direção ao início
        // j não pode ser menor do que o índice do início
        while (vet[j] > pivo){
            quantComparacoes++;  // Adiciona mais uma comparação à contagem
            j--;  // Avança para o próximo número à esquerda
        }

        if (j <= ini){
            break;
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
        // vet[ij] é um número menor do que o pivô e que está à direita dele
        // Os valores de vet[i] e vet[j] devem ser trocados
        quantTrocas++;  // Adiciona mais uma troca à contagem
        int aux = vet[i];  // Uso de uma variável auxiliar para fazer a troca
        vet[i] = vet[j];
        vet[j] = aux;

    }

    // Neste ponto, todos os números menores do que o pivô estão à sua esquerda
    // e os maiores à sua direita

    // O algoritmo então é chamado recursivamente para ordenar a parte à direita e à esquerda da partição
    // A partição pode ser tanto i quanto j, pois tem o mesmo valor
    // A parte à esquerda é do início até i (incluindo i)
    // A parte à direita é de i+1 até o fim

    // Ordena a parte à esquerda da partição se i não for o início
    // Se i for o início, então o número já está no seu devido lugar
    // e não é necessário chamar a função novamente
    if (i > ini){
    quickSort(vet, ini, i);
    }

    // Aqui será organizada a parte direita, começando por i+1
    // Se i+1 for igual ao fim, o número já está no seu devido lugar
    // e não é necessário chamar a função novamente
    if (i+1 < fim){
        quickSort(vet, i+1, fim);
    }
}


int main(){

    // Gerar um vetor com 50000 números
    int n = 50000;
    int vet[n];
    gera_vetor_aleatorio(vet, n);
    // gera_vetor_ordenado_ASC(vet, n);
    // gera_vetor_ordenado_DESC(vet, n);
    // imprime_vetor(vet,n);

    // Tempo inicial da execução
    float t = clock();

    // Ordenar vetor
    // Do índice 0 até o último para ordenar todo o vetor
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execução
    t = clock() - t;

    // Exibir tempo de execução, número de comparações e de trocas
    printf("Tempo de execução: %.3f ms\n", t/1000);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n", quantTrocas);
    // imprime_vetor(vet, n);


    return 0;
}