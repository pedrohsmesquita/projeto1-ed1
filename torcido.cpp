#include "torcido.h"
#include "render.h"
#include "teclado.h"

#define PALAVRA_VALIDA_PONTUACAO 50
#define PALAVRA_CORRETA_PONTUACAO 100

/**
 * INVALIDA - 0 Pontos
 * VALIDA   - 50 pontos
 * Acertou  - 100 pontos
 */
enum Resultado {INVALIDA, VALIDA, ACERTOU};

void inicializarRelogioEstilo(lista_grafica::ListaLetra &tempo);
void inicializarPontuacaoEstilo(lista_grafica::ListaLetra &pontuacao);
void inicializarListaEntradas(lista_list::ListaLista &listaV);
void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, dicionario::ListaExterna &dicionario);
void processarGraficosEntrada(lista_grafica::ListaLetra &lista, TecladoStatus &status);
void processarTemporizado(int &tempoRestante, float &tempoPassado, string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV);
void processarPontuacao(int pontuacao, string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV);
Resultado validarPalavra(string_lista::String &entrada, string_lista::String &palavraEscolhida, dicionario::ListaExterna &dicionario);

void telaJogo(bool &janelaAtiva, dicionario::ListaExterna &dicionario) {
    string_lista::String entrada, palavraSorteada, palavraEmbaralhada, tempoS, pontuacaoS;
    palavra_lista::ListaPalavra listaPalavras;
    lista_grafica::ListaLetra entradaV, palavraSorteadaV, tempoV, pontuacaoV;
    lista_grafica::ListaCaixa placeholders;
    lista_list::ListaLista listaPalavrasV;
    Mouse *mouse = obterMouse();
    TecladoStatus tecladoStatus;
    float tempoPassado = 0.0f;
    int tempoRestante = 60, pontuacao = 0;
    bool sucesso;

    // Entrada do usuário, palavra sorteada e plaveholders
    inicializarListaEntradas(listaPalavrasV);
    palavra_lista::criarLista(listaPalavras);
    lista_grafica::criarLista(palavraSorteadaV);
    lista_grafica::criarLista(placeholders);
    string_lista::criarLista(entrada);
    string_lista::criarLista(palavraEmbaralhada);
    escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
    definirEstiloCabecaSorteada(palavraSorteadaV);
    lista_grafica::utils::inserirString(palavraSorteadaV, palavraSorteada, 3.0f);
    //centralizar(palavraSorteadaV);
    letrasPlaceholders(palavraSorteadaV, placeholders);
    lista_grafica::criarLista(entradaV, placeholders.primeiro->prox->caixa);
    // Cronômetro
    string_lista::criarLista(tempoS);
    lista_grafica::criarLista(tempoV);
    inicializarRelogioEstilo(tempoV);
    string_lista::utils::intStr(tempoS, tempoRestante, 2);
    lista_grafica::utils::inserirStringEstilo(tempoV, tempoS);
    // Pontuacao
    string_lista::criarLista(pontuacaoS);
    lista_grafica::criarLista(pontuacaoV);
    inicializarPontuacaoEstilo(pontuacaoV);
    string_lista::utils::intStr(pontuacaoS, pontuacao, 6);
    lista_grafica::utils::inserirStringEstilo(pontuacaoV, pontuacaoS);

    while (janelaAtiva) {
        sucesso = false;
        tecladoStatus = lerEntradaTeclado(entrada, entradaV, palavraSorteada.primeiro->val);
        processarGraficosEntrada(entradaV, tecladoStatus);
        processarTemporizado(tempoRestante, tempoPassado, tempoS, tempoV);
        if (entrada.primeiro->val >= 3 && IsKeyPressed(KEY_ENTER)) {
            Resultado resultado = validarPalavra(entrada, palavraSorteada, dicionario);
            if (resultado == INVALIDA) {
                string_lista::utils::deletar(entrada);
                lista_grafica::utils::deletar(entradaV);
            } else if (resultado == VALIDA) {
                //string_lista::utils::deletar(entrada);
                //lista_grafica::utils::deletar(entradaV);
                pontuacao += PALAVRA_VALIDA_PONTUACAO;
                //processarPontuacao(pontuacao, pontuacaoS, pontuacaoV);
                sucesso = true;
            } else if (resultado == ACERTOU) {
                //palavra_lista::utils::inserePalavra(listaPalavras, entrada);
                //lista_list::utils::inserePalavra(listaPalavrasV, listaPalavras);
                string_lista::utils::deletar(palavraEmbaralhada);
                //string_lista::utils::deletar(entrada);
                escolherPalavra(palavraSorteada, palavraEmbaralhada, dicionario);
                lista_grafica::utils::deletar(palavraSorteadaV);
                lista_grafica::utils::deletar(placeholders);
                //lista_grafica::utils::deletar(entradaV);
                lista_grafica::utils::inserirString(palavraSorteadaV, palavraSorteada, 3.0f);
                letrasPlaceholders(palavraSorteadaV, placeholders);
                tempoRestante = 60;
                tempoPassado = 0.0f;
                processarTemporizado(tempoRestante, tempoPassado, tempoS, tempoV);
                pontuacao += PALAVRA_CORRETA_PONTUACAO;
                //processarPontuacao(pontuacao, pontuacaoS, pontuacaoV);
                sucesso = true;
            }
            if (sucesso) {
                processarPontuacao(pontuacao, pontuacaoS, pontuacaoV);
                palavra_lista::utils::inserePalavra(listaPalavras, entrada);
                string_lista::utils::deletar(entrada);
                lista_grafica::utils::deletar(entradaV);
                lista_list::utils::inserePalavra(listaPalavrasV, listaPalavras);
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);
        desenharCaixa(placeholders);
        desenharPalavraCaixa(entradaV);
        desenharPalavraCaixa(palavraSorteadaV);
        desenharCronometro(tempoV);
        desenharPontuacao(pontuacaoV);
        desenharListaPalavras(listaPalavrasV);
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
        if (tempoRestante == 0) tempoRestante = 60; // Temporário
        tempoPassado -= 1.0f;
        string_lista::utils::intStr(tempoS, tempoRestante, 2);
        lista_grafica::utils::deletar(tempoV);
        lista_grafica::utils::inserirStringEstilo(tempoV, tempoS);
    }
}

Resultado validarPalavra(string_lista::String &entrada, string_lista::String &palavraEscolhida, dicionario::ListaExterna &dicionario) {
    using namespace string_lista::utils;
    if (!LetrasContidasNaPalavra(entrada, palavraEscolhida))
        return INVALIDA;
    if (comparaString(entrada, palavraEscolhida))
        return ACERTOU;
    if (dicionario::utils::palavraInseridaExiste(entrada, &dicionario))
        return VALIDA;
    return INVALIDA;
}

void inicializarRelogioEstilo(lista_grafica::ListaLetra &tempo) {
    tempo.primeiro->info.estilo.cor = BLACK;
    tempo.primeiro->info.estilo.fonte = obterOpenSansSemiBold18();
    tempo.primeiro->info.estilo.tamanho = 18.0f;
    tempo.primeiro->info.estilo.posicao = {
        LARGURA_TELA - 80, ALTURA_TELA - 60
    };
}

void inicializarPontuacaoEstilo(lista_grafica::ListaLetra &pontuacao) {
    pontuacao.primeiro->info.estilo.cor = BLACK;
    pontuacao.primeiro->info.estilo.fonte = obterOpenSansSemiBold18();
    pontuacao.primeiro->info.estilo.tamanho = 18.0f;
    pontuacao.primeiro->info.estilo.posicao = {
        LARGURA_TELA - 160, ALTURA_TELA - 60
    };
}

void processarPontuacao(int pontuacao, string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV) {
    string_lista::utils::intStr(pontuacaoS, pontuacao, 6);
    lista_grafica::utils::deletar(pontuacaoV);
    lista_grafica::utils::inserirStringEstilo(pontuacaoV, pontuacaoS);
}

void inicializarListaEntradas(lista_list::ListaLista &listaV) {
    lista_list::criarLista(listaV);
    lista_grafica::criarLista(listaV.primeiro->palavra);
    lista_grafica::LetraEstilo estilo;

    estilo.cor = BLACK;
    estilo.fonte = obterOpenSansSemiBold18();
    estilo.tamanho = 18.0f;
    estilo.posicao = {LARGURA_TELA - 200.0f, 1.0f};
    listaV.primeiro->palavra.primeiro->info.estilo = estilo;
}
