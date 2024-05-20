#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

// Definição do tamanho do labirinto
#define LINHAS 12
#define COLUNAS 12
#define LINHAS2 22
#define COLUNAS2 22
#define LINHAS3 42
#define COLUNAS3 42
#define MAX_INIMIGOS 5
// Declaração das variáveis globais
int jogadorX, jogadorY;
int chaveX, chaveY;
int portaX, portaY;
int botaoX, botaoY;
char labirinto[LINHAS][COLUNAS];
char labirinto2[LINHAS2][COLUNAS2];
char labirinto3[LINHAS3][COLUNAS3];
int possuichave = 0;
int fim1 = 0;
int fim2 = 0;
int fim3 = 0;
int espinhoX[15];
int espinhoY[15];
int vidas;
int eminemY2, eminemX2;
int eminemY3, eminemX3;
int portal1Y, portal1X;
int portal2Y, portal2X;
int pressbotao = 0;

// Função para inicializar o labirinto
void inicializarLabirinto() {
    // Preencher o labirinto com espaços em branco
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            if (i == 0 || i == LINHAS - 1 || j == 0 || j == COLUNAS - 1) {
                labirinto[i][j] = '*';
            } else {
                labirinto[i][j] = ' ';
            }
        }
    }
    // Colocar o jogador na posição inicial
    jogadorX = 1;
    jogadorY = 1;
    labirinto[jogadorY][jogadorX] = '&'; // '&' representa o jogador

    // Colocar a chave em uma posição aleatória
    srand(time(NULL));
    chaveX = rand() % (COLUNAS - 2) + 1;
    chaveY = rand() % (LINHAS - 2) + 1;
    labirinto[chaveY][chaveX] = '@'; // '@' representa a chave

    // Colocar a porta fechada em uma posição aleatória
    portaX = rand() % (COLUNAS - 2) + 1;
    portaY = rand() % (LINHAS - 2) + 1;
    labirinto[portaY][portaX] = 'D'; // 'D' representa a porta fechada
}

// Função para colocar os espinhos em posições aleatórias
void colocarEspinhos() {
    int num_espinhos = 15; // Defina o número desejado de espinhos
    int k;
    for (k = 0; k < num_espinhos; k++) {
        do {
            espinhoX[k] = rand() % (COLUNAS2 - 2) + 1;
            espinhoY[k] = rand() % (LINHAS2 - 2) + 1;
        } while (labirinto2[espinhoY[k]][espinhoX[k]] != ' '); // Garantir que o espinho é colocado em uma posição vazia
        labirinto2[espinhoY[k]][espinhoX[k]] = '#'; // '#' representa um espinho
        // Atualizar as coordenadas dos espinhos
    }
}

void colocarEspinhos2() {
    int num_espinhos = 40; // Defina o número desejado de espinhos
    int k;
    for (k = 0; k < num_espinhos; k++) {
        do {
            espinhoX[k] = rand() % (COLUNAS3 - 2) + 1;
            espinhoY[k] = rand() % (LINHAS3 - 2) + 1;
        } while (labirinto3[espinhoY[k]][espinhoX[k]] != ' '); // Garantir que o espinho é colocado em uma posição vazia
        labirinto3[espinhoY[k]][espinhoX[k]] = '#'; // '#' representa um espinho
        // Atualizar as coordenadas dos espinhos
    }
}
void recolocarEspinhos2() {
    int num_espinhos = 40; // Defina o número desejado de espinhos
    int k;
        for (k = 0; k < num_espinhos; k++) {
        do {
            espinhoX[k] = 0;
            espinhoY[k] = 0;
        } while (labirinto3[espinhoY[k]][espinhoX[k]] != ' '); // Garantir que o espinho é colocado em uma posição vazia
        labirinto3[espinhoY[k]][espinhoX[k]] = '*'; // '#' representa um espinho
        // Atualizar as coordenadas dos espinhos
    }
    for (k = 0; k < num_espinhos; k++) {
        do {
            espinhoX[k] = rand() % (COLUNAS3 - 2) + 1;
            espinhoY[k] = rand() % (LINHAS3 - 2) + 1;
        } while (labirinto3[espinhoY[k]][espinhoX[k]] != ' '); // Garantir que o espinho é colocado em uma posição vazia
        labirinto3[espinhoY[k]][espinhoX[k]] = '#'; // '#' representa um espinho
        // Atualizar as coordenadas dos espinhos
    }
}

