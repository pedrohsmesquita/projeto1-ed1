#include <ctime>
#include <fstream>
#include "torcido.h"
#include "render.h"
#include "mouse.h"
#include "palavras_lista.h"
#include "interface.h"

enum OpcoesTelaInicial {INVALIDO, JOGAR, AJUDA, SAIR};

void inicializarCaixaTexto(CaixaTexto &ct1, CaixaTexto &ct2, CaixaTexto &ct3);

void carregarDicionario(Dicionario opcao,  palavra_lista::ListaPalavra &lista);

const int LARGURA = 800;
const int ALTURA = 450;

int main(void) {
    srand(time(NULL));
    bool janelaAtiva;
    OpcoesTelaInicial opcao;
    CaixaTexto ct1, ct2, ct3;
    Mouse *mouse = obterMouse();
    palavra_lista::ListaPalavra dicionario;
    tbl_indxd::TabelaIndexada tabela;

    tbl_indxd::criarTabela(tabela);
    palavra_lista::criarLista(dicionario);

    SetConfigFlags (FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(LARGURA, ALTURA, "Torcido");
    SetExitKey(0);
    InitAudioDevice();
    SetTargetFPS(60);
    carregarFontes();
    carregarLogotipo();
    carregarFundo();
    inicializarCaixaTexto(ct1, ct2, ct3);

    janelaAtiva = !WindowShouldClose();
    opcao = INVALIDO;
    while (janelaAtiva) {
        Dicionario opcaoDicionario;
        ct1.caixa.mouseSobre = false; ct1.texto.mouseSobre = false; // PROVISÓRIO
        ct2.caixa.mouseSobre = false; ct2.texto.mouseSobre = false; // PROVISÓRIO
        ct3.caixa.mouseSobre = false; ct3.texto.mouseSobre = false; // PROVISÓRIO
        switch (opcao) {
        case JOGAR:
            opcaoDicionario = telaSelecaoDicionario(janelaAtiva);
            if (opcaoDicionario != INVLD) {
                carregarDicionario(opcaoDicionario, dicionario);
                tbl_indxd::utils::indexarTabela(tabela, dicionario);
                telaJogo(janelaAtiva, tabela);
                palavra_lista::utils::deletarConteudo(dicionario);
                palavra_lista::utils::deletar(dicionario);
                tbl_indxd::utils::deletarConteudoTabela(tabela);
            }
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
                ClearBackground((Color) {7, 56, 62, 255});
                desenharFundo();
                desenharLogotipo();
                desenharBotao(ct1, 0.75f, 0.75f);
                desenharBotao(ct2, 0.75f, 0.75f);
                desenharBotao(ct3, 0.75f, 0.75f);
            EndDrawing();
            janelaAtiva = !WindowShouldClose();
        }
    }

    tbl_indxd::utils::destruir(tabela);
    descarregarLogotipo();
    descarregarFundo();
    CloseWindow();

    return 0;
}

void inicializarCaixaTexto(CaixaTexto &ct1, CaixaTexto &ct2, CaixaTexto &ct3) {
    Vector2 temp;
    ct1.id = JOGAR;
    ct1.texto.conteudo = "JOGAR";
    ct1.caixa.cor = (Color){240, 220, 116, 255};
    ct1.caixa.corSobre = (Color) {255, 223, 153, 255};
    ct1.caixa.mouseSobre = false;
    ct1.caixa.redondeza = 0.3;
    ct1.caixa.segmentos = 10;
    ct1.caixa.retangulo = {
        LARGURA/2 - 80.0f, ALTURA/2 - 30.0f,
        160.0f, 60.0f
    };

    ct1.texto.cor = (Color) {7, 56, 62, 255};
    ct1.texto.corSobre = (Color) {7, 56, 62, 255};
    ct1.texto.espacamento = 2.0f;
    ct1.texto.mouseSobre = false;
    ct1.texto.tamanho = LETRA_BOTOES_TAM;
    ct1.texto.fonte = obterOpenSansBold48();
    temp = MeasureTextEx(*ct1.texto.fonte, ct1.texto.conteudo, ct1.texto.tamanho, ct1.texto.espacamento);
    ct1.texto.posicao = {
        ct1.caixa.retangulo.x + (ct1.caixa.retangulo.width - temp.x)/2,
        ct1.caixa.retangulo.y + (ct1.caixa.retangulo.height - temp.y)/2
    };

    ct2.id = AJUDA;
    ct2.texto.conteudo = "AJUDA";
    ct2.caixa = ct1.caixa;
    ct2.texto.cor = ct1.texto.cor;
    ct2.texto.corSobre = ct1.texto.corSobre;
    ct2.texto.espacamento = ct1.texto.espacamento;
    ct2.texto.fonte = ct1.texto.fonte;
    ct2.texto.mouseSobre = false;
    ct2.texto.tamanho = ct1.texto.tamanho;
    ct2.caixa.retangulo.y += ct1.caixa.retangulo.height + 15.0f;
    temp = MeasureTextEx(*ct2.texto.fonte, ct2.texto.conteudo, ct2.texto.tamanho, ct2.texto.espacamento);
    ct2.texto.posicao = {
        ct2.caixa.retangulo.x + (ct2.caixa.retangulo.width - temp.x)/2,
        ct2.caixa.retangulo.y + (ct2.caixa.retangulo.height - temp.y)/2
    };

    ct3.id = SAIR;
    ct3.texto.conteudo = "SAIR";
    ct3.caixa = ct2.caixa;
    ct3.texto.cor = ct2.texto.cor;
    ct3.texto.corSobre = ct2.texto.corSobre;
    ct3.texto.espacamento = ct2.texto.espacamento;
    ct3.texto.fonte = ct2.texto.fonte;
    ct3.texto.mouseSobre = false;
    ct3.texto.tamanho = ct2.texto.tamanho;
    ct3.caixa.retangulo.y += ct2.caixa.retangulo.height + 15.0f;
    temp = MeasureTextEx(*ct3.texto.fonte, ct3.texto.conteudo, ct3.texto.tamanho, ct3.texto.espacamento);
    ct3.texto.posicao = {
        ct3.caixa.retangulo.x + (ct3.caixa.retangulo.width - temp.x)/2,
        ct3.caixa.retangulo.y + (ct3.caixa.retangulo.height - temp.y)/2
    };
}

void carregarDicionario(Dicionario opcao,  palavra_lista::ListaPalavra &lista) {
    string_lista::String linha;
    std::ifstream arquivo;
    if (opcao == PORTUGUES)
        arquivo.open("portugues.txt");
    else
        arquivo.open("ingles.txt");
    while (!arquivo.eof()) {
        linha = string_lista::utils::lerLinha(arquivo);
        if (linha.primeiro->val >= 3)
            palavra_lista::insereFinal(lista, linha);
        else string_lista::utils::destruir(linha);
    }
    arquivo.close();
}
