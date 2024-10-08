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

    // Escolha de um piv? para fazer as compara??es
    // A escolha do piv? como o elemento do meio ? vantajosa
    // porque tende a evitar que o piv? seja o maior ou menor n?mero do vetor
    // int pivo = vet[ini + (fim-ini) / 2];
    // int pivo = median3(vet, ini, fim);
    int pivo =  vet[ini + (fim - ini) / 2];

    // Vari?veis i e j para percorrer o vetor
    // i come?a no primeiro elemento da parte do vetor a ser ordenada
    // j come?a no ?ltimo elemento da parte do vetor a ser ordenada
    int i = ini;
    int j = fim;
    int counter = 0;

    // Este loop while controla a parti??o
    // Ao final do loop, os n?meros que s?o maiores do que o piv?
    // estar?o ? sua esquerda, e os maiores ? sua direita
    // A condi??o de parada ? quando i for maior ou igual a j
    while (i < j){

        // Loop para encontrar um elemento que seja
        // maior do que o piv? e que esteja antes do piv?
        // i percorre o vetor do in?cio em dire??o ao fim
        // i n?o pode ultrapassar o ?ndice do fim
        while (vet[i] < pivo){
            quantComparacoes++;  // Adiciona mais uma compara??o ? contagem
            i++;  // Avan?a para o pr?ximo n?mero ? direita
        }

        // Loop para encontrar um elemento que seja
        // menor do que o piv? e que esteja depois do piv?
        // j percorre o vetor do fim em dire??o ao in?cio
        // j n?o pode ser menor do que o ?ndice do in?cio
        while (vet[j] > pivo){
            quantComparacoes++;  // Adiciona mais uma compara??o ? contagem
            j--;  // Avan?a para o pr?ximo n?mero ? esquerda
        }

        // Neste ponto, vet[i] ? um n?mero maior do que o piv?
        // e vet[j] um n?mero menor do que o piv?
        // O loop deve ser interrompido caso i seja maior ou igual a j

        // Caso i seja maior ou igual a j, ent?o todo o vetor j? foi percorrido
        if (i == j){
            
            if (counter == 0){
                return;
            } 

            break;

        }
        counter++;

        // Se o c?digo chegou aqui, ent?o i e j ainda n?o se cruzaram
        // vet[i] ? um n?mero maior do que o piv? e que est? ? esquerda dele
        // vet[ij] ? um n?mero menor do que o piv? e que est? ? direita dele
        // Os valores de vet[i] e vet[j] devem ser trocados
        quantTrocas++;  // Adiciona mais uma troca ? contagem
        int aux = vet[i];  // Uso de uma vari?vel auxiliar para fazer a troca
        vet[i] = vet[j];
        vet[j] = aux;
    }

    // Neste ponto, todos os n?meros menores do que o piv? est?o ? sua esquerda
    // e os maiores ? sua direita

    // O algoritmo ent?o ? chamado recursivamente para ordenar a parte ? direita e ? esquerda da parti??o
    // A parti??o pode ser tanto i quanto j, pois tem o mesmo valor
    // A parte ? esquerda ? do in?cio at? i (incluindo i)
    // A parte ? direita ? de i+1 at? o fim

    // Ordena a parte ? esquerda da parti??o se i n?o for o in?cio
    // Se i for o in?cio, ent?o o n?mero j? est? no seu devido lugar
    // e n?o ? necess?rio chamar a fun??o novamente
    if (i > ini){
    quickSort(vet, ini, i);
    }

    // Aqui ser? organizada a parte direita, come?ando por i+1
    // Se i+1 for igual ao fim, o n?mero j? est? no seu devido lugar
    // e n?o ? necess?rio chamar a fun??o novamente
    if (i+1 < fim){
        quickSort(vet, i+1, fim);
    }
}


int main(){

    // Gerar um vetor com 50000 n?meros
    int n = 50;
    int vet[n];
    // gera_vetor_aleatorio(vet, n);
    // gera_vetor_ordenado_ASC(vet, n);
    gera_vetor_ordenado_DESC(vet, n);
    // imprime_vetor(vet,n);

    // Tempo inicial da execu??o
    float t = clock();

    // Ordenar vetor
    // Do ?ndice 0 at? o ?ltimo para ordenar todo o vetor
    quickSort(vet, 0, n-1);

    // Calcular o tempo total de execu??o
    t = clock() - t;

    // Exibir tempo de execu??o, n?mero de compara??es e de trocas
    // imprime_vetor(vet, n);
    printf("Tempo de execucao: %.3f ms\n", t/1000);  // Exibir em ms
    printf("Quantidade de Comparacoes: %d\n", quantComparacoes);
    printf("Quantidade de trocas: %d\n", quantTrocas);


    return 0;
}