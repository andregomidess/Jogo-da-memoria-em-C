// Protótipo de um Jogo da Memória criado pelos alunos André Lucca Gomides de Lima, Elisa Faria Almeida e Enzo Oliveira Vizotto//

// Disciplina: Fundamentos da Programação (COM110) - 2021.1


// Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


// Registro para armazenar os dados dos jogadores
struct jogadores {

	char nome[100];
	int pontuacao;
  int erros;
	float tempo_gasto;

};

// Função do menu
int menu() {

int m;

// Condição para imprimir o menu novamente caso o número digitado seja diferente de 1 e 2.
	do {

		printf("\n======================= JOGO DA MEMÓRIA ==========================\n"); 
		printf ("\nCOMO JOGAR: o jogador deve escolher duas posições dentre as 10 disponíveis, sendo elas preenchidas por pares de 5 números. O objetivo do jogo é obter dois números iguais, formando todos os 5 pares possíveis.\n"); 
		printf("\n=====================================================================\n");
		printf("\n************ MENU *************\n");
		printf ("\nDigite [1] para jogar \n");
		printf("Digite [2] para sair\n ");
		printf("\nOpção escolhida: ");
		scanf("%d", &m);
		system ("clear");

	} while ((m < 1) || (m > 2));
  
	return m;
}

// Função para embaralhar o vetor
void mudar_posicao(int *vet, int tamanho_vetor) {
  
	int i, aux, r;

	for (i = 0; i < tamanho_vetor; i++) {
		r = rand() % tamanho_vetor;
		aux = vet[i];
		vet[i] = vet[r];
		vet[r] = aux;
	}
} 

// Função contador para limpar a tela
void contador (int x) {

	int s = 0;
	x = 5;
  
	do {
		printf ("\n%d...",x);
		fflush(stdout);
		sleep (1);
		x--;
		if (x == 0){
			system ("clear");
			break;
		}
	} while (s==0);

}	

// Função main
int main (void) { 

// Declaração das variáveis
int  i, j, num1, num2, acertos, cont, op, tentativas, k;
int escolha[10] = {1,7,3,5,6,7,3,1,6,5};
char sim_nao;
struct jogadores jogador[10];
float tempo;
time_t t_ini, t_fim;

// Declaração de variável do tipo arquivo
FILE *pont_quadro;

//Abertura do arquivo "pont_quadro.txt"
pont_quadro = fopen ("pont_quadro.txt", "w");

fprintf (pont_quadro,"######## QUADRO DE PONTUAÇÃO #########\n\n");

// Função para gerar números aleatórios no vetor
srand(time(NULL));

//função para embaralhar o vetor
mudar_posicao(escolha, 10); 

//Atribuindo o retorno da função "menu" à váriável "op"
op = menu();

//condição para iniciar ou parar o jogo
switch (op){

case 1:

	// Laço for para contabilizar as rodadas
	for (k = 0; k < 10; k++) {
		tentativas = 3;
	 	acertos = 0;	
	 	system ("clear");
   		printf ("\nDigite o nome do jogador %d: ", k+1);
   		scanf (" %s", jogador[k].nome);
	  	t_ini = time(NULL);
 		
		 for (cont = 0; cont < 12; cont++) {  
			printf ("\nAcertos: %d", acertos);
			printf ("\nVocê tem %d tentativas", tentativas);
			
			tentativas--; 

 			printf("\nEscolha a primeira posição (de 1 a 10): ");
 			scanf("%d", &num1);
 			printf("Escolha a segunda posição (de 1 a 10): ");
 			scanf("%d", &num2);
 
			i = num1 - 1;
			j = num2 - 1;
			
			if (escolha[i] == escolha [j]) {
			printf("O número da %d° posição é: %d \nO número da %d° posição é: %d", num1, escolha[i], num2, escolha[j]);
			printf("\nVocê acertou!\n");
			acertos++;

			} else if (escolha[i] != escolha [j]) {

  			printf("O número da %d° posição é: %d \nO número da %d° posição é: %d", num1, escolha[i], num2, escolha[j]);
  			printf("\nUia, foi quase! Tente mais uma vez: \n");

  			}

			if (acertos == 5) {
			printf ("\nParabéns você acertou tudo!!");
			break;

			} else if (tentativas == 0) {
				printf ("\nSuas tentativas acabaram, tente jogar outra vez!!"); 
    		sleep(1);
				system ("clear");
				break;
		
			}
			//Função para contagem regressiva
			contador(5);
 		}

	t_fim = time(NULL);
	// Função para calcular a diferença de tempo
	tempo = difftime (t_fim, t_ini);
	printf ("\nTEMPO: %.2f seg", tempo);

	jogador[k].pontuacao = acertos;
	jogador[k].erros = 3 - acertos;
	jogador[k].tempo_gasto = tempo;

     // Confirmar se o arquivo foi gerado.
     if (pont_quadro == NULL){

       printf ("Erro ao gerar o quadro de pontuação.");
       return 1;

     } else {
      
      	fprintf (pont_quadro,"Jogador: %s \n",  jogador[k].nome);
      	fprintf (pont_quadro,"Acertos: %d \n", jogador[k].pontuacao);
      	fprintf (pont_quadro,"Erros: %d \n", jogador[k].erros);
				fprintf (pont_quadro,"Tempo gasto: %.2f seg \n\n", jogador[k].tempo_gasto);
     }

    // Perguntar para o usuário se ele deseja jogar novamente
	printf ("\nVocê deseja jogar novamente? [S/N] ");
	scanf (" %c", &sim_nao);
     
	if (sim_nao == 83 || sim_nao == 115)
	{
		continue;
	}

	if (sim_nao == 78 || sim_nao == 110){
		// fechando o arquivo
		fclose (pont_quadro);   
	
		printf ("OK, o jogo será finalizado!\n"); 
		sleep(1);
		system ("clear");

		FILE *arq;
		char Linha[9999];
		char *result;  	

		// Abre um arquivo TEXTO para LEITURA
		arq = fopen("pont_quadro.txt", "r");
		if (arq == NULL)  // Se houve erro na abertura
		{
			printf("Problemas na abertura do arquivo\n");
			return 1;
		}

		i = 1;
		while (!feof(arq))
		{			
			result = fgets(Linha, 100, arq);  
			if (result) {
				printf("%s", Linha);
			}

			i++;
		}
		fclose(arq);	

		return 0;
	}
	 	 
 }
 	
 case 2:

 break;

} 


  return 0; 
}