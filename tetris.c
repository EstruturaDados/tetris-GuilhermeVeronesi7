#include<stdio.h>
#include<stdlib.h> 
#include<time.h>

typedef struct{      //struct das Peças com nome e id 
	char nome;
	int id;
} Peca;

#define MAX_FILA 5           //definindo o max como 5 
#define MAX_PILHA 3         //definindo o max pilha como 3

typedef struct{             //struct da fila
	Peca itens[MAX_FILA];
	int inicio;
	int fim;
	int total;
} Fila;

typedef struct{
	Peca itens[MAX_PILHA];
	int topo;
} Pilha;

void inicializarFila(Fila *f){    //função para inicializar a fila zerada
	f -> inicio = 0;
	f -> fim = 0;
	f -> total = 0;
}
int filaCheia(Fila *f){      //faz a verificação apra ver se a fila esta com todos os indices ocupados
	return f -> total == MAX_FILA;
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
    return p->topo == MAX_PILHA - 1;
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
	f -> fim = (f -> fim+1) % MAX_FILA;
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
		i = (i+1) % MAX_FILA;
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

void mostrarEstado(Fila *f, Pilha *p){
	printf("\n======= Estado Atual =======\n");
	mostrarFila(f);
	printf("\n");
	mostrarPilha(p);
	printf("\n============================\n");	
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
	f->inicio = (f->inicio + 1) % MAX_FILA;
	f->total--;
	return removida;
}

int main(){
	Fila f;
	Pilha p;
	inicializarFila(&f);      //inicializa a fila
	inicializarPilha(&p);    //inicializa a pilha
	srand(time(NULL));      // para não sair sempre com a mesma sequencia 
	for (int i = 0 ; i < MAX_FILA ; i++){     //esse laço de repetição vai ate MAX ou seja 5 gerando 5 peças
		inserir(&f, gerarPeca());     //cria uma peça aleatoria e insere na fila 
	}

	printf("Inicio do jogo, voce tem as seguintes pecas: \n");
	mostrarEstado(&f, &p);
	int opcao;
	do{
		printf("\n========= Menu =========\n");
		printf("1- Jogar peca da frente da fila\n");
		printf("2- Enviar peca da fila para a pilha (reserva)\n");
		printf("3- Usar peca da reserva (pilha)\n");
		printf("4- Trocar peca da frente da fila com o topo da pilha\n");
		printf("5- Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
		printf("0- Sair\n");
		printf("========================\n");
		printf("Digite a opcao desejada: ");
		scanf("%d", &opcao);
		switch(opcao){
		case 1: 
			remover(&f);
			inserir(&f, gerarPeca());
			mostrarEstado(&f, &p);
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
			mostrarEstado(&f, &p);
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
	    	mostrarEstado(&f, &p);
	    	break;
		}	
		case 4:
		{
			if (filaVazia(&f) || pilhaVazia(&p)){
				printf("Nao e possivel realizar a troca!\n");
			}
			else{
				Peca temp;
				temp = f.itens[f.inicio];
				f.itens[f.inicio] = p.itens[p.topo];
				p.itens[p.topo] = temp;
				printf("Troca realizada com sucesso!\n"); 
			}
			mostrarEstado(&f, &p);
			break;
		}
		case 5: {
			Peca filaTemp[3];
			Peca pilhaTemp[3];
			int pos = f.inicio;                  //variavel auxiliar de posição (ajuda na questão da fila circular nem sempre começar no 0)
			if (f.total < 3 || p.topo < 2) {
				printf("Nao e possivel realizar a troca. Fila ou pilha possuem menos de 3 elementos.\n");
			}
			else{
				for (int i = 0; i < 3; i++)
				{
					filaTemp[i] = f.itens[pos];      //copia o elemento atual da fila
					pos = (pos + 1) % MAX_FILA;      //avança na fila de forma circular
				}
				pilhaTemp[0] = p.itens[p.topo];                //armazena na pilhaTemp (variavel temperoria) o topo da pilha
				pilhaTemp[1] = p.itens[p.topo -1];             //p.topo-1 pois é LIFO (last in first out)
				pilhaTemp[2] = p.itens[p.topo -2];
				pos = f.inicio;
				for (int i = 0; i < 3; i++)
				{
					f.itens[pos] = pilhaTemp[i];
					pos =(pos + 1) % MAX_FILA;
				}
				p.itens[p.topo] = filaTemp[2];
				p.itens[p.topo -1] = filaTemp[1];
				p.itens[p.topo -2] = filaTemp[0];
				printf("Troca multipla realizada com sucesso!\n");
				mostrarEstado(&f, &p);
			}
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
