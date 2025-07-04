#include "interface.h"

namespace lista_grafica {
    void criarLista(ListaLetra &lista) {
        lista.primeiro = new NodoLetra;
        lista.primeiro->info.letra = NULL;
        lista.primeiro->prox = NULL;
        lista.primeiro->ant = NULL;
        lista.ultimo = lista.primeiro;
    }

    void criarLista(ListaLetra &lista, Caixa &caixa) {
        lista.primeiro = new NodoLetra;
        lista.primeiro->info.letra = NULL;
        lista.primeiro->prox = NULL;
        lista.primeiro->ant = NULL;
        lista.primeiro->info.caixa = caixa;
        lista.ultimo = lista.primeiro;
    }

    void criarLista(ListaCaixa &lista) {
        lista.primeiro = new NodoCaixa;
        lista.primeiro->prox = NULL;
        lista.ultimo = lista.primeiro;
    }

    bool vazia(ListaLetra &lista) {
        return lista.primeiro == lista.ultimo;
    }

    bool vazia(ListaCaixa &lista) {
        return lista.primeiro == lista.ultimo;
    }

    void insereFinal(ListaLetra &lista, string_lista::NodoString *letra) {
        NodoLetra *p = new NodoLetra;
        //p->info.estilo = lista.primeiro->info.estilo;
        //p->info.caixa = lista.primeiro->info.caixa;
        p->info.letra = letra;
        p->prox = NULL;
        if (lista.ultimo == lista.primeiro)
            p->ant = NULL;
        else p->ant = lista.ultimo;
        lista.ultimo->prox = p;
        lista.ultimo = p;
    }

    void insereFinal(ListaCaixa &lista, Caixa &caixa) {
        NodoCaixa *p = new NodoCaixa;

        p->caixa = caixa;
        p->prox = NULL;
        lista.ultimo->prox = p;
        lista.ultimo = p;
    }

    void removeInicio(ListaLetra &lista) {
        if (vazia(lista))
            return;
        NodoLetra *p = lista.primeiro->prox;
        lista.primeiro->prox = p->prox;
        if (lista.primeiro->prox == NULL)
            lista.ultimo = lista.primeiro;
        else lista.primeiro->prox->ant = NULL;
        delete p;
    }

    void removeFinal(ListaLetra &lista) {
        if (vazia(lista))
            return;
        NodoLetra *p = lista.ultimo;
        lista.ultimo = p->ant;
        if (lista.ultimo == NULL)
            lista.ultimo = lista.primeiro;
        lista.ultimo->prox = NULL;
        delete p;
    }

    void removeFinal(ListaCaixa &lista) {
        if (vazia(lista))
            return;
        NodoCaixa *tmp = lista.primeiro, *aux = lista.primeiro->prox;

        while (aux->prox != NULL) {
            tmp = aux;
            aux = aux->prox;
        }
        tmp->prox = NULL;
        lista.ultimo = tmp;
        delete aux;
    }

    void removeInicio(ListaCaixa &lista) {
        if (vazia(lista))
            return;
        NodoCaixa *p = lista.primeiro->prox;
        lista.primeiro->prox = p->prox;
        if (lista.primeiro->prox == NULL)
            lista.ultimo = lista.primeiro;
        delete p;
    }

    namespace utils {
        void inserirString(ListaLetra &lista, string_lista::String &listaS, float espaco) {
            string_lista::NodoString *no = listaS.primeiro->prox;
            while (no != NULL) {
                inserirLetra(lista, no, false, espaco);
                no = no->prox;
            }
        }

        void inserirStringEstililizada(ListaLetra &lista, string_lista::String &listaS) {
            string_lista::NodoString *no = listaS.primeiro->prox;
            while (no != NULL) {
                inserirLetra(lista, no);
                no = no->prox;
            }
        }

        void inserirString(ListaLetra &lista, string_lista::String &listaS) {
            string_lista::NodoString *no = listaS.primeiro->prox;
            while (no != NULL) {
                insereFinal(lista, no);
                no = no->prox;
            }
        }

        void deletar(ListaLetra &lista) {
            while (!vazia(lista))
                removeInicio(lista);
        }

        void deletar(ListaCaixa &lista) {
            while (!vazia(lista))
                removeInicio(lista);
        }

