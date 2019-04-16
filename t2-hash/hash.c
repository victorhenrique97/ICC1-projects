// Vh

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

    int a, i, j, k;
    int value, dados;
    int *counter;
    int **pp;



    scanf("%d", &k); //Leitura da chave
    scanf("%d", &dados); // Leitura do número de valores a serem digitados


    pp = (int **) calloc(k, sizeof(int *)); // alocação do ponteiro duplo
    counter = (int *) calloc(k, sizeof(int)); /* alocação do ponteiro counter que será utilizado na alocação de espaços com o realloc.
    Utilizei calloc nesse caso, e aloquei o tamanho de k, pois o número de ponteiros que criarei será o mesmo número da chave k.*/

    for(i=0; i<dados; i++){
        scanf("%d", &value);
        a = value % k; // o 'a' recebe o mod da divisão por k.
        pp[a] = (int *) realloc(pp[a], sizeof(int)*(counter[a]+1)); /* Estou fazendo uma alocação dinamica para onde o ponteiro duplo aponta, sendo que
        esse [a] representa a posição na qual será feita a realocação. */
        pp[a][counter[a]++] = value;// o ponteiro duplo na posição a, aponta para outro ponteiro, onde o contador[a] recebe o valor e é incrementado.
    }

    for(i=0; i<k; i++){
        printf("%d:",i); //imprimo o i que será as colunas que conterá os valores de 0 até k-1.
        for(j=0; j<counter[i]; j++){
            printf(" %d", pp[i][j]); // dentro da coluna i acima, percorro os elementos contidos na linha e imprimo-os.
        }
        printf("\n"); // ao sair do primeiro for imprimo uma quebra de linha
    }

    for(i=0; i<k; i++){
        free(pp[i]); //liberação dos ponteiros para o qual o ponteiro duplo aponta
     }

    free(counter); //liberação do ponteiro counter
    free(pp); //liberação do ponteiro duplo

return 0;
}
