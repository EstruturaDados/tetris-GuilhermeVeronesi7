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

typedef struct{
	Peca itens[MAX];
	int topo;
} Pilha;

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

void inicializarPilha(Pilha *p){    //função de inicializaçao da pilha 
	p->topo = -1;                  //topo da pilha iniciando em -1 quer dizer que a pilha esta vazia
}

int pilhaVazia(Pilha *p){        //verifica se a pilha esta vazia
    return p->topo == -1;
}

int pilhaCheia(Pilha *p){       //verifica se a pilha esta cheia
    return p->topo == MAX - 1;
}

void push(Pilha *p, Peca item){
	if (pilhaCheia(p)){
		printf("Pilha Cheia! Nao e possivel inserir.\n");
		return;
	}
	p->topo++;
	p->itens[p->topo] = item;
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
void mostrarPilha(Pilha *p){
	printf("Pilha (Topo -> Base): \n");
	if (pilhaVazia(p)){
    printf("Pilha vazia.\n");
    return;
}
	for (int i= p->topo; i>=0; i--){
	printf("[%c %d]\n", p->itens[i].nome, p->itens[i].id);
	}
	printf("\n");
}

Peca pop(Pilha *p){
	Peca removida;
	if (pilhaVazia(p)){
		printf("Pilha vazia! Nao e possivel remover.\n");
		removida.nome = ' ';
		removida.id = -1;
		return removida;
	}
	removida = p ->itens[p->topo];
	p->topo--;
	return removida;
}

Peca remover(Fila *f){               //função de remoção da peça no caso a peça do inicio (fila FIFO - first in first out)
	Peca removida;                  //criando uma variavel para armazenar a peça que sera removida (caixinha temporaria)
    if(filaVazia(f))
    {
        printf("\nFila vazia!\n");
        removida.nome= ' ';
        removida.id= -1;
        return removida;
    }
	removida = f -> itens[f->inicio];
	printf("Peca escolhida: %c %d\n", removida.nome, removida.id);
	f->inicio = (f->inicio + 1) % MAX;
	f->total--;
	return removida;
}

int main(){
	Fila f;
	Pilha p;
	inicializarFila(&f);      //inicializa a fila
	inicializarPilha(&p);    //inicializa a pilha
	srand(time(NULL));      // para não sair sempre com a mesma sequencia 
	for (int i = 0 ; i < MAX ; i++){     //esse laço de repetição vai ate MAX ou seja 5 gerando 5 peças
		inserir(&f, gerarPeca());     //cria uma peça aleatoria e insere na fila 
	}

	printf("Inicio do jogo, voce tem as seguintes pecas: \n");
	mostrarFila(&f);
	int opcao;
	do{
		printf("\n========= Menu =========\n");
		printf("1- Jogar peca\n");
		printf("2- Reservar peca\n");
		printf("3- Usar peca reservada\n");
		printf("0- Sair\n");
		printf("========================\n");
		printf("Digite a opcao desejada: ");
		scanf("%d", &opcao);
		switch(opcao){
		case 1: 
			remover(&f);
			inserir(&f, gerarPeca());
			mostrarFila(&f);
			mostrarPilha(&p);
			break;
		case 2:
		{
    		if (pilhaCheia(&p))
    		{
        		printf("Pilha cheia!\n");
    		}	
    		else
    		{
        		Peca x = remover(&f);
        		push(&p, x);
        		inserir(&f, gerarPeca());
	    	}
			mostrarFila(&f);
	   		mostrarPilha(&p);
	   		break;
		}
		case 3:
		{
			if(pilhaVazia(&p)){
				printf("Nao ha pecas reservadas!\n");
			}
			else{
	    		Peca x = pop(&p);
	    		printf("Usou peca reservada: %c %d\n", x.nome, x.id);
	    	}
	
	    	mostrarFila(&f);
	    	mostrarPilha(&p);
	    	break;
		}		
		case 0:
			printf("Saindo do programa...");
			break;
		default:
            printf("Opcao invalida!\n");
	}			
	} while(opcao != 0);
	
	return 0;
}