        void destruir(ListaLetra &lista) {
            deletar(lista);
            delete lista.primeiro;
        }

        void destruir(ListaCaixa &lista) {
            deletar(lista);
            delete lista.primeiro;
        }

        void inserirLetra(ListaLetra &lista, string_lista::NodoString *letra, bool animando, float espaco) {
            insereFinal(lista, letra);
            lista.ultimo->info.animando = animando;
            if (lista.ultimo->ant == NULL) {
                lista.ultimo->info.caixa = lista.primeiro->info.caixa;
                lista.ultimo->info.estilo = lista.primeiro->info.estilo;
                centralizarTextoCaixa(lista.ultimo);
            } else {
                lista.ultimo->info.estilo = lista.ultimo->ant->info.estilo;
                lista.ultimo->info.caixa = lista.ultimo->ant->info.caixa;
                lista.ultimo->info.caixa.retangulo.x += lista.ultimo->info.caixa.retangulo.width + espaco;
                centralizarTextoCaixa(lista.ultimo);
            }
            if (animando) {
                lista.ultimo->info.estilo.posicao.y = 0;
                lista.ultimo->info.caixa.retangulo.y = 0;
            }
        }

        void inserirLetra(ListaLetra &lista, string_lista::NodoString *letra) {
            insereFinal(lista, letra);
            if (lista.ultimo->ant == NULL) {
                lista.ultimo->info.estilo = lista.primeiro->info.estilo;
            } else {
                Vector2 medida = MeasureTextEx(*lista.ultimo->ant->info.estilo.fonte,
                                              &lista.ultimo->ant->info.letra->val,
                                              lista.ultimo->ant->info.estilo.tamanho,
                                              0.0f);
                lista.ultimo->info.estilo = lista.ultimo->ant->info.estilo;
                lista.ultimo->info.estilo.posicao.x += medida.x;
            }
        }

        void estilizarLista(ListaLetra &lista, LetraEstilo &estilo) {
            NodoLetra *no = lista.primeiro->prox, *ant;

            no->info.estilo = estilo;
            ant = no;
            no = no->prox;
            while (no != NULL) {
                no->info.estilo = ant->info.estilo;
                Vector2 medida = MeasureTextEx(*ant->info.estilo.fonte, &ant->info.letra->val,
                                               ant->info.estilo.tamanho, 0.0f);
                no->info.estilo.posicao.x += medida.x;
                ant = no;
                no = no->prox;
            }
        }
    }
}

namespace lista_list {
    void criarLista(ListaLista &lista) {
        lista.primeiro = new NodoLista;
        lista.primeiro->prox = NULL;
        lista.ultimo = lista.primeiro;
    }

    void insereFinal(ListaLista &lista, lista_grafica::ListaLetra &palavra) {
        NodoLista *p = new NodoLista;
        p->palavra = palavra;
        p->prox = NULL;
        lista.ultimo->prox = p;
        lista.ultimo = p;
    }

    bool vazia(ListaLista &lista) {
        return lista.primeiro == lista.ultimo;
    }

    void removeInicio(ListaLista &lista) {
        if (vazia(lista))
            return;
        NodoLista *aux = lista.primeiro->prox;
        lista.primeiro->prox = aux->prox;
        if (lista.primeiro->prox == NULL)
            lista.ultimo = lista.primeiro;
        delete aux;
    }

    namespace utils {
        void inserePalavra(ListaLista &lista, palavra_lista::ListaPalavra &palavra) {
            NodoLista *ant = lista.ultimo;
            lista_grafica::ListaLetra novaPalavra;
            lista_grafica::LetraEstilo estilo;
            lista_grafica::criarLista(novaPalavra);
            lista_grafica::utils::inserirString(novaPalavra, palavra.ultimo->palavra);
            insereFinal(lista, novaPalavra);

            if (lista.primeiro->prox == lista.ultimo) {
                estilo = lista.primeiro->palavra.primeiro->info.estilo;
            } else {
                estilo = ant->palavra.primeiro->prox->info.estilo;
                estilo.posicao.y += 16.0f;
            }
            lista_grafica::utils::estilizarLista(lista.ultimo->palavra, estilo);
        }