// Função para inicializar o labirinto
void inicializarLabirinto2() {
    // Preencher o labirinto com espaços em branco
    int i, j;
    possuichave = 0;
    for (i = 0; i < LINHAS2; i++) {
        for (j = 0; j < COLUNAS2; j++) {
            if (i == 0 || i == LINHAS2 - 1 || j == 0 || j == COLUNAS2 - 1) {
                labirinto2[i][j] = '*';
            } else {
                labirinto2[i][j] = ' ';
            }
        }
    }
    // Colocar os espinhos
    colocarEspinhos();

    // Colocar o jogador na posição inicial
    jogadorX = 1;
    jogadorY = 1;
    labirinto2[jogadorY][jogadorX] = '&'; // '&' representa o jogador

    // Colocar a chave em uma posição aleatória, garantindo que não esteja entre os espinhos
    do {
        chaveX = rand() % (COLUNAS2 - 2) + 1;
        chaveY = rand() % (LINHAS2 - 2) + 1;
    } while (labirinto2[chaveY][chaveX] != ' ' || (chaveX == portaX && chaveY == portaY)); // Garantir que a chave está em uma posição vazia e não coincide com a posição da porta
    labirinto2[chaveY][chaveX] = '@'; // '@' representa a chave

    // Colocar a porta fechada em uma posição aleatória, garantindo que não esteja entre os espinhos e nem coincida com a posição da chave
    do {
        portaX = rand() % (COLUNAS2 - 2) + 1;
        portaY = rand() % (LINHAS2 - 2) + 1;
    } while (labirinto2[portaY][portaX] != ' ' || (portaX == chaveX && portaY == chaveY)); // Garantir que a porta está em uma posição vazia e não coincide com a posição da chave
    labirinto2[portaY][portaX] = 'D'; // 'D' representa a porta fechada

    // Colocar o inimigo em uma posição aleatória, garantindo que não esteja entre os espinhos, nem coincida com a posição da chave ou da porta
    do {
        eminemX2 = rand() % (COLUNAS2 - 2) + 1;
        eminemY2 = rand() % (LINHAS2 - 2) + 1;
    } while (labirinto2[eminemY2][eminemX2] != ' ' || (eminemX2 == chaveX && eminemY2 == chaveY) || (eminemX2 == portaX && eminemY2 == portaY)); // Garantir que o inimigo está em uma posição vazia e não coincide com a posição da chave ou da porta
    labirinto2[eminemY2][eminemX2] = 'X'; // 'X' representa o inimigo
    do {
        botaoX = rand() % (COLUNAS2 - 2) + 1;
        botaoY = rand() % (LINHAS2 - 2) + 1;
    } while (labirinto2[botaoY][botaoX] != ' ' || (botaoX == chaveX && botaoY == chaveY) || (botaoX == portaX && botaoY == portaY)); // Garantir que o inimigo está em uma posição vazia e não coincide com a posição da chave ou da porta
    labirinto2[botaoY][botaoX] = 'O'; // 'X' representa o inimigo
}

