#include "mouse.h"

/**
 * Faz a leitura do estado atual do mouse: posição e se foi clicado ou não.
 * Além disso, define valores padrões para serem alterados posteriormente
 * (opcaoSelecionada e tipoCursor).
 */
void lerMouse(Mouse& mouse) {
    mouse.posicao = GetMousePosition();
    mouse.opcaoSelecionada = SEM_SELECAO;
    mouse.tipoCursor = MOUSE_CURSOR_DEFAULT;
    mouse.botaoEsqClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
 }


 /**
  * Parâmetros:
  *     "mouse" é uma variável estática (static), isto é, vai existir mesmo
  *     quando o programa sair da função.
  * Retorna:
  *     O endereço da variável mouse.
  */
 Mouse *obterMouse() {
    static Mouse mouse;
    return &mouse;
 }
