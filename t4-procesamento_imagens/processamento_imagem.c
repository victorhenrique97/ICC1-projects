#include <stdlib.h>
#include <stdio.h>

#define ENTER 10
//----------------------------------------------------------------------------------------//
/*Criação de uma struct para armazenar o número mágico, número de colunas e linhas
 da matriz e o valor máximo que determinado pixel pode receber.*/

typedef struct{
	
	char *magic_number;
	int col, row;
	int max_value;

}hfile;
//--------------------------------------------------------------------------------//
/*Função criada para a leitura de alguma string a partir de um arquivo.*/
char *readfromfile(FILE *fp){
	
	char *string = NULL;
	char letter;
	int counter = 0;

	do{
		letter = fgetc(fp);
		string = (char *) realloc(string, sizeof(char)*(counter+1));
		string[counter++] = letter;
	} while(letter!= ENTER);
	string[counter-1] = '\0';

return string;
	
}
//---------------------------------------------------------------------------------//
/*Função criada para a alocar e zerar os elementos de uma matriz.*/
float **calloc_matrix(int row, int col){

	float **matrix;
	int i;

	matrix = (float **) calloc(row, sizeof(float*));

	for(i=0; i<row; i++)
		matrix[i] = (float *) calloc(col, sizeof(float));

return matrix;
}
//-------------------------------------------------------------------------------------------//
/* Função criada para liberar a memória heap que foi alocada por alguma matriz */
void matrix_free(float **matrix, int row){

	int i;

	for(i=0; i<row; i++)
		free(matrix[i]);

	free(matrix);

}
//---------------------------------------------------------------------------------------------//
/* Função Criada para a impressão da matriz na tela */
void print_matrix(float **matrix, int row, int col){
	
	int i, j;

	for(i=0; i<row; i++){
		for(j=0; j<col; j++)
			printf("%.f ",matrix[i][j]);
		printf("\n");
	}
}
//--------------------------------------------------------------------------------------------//
/* Função criada para a impressão do cabeçalho da imagem */
void print_headfile(hfile headfile){

	printf("%s\n", headfile.magic_number);
	printf("%d %d\n", headfile.col, headfile.row);
	printf("%d\n", headfile.max_value);

}
//-------------------------------------------------------------------------------------------//
/*Função criada para a normalização dos piexels uma vez que podem assumir valores maiores que
  v_max*/
void normalize(float **matrix, int row, int col, int v_max){

	int i, j;	
	int max = 0;
	int min = 0;

	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			if(matrix[i][j]>max) max = matrix[i][j]; // -> descobrindo o valor máximo após a concatenação
	min = max;

	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			if(matrix[i][j]<min) min = matrix[i][j]; // -> descobrindo o valor mínimo após a concatenação

	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			matrix[i][j] = (int) (v_max*(matrix[i][j] - min)/(max - min)); //-> normalizando e convertendo para inteiro através de um cast

}
//------------------------------------------------------------------------------------------//
/*Função criada para multiplicação de um elemento da  matriz por outro diametralmente oposto*/
float multiplication(float **matrix, float **matrix2, int dim){
		
	int res = 0;
	int i, j, k, l;


	for(i=0, j=dim-1; i<dim; i++, j--)
		for(k=0, l=dim-1; k<dim; k++, l--)
			res += matrix[i][k] * matrix2[j][l]; // -> ex: multiplico o elemento a00 por a22, a01 por a a21 ...
		
return res;
}
//-----------------------------------------------------------------------------------------//
/*Função criada para a concatenação da imagem (aplicação de uma mascara) */
void filter (float **matrix, int row, int col, float **mask, int dim){

	float **matrix_ext;
	int i, j, k, l;
	float **matrix_red;


	matrix_ext = calloc_matrix(row+(2*(dim/2)), col+(2*(dim/2))); // -> alocação da matriz com os zeros adicionais nas extremidades.
	matrix_red = calloc_matrix(dim, dim); 			      // -> alocação da matriz quadrada para a realização da multiplicação termo a termo oposto.

	for(i=dim/2; i<row+(dim/2); i++)
		for(j=dim/2; j<col+(dim/2); j++)
			matrix_ext[i][j] = matrix[i-(dim/2)][j-(dim/2)]; //-> preencho os elemetos centrais com os elementos da matriz base(imagem).

	for(i=0; i<=row+(2*(dim/2)-dim); i++)
		for(j=0; j<=col+(2*(dim/2)-dim); j++){
			for(k=i; k<dim+i; k++)
				for(l=j; l<dim+j; l++)
					matrix_red[k-i][l-j] = matrix_ext[k][l]; //-> preencho a matriz quadrada para a multiplicação.
				
			matrix[i][j] = (int) multiplication(mask, matrix_red, dim); //-> multiplico e armazeno o resultado na matriz base(imagem).
		}


	for(i=0; i<dim; i++)
		free(matrix_red[i]);
	for(i=0; i<row+(2*(dim/2)); i++)
		free(matrix_ext[i]);
	free(matrix_ext);
	free(matrix_red);

}

