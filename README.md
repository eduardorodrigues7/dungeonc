# dungeonc
Dungeon Crawler - Jogo avaliativo desenvolvido em Linguagem C para o curso de Ciência da Computação.

Professores:
Ricardo Casseb
Pedro Henrique Sales Girotto

Regras:

W: O jogador movimenta uma unidade para cima;
A: O jogador movimenta uma unidade para esquerda;
S: O jogador movimenta uma unidade para baixo;
D: O jogador movimenta uma unidade para direita;
I: O jogador interage com o objeto que está em cima.
O jogo possui os seguintes elementos nas fases:
&: Símbolo que representa o jogador.
*: Símbolo que representa uma parede, o jogador ao se movimentar não pode passar pela parede.
@: Símbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave.
D: Símbolo que representa a porta fechada.
=: Símbolo que representa a porta aberta quando o jogador interage com a chave.
O: Símbolo que representa um botão que o usuário pode interagir, o botão fica no chão e o jogador deve ficar em cima dele para poder interagir.
#: Símbolo que representa um espinho. A fase é reiniciada quando o jogador toca no espinho, caso a fase seja reiniciada três vezes, o jogo volta para o menu principal.
>: Símbolo que representa um teletransporte. O teletransporte sempre deve vir em pares, quando o jogador toca em um ele é transportado para o outro e vice-versa.
X: Símbolo que representa o monstro nível 1. O mostro tem um movimento aleatório, logo, ele movimenta um bloco para cima ou para direita ou para esquerda ou para baixo. O 	mostro sempre faz uma movimentação depois do usuário se movimentar ou interagir com um objeto.
V: Símbolo que representa o monstro nível 2. O mostro nível dois tem uma inteligência de se movimentar na direção do jogador. O    monstro não precisa saber desviar de 	obstáculos, ele sempre vai andar em linha reta em direção do jogador.

Fase 1: A Fase 1 é inicializada quando o jogador seleciona a opção Jogar no Menu Principal;
Fase 2: A Fase 2 é inicializada quando o jogador termina a Fase 1;
Fase 3: A Fase 3 é inicializada quando o jogador termina a Fase 2;

Desenvolvedores:
César Ribeiro
Everton Gustavo
Eduardo Rodrigues