// Função para inicializar o terceiro labirinto
void reinicializarLabirinto3() {
    int i, j;
    for (i = 0; i < LINHAS3; i++) {
        for (j = 0; j < COLUNAS3; j++) {
                labirinto3[i][j] = ' ';
        }
    }
    // Preencher o segundo labirinto com espaços em branco
    for (i = 0; i < LINHAS3; i++) {
        for (j = 0; j < COLUNAS3; j++) {
			if (i == 0 || i == LINHAS3 -1 || j == 0 || j == COLUNAS3 -1 ) {
                labirinto3[i][j] = '*';
            } else {
                labirinto3[i][j] = ' ';
            }
        }
    }
    // Colocar os espinhos
    recolocarEspinhos2();
    
    labirinto3[botaoY][botaoX] = 'O';
    labirinto3[jogadorY][jogadorX] = '&';
    
    portal1X = 2;
    portal1Y = 39;
    labirinto3[portal1Y][portal1X] = '>';
    
    portal2X = 39;
    portal2Y = 2;
    labirinto3[portal2Y][portal2X] = '>';

    // Colocar a chave em uma posição aleatória, garantindo que não esteja entre os espinhos
    do {
        chaveX = rand() % (COLUNAS3 - 2) + 1;
        chaveY = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[chaveY][chaveX] != ' ' || (chaveX == portaX && chaveY == portaY) && labirinto3[chaveY][chaveX] != '&'); // Garantir que a chave está em uma posição vazia e não coincide com a posição da porta
    labirinto3[chaveY][chaveX] = '@'; // '@' representa a chave

    // Colocar a porta fechada em uma posição aleatória, garantindo que não esteja entre os espinhos e nem coincida com a posição da chave
    do {
        portaX = rand() % (COLUNAS3 - 2) + 1;
        portaY = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[portaY][portaX] != ' ' || (portaX == chaveX && portaY == chaveY) && labirinto3[chaveY][chaveX] != '&'); // Garantir que a porta está em uma posição vazia e não coincide com a posição da chave
    labirinto3[portaY][portaX] = 'D'; // 'D' representa a porta fechada

    // Colocar o inimigo em uma posição aleatória, garantindo que não esteja entre os espinhos, nem coincida com a posição da chave ou da porta
    do {
        eminemX3 = rand() % (COLUNAS3 - 2) + 1;
        eminemY3 = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[eminemY3][eminemX3] != ' ' || (eminemX3 == chaveX && eminemY3 == chaveY) || (eminemX3 == portaX && eminemY3 == portaY) && labirinto3[chaveY][chaveX] != '&'); // Garantir que o inimigo está em uma posição vazia e não coincide com a posição da chave ou da porta
    labirinto3[eminemY3][eminemX3] = 'V'; // 'V' representa o inimigo
}
void inicializarLabirinto3() {
    possuichave = 0;
    int i, j;
    // Preencher o segundo labirinto com espaços em branco
    for (i = 0; i < LINHAS3; i++) {
        for (j = 0; j < COLUNAS3; j++) {
            if (i == 0 || i == LINHAS3 -1 || j == 0 || j == COLUNAS3 -1 ) {
                labirinto3[i][j] = '*';
            } else {
                labirinto3[i][j] = ' ';
            }
        }
    }
    // Colocar os espinhos
    colocarEspinhos2();

    // Colocar o jogador na posição inicial
    jogadorX = 1;
    jogadorY = 1;
    labirinto3[jogadorY][jogadorX] = '&'; // '&' representa o jogador
    
    portal1X = 2;
    portal1Y = 39;
    labirinto3[portal1Y][portal1X] = '>';
    
    portal2X = 39;
    portal2Y = 2;
    labirinto3[portal2Y][portal2X] = '>';

    // Colocar a chave em uma posição aleatória, garantindo que não esteja entre os espinhos
    do {
        chaveX = rand() % (COLUNAS3 - 2) + 1;
        chaveY = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[chaveY][chaveX] != ' ' || (chaveX == portaX && chaveY == portaY)); // Garantir que a chave está em uma posição vazia e não coincide com a posição da porta
    labirinto3[chaveY][chaveX] = '@'; // '@' representa a chave

    // Colocar a porta fechada em uma posição aleatória, garantindo que não esteja entre os espinhos e nem coincida com a posição da chave
    do {
        portaX = rand() % (COLUNAS3 - 2) + 1;
        portaY = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[portaY][portaX] != ' ' || (portaX == chaveX && portaY == chaveY)); // Garantir que a porta está em uma posição vazia e não coincide com a posição da chave
    labirinto3[portaY][portaX] = 'D'; // 'D' representa a porta fechada

    // Colocar o inimigo em uma posição aleatória, garantindo que não esteja entre os espinhos, nem coincida com a posição da chave ou da porta
    do {
        eminemX3 = rand() % (COLUNAS3 - 2) + 1;
        eminemY3 = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto3[eminemY3][eminemX3] != ' ' || (eminemX3 == chaveX && eminemY3 == chaveY) || (eminemX3 == portaX && eminemY3 == portaY)); // Garantir que o inimigo está em uma posição vazia e não coincide com a posição da chave ou da porta
    labirinto3[eminemY3][eminemX3] = 'V'; // 'X' representa o inimigo
    do {
        botaoX = rand() % (COLUNAS3 - 2) + 1;
        botaoY = rand() % (LINHAS3 - 2) + 1;
    } while (labirinto2[botaoY][botaoX] != ' ' || (botaoX == chaveX && botaoY == chaveY) || (botaoX == portaX && botaoY == portaY)); // Garantir que o inimigo está em uma posição vazia e não coincide com a posição da chave ou da porta
    labirinto3[botaoY][botaoX] = 'O'; // 'X' representa o inimigo
}

