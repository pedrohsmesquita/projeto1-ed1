#include "mouse.h"

/**
 * Faz a leitura do estado atual do mouse: posi��o e se foi clicado ou n�o.
 * Al�m disso, define valores padr�es para serem alterados posteriormente
 * (opcaoSelecionada e tipoCursor).
 */
void lerMouse(Mouse& mouse) {
    mouse.posicao = GetMousePosition();
    mouse.opcaoSelecionada = SEM_SELECAO;
    mouse.tipoCursor = MOUSE_CURSOR_DEFAULT;
    mouse.botaoEsqClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
 }


 /**
  * Par�metros:
  *     "mouse" � uma vari�vel est�tica (static), isto �, vai existir mesmo
  *     quando o programa sair da fun��o.
  * Retorna:
  *     O endere�o da vari�vel mouse.
  */
 Mouse *obterMouse() {
    static Mouse mouse;
    return &mouse;
 }
