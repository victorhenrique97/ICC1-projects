//Vh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ENTER 10

//------------------------------------READ-----------------------------------//
/* Essa função foi criada tanto para ler e armazenar em um ponteiro o nome do
arquivo quanto a string que será utilizada na parte 3. */

char *read() {
    char *string = NULL;
    char c;
    int counter = 0;

    do{
        c = fgetc(stdin);
        string = (char *) realloc(string, sizeof(char)*(counter+1));
        string [counter++] = c;
    } while(c != ENTER);
    string[counter-1] = '\0';

return string;
}

//----------------------------------DESINVERT--------------------------------//
/* Essa função foi criada para desinverter o vetor. */

void desinvert(unsigned int *vector, int n_of_int){

    int i, j;
    int aux;


    for(i=0, j=n_of_int-1; i<j; i++, j--){  //Começo com 'i' no ínicio do vetor e com 'j' no final do vetor.
        aux = vector[i];                    //Variável auxiliar recebe o que está contido em vetor na posição 'i'.
        vector[i] = vector[j];              //Vetor na posição 'i' recebe o que está contido na posição 'j'.
        vector[j] = aux;                    //Vetor na posição 'j' recebe o que está contido em aux.
    }

}

//------------------------------------CHECK---------------------------------//
/* Essa função foi criada apenas para checkar se preciso ou não shiftar 'j' */

int check (unsigned int j){

    char *checker;
    int i;

    checker = (char *) &j;  //Ponteiro do tipo (char *) recebe o endereço da variável 'j'.

	for(i=0; i < sizeof(int); i++){ //Como o ponteiro percorre apenas 4 bytes, criei o laço dessa forma.
		if(!(checker[i] == '\0' || (checker[i] >= '0' && checker[i] <= '9') || (checker[i] >= 'a' && checker[i] <= 'z') || (checker[i] >= 'A' && checker[i] <= 'Z') || checker[i] == ':' || checker[i] == '.' || checker[i] == ',' || checker[i] == ' ' || checker[i] == '?' || checker[i] == '!' || checker[i] == ')' || checker[i] == '(')) {return 0;}
	}   // Caso não esteja na condição acima, imediatamente retorno '0' para avisar a função descript que o 'j' precisa ser shiftado para direita.

return 1; //Caso não precise, retorno '1'
}

//----------------------------------DESCRIPT---------------------------------//
/* Criei essa função para descriptografar a mensagem. */

void descript (unsigned int *vector, int n_of_int){

    int i;
    unsigned int j;

    for(i=0; i<n_of_int; i++){
        j = vector[i];
        if(check(j) == 0) {     //Chamo a função que checka se 'j' precisa ou não ser shiftado para direita;
            j /= 2;             //Caso necessário shifto o 'j';
            vector[i] = j;      // E o vetor recebe 'j'.
		}
	}
}

//---------------------------------------CONT--------------------------------//
/* Criei essa função que conta o número de ocorrencias de uma string na mensagem*/

 void count(unsigned int *vector){

    char *string;
    char *vector_char;
    int counter2=0, counter=0;
    int i, j, k;
    int n_of_char_string, n_of_char_vector;


    vector_char = (char *) vector;                  // Vetor de caracteres aponta para o local onde o vetor de unsigned int aponta.
    n_of_char_vector = strlen(vector_char);         // Cálculo do comprimeto de vetor.

    string = read();                        //Leitura do nome da string.
    n_of_char_string = strlen(string);      //Cálculo do comprimento de string.

    for(i=0; i<n_of_char_vector; i++){                  //Rodo o laço até percorrer toda a mensagem.
        for(j=0, k=i; j<n_of_char_string; j++, k++){    //Rodo esse laço interno até percorrer toda a string, sendo que 'k' recebe aonde está o 'i'.
            if(vector_char[k] == string[j])counter2++;  //Caso os elementos sejam iguais incremento um contador2.
        }
        if(counter2 == n_of_char_string)counter++;      //Caso o contador2 seja igual ao numero de caracteres da string incrmento outro contador, dessa vez o de ocorrências.
        counter2=0;                                     //Zero o contador 2 para que ele possa ser incrementado a partir do zero.
    }
    printf("%d\n", counter);        //Imprimo o número de ocorrências.

    free(string);                   //Libero a memória utilizada para armazenar a string.
 }

 //-----------------------------------EXTRACTER---------------------------------//