// Função para imprimir o labirinto na tela
void imprimirLabirinto() {
    int i, j;
    system("cls");
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            printf("%c ", labirinto[i][j]);
        }
        printf("\n");
    }
}

// Função para imprimir o segundo labirinto na tela
void imprimirLabirinto2() {
    int i, j;
    system("cls");
    for (i = 0; i < LINHAS2; i++) {
        for (j = 0; j < COLUNAS2; j++) {
            printf("%c ", labirinto2[i][j]);
        }
        printf("\n");
    }
}
void imprimirLabirinto3() {
    int i, j;
    system("cls");
    for (i = 0; i < LINHAS3; i++) {
        for (j = 0; j < COLUNAS3; j++) {
            printf("%c ", labirinto3[i][j]);
        }
        printf("\n");
    }
}

// Função para mover o jogador no primeiro labirinto
void moverJogador(char direcao) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    // Calcular a nova posição do jogador
    switch (direcao) {
        case 'w':
            novoY--;
            break;
        case 's':
            novoY++;
            break;
        case 'a':
            novoX--;
            break;
        case 'd':
            novoX++;
            break;
        case 'i':
            if (jogadorX == chaveX && jogadorY == chaveY) {
                printf("Voce pegou a chave!\n");
                system("pause");
                possuichave = 1;
            }
            break;
    }

    // Verificar se a nova posição é válida
    if (novoX >= 0 && novoX < COLUNAS && novoY >= 0 && novoY < LINHAS && labirinto[novoY][novoX] != '*') {
        // Atualizar a posição do jogador
        labirinto[jogadorY][jogadorX] = ' ';
        jogadorX = novoX;
        jogadorY = novoY;
        labirinto[jogadorY][jogadorX] = '&';

        // Verificar se o jogador pegou a chave
        if (possuichave == 1) {
            labirinto[chaveY][chaveX] = ' ';
            labirinto[portaY][portaX] = '='; // 'D' se torna '=' indicando que a porta está aberta
        } else {
            labirinto[chaveY][chaveX] = '@';
            labirinto[portaY][portaX] = 'D';
        }
        // Verificar se o jogador chegou à porta com a chave
        if (jogadorX == portaX && jogadorY == portaY && possuichave == 1) {
            system("cls");
            printf("VOCE PASSOU DE FASE!!!\n");
            fim1 = 1;
            system("pause");
        }
    }
}