        void deletarConteudo(ListaLista &lista) {
            NodoLista *no = lista.primeiro->prox;

            while (no != NULL) {
                lista_grafica::utils::destruir(no->palavra);
                no = no->prox;
            }
        }

        void deletar(ListaLista &lista) {
            deletarConteudo(lista);
            while (!vazia(lista))
                removeInicio(lista);
        }

        void destruir(ListaLista &lista) {
            deletar(lista);
            delete lista.primeiro;
        }
    }
}

#define OPENSANS_BOLD "assets/fonts/open-sans/OpenSans-Bold.ttf"
#define OPENSANS_SEMIBOLD "assets/fonts/open-sans/OpenSans-Semibold.ttf"

Fontes fontes;

void carregarFontes() {
    fontes.openSansBold48 = LoadFontEx(OPENSANS_BOLD, LETRA_BOTOES_TAM, NULL, 0);
    fontes.openSansBold30 = LoadFontEx(OPENSANS_BOLD, LETRA_ESCOLHIDA_TAM, NULL, 0);
    fontes.openSansSemiBold18 = LoadFontEx(OPENSANS_SEMIBOLD, 18.0f, NULL, 0);
    fontes.openSansSemiBold24 = LoadFontEx(OPENSANS_SEMIBOLD, LETRA_DIGITADA_TAM, NULL, 0);
}

Font *obterOpenSansBold48() {
    return &fontes.openSansBold48;
}

Font *obterOpenSansBold30() {
    return &fontes.openSansBold30;
}

Font *obterOpenSansSemiBold24() {
    return &fontes.openSansSemiBold24;
}

Font *obterOpenSansSemiBold18() {
    return &fontes.openSansSemiBold18;
}

void definirEstiloCabecaSorteada(lista_grafica::ListaLetra &lista) {
    lista_grafica::LetraEstilo estilo;
    Caixa caixa;

    estilo.fonte = obterOpenSansBold30();
    estilo.cor = WHITE;
    estilo.tamanho = LETRA_ESCOLHIDA_TAM;
    estilo.posicao = {26.0f, ALTURA_TELA - 64.0f};
    caixa.cor = BLACK;
    caixa.redondeza = 0.3f;
    caixa.retangulo = {estilo.posicao.x, estilo.posicao.y, 34.0f, estilo.tamanho + 8};
    caixa.segmentos = 10;
    lista.primeiro->info.estilo = estilo;
    lista.primeiro->info.caixa = caixa;
}

void centralizar(lista_grafica::ListaLetra &lista){
    lista_grafica::NodoLetra *no = lista.primeiro->prox;

    no = lista.primeiro->prox;
    centralizarTextoCaixa(no);
    no = no->prox;
    while (no != NULL) {
        no->info.caixa.retangulo.x = no->ant->info.caixa.retangulo.x + no->info.caixa.retangulo.width + 3.0f;
        centralizarTextoCaixa(no);
        no = no->prox;
    }
}

void centralizarTextoCaixa(lista_grafica::NodoLetra *no) {
    Vector2 medidaAtual = MeasureTextEx(*no->info.estilo.fonte, &no->info.letra->val,
                                        no->info.estilo.tamanho, 0.0f);
    no->info.estilo.posicao.x = (no->info.caixa.retangulo.x + no->info.caixa.retangulo.width/2) -
                            medidaAtual.x/2;
    no->info.estilo.posicao.y = (no->info.caixa.retangulo.y + no->info.caixa.retangulo.height/2) -
                            medidaAtual.y/2;;
}

void letrasPlaceholders(lista_grafica::ListaLetra &listaP, lista_grafica::ListaCaixa &listaC) {
    Caixa tmp;
    lista_grafica::NodoLetra *no = listaP.primeiro->prox;

    tmp.cor = (Color) {4, 35, 38, 255};
    tmp.redondeza = 0.2f;
    tmp.segmentos = 10;
    tmp.retangulo = {26.0f, ALTURA_TELA/2, 32.0f, 32.0f};
    while (no != NULL) {
        lista_grafica::insereFinal(listaC, tmp);
        no = no->prox;
        tmp.retangulo.x += tmp.retangulo.width + 2.0f;
    }
}
