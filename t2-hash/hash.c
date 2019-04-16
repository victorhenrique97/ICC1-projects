// Vh

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

    int a, i, j, k;
    int value, dados;
    int *counter;
    int **pp;



    scanf("%d", &k); //Leitura da chave
    scanf("%d", &dados); // Leitura do n�mero de valores a serem digitados


    pp = (int **) calloc(k, sizeof(int *)); // aloca��o do ponteiro duplo
    counter = (int *) calloc(k, sizeof(int)); /* aloca��o do ponteiro counter que ser� utilizado na aloca��o de espa�os com o realloc.
    Utilizei calloc nesse caso, e aloquei o tamanho de k, pois o n�mero de ponteiros que criarei ser� o mesmo n�mero da chave k.*/

    for(i=0; i<dados; i++){
        scanf("%d", &value);
        a = value % k; // o 'a' recebe o mod da divis�o por k.
        pp[a] = (int *) realloc(pp[a], sizeof(int)*(counter[a]+1)); /* Estou fazendo uma aloca��o dinamica para onde o ponteiro duplo aponta, sendo que
        esse [a] representa a posi��o na qual ser� feita a realoca��o. */
        pp[a][counter[a]++] = value;// o ponteiro duplo na posi��o a, aponta para outro ponteiro, onde o contador[a] recebe o valor e � incrementado.
    }

    for(i=0; i<k; i++){
        printf("%d:",i); //imprimo o i que ser� as colunas que conter� os valores de 0 at� k-1.
        for(j=0; j<counter[i]; j++){
            printf(" %d", pp[i][j]); // dentro da coluna i acima, percorro os elementos contidos na linha e imprimo-os.
        }
        printf("\n"); // ao sair do primeiro for imprimo uma quebra de linha
    }

    for(i=0; i<k; i++){
        free(pp[i]); //libera��o dos ponteiros para o qual o ponteiro duplo aponta
     }

    free(counter); //libera��o do ponteiro counter
    free(pp); //libera��o do ponteiro duplo

return 0;
}
