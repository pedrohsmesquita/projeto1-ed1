#include <ctime>
#include <fstream>
#include "torcido.h"
#include "render.h"
#include "mouse.h"
#include "palavras_lista.h"

enum OpcoesTelaInicial {INVALIDO, JOGAR, AJUDA, SAIR};

void inicializarCaixaTexto(CaixaTexto &ct1, CaixaTexto &ct2, CaixaTexto &ct3);

void carregarDicionario(char *nomeArquivo,  palavra_lista::ListaPalavra &lista);

int main(void) {
    //srand(time(NULL));
    const int LARGURA = 800;
    const int ALTURA = 450;
    bool janelaAtiva;
    OpcoesTelaInicial opcao;
    CaixaTexto ct1, ct2, ct3;
    Mouse *mouse = obterMouse();
    //dicionario::ListaExterna dicionario;
    palavra_lista::ListaPalavra dicionario;
    tbl_indxd::TabelaIndexada tabela;

    //dicionario::inicializarListaExterna(dicionario);
    // Dicionário e Tabela Indexada
    tbl_indxd::criarTabela(tabela);
    palavra_lista::criarLista(dicionario);
    carregarDicionario("Lista-de-Palavras.txt", dicionario);
    tbl_indxd::utils::indexarTabela(tabela, dicionario);
    //
    inicializarCaixaTexto(ct1, ct2, ct3);
    SetConfigFlags (FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(LARGURA, ALTURA, "Torcido");
    SetExitKey(0);
    InitAudioDevice();
    SetTargetFPS(60);

    janelaAtiva = !WindowShouldClose();
    opcao = INVALIDO;
    while (janelaAtiva) {
        ct1.caixa.mouseSobre = false; ct1.texto.mouseSobre = false; // PROVISÓRIO
        ct2.caixa.mouseSobre = false; ct2.texto.mouseSobre = false; // PROVISÓRIO
        ct3.caixa.mouseSobre = false; ct3.texto.mouseSobre = false; // PROVISÓRIO
        switch (opcao) {
        case JOGAR:
            telaJogo(janelaAtiva, tabela);
            opcao = INVALIDO;
            break;
        case AJUDA:
            telaAjuda();
            opcao = INVALIDO;
            break;
        case SAIR:
            janelaAtiva = false;
            break;
        default:
            break;
        }
        if (janelaAtiva) {
            lerMouse(*mouse);
            if (CheckCollisionPointRec(mouse->posicao, ct1.caixa.retangulo)) {          // PROVISÓRIO
                ct1.caixa.mouseSobre = true; ct1.texto.mouseSobre = true;
                if (mouse->botaoEsqClick)
                    mouse->opcaoSelecionada = ct1.id;
            } else if (CheckCollisionPointRec(mouse->posicao, ct2.caixa.retangulo)) {   // PROVISÓRIO
                ct2.caixa.mouseSobre = true; ct2.texto.mouseSobre = true;
                if (mouse->botaoEsqClick)
                    mouse->opcaoSelecionada = ct2.id;
            } else if (CheckCollisionPointRec(mouse->posicao, ct3.caixa.retangulo)) {   // PROVISÓRIO
                ct3.caixa.mouseSobre = true; ct3.texto.mouseSobre = true;
                if (mouse->botaoEsqClick)
                    mouse->opcaoSelecionada = ct3.id;
            }
            opcao = (OpcoesTelaInicial) mouse->opcaoSelecionada;
            BeginDrawing();                     // Todo desenho deve estar entre BeginDrawing() e EndDrawing()
                ClearBackground(RAYWHITE);

                desenharBotao(ct1, 1.0f, 1.0f);
                desenharBotao(ct2, 1.0f, 1.0f);
                desenharBotao(ct3, 1.0f, 1.0f);
            EndDrawing();
            janelaAtiva = !WindowShouldClose();
        }
    }

    CloseWindow();

    return 0;
}

// Inicialização qualquer apenas para testes
void inicializarCaixaTexto(CaixaTexto &ct) {
    ct.caixa.cor = BLUE;
    ct.caixa.cor = DARKBLUE;
    ct.caixa.mouseSobre = false;
    ct.caixa.redondeza = 0.1;
    ct.caixa.segmentos = 10;
    ct.caixa.retangulo = {
        200.0f, 100.0f,
        80.0f, 30.0f
    };

    ct.texto.cor = WHITE;
    ct.texto.corSobre = RED;
    ct.texto.espacamento = 1.0f;
    ct.texto.mouseSobre = false;
    ct.texto.tamanho = 14.0f;
    ct.texto.posicao = {ct.caixa.retangulo.x, ct.caixa.retangulo.y + 5.0f};
    ct.texto.fonte = GetFontDefault();
}

void inicializarCaixaTexto(CaixaTexto &ct1, CaixaTexto &ct2, CaixaTexto &ct3) {
    ct1.id = JOGAR;
    ct1.texto.conteudo = "Jogar";
    inicializarCaixaTexto(ct1);
    ct2.id = AJUDA;
    ct2.texto.conteudo = "Ajuda";
    inicializarCaixaTexto(ct2);
    ct2.caixa.retangulo.y += 50.0f;
    ct2.texto.posicao.y += 50.f;
    ct3.id = SAIR;
    ct3.texto.conteudo = "Sair";
    inicializarCaixaTexto(ct3);
    ct3.caixa.retangulo.y += 100.0f;
    ct3.texto.posicao.y += 100.f;
}

void carregarDicionario(char *nomeArquivo,  palavra_lista::ListaPalavra &lista) {
    string_lista::String linha;
    std::ifstream arquivo(nomeArquivo);

    //dicionario::inicializarListaExterna(lista);
    while (!arquivo.eof()) {
        linha = string_lista::utils::lerLinha(arquivo);
        if (linha.primeiro->val >= 3)
            palavra_lista::insereFinal(lista, linha);
        else string_lista::utils::deletar(linha);
    }
    arquivo.close();
}
