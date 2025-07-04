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
        desenharFundo();
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

void inicializarCaixaSelecaoDicionario(CaixaTexto &ct1, CaixaTexto &ct2);
void inicializarTexto(Texto &texto);

#define LARGURA 800
#define ALTURA 450

Dicionario telaSelecaoDicionario(bool &janelaAtiva) {
    CaixaTexto ct1, ct2;
    Texto texto;
    Mouse *mouse = obterMouse();
    Dicionario selecionado = INVLD;

    inicializarCaixaSelecaoDicionario(ct1, ct2);
    inicializarTexto(texto);

    while (janelaAtiva) {
        switch (selecionado) {
        case PORTUGUES:
            return PORTUGUES;
        case INGLES:
            return INGLES;
        default:
            break;
        }
        if (janelaAtiva) {
            ct1.caixa.mouseSobre = false; ct1.texto.mouseSobre = false;
            ct2.caixa.mouseSobre = false; ct2.texto.mouseSobre = false;
            lerMouse(*mouse);
            if (CheckCollisionPointRec(mouse->posicao, ct1.caixa.retangulo)) {          // PROVISÓRIO
                ct1.caixa.mouseSobre = true; ct1.texto.mouseSobre = true;
                if (mouse->botaoEsqClick)
                    mouse->opcaoSelecionada = ct1.id;
            } else if (CheckCollisionPointRec(mouse->posicao, ct2.caixa.retangulo)) {   // PROVISÓRIO
                ct2.caixa.mouseSobre = true; ct2.texto.mouseSobre = true;
                if (mouse->botaoEsqClick)
                    mouse->opcaoSelecionada = ct2.id;
            }
            selecionado = (Dicionario) mouse->opcaoSelecionada;
            BeginDrawing();
            ClearBackground((Color) {7, 56, 62, 255});
            desenharFundo();
            desenharLetraContorno(texto, 2.0f);
            desenharBotao(ct1, 0.35f, 0.75f);
            desenharBotao(ct2, 0.35f, 0.75f);
            EndDrawing();
            janelaAtiva = !WindowShouldClose();
        }
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

void inicializarCaixaSelecaoDicionario(CaixaTexto &ct1, CaixaTexto &ct2) {
    Vector2 temp;
    ct1.id = PORTUGUES;
    ct1.texto.conteudo = "Portugues";
    ct1.caixa.cor = (Color){240, 220, 116, 255};
    ct1.caixa.corSobre = (Color) {255, 223, 153, 255};
    ct1.caixa.mouseSobre = false;
    ct1.caixa.redondeza = 0.3;
    ct1.caixa.segmentos = 10;
    ct1.caixa.retangulo = {
        LARGURA/2 - 80.0f, ALTURA/2 - 60.0f,
        160.0f, 60.0f
    };

    ct1.texto.cor = (Color) {7, 56, 62, 255};
    ct1.texto.corSobre = (Color) {7, 56, 62, 255};
    ct1.texto.espacamento = 2.0f;
    ct1.texto.mouseSobre = false;
    ct1.texto.tamanho = LETRA_ESCOLHIDA_TAM;
    ct1.texto.fonte = obterOpenSansBold30();
    temp = MeasureTextEx(*ct1.texto.fonte, ct1.texto.conteudo, ct1.texto.tamanho, ct1.texto.espacamento);
    ct1.texto.posicao = {
        ct1.caixa.retangulo.x + (ct1.caixa.retangulo.width - temp.x)/2,
        ct1.caixa.retangulo.y + (ct1.caixa.retangulo.height - temp.y)/2
    };

    ct2.id = INGLES;
    ct2.texto.conteudo = "Ingles";
    ct2.caixa = ct1.caixa;
    ct2.texto.cor = ct1.texto.cor;
    ct2.texto.corSobre = ct1.texto.corSobre;
    ct2.texto.espacamento = ct1.texto.espacamento;
    ct2.texto.fonte = ct1.texto.fonte;
    ct2.texto.mouseSobre = false;
    ct2.texto.tamanho = ct1.texto.tamanho;
    ct2.caixa.retangulo.y += ct1.caixa.retangulo.height + 45.0f;
    temp = MeasureTextEx(*ct2.texto.fonte, ct2.texto.conteudo, ct2.texto.tamanho, ct2.texto.espacamento);
    ct2.texto.posicao = {
        ct2.caixa.retangulo.x + (ct2.caixa.retangulo.width - temp.x)/2,
        ct2.caixa.retangulo.y + (ct2.caixa.retangulo.height - temp.y)/2
    };
}

void inicializarTexto(Texto &texto) {
    texto.conteudo = " ESCOLHA O\nDICIONARIO";
    texto.cor = (Color){240, 220, 116, 255};
    texto.espacamento = 1.0f;
    texto.fonte = obterOpenSansBold48();
    texto.tamanho = LETRA_BOTOES_TAM;
    texto.mouseSobre = false;
    Vector2 medida = MeasureTextEx(*texto.fonte, texto.conteudo, texto.tamanho, texto.espacamento);
    texto.posicao = {LARGURA/2 - medida.x/2, medida.y/4};
}
