//Vh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ENTER 10

//------------------------------------READ-----------------------------------//
/* Essa fun��o foi criada tanto para ler e armazenar em um ponteiro o nome do
arquivo quanto a string que ser� utilizada na parte 3. */

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
/* Essa fun��o foi criada para desinverter o vetor. */

void desinvert(unsigned int *vector, int n_of_int){

    int i, j;
    int aux;


    for(i=0, j=n_of_int-1; i<j; i++, j--){  //Come�o com 'i' no �nicio do vetor e com 'j' no final do vetor.
        aux = vector[i];                    //Vari�vel auxiliar recebe o que est� contido em vetor na posi��o 'i'.
        vector[i] = vector[j];              //Vetor na posi��o 'i' recebe o que est� contido na posi��o 'j'.
        vector[j] = aux;                    //Vetor na posi��o 'j' recebe o que est� contido em aux.
    }

}

//------------------------------------CHECK---------------------------------//
/* Essa fun��o foi criada apenas para checkar se preciso ou n�o shiftar 'j' */

int check (unsigned int j){

    char *checker;
    int i;

    checker = (char *) &j;  //Ponteiro do tipo (char *) recebe o endere�o da vari�vel 'j'.

	for(i=0; i < sizeof(int); i++){ //Como o ponteiro percorre apenas 4 bytes, criei o la�o dessa forma.
		if(!(checker[i] == '\0' || (checker[i] >= '0' && checker[i] <= '9') || (checker[i] >= 'a' && checker[i] <= 'z') || (checker[i] >= 'A' && checker[i] <= 'Z') || checker[i] == ':' || checker[i] == '.' || checker[i] == ',' || checker[i] == ' ' || checker[i] == '?' || checker[i] == '!' || checker[i] == ')' || checker[i] == '(')) {return 0;}
	}   // Caso n�o esteja na condi��o acima, imediatamente retorno '0' para avisar a fun��o descript que o 'j' precisa ser shiftado para direita.

return 1; //Caso n�o precise, retorno '1'
}

//----------------------------------DESCRIPT---------------------------------//
/* Criei essa fun��o para descriptografar a mensagem. */

void descript (unsigned int *vector, int n_of_int){

    int i;
    unsigned int j;

    for(i=0; i<n_of_int; i++){
        j = vector[i];
        if(check(j) == 0) {     //Chamo a fun��o que checka se 'j' precisa ou n�o ser shiftado para direita;
            j /= 2;             //Caso necess�rio shifto o 'j';
            vector[i] = j;      // E o vetor recebe 'j'.
		}
	}
}

//---------------------------------------CONT--------------------------------//
/* Criei essa fun��o que conta o n�mero de ocorrencias de uma string na mensagem*/

 void count(unsigned int *vector){

    char *string;
    char *vector_char;
    int counter2=0, counter=0;
    int i, j, k;
    int n_of_char_string, n_of_char_vector;


    vector_char = (char *) vector;                  // Vetor de caracteres aponta para o local onde o vetor de unsigned int aponta.
    n_of_char_vector = strlen(vector_char);         // C�lculo do comprimeto de vetor.

    string = read();                        //Leitura do nome da string.
    n_of_char_string = strlen(string);      //C�lculo do comprimento de string.

    for(i=0; i<n_of_char_vector; i++){                  //Rodo o la�o at� percorrer toda a mensagem.
        for(j=0, k=i; j<n_of_char_string; j++, k++){    //Rodo esse la�o interno at� percorrer toda a string, sendo que 'k' recebe aonde est� o 'i'.
            if(vector_char[k] == string[j])counter2++;  //Caso os elementos sejam iguais incremento um contador2.
        }
        if(counter2 == n_of_char_string)counter++;      //Caso o contador2 seja igual ao numero de caracteres da string incrmento outro contador, dessa vez o de ocorr�ncias.
        counter2=0;                                     //Zero o contador 2 para que ele possa ser incrementado a partir do zero.
    }
    printf("%d\n", counter);        //Imprimo o n�mero de ocorr�ncias.

    free(string);                   //Libero a mem�ria utilizada para armazenar a string.
 }

 //-----------------------------------EXTRACTER---------------------------------//
/*Criei essa fun��o que recebe 'k' e o 'i' e extrai o n�mero que est� na posi��o 'k'*/

int extracter (int k, unsigned int i){

    int j, aux;


    for(j=0; j<k+1; j++){
        aux = i%10;         //Vari�vel auxiliar recebe o resto da divis�o de i por 10, uma vez que preciso retornar o elemento que ser� resto de uma divis�o por 10.
        i /=10;
    }

return aux;
}

//-------------------------------------MAP------------------------------------//
/* Essa fun��o foi criada para o mapeamento de d�gitos, passo como par�metro:
o vetor, o nome do arquivo (que cont�m a chave k), e o n�meoro de inteiros. */

void map (unsigned int *vector, char *file_name, int n_of_int){

    unsigned int  i;
    int j, k;


    k = file_name[0];    // A vari�vel 'k' recebe o n�mero na forma de caractere que est� contida no nome do arquivo.
    k -=48;             // Convers�o de caractere para inteiro.

    for(j=0; j<n_of_int; j++){
        i = vector[j];          // 'i' recebe o elemento do vetor na posi��o j.
        k = extracter(k, i);    // Chamada da fun��o que extrai o elemento na posi��o 'k'.
        printf("%d", k);        // Impress�o do inteiro que estava na posi��o 'k'.
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
    fp_in = fopen(file_name, "rb");                 // Abrindo o arquivo no modo leitura de arquivo bin�rio.
    fseek(fp_in, 0, SEEK_END);                      // Posicionando o cursor no fim do arquivo para saber o n�mero de bytes.
    n_of_int = ftell(fp_in)/sizeof(unsigned int);   // Calculo do n�mero de inteiros presentes no arquivo.

    vector = (unsigned int *) calloc(n_of_int, sizeof(unsigned int));   //Aloca��o de mem�ria para o vetor.
    rewind(fp_in);                                                      //Retornando o cursor para o in�cio do arquivo.
    fread(vector, sizeof(unsigned int), n_of_int, fp_in);               //Lendo uma �nica vez o arquivo e armazenando os dados em um vetor.
    desinvert(vector, n_of_int);                                        //Chamando a fun��o que desinverte o vetor.

    select = fgetc(stdin);  //Leitura do teclado e atribui��o do que foi lido a uma var�vel que ser� utilizada para selecionar qual opera��o a ser feita.
    getchar();              //Limpeza do buffer do teclado.


    switch(select){         //Criei esse switch para selecionar a partir de select a opera��o que ser� realizada.
    case '1':
        map(vector, file_name, n_of_int);   //Caso seja selecionada essa op��o, chamo a fun��o que mapeia os d�gitos.
        break;
    case '2':
        descript(vector, n_of_int);         //Caso seja selecionada essa op��o, chamo a fun��o que descriptografa a mensagem.
        printf("%s\n", (char *) vector);    //Impress�o da mensagem descriptografada.
        break;

    case '3':
        descript(vector, n_of_int);         //Caso seja selecionada essa op��o, chamo a fun��o que descriptografa a mensagem;
        count(vector);                      // E logo em seguida a fun��o que conta o n�mero de ocorr�ncias de uma string.
    break;
    }

    free(vector);       //Libera��o da mem�ria utilizada para armazenar o vetor.
    free(file_name);    //Libera��o da mem�ria utilizad para armazenar o nome do arquivo.
    fclose(fp_in);      //Fechando o arquivo.

return 0;
}
