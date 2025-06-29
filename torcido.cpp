#include "torcido.h"
#include "render.h"
#include "teclado.h"

void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, dicionario::ListaExterna &dicionario);

void telaJogo(bool &janelaAtiva, dicionario::ListaExterna &dicionario) {
    string_lista::String entrada, palavraSorteada, palavraEmbaralhada;
    lista_grafica::ListaLetra entradaV, palavraSorteadaV;
    lista_grafica::LetraEstilo estilo, estiloSorteada;
    Mouse *mouse = obterMouse();

    lista_grafica::criarLista(entradaV);
    lista_grafica::criarLista(palavraSorteadaV);
    string_lista::criarLista(entrada);
    string_lista::criarLista(palavraEmbaralhada);
    escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
    definirEstiloCabecaSorteada(palavraSorteadaV);
    lista_grafica::utils::inserirString(palavraSorteadaV, palavraEmbaralhada);
    centralizar(palavraSorteadaV);

    while (janelaAtiva) {
        //lerEntradaTeclado(entrada, entradaV, 10);
        if (IsKeyPressed(KEY_ENTER)) {
            string_lista::utils::deletar(palavraEmbaralhada);
            escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
            lista_grafica::utils::deletar(palavraSorteadaV);
            lista_grafica::utils::inserirString(palavraSorteadaV, palavraEmbaralhada);
            centralizar(palavraSorteadaV);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        //desenharPalavra(entradaV);
        desenharPalavraCaixa(palavraSorteadaV);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
}

void telaAjuda() {
    Mouse *mouse = obterMouse();
}

void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, dicionario::ListaExterna &dicionario) {
    dicionario::utils::escolherPalavra(&dicionario, palavra);
    string_lista::utils::strcpy(embaralhada, palavra);
    string_lista::utils::embaralhar(embaralhada);
}
