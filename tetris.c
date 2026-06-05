#include<stdio.h>
#include<stdlib.h> 
#include<time.h>

typedef struct{      //struct das Peças com nome e id 
	char nome;
	int id;
} Peca;

#define MAX 5           //definindo o max como 5 

typedef struct{             //struct da fila
	Peca itens[MAX];
	int inicio;
	int fim;
	int total;
} Fila;

void inicializarFila(Fila *f){    //função para inicializar a fila zerada
	f -> inicio = 0;
	f -> fim = 0;
	f -> total = 0;
}
int filaCheia(Fila *f){      //faz a verificação apra ver se a fila esta com todos os indices ocupados
	return f -> total == MAX;
}
int filaVazia(Fila *f){       //verifica se a lista esta vazia 
	return f-> total == 0;
}

void inserir(Fila *f, Peca p){       //função para inserir ou ENQUEUE
	if (filaCheia(f)){
		printf("\nFila cheia. Nao e possivel inserir.\n");
		return;
	}
	f -> itens[f->fim] = p;
	f -> fim = (f -> fim+1) % MAX;
	f -> total++;
}
int proximoId = 0;       //inicializando a varivel referente ao id com o valor 0
Peca gerarPeca(){
	Peca p;
	char tipo[] = {'I','O','T','L'};    //char tipo (com os tipos de "letras/peças" que serao geradas)
	p.nome = tipo[rand() % 4];     //randomizando as letras com rand, %4 pois são 4 elementos
	p.id = proximoId ++;
	return p;                    //retornando para variavel p o tipo gerado (letras I ou O ou T ou L)
	
}
void mostrarFila(Fila *f){
	printf("\nFila de Pecas:\n");
	int i = f->inicio;
	for (int count = 0; count < f->total; count++){
		printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
		i = (i+1) % MAX;
	}
	printf("\n");
}

void remover(Fila *f){               //função de remoção da peça no caso a peça do inicio (fila FIFO - first in first out)
    if(filaVazia(f))
    {
        printf("\nFila vazia!\n");
        return;
    }
	Peca removida = f -> itens[f->inicio];
	printf("Peca jogada: %c %d\n", removida.nome, removida.id);
	f->inicio = (f->inicio + 1) % MAX;
	f->total--;
}

int main(){
	Fila f;
	inicializarFila(&f);      //inicializa a fila
	srand(time(NULL));      // para não sair sempre com a mesma sequencia 
	for (int i = 0 ; i < MAX ; i++){     //esse laço de repetição vai ate MAX ou seja 5 gerando 5 peças
		inserir(&f, gerarPeca());     //cria uma peça aleatoria e insere na fila 
	}

	printf("Inicio do jogo, voce tem as seguintes pecas: \n");
	mostrarFila(&f);
	int opcao;
	do{
		printf("\n======= Menu =======\n");
		printf("1- Jogar peca\n");
		printf("2- Inserir nova peca\n");
		printf("0- Sair\n");
		printf("Digite a opcao desejada: ");
		scanf("%d", &opcao);
		switch(opcao){
		case 1: 
			remover(&f);
			mostrarFila(&f);
			break;
		case 2:
			inserir(&f, gerarPeca());
			mostrarFila(&f);
			break;
		case 0:
			printf("Saindo do programa...");
			break;
		default:
            printf("Opcao invalida!\n");
	}			
	} while(opcao != 0);
	
	return 0;
}
