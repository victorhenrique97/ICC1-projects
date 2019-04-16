// Vh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//----------------------text------------------------------------------

/* Criei esta função para fazer a leitura do teclado e armazenar os 'n'
caracteres na memória heap e retornar um ponteiro para a main. */

 char *text(int n){

     char caractere;
     char *text;
     int counter = 0;

      text = (char *) calloc((n+1), sizeof(char));

      do{
            caractere = fgetc(stdin);
            text[counter++] = caractere;
            n--;
        }
     while(n>0);

        text[counter] = '\0';

 return text;
 }

//------------------cifracesar----------------------------------

/* criei esta função para caso seja selecionado esta cifra,
ela codifique a mensagem, aloque na heap e retorne um ponteiro
para a main. */

  char* cifracesar (int n, char *string){

    int k;
    char *codified;
    int counter;

      codified = (char *) calloc((n+1), sizeof(char));

      scanf("%d", &k);

    for(counter =0; counter<strlen(string); counter++){

      if(string[counter]>= 65 && string[counter]<=90){ //caso o caractere seja maiúsculo passa pela conversão

        codified[counter] = (string[counter]-65+k)%26; //subtraio 65 para trabalhar com A valendo zero até Z valendo 25, somo ao k e uso mod para retornar o resto da divisão por 26(letras do alfabeto)
        codified[counter] = codified[counter]+65; // somo 65 para que a letra receba o valor correspondente na tabela ASCII (ex: A = 0+65 = 65, B= 1+65 = 66 ...)
       }

      else{codified[counter] = string[counter];} // caso não seja maiúsculo, não é convertido
    }
     codified[counter] = '\0';

return codified;
 }

 //---------------------cifravegenere------------------------

 /* criei essa função para caso seja selecionado esta cifra,
ela codifique a mensagem, aloque na heap e retorne um ponteiro
para a main. */

  char* cifravegenere (int n, char *string){


      char *codified;
      char *chave;
      int i=0;
      int counter;

        codified = (char *) calloc((n+1), sizeof(char));

         scanf("%d\n", &n);
         chave = text(n);

       for(counter=0; counter<strlen(string); counter++){

       if(string[counter]>= 65 && string[counter]<=90){ //caso o caractere seja maiúsculo passa pela conversão

          codified[counter] = ((string[counter]-65) + (chave[i]-65))%26; //subtraio 65 tanto da string quanto da chave para trabalhar com valores entre 0 e 25, depois retorno o resto da divisão por 26(letras do alfabeto)
          codified[counter] = codified[counter]+65; // somo 65 para que a letra receba o valor correspondente na tabela ASCII (ex: A = 0+65 = 65, B= 1+65 = 66 ...)

         if(i<strlen(chave)-1){i++;}
         else{i=0;} // caso a chave seja menor que a mensagem, a chave precisa voltar para o ínicio

        }
       else{codified[counter]=string[counter];} // caso não seja maiúsculo, não é convertido
      }
        codified[counter] = '\0';

return codified;
  }
//-----------------------main--------------------------------

 int main(int argc, char *argv[]){

     int n, op;
     char *string;
     char *cripted;


     scanf("%d\n", &n);
     string = text(n);
     scanf("%d\n", &op);


    if(op == 1){cripted = cifracesar(n, string);
                printf("%s\n", cripted);}

    if(op == 2){cripted = cifravegenere(n, string);
                printf("%s\n", cripted);}


    free(string);
    free(cripted);
 return 0;
 }
