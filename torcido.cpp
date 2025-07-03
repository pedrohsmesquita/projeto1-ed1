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

void inicializarListaEntradas(lista_list::ListaLista &listaV);
void inicializarEntrada(string_lista::String &entrada, lista_grafica::ListaLetra &entradaV, Caixa &caixa);
void inicializarRelogio(string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV, int tempoRestante);
void inicializarPontuacao(string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV, int pontuacao);
void inicializarPalavraSorteada(string_lista::String &palavraSorteada, string_lista::String &palavraEmbaralhada, lista_grafica::ListaLetra &palavraSorteadaV);
void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, tbl_indxd::TabelaIndexada &tabela);
void processarGraficosEntrada(lista_grafica::ListaLetra &lista, TecladoStatus &status);
void processarTemporizado(int &tempoRestante, float &tempoPassado, string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV);
void processarPontuacao(int pontuacao, string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV);
Resultado validarPalavra(string_lista::String &entrada, string_lista::String &palavraEscolhida, tbl_indxd::TabelaIndexada &tabela);

void telaJogo(bool &janelaAtiva, tbl_indxd::TabelaIndexada &tabela) {
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
    inicializarPalavraSorteada(palavraSorteada, palavraEmbaralhada, palavraSorteadaV);
    escolherPalavra(palavraSorteada, palavraEmbaralhada, tabela);
    lista_grafica::utils::inserirString(palavraSorteadaV, palavraSorteada, 3.0f);
    lista_grafica::criarLista(placeholders);
    letrasPlaceholders(palavraSorteadaV, placeholders);
    inicializarListaEntradas(listaPalavrasV);
    inicializarEntrada(entrada, entradaV, placeholders.primeiro->prox->caixa);
    inicializarRelogio(tempoS, tempoV, tempoRestante);
    inicializarPontuacao(pontuacaoS, pontuacaoV, pontuacao);
    palavra_lista::criarLista(listaPalavras);


    while (janelaAtiva) {
        sucesso = false;
        tecladoStatus = lerEntradaTeclado(entrada, entradaV, palavraSorteada.primeiro->val);
        processarGraficosEntrada(entradaV, tecladoStatus);
        processarTemporizado(tempoRestante, tempoPassado, tempoS, tempoV);
        if (entrada.primeiro->val >= 3 && IsKeyPressed(KEY_ENTER)) {
            Resultado resultado = validarPalavra(entrada, palavraSorteada, tabela);
            if (resultado == INVALIDA) {
                string_lista::utils::deletar(entrada);
                lista_grafica::utils::deletar(entradaV);
            } else if (resultado == VALIDA) {
                pontuacao += PALAVRA_VALIDA_PONTUACAO;
                sucesso = true;
            } else if (resultado == ACERTOU) {
                string_lista::utils::deletar(palavraEmbaralhada);
                escolherPalavra(palavraSorteada, palavraEmbaralhada, tabela);
                lista_grafica::utils::deletar(palavraSorteadaV);
                lista_grafica::utils::deletar(placeholders);
                lista_grafica::utils::inserirString(palavraSorteadaV, palavraSorteada, 3.0f);
                letrasPlaceholders(palavraSorteadaV, placeholders);
                tempoRestante = 60;
                tempoPassado = 0.0f;
                processarTemporizado(tempoRestante, tempoPassado, tempoS, tempoV);
                pontuacao += PALAVRA_CORRETA_PONTUACAO;
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
        ClearBackground((Color) {7, 56, 62, 255});
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

void escolherPalavra(string_lista::String &palavra, string_lista::String &embaralhada, tbl_indxd::TabelaIndexada &tabela) {
    tbl_indxd::utils::escolherPalavra(tabela, palavra);
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
        lista_grafica::utils::inserirStringEstililizada(tempoV, tempoS);
    }
}

Resultado validarPalavra(string_lista::String &entrada, string_lista::String &palavraEscolhida, tbl_indxd::TabelaIndexada &tabela) {
    using namespace string_lista::utils;
    if (!LetrasContidasNaPalavra(entrada, palavraEscolhida))
        return INVALIDA;
    if (comparaString(entrada, palavraEscolhida))
        return ACERTOU;
    if (tbl_indxd::utils::palavraInseridaExiste(entrada, tabela))
        return VALIDA;
    return INVALIDA;
}

void inicializarRelogioEstilo(lista_grafica::ListaLetra &tempo) {
    tempo.primeiro->info.estilo.cor = WHITE;
    tempo.primeiro->info.estilo.fonte = obterOpenSansSemiBold18();
    tempo.primeiro->info.estilo.tamanho = 18.0f;
    tempo.primeiro->info.estilo.posicao = {
        LARGURA_TELA - 80.0f, ALTURA_TELA - 48.0f
    };
}

void inicializarPontuacaoEstilo(lista_grafica::ListaLetra &pontuacao) {
    pontuacao.primeiro->info.estilo.cor = WHITE;
    pontuacao.primeiro->info.estilo.fonte = obterOpenSansSemiBold18();
    pontuacao.primeiro->info.estilo.tamanho = 18.0f;
    pontuacao.primeiro->info.estilo.posicao = {
        LARGURA_TELA - 160.0f, ALTURA_TELA - 48.0f
    };
}

void processarPontuacao(int pontuacao, string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV) {
    string_lista::utils::intStr(pontuacaoS, pontuacao, 6);
    lista_grafica::utils::deletar(pontuacaoV);
    lista_grafica::utils::inserirStringEstililizada(pontuacaoV, pontuacaoS);
}

void inicializarListaEntradas(lista_list::ListaLista &listaV) {
    lista_list::criarLista(listaV);
    lista_grafica::criarLista(listaV.primeiro->palavra);
    lista_grafica::LetraEstilo estilo;

    estilo.cor = WHITE;
    estilo.fonte = obterOpenSansSemiBold18();
    estilo.tamanho = 18.0f;
    estilo.posicao = {LARGURA_TELA - 200.0f, 1.0f};
    listaV.primeiro->palavra.primeiro->info.estilo = estilo;
}


void inicializarEntrada(string_lista::String &entrada, lista_grafica::ListaLetra &entradaV, Caixa &caixa) {
    string_lista::criarLista(entrada);
    lista_grafica::criarLista(entradaV, caixa);
    entradaV.primeiro->info.estilo.tamanho = 30;
    entradaV.primeiro->info.estilo.fonte = obterOpenSansBold30();
    entradaV.primeiro->info.caixa.cor = (Color){240, 220, 116, 255};
    entradaV.primeiro->info.estilo.cor = (Color) {7, 56, 62, 255};
    entradaV.primeiro->info.estilo.posicao = {caixa.retangulo.x, caixa.retangulo.y};
    entradaV.primeiro->info.estilo.tamanho = LETRA_DIGITADA_TAM;
    entradaV.primeiro->info.estilo.fonte = obterOpenSansSemiBold24();
}

void inicializarRelogio(string_lista::String &tempoS, lista_grafica::ListaLetra &tempoV, int tempoRestante) {
    string_lista::criarLista(tempoS);
    lista_grafica::criarLista(tempoV);
    inicializarRelogioEstilo(tempoV);
    string_lista::utils::intStr(tempoS, tempoRestante, 2);
    lista_grafica::utils::inserirStringEstililizada(tempoV, tempoS);
}

void inicializarPontuacao(string_lista::String &pontuacaoS, lista_grafica::ListaLetra &pontuacaoV, int pontuacao) {
    string_lista::criarLista(pontuacaoS);
    lista_grafica::criarLista(pontuacaoV);
    inicializarPontuacaoEstilo(pontuacaoV);
    string_lista::utils::intStr(pontuacaoS, pontuacao, 6);
    lista_grafica::utils::inserirStringEstililizada(pontuacaoV, pontuacaoS);
}

void inicializarPalavraSorteada(string_lista::String &palavraSorteada, string_lista::String &palavraEmbaralhada, lista_grafica::ListaLetra &palavraSorteadaV) {
    lista_grafica::criarLista(palavraSorteadaV);
    string_lista::criarLista(palavraEmbaralhada);
    definirEstiloCabecaSorteada(palavraSorteadaV);
}
