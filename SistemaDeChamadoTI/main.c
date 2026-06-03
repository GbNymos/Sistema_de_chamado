
/* =========================================================
SISTEMA DE CHAMADOS DE TI
=========================================================
Este sistema utiliza duas estruturas de dados:

FILA (FIFO - First In, First Out)
---------------------------------
A fila armazena os chamados que aguardam atendimento.
Cada novo chamado é inserido no final da fila e o
primeiro chamado cadastrado é o primeiro a ser atendido.

PILHA (LIFO - Last In, First Out)
---------------------------------
A pilha armazena o histórico dos chamados atendidos.
Quando um chamado é atendido, ele é removido da fila
e inserido no topo da pilha. Assim, o último chamado
atendido é exibido primeiro no histórico.

REFERÊNCIAS: 
W3Schools. C Tutorial. Disponível em: https://www.w3schools.com/c/
Mais de 15 ideias empolgantes de projetos em C com código-fonte :https://www-interviewbit-com.translate.goog/blog/c-projects/?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt&_x_tr_pto=tc
IA utilizada apenas como suporte: Copilot (Microsoft)
=========================================================
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char nome[50];
    char problema[100];
} Chamado;

// FILA
Chamado fila[MAX];
int inicio = 0;
int fim = -1;

// PILHA
Chamado pilha[MAX];
int topo = -1;


// LER INTEIRO
int lerInteiro() {
    char entrada[20];
    fgets(entrada, sizeof(entrada), stdin);
    return atoi(entrada);
}


// VERIFICAR ID REPETIDO
int existeID(int id) {

    for(int i = inicio; i <= fim; i++) {
        if(fila[i].id == id)
            return 1;
    }

    for(int i = 0; i <= topo; i++) {
        if(pilha[i].id == id)
            return 1;
    }

    return 0;
}


// ABRIR CHAMADO
void abrirChamado() {

    if(fim == MAX - 1) {
        printf("\nFila cheia!\n");
        return;
    }

    Chamado c;

    do {
        printf("\nID do chamado: ");
        c.id = lerInteiro();

        if(existeID(c.id))
            printf("ID ja cadastrado!\n");

    } while(existeID(c.id));

    printf("Nome do solicitante: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Descricao do problema: ");
    fgets(c.problema, sizeof(c.problema), stdin);
    c.problema[strcspn(c.problema, "\n")] = '\0';

    fila[++fim] = c;

    printf("\nChamado cadastrado com sucesso!\n");
}


// VISUALIZAR FILA
void visualizarFila() {

    if(inicio > fim) {
        printf("\nNao ha chamados na fila.\n");
        return;
    }

    printf("\n===== FILA DE CHAMADOS =====\n");

    for(int i = inicio; i <= fim; i++) {

        printf("\nID: %d", fila[i].id);
        printf("\nSolicitante: %s", fila[i].nome);
        printf("\nProblema: %s\n", fila[i].problema);
    }
}


// ATENDER CHAMADO
void atenderChamado() {

    if(inicio > fim) {
        printf("\nNenhum chamado para atender.\n");
        return;
    }

    Chamado atendido = fila[inicio++];

    if(topo < MAX - 1)
        pilha[++topo] = atendido;

    printf("\nChamado atendido com sucesso!");
    printf("\nID: %d", atendido.id);
    printf("\nSolicitante: %s\n", atendido.nome);
}


// HISTÓRICO
void visualizarHistorico() {

    if(topo == -1) {
        printf("\nNenhum chamado foi atendido ainda.\n");
        return;
    }

    printf("\n===== HISTORICO =====\n");

    for(int i = topo; i >= 0; i--) {

        printf("\nID: %d", pilha[i].id);
        printf("\nSolicitante: %s", pilha[i].nome);
        printf("\nProblema: %s\n", pilha[i].problema);
    }
}

// PESQUISAR CHAMADO
void pesquisarChamado() {

    int idBusca;
    int encontrado = 0;

    printf("\nDigite o ID do chamado: ");
    idBusca = lerInteiro();

    for(int i = inicio; i <= fim; i++) {

        if(fila[i].id == idBusca) {

            printf("\nChamado encontrado na FILA");
            printf("\nSolicitante: %s", fila[i].nome);
            printf("\nProblema: %s\n", fila[i].problema);

            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {

        for(int i = topo; i >= 0; i--) {

            if(pilha[i].id == idBusca) {

                printf("\nChamado encontrado no HISTORICO");
                printf("\nSolicitante: %s", pilha[i].nome);
                printf("\nProblema: %s\n", pilha[i].problema);

                encontrado = 1;
                break;
            }
        }
    }

    if(!encontrado)
        printf("\nChamado nao encontrado.\n");
}


// MENU DE ESCOLHAS
int main() {

    int opcao;

    do {

        printf("\n===============================");
        printf("\n SISTEMA DE CHAMADOS DE TI");
        printf("\n===============================");

        printf("\n1 - Abrir chamado");
        printf("\n2 - Visualizar fila");
        printf("\n3 - Atender chamado");
        printf("\n4 - Visualizar historico");
        printf("\n5 - Pesquisar chamado");
        printf("\n6 - Sair");

        printf("\nOpcao: ");
        opcao = lerInteiro();

        switch(opcao) {

            case 1:
                abrirChamado();
                break;

            case 2:
                visualizarFila();
                break;

            case 3:
                atenderChamado();
                break;

            case 4:
                visualizarHistorico();
                break;

            case 5:
                pesquisarChamado();
                break;

            case 6:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 6);

    return 0;
}