//-------------------------------------------------------------------------------------------//
/*Função criada para leitura de dados de um arquivo e armanezar na matriz*/
void read_matrix (float **matrix, FILE *fp, int row, int col){
	
	int i, j;

	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			fscanf(fp, "%f", &matrix[i][j]); 
	
}


//---------------------------------------------------------------------------------------------//
/* Função criada para a realização da operação 2 (concatenação) */
void operation2 (float **matrix, int row, int col, int max){

	FILE *mask = NULL;
	char *mask_name;
	float **mask_matrix;
	int dim;

	        mask_name = readfromfile(stdin); 
		mask = fopen(mask_name, "r");
		fscanf(mask, "%d%*c" , &dim);
		mask_matrix = calloc_matrix(dim, dim);
		read_matrix(mask_matrix, mask, dim, dim); 	// -> leitura da matriz
		filter(matrix, row, col, mask_matrix, dim); 	// -> concatenação matriz/máscara
		normalize(matrix, row, col, max);     		// -> normalização dos pixels

	
	matrix_free(mask_matrix, dim);
	free(mask_name);
	fclose(mask);
}
//----------------------------------------------------------------------------------------------//
/*Função criada para realçar(aplicar negativo) a imagem. */
void realce(float **matrix, int row, int col, int max){
	
	int i, j;

	for(i=0; i<row; i++)
		for(j=0; j<col; j++)
			matrix[i][j] = (max - matrix[i][j]); // -> o pixel é substituido pelo valor máximo menos o valor original do pixel
}
//---------------------------------------------------------------------------------------------//
/*Função criada para armazenar o cabeçalho da imagem em uma struct*/
hfile read_headfile(FILE *fp){

	hfile headfile;
	char c;
	char *string = NULL;
	
	
	headfile.magic_number = readfromfile(fp); 		//-> leitura do número mágico
	c = fgetc(fp);						
	if(c == '#') string = readfromfile(fp);			//-> caso o caractere seja uma hastag leio o resto do comentário descarto-o
	else ungetc(c, fp);					//-> caso não seja, retorno uma posição para pegar o numero de colunas que há na imagem
	fscanf(fp,"%d %d %d", &headfile.col, &headfile.row, &headfile.max_value); //-> pego o número de colunas, linhas e valor máximo

	if(string!=NULL) free(string);				//-> descarto se houver o comentário

return headfile;
}

//=============================================================================================//
int main(int argc, char *argv[]){
	
	FILE *fp = NULL;
	char *file_name;
	hfile headfile;
	float **matrix;
	int op;

	scanf("%d%*c", &op);
	file_name = readfromfile(stdin);
	fp = fopen(file_name, "r");
	
	headfile = read_headfile(fp);

	matrix = calloc_matrix(headfile.row, headfile.col); 
	read_matrix(matrix, fp, headfile.row, headfile.col); // -> leitura da matriz

	switch(op){
		case 1: realce(matrix, headfile.row, headfile.col, headfile.max_value);	//-> aplicação do negativo sobre a imagem	 
		break;
		case 2: operation2(matrix, headfile.row, headfile.col, headfile.max_value); //-> concatenação da imagem
		break;
	}

	print_headfile(headfile);				// -> impressão do cabeçalho
	print_matrix(matrix, headfile.row, headfile.col);	// -> impressão da matriz
	matrix_free(matrix, headfile.row);
	free(file_name);
	free(headfile.magic_number);
	fclose(fp);

return 0;
}

