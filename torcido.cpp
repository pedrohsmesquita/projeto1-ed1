#include "torcido.h"
#include "render.h"
#include "teclado.h"

void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, dicionario::ListaExterna &dicionario);
void processarGraficosEntrada(lista_grafica::ListaLetra &lista, TecladoStatus &status);
void processarTemporizado(int &tempoRestante, float &tempoPassado, string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV);

void telaJogo(bool &janelaAtiva, dicionario::ListaExterna &dicionario) {
    string_lista::String entrada, palavraSorteada, palavraEmbaralhada, tempoS;
    lista_grafica::ListaLetra entradaV, palavraSorteadaV, tempoV;
    //lista_grafica::LetraEstilo estilo, estiloSorteada;
    lista_grafica::ListaCaixa placeholders;
    Mouse *mouse = obterMouse();
    TecladoStatus tecladoStatus;
    float tempoPassado = 0.0f;
    int tempoRestante = 60;

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
    string_lista::criarLista(tempoS);
    lista_grafica::criarLista(tempoV);
    tempoV.primeiro->info.estilo.posicao = {90.0f, 20.0f};
    tempoV.primeiro->info.estilo.tamanho = 18.0f;
    tempoV.primeiro->info.estilo.cor = WHITE;
    tempoV.primeiro->info.estilo.fonte = obterOpenSansSemiBold18();
    tempoV.primeiro->info.caixa.retangulo = {90.0f, 20.0f, 32.0f, 32.0f};
    tempoV.primeiro->info.caixa.cor = BLACK;
    tempoV.primeiro->info.caixa.redondeza = 0.2f;
    tempoV.primeiro->info.caixa.segmentos = 10;
    string_lista::utils::intStr(tempoS, tempoRestante, 2);
    lista_grafica::utils::inserirString(tempoV, tempoS, 2.0f);

    while (janelaAtiva) {
        tecladoStatus = lerEntradaTeclado(entrada, entradaV, palavraSorteada.primeiro->val);
        processarGraficosEntrada(entradaV, tecladoStatus);
        processarTemporizado(tempoRestante, tempoPassado, tempoS, tempoV);
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
        desenharPalavraCaixa(tempoV);
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

void processarTemporizado(int &tempoRestante, float &tempoPassado, string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV) {
    const float deltaT = GetFrameTime();

    tempoPassado += deltaT;

    if (tempoPassado >= 1.0f) {
        tempoRestante--;
        tempoPassado = 0.0f;
        string_lista::utils::intStr(tempoS, tempoRestante, 2);
        lista_grafica::utils::deletar(tempoV);
        lista_grafica::utils::inserirString(tempoV, tempoS, 2.0f);
    }
}
