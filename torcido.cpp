#include "torcido.h"
#include "render.h"
#include "teclado.h"

void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, dicionario::ListaExterna &dicionario);

void processarGraficosEntrada(lista_grafica::ListaLetra &lista, TecladoStatus &status);

void telaJogo(bool &janelaAtiva, dicionario::ListaExterna &dicionario) {
    string_lista::String entrada, palavraSorteada, palavraEmbaralhada;
    lista_grafica::ListaLetra entradaV, palavraSorteadaV;
    lista_grafica::LetraEstilo estilo, estiloSorteada;
    lista_grafica::ListaCaixa placeholders;
    Mouse *mouse = obterMouse();
    TecladoStatus tecladoStatus;

    lista_grafica::criarLista(palavraSorteadaV);
    lista_grafica::criarLista(placeholders);
    string_lista::criarLista(entrada);
    string_lista::criarLista(palavraEmbaralhada);
    escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
    definirEstiloCabecaSorteada(palavraSorteadaV);
    lista_grafica::utils::inserirString(palavraSorteadaV, palavraEmbaralhada, 3.0f);
    //centralizar(palavraSorteadaV);
    letrasPlaceholders(palavraSorteadaV, placeholders);
    lista_grafica::criarLista(entradaV, placeholders.primeiro->prox->caixa);

    while (janelaAtiva) {
        tecladoStatus = lerEntradaTeclado(entrada, entradaV, palavraSorteada.primeiro->val);
        processarGraficosEntrada(entradaV, tecladoStatus);
        if (IsKeyPressed(KEY_ENTER)) {
            string_lista::utils::deletar(palavraEmbaralhada);
            string_lista::utils::deletar(entrada);
            escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
            lista_grafica::utils::deletar(palavraSorteadaV);
            lista_grafica::utils::deletar(placeholders);
            lista_grafica::utils::deletar(entradaV);
            lista_grafica::utils::inserirString(palavraSorteadaV, palavraEmbaralhada, 3.0f);
            //centralizar(palavraSorteadaV);
            letrasPlaceholders(palavraSorteadaV, placeholders);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        desenharCaixa(placeholders);
        desenharPalavraCaixa(entradaV);
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

void processarGraficosEntrada(lista_grafica::ListaLetra &lista, TecladoStatus &status) {
    lista_grafica::NodoLetra *no = lista.primeiro->prox;
    const float v = 500;
    const float deltaT = GetFrameTime();
    const float yMax = lista.primeiro->info.caixa.retangulo.y;

    while (no != NULL) {
        if (no->info.animando) {
            no->info.caixa.retangulo.y += v * deltaT;
            no->info.estilo.posicao.y += v * deltaT;
            if (no->info.caixa.retangulo.y >= yMax)
                no->info.caixa.retangulo.y = yMax;
            centralizarTextoCaixa(no);
        }
        no = no->prox;
    }
}
