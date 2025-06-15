#include "interface.h"

namespace letra_lista {
    void criarLista(ListaLetra &lista, LetraEstilo &estiloBase) {
        lista.primeiro = new NodoLetra;
        lista.primeiro->info.estilo = estiloBase;
        lista.primeiro->info.letra = NULL;
        lista.primeiro->prox = NULL;
        lista.primeiro->ant = NULL;
        lista.ultimo = lista.primeiro;
    }

    bool vazia(ListaLetra &lista) {
        return lista.primeiro == lista.ultimo;
    }

    void insereFinal(ListaLetra &lista, string_lista::NodoString *letra) {
        NodoLetra *p = new NodoLetra;
        p->info.estilo = lista.primeiro->info.estilo;
        p->info.letra = letra;
        p->prox = NULL;
        if (lista.ultimo == lista.primeiro)
            p->ant = NULL;
        else p->ant = lista.ultimo;
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
        else lista.ultimo->prox = NULL;
        delete p;
    }
}

namespace lista_list {
    void criarLista(ListaLista &lista) {
        lista.primeiro = new NodoLista;
        lista.primeiro->prox = NULL;
        lista.ultimo = lista.primeiro;
    }

    void insereFinal(ListaLista &lista, letra_lista::ListaLetra &palavra) {
        NodoLista *p = new NodoLista;
        p->palavra = palavra;
        p->prox = NULL;
        lista.ultimo->prox = p;
        lista.ultimo = p;
    }
}