// Função para mover o jogador no segundo labirinto
void moverJogador2(char direcao) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    // Calcular a nova posição do jogador
    switch (direcao) {
        case 'w':
            novoY--;
            break;
        case 's':
            novoY++;
            break;
        case 'a':
            novoX--;
            break;
        case 'd':
            novoX++;
            break;
        case 'i':
            if (jogadorX == chaveX && jogadorY == chaveY) {
                printf("Voce pegou a chave!\n");
                system("pause");
                possuichave = 1;
            }else if (jogadorX == botaoX && jogadorY == botaoY) {
                // O jogador interagiu com um botão
                printf("Voce pressionou o botao!\n");
                colocarEspinhos();
                system("pause");
            }
            break;
    }

    // Verificar se a nova posição é válida
    if (novoX >= 0 && novoX < COLUNAS2 && novoY >= 0 && novoY < LINHAS2 && labirinto2[novoY][novoX] != '*') {
        // Atualizar a posição do jogador
        labirinto2[jogadorY][jogadorX] = ' ';
        labirinto2[botaoY][botaoX] = 'O';
        jogadorX = novoX;
        jogadorY = novoY;
        labirinto2[jogadorY][jogadorX] = '&';

        // Verificar se o jogador pegou a chave
        if (possuichave == 1) {
            labirinto2[chaveY][chaveX] = ' ';
            labirinto2[portaY][portaX] = '='; // 'D' se torna '=' indicando que a porta está aberta
        } else {
            labirinto2[chaveY][chaveX] = '@';
            labirinto2[portaY][portaX] = 'D';
        }
        // Verificar se o jogador chegou à porta com a chave
        if (jogadorX == portaX && jogadorY == portaY && possuichave == 1) {
            system("cls");
            printf("VOCE PASSOU DE FASE!!!\n");
            fim2 = 1;
            system("pause");
        }
        
    }
}
// Função para mover o jogador no terceiro labirinto
void moverJogador3(char direcao) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    // Calcular a nova posição do jogador
    switch (direcao) {
        case 'w':
            novoY--;
            labirinto2[botaoY][botaoX] = 'O';
            break;
        case 's':
            novoY++;
            labirinto2[botaoY][botaoX] = 'O';
            break;
        case 'a':
            novoX--;
            labirinto2[botaoY][botaoX] = 'O';
            break;
        case 'd':
            novoX++;
            labirinto2[botaoY][botaoX] = 'O';
            break;
        case 'i':
            if (jogadorX == chaveX && jogadorY == chaveY) {
                printf("Voce pegou a chave!\n");
                sleep(1);
                possuichave = 1;
            }if (jogadorX == botaoX && jogadorY == botaoY) {
                // O jogador interagiu com um botão
                printf("Voce pressionou o botao!\n");
                colocarEspinhos2();
                //pressbotao = 1;
                
                system("pause");    
            }
            if (jogadorX == portal1X && jogadorY == portal1Y) {
                novoY = portal2Y;
                novoX = portal2X;
            }else if (jogadorX == portal2X && jogadorY == portal2Y) {
                novoY = portal1Y;
                novoX = portal1X;
            }
            break;
    }

    // Verificar se a nova posição é válida
    if (novoX >= 0 && novoX < COLUNAS3 && novoY >= 0 && novoY < LINHAS3 && labirinto3[novoY][novoX] != '*') {
        // Atualizar a posição do jogador
        labirinto3[jogadorY][jogadorX] = ' ';
        labirinto3[portal1Y][portal1X] = '>';
        labirinto3[portal2Y][portal2X] = '>';
        labirinto2[botaoY][botaoX] = 'O';
        jogadorX = novoX;
        jogadorY = novoY;
        labirinto3[jogadorY][jogadorX] = '&';

        // Verificar se o jogador pegou a chave
        if (possuichave == 1) {
            labirinto3[chaveY][chaveX] = ' ';
            labirinto3[portaY][portaX] = '=';
        } else {
            labirinto3[chaveY][chaveX] = '@';
            labirinto3[portaY][portaX] = 'D';
        }
        // Verificar se o jogador chegou à porta com a chave
        if (jogadorX == portaX && jogadorY == portaY && possuichave == 1) {
            system("cls");
            printf("VOCE PASSOU DE FASE!!!\n");
            fim3 = 1;
            system("pause");
        }
        
    }
}
// Função para mover o inimigo no segundo labirinto
void eminemMove2() {
    int novoEX = eminemX2;
    int novoEY = eminemY2;
    int direcao;

    // Gerar uma direção aleatória para o inimigo
    srand(time(NULL));
    direcao = rand() % 4;

    // Calcular a nova posição do inimigo
    switch (direcao) {
        case 0: // Mover para cima
            novoEY--;
            break;
        case 1: // Mover para baixo
            novoEY++;
            break;
        case 2: // Mover para a esquerda
            novoEX--;
            break;
        case 3: // Mover para a direita
            novoEX++;
            break;
    }

    // Verificar se a nova posição é válida
    if (novoEX >= 0 && novoEX < COLUNAS2 && novoEY >= 0 && novoEY < LINHAS2 && labirinto2[novoEY][novoEX] != '*') {
        // Atualizar a posição do inimigo
		labirinto2[eminemY2][eminemX2] = ' ';
		eminemX2 = novoEX;
		eminemY2 = novoEY;
		labirinto2[eminemY2][eminemX2] = 'X';
    }
}
// Função para mover o inimigo na terceira fase
void moverInimigo3() {
    // Calcula a direção na qual o inimigo deve se mover para seguir o jogador
    int deltaX = 0;
    int deltaY = 0;

    // Gera um número aleatório entre 0 e 1
    srand(time(NULL));
    int chanceMovimento = rand() % 4;

    // Se a chance de movimento for maior ou igual a 0.5, o inimigo se move
    if (chanceMovimento != 0) {
        // Prioriza o movimento horizontal se a diferença em X for maior do que em Y
        if (abs(jogadorX - eminemX3) > abs(jogadorY - eminemY3)) {
            if (jogadorX < eminemX3) {
                deltaX = -1; // Move para a esquerda
            } else if (jogadorX > eminemX3) {
                deltaX = 1; // Move para a direita
            }
        }
        // Prioriza o movimento vertical se a diferença em Y for maior ou igual à diferença em X
        else {
            if (jogadorY < eminemY3) {
                deltaY = -1; // Move para cima
            } else if (jogadorY > eminemY3) {
                deltaY = 1; // Move para baixo
            }
        }

        // Verifica se o próximo movimento é válido e move o inimigo
        if (eminemX3 + deltaX >= 0 && eminemX3 + deltaX < COLUNAS3 && labirinto3[eminemY3][eminemX3 + deltaX] != '*') {
            labirinto3[eminemY3][eminemX3] = ' ';
            eminemX3 += deltaX;
        }

        if (eminemY3 + deltaY >= 0 && eminemY3 + deltaY < LINHAS3 && labirinto3[eminemY3 + deltaY][eminemX3] != '*') {
            eminemY3 += deltaY;
        }
    }

    // Atualiza a posição do inimigo no labirinto
    labirinto3[eminemY3][eminemX3] = 'V';
}
int main() {
    char menu;
    int iniciar = 0;
    int controle = 0;

	system("cls");
    printf("Menu Inicial:\n\n[1] Jogar\n[2] Tutorial\n[3] Sair\n\nEscolha: ");
    scanf(" %c", &menu); // Adicionei um espaço antes do %c para ignorar espaços em branco

    if (menu == '1') {
        system("cls");
        iniciar = 1;
    } else if (menu == '2') {
        while (iniciar != 1) {
            system("cls");
            printf("O jogador possui os seguintes comandos:\n\nW: O jogador movimenta uma unidade para cima;\nA: O jogador movimenta uma unidade para esquerda;\nS: O jogador movimenta uma unidade para baixo;\nD: O jogador movimenta uma unidade para direita;\nI: O jogador interage com o objeto que esta em cima.\n\nO jogo possui os seguintes elementos nas fases:\n\n&: Simbolo que representa o jogador.\n*: Simbolo que representa uma parede, o jogador ao se movimentar nao pode passar pela parede.\n@: Simbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave.\nD: Simbolo que representa a porta fechada.\n=: Simbolo que representa a porta aberta quando o jogador interage com a chave.\nX: Simbolo que representa o inimigo.\n#: Simbolo que representa um espinho. A fase e reiniciada quando o jogador toca no espinho e perde uma vida.\n\nPressione 1 para iniciar o jogo: ");
            scanf("%d", &iniciar);
        }
    } else if (menu == '4') {
        while (iniciar != 1) {
            system("cls");
            iniciar = 2;
        }
    }
	else {
        system("cls");
        exit(0);
    }

    if(iniciar == 1){
    	char movimento;
    	int vidas = 3;
    	// Inicializar o labirinto
    	inicializarLabirinto();
    	// Loop principal do jogo
    	while (fim1 != 1) { // Utilizando a variável de controle de fim do jogo
  	      // Imprimir o labirinto
  	      imprimirLabirinto();
  	      // Ler o movimento do jogador
  	      movimento = getch();
  	      // Mover o jogador
  	      moverJogador(movimento);
   		}
   		while (fim2 != 1){
   			system("cls");
   			if (vidas <= 0) {
		        system("cls");
		        printf("Ah, que pena! Parece que voce se perdeu no labirinto. Talvez a proxima vez voce encontre o caminho certo, ou quem sabe apenas tente nao esbarrar em tantas paredes. Se precisar de um mapa ou de um guia turistico, estamos aqui para ajudar! Boa sorte na proxima tentativa, explorador! \n");
		        system("pause");
		        // Retornar ao menu principal
		        fim1 = 0;
				fim2 = 0;
		        main();
		    }
	   		inicializarLabirinto2();
	   		controle = 0;
	   		while (fim2 != 1 && controle == 0) { 
				// Imprimir o labirinto
				imprimirLabirinto2();
				// Ler o movimento do jogador
				movimento = getch();
				// Mover o jogador
				eminemMove2();
				// Verificar se o jogador colidiu com o inimigo ou com o espinho
				moverJogador2(movimento);
				// Movimento do inimigo

		        int k;
		        int ispinhosX;
		        int ispinhosY;
		        for (k = 0; k < 15; k++){
		        	ispinhosX = espinhoX[k];
		        	ispinhosY = espinhoY[k];
		        	if ((jogadorX == eminemX2 && jogadorY == eminemY2) || (jogadorX == ispinhosX && jogadorY == ispinhosY)) {
		            printf("VOCE PERDEU UMA VIDA!\n");
		            vidas--;
		            printf("VIDAS RESTANTES: %d\n", vidas);
		            system("pause");
		            
		            controle++;
		        	}
				}
			}
		}
		controle == 0;
		while (fim3 != 1){
	   		system("cls");
	   		if (vidas <= 0) {
			    system("cls");
			    printf("Voce foi incrivel... na arte de se perder! Se houvesse uma medalha de ouro para isso, voce ja estaria no podio! Mas olha pelo lado bom, agora voce sabe todos os caminhos que nao deve seguir. Quem sabe na proxima voce descobre o caminho certo e mostra do que e capaz? Continue tentando, campeao!!\n");
			    system("pause");
			    // Retornar ao menu principal
			    fim1 = 0;
				fim2 = 0;
				fim3 = 0;
			    main();
			}
		   	inicializarLabirinto3();
		   	controle = 0;
		   	while (fim3 != 1 && controle == 0) { 
		   	
				/*if(pressbotao != 0){
					reinicializarLabirinto3();
					pressbotao = 0;
				}*/
				// Imprimir o labirinto
				imprimirLabirinto3();
				// Ler o movimento do jogador
				movimento = getch();
				// Mover o jogador
				    int novoX = jogadorX;
				    int novoY = jogadorY;
				
				    // Calcular a nova posição do jogador
				    switch (movimento) {
				        case 'w':
				            novoY--;
				            labirinto2[botaoY][botaoX] = 'O';
				            break;
				        case 's':
				            novoY++;
				            labirinto2[botaoY][botaoX] = 'O';
				            break;
				        case 'a':
				            novoX--;
				            labirinto2[botaoY][botaoX] = 'O';
				            break;
				        case 'd':
				            novoX++;
				            labirinto2[botaoY][botaoX] = 'O';
				            break;
				        case 'i':
				            if (jogadorX == chaveX && jogadorY == chaveY) {
				                printf("Voce pegou a chave!\n");
				                sleep(1);
				                possuichave = 1;
				            }if (jogadorX == botaoX && jogadorY == botaoY) {
				                // O jogador interagiu com um botão
				                printf("Voce pressionou o botao!\n");
				                colocarEspinhos2();
				                //pressbotao = 1;
				                system("pause");    
				            }
				            if (jogadorX == portal1X && jogadorY == portal1Y) {
				                novoY = portal2Y;
				                novoX = portal2X;
				            }else if (jogadorX == portal2X && jogadorY == portal2Y) {
				                novoY = portal1Y;
				                novoX = portal1X;
				            }
				            break;
				    }
				    if(labirinto3[novoY][novoX] == '#'){
		            	printf("VOCE PERDEU UMA VIDA!\n");
		            	vidas--;
		            	printf("VIDAS RESTANTES: %d\n", vidas);
						system("pause");
		            
		            	controle++;
		            }
				
				    // Verificar se a nova posição é válida
				    if (novoX >= 0 && novoX < COLUNAS3 && novoY >= 0 && novoY < LINHAS3 && labirinto3[novoY][novoX] != '*') {
				        // Atualizar a posição do jogador
				        labirinto3[jogadorY][jogadorX] = ' ';
				        labirinto3[portal1Y][portal1X] = '>';
				        labirinto3[portal2Y][portal2X] = '>';
				        labirinto2[botaoY][botaoX] = 'O';
				        jogadorX = novoX;
				        jogadorY = novoY;
				        labirinto3[jogadorY][jogadorX] = '&';
				
				        // Verificar se o jogador pegou a chave
				        if (possuichave == 1) {
				            labirinto3[chaveY][chaveX] = ' ';
				            labirinto3[portaY][portaX] = '=';
				        } else {
				            labirinto3[chaveY][chaveX] = '@';
				            labirinto3[portaY][portaX] = 'D';
				        }
				        // Verificar se o jogador chegou à porta com a chave
				        if (jogadorX == portaX && jogadorY == portaY && possuichave == 1) {
				            system("cls");
				            printf("VOCE PASSOU DE FASE!!!\n");
				            fim3 = 1;
				            system("pause");
				        }
				        
				    }
				moverInimigo3();
				
				int k;
		        int ispinhosX;
		        int ispinhosY;
				for (k = 0; k < 40; k++){
		        	ispinhosX = espinhoX[k];
		        	ispinhosY = espinhoY[k];
		        	if ((jogadorX == eminemX3 && jogadorY == eminemY3)){
		            	printf("VOCE PERDEU UMA VIDA!\n");
		           		vidas--;
		            	printf("VIDAS RESTANTES: %d\n", vidas);
		            	k=40;
						system("pause");
		            	
		            	controle++;
		        	} else if(labirinto3[jogadorY][jogadorX] == '#'){
		            	printf("VOCE PERDEU UMA VIDA!\n");
		            	vidas--;
		            	printf("VIDAS RESTANTES: %d\n", vidas);
		            	k=40;
						system("pause");
		            
		            	controle++;
					}
				}
			}
			if (fim3 == 1) {
            	system("cls");
            	printf("PARABENS, VOCE VENCEU O JOGO!\n");
            	system("pause");
            	main(); // Retornar ao menu principal após a vitória
            }
		}
	}
    return 0;
}