/*Criei essa função que recebe 'k' e o 'i' e extrai o número que está na posição 'k'*/

int extracter (int k, unsigned int i){

    int j, aux;


    for(j=0; j<k+1; j++){
        aux = i%10;         //Variável auxiliar recebe o resto da divisão de i por 10, uma vez que preciso retornar o elemento que será resto de uma divisão por 10.
        i /=10;
    }

return aux;
}

//-------------------------------------MAP------------------------------------//
/* Essa função foi criada para o mapeamento de dígitos, passo como parâmetro:
o vetor, o nome do arquivo (que contém a chave k), e o númeoro de inteiros. */

void map (unsigned int *vector, char *file_name, int n_of_int){

    unsigned int  i;
    int j, k;


    k = file_name[0];    // A variável 'k' recebe o número na forma de caractere que está contida no nome do arquivo.
    k -=48;             // Conversão de caractere para inteiro.

    for(j=0; j<n_of_int; j++){
        i = vector[j];          // 'i' recebe o elemento do vetor na posição j.
        k = extracter(k, i);    // Chamada da função que extrai o elemento na posição 'k'.
        printf("%d", k);        // Impressão do inteiro que estava na posição 'k'.
    }
    printf("\n");
}

//========================================MAIN=================================//

 int main (int argc, char *argv[]){

    FILE *fp_in;
    char *file_name;
    unsigned int *vector;
    int n_of_int;
    int select;


    file_name = read();                             //Leitura do nome do arquivo.
    fp_in = fopen(file_name, "rb");                 // Abrindo o arquivo no modo leitura de arquivo binário.
    fseek(fp_in, 0, SEEK_END);                      // Posicionando o cursor no fim do arquivo para saber o número de bytes.
    n_of_int = ftell(fp_in)/sizeof(unsigned int);   // Calculo do número de inteiros presentes no arquivo.

    vector = (unsigned int *) calloc(n_of_int, sizeof(unsigned int));   //Alocação de memória para o vetor.
    rewind(fp_in);                                                      //Retornando o cursor para o início do arquivo.
    fread(vector, sizeof(unsigned int), n_of_int, fp_in);               //Lendo uma única vez o arquivo e armazenando os dados em um vetor.
    desinvert(vector, n_of_int);                                        //Chamando a função que desinverte o vetor.

    select = fgetc(stdin);  //Leitura do teclado e atribuição do que foi lido a uma varável que será utilizada para selecionar qual operação a ser feita.
    getchar();              //Limpeza do buffer do teclado.


    switch(select){         //Criei esse switch para selecionar a partir de select a operação que será realizada.
    case '1':
        map(vector, file_name, n_of_int);   //Caso seja selecionada essa opção, chamo a função que mapeia os dígitos.
        break;
    case '2':
        descript(vector, n_of_int);         //Caso seja selecionada essa opção, chamo a função que descriptografa a mensagem.
        printf("%s\n", (char *) vector);    //Impressão da mensagem descriptografada.
        break;

    case '3':
        descript(vector, n_of_int);         //Caso seja selecionada essa opção, chamo a função que descriptografa a mensagem;
        count(vector);                      // E logo em seguida a função que conta o número de ocorrências de uma string.
    break;
    }

    free(vector);       //Liberação da memória utilizada para armazenar o vetor.
    free(file_name);    //Liberação da memória utilizad para armazenar o nome do arquivo.
    fclose(fp_in);      //Fechando o arquivo.

return 0;
}
