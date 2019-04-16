//Vh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ENTER 10

typedef struct snode snode;
/////////////////////////////////////////////////////////////////////////////////////////
/*Crio o node que contém um ponteiro para o próximo da lista, para o anterior e um byte
para o caractere*/
typedef struct snode{
	char element; 
	snode *prev, *next;
}snode;
/////////////////////////////////////////////////////////////////////////////////////////
/*Crio a struct que armazenará o enderço do primeiro e do ultimo elemento do deck,
além de armazenar o seu tamanho */
typedef struct sdeck{
	snode *first, *last;
	int size;
}sdeck;
/////////////////////////////////////////////////////////////////////////////////////////
/*Nessa função eu libero os nodes contidos no deck */
void clear(sdeck *deck){
	
	snode *aux;
	aux = deck->first;

	while(aux != NULL) {
		deck->first = aux->next;
		free(aux);
		aux = deck->first;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*Nessa função chamo a clear que desaloca os elementos do deck, e nessa eu libero o deck */
void destroy(sdeck *deck){
	clear(deck);
	free(deck);
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Nessa função imprimo recursivamente os elementos contidos no deck*/
void print2(snode *aux){
	if (aux == NULL){
		printf("\n");
		return;
	}

	printf("%c", aux->element);
	print2(aux->next);
}
///////////////////////////////////////////////////////////////////////////////////////////
/* Nessa função chamo a print2 para imprimir recursivamente os elementos*/
void print(sdeck *deck){

	snode *aux;
	aux = deck->first;
	print2(aux);
}
///////////////////////////////////////////////////////////////////////////////////////////
/*Nessa função retorno o inteiro responsável por armazenar o número de elementos do deck
sendo que o valor dele é alterado em algumas funções como (pop_back, push_front...) */
int size(sdeck *deck){

return deck->size;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*Nessa função vejo se o deck está ou não vazio, para isso chamo a função size que retorna
zero se estiver vazio e algo diferente de zero se não estiver, que no caso é o número de
elementos*/
int empty(sdeck *deck){

	if(!size(deck)) return 1;

return 0;
}
////////////////////////////////////////////////////////////////////////////////////
/*Caso o deck esteja vazio eu adciono o elemento e faço os dois ponteiros
(first e last apontar para ele)*/
void push_empty(sdeck *deck ,char letter){

	snode *aux;

		aux =(snode *)calloc(1, sizeof(snode));
		aux->element = letter;
		aux->prev = NULL;
		aux->next = NULL;
		deck->first = aux;
		deck->last = aux;
		deck->size++;
		return;

}
/////////////////////////////////////////////////////////////////////////////////////
/*Nessa função caso o deck não esteja cheio eu adciono um elemento no final dele */
void push_back(sdeck *deck, char letter){
	
	snode *aux;

	if(empty(deck)){
		push_empty(deck, letter);
		return;
	}
		
	aux =(snode *)calloc(1, sizeof(snode));
	aux->element = letter;
	aux->prev = deck->last;
	deck->last->next = aux;
	deck->last = aux;
	deck->size++;
	
}
//////////////////////////////////////////////////////////////////////////////////////
/*Nessa função caso o deck não esteja cheio eu adciono um elemento na frente dele */
void push_front(sdeck *deck, char letter){
	
	snode *aux;

	if(empty(deck)){
		push_empty(deck, letter);
		return;
	}

	aux = (snode *)calloc(1, sizeof(snode));
	aux->element = letter;
	aux->next = deck->first;
	deck->first->prev = aux;
	deck->first = aux;
	deck->size++;
}
////////////////////////////////////////////////////////////////////////////
/*Função para criar o deck*/
sdeck *create(){

	sdeck *deck;
	
	deck = (sdeck *) calloc(1, sizeof(sdeck));
	deck->size = 0;

return deck;
}
/////////////////////////////////////////////////////////////////////////////
/*Função para a leitura da string*/
char *readline(){

	char *string = NULL;
	char letter;
	int counter = 0;

	do{
	letter = fgetc(stdin);
	string = (char *) realloc(string, sizeof(char)*(counter+1));
	string[counter++] = letter;
	}while(letter != ENTER);

	string[counter-1] = '\0';

return string;
}
//////////////////////////////////////////////////////////////////////////////
/*Nessa função eu retorno o primeiro elemento do deck */
char front(sdeck *deck){

	char letter;
	letter = deck->first->element;

return letter;
}
///////////////////////////////////////////////////////////////////////////////////////
/*Nessa função eu retorno o ultimo elemento do deck */
char back(sdeck *deck){

	char letter; 
	letter = deck->last->element;

return letter;
}
//////////////////////////////////////////////////////////////////////////////////////
/*Caso seja o ultimo elemento eu não removo a memória alocada para ele, apenas
faço com que o elemento receba zero, obs não decremento o size pois eu apenas zero o
ultimo elemento, deixo para a função clear remover esse node. */
void pop_last(sdeck *deck){

	deck->last->element = 0;
}
///////////////////////////////////////////////////////////////////////////////////
/*Nessa função eu recebo um deck, e caso o número de elementos seja diferente de 1
eu removo o primeiro elemento */
void pop_front(sdeck *deck){

	snode *aux;

	if(size(deck) == 1){
		pop_last(deck);
		return;
	}

	aux = deck->first;
	deck->first = deck->first->next;
	free(aux);
	deck->first->prev = NULL;
	deck->size--;	
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*Nessa função eu recebo um deck, e caso o número de elementos seja diferente de 1
eu removo o ultimo elemento */
void pop_back(sdeck *deck){

	snode *aux;

	if(size(deck) == 1){
		pop_last(deck);
		return;
	}

	aux = deck->last;
	deck->last = deck->last->prev;
	free(aux);
	deck->last->next = NULL;
	deck->size--;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/* Nessa função eu tenho 3 parametros, sendo o ultimo o tamanho da string obs(
passo n-1 pois a cada chamada da função eu retiro ou pelo menos tento remover um elemento ou
da frente ou do final do deck2, assim quando o n valer zero não haverá mais elementos no deck, 
e se todos os elementos forem removidos é porque é possivel formar a palavra)
	Sendo que eu sempre tento remover os elementos do final do Deck2, caso chegue em algum passo
onde isso não seja possível eu retorno para a função que chamou ela e coloco os elementos denovo
no final do deck, e tento remover o da frente, caso não seja possivel remover nem da frente nem
do final, retorno 0 indicando que não é possível formar o deck2 a partir do deck1, se retornar
1, é possivel formar.
*/
int checker(sdeck *deck1, sdeck *deck2, int n){

	char aux, aux2;
	int ret = 0;

	if(n == 0) return 1; // Caso Base

	aux = back(deck1);
	aux2 = back(deck2);

	if(aux == aux2){
		pop_back(deck1);
		pop_back(deck2);
		ret = checker(deck1, deck2, n-1); // Passo recursivo
		if(ret == 0){
			push_back(deck1, aux);
			push_back(deck2, aux2);
		}
	}

	aux2 = front(deck2);

	if(aux == aux2){
		pop_back(deck1);
		pop_front(deck2);
		ret = checker(deck1, deck2, n-1); // Passo recursivo
	}

	return ret;
}
///////////////////////////////////////////////////////////////////////////////////////////
/* Nessa função executo a parte 2 do trabalho, para isso leio as duas strings, armazeno-as
em decks, e chamo a função checker que ve se é ou não possivel formar a string B a partir da
string A. */ 
void Strings(){

	char *stringA, *stringB;
	sdeck *deckA ,*deckB;
	int i, len;
	
	stringA = readline();
	stringB = readline();
	deckA = create();
	deckB = create();
	len = strlen(stringA);

	for(i=0; i<len; i++){
		push_back(deckA, stringA[i]);
		push_back(deckB, stringB[i]);
	}

	free(stringA);
	free(stringB);

	if(checker(deckA, deckB, len))printf("S\n");
	else printf("N\n");

	destroy(deckA);
	destroy(deckB);

}
///////////////////////////////////////////////////////////////////////////////////////
/* Nessa função executo a parte 1 do trabalho, como o objetivo é formar a 
maior palavra (em ordem lexicográfica), pego cada letra da minha word do inicio 
para o final e se for maior ou igual ao primeiro caractere do deck, coloco na frente, 
senão coloco no final do deck.*/
void The_Last_Word(){

	char *word;
	int len, i;
	sdeck *deck;

	word = readline();
	len = strlen(word);
	deck = create();

	for(i=0; i<len; i++){
		if(empty(deck)) push_empty(deck, word[i]);
		else if(word[i]>=deck->first->element) push_front(deck, word[i]); 
		else push_back(deck, word[i]);
	}

	print(deck);
	destroy(deck);
	free(word);
}
///////////////////////////////////////////////////////////////////////////////////////
/*Main: Leio o numero responsavel pela operação e chamo a função correspondente */
int main(int argc, char *argv[]){

	int select;

	scanf("%d%*c", &select);
	if(select == 1)The_Last_Word();
	if(select == 2)Strings();

return 0;
}
