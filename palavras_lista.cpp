#include "palavras_lista.h"

namespace palavra_lista {
    void criarLista(ListaPalavra &lista) {
        lista.primeiro = new NodoPalavra;
        lista.primeiro->prox = NULL;
        lista.ultimo = lista.primeiro;
    }

    bool vazia(ListaPalavra &lista) {
        return lista.primeiro == lista.ultimo;
    }

    void insereFinal(ListaPalavra &lista, string_lista::String &palavra) {
        NodoPalavra *ptr = new NodoPalavra;
        ptr->palavra = palavra;
        ptr->prox = NULL;
        lista.ultimo->prox = ptr;
        lista.ultimo = ptr;
    }

    void removeFinal(ListaPalavra &lista) {
        if (vazia(lista)) {
            printf("Lista vazia.\n");
            exit(1);                    // Por agora, vamos fechar
        }
        NodoPalavra *aux = lista.primeiro->prox, *tmp = lista.primeiro;

        while (aux->prox != NULL) {
            tmp = aux;
            aux = aux->prox;
        }
        tmp->prox = NULL;
        lista.ultimo = tmp;
        delete aux;
    }

    namespace utils {
        void inserePalavra(ListaPalavra &lista, string_lista::String &palavra) {
            string_lista::String copia;
            string_lista::criarLista(copia);
            string_lista::utils::strcpy(copia, palavra);
            insereFinal(lista, copia);
        }
    }
}

namespace dicionario {
    void inicializarListaInterna(ListaInterna &lista) {
        ListaInterna *aux = &lista;
        // Cria primeira lista de palavras
        palavra_lista::criarLista(aux->lista);

        // Percorre laço para criar 26 (1 + 25) ListaInterna, cada uma
        // inicializando uma lista de palavra.
        for (int i = 0; i < 25; i++) {
            aux->prox = new ListaInterna;
            aux = aux->prox;
            palavra_lista::criarLista(aux->lista);
            aux->prox = NULL;
        }
    }

    void inicializarListaExterna(ListaExterna &lista) {
        ListaExterna *aux = &lista;
        // Cria primeira lista interna
        inicializarListaInterna(aux->listaI);

        // Percorre laço para criar 26 (1 + 25) ListaExterna.
        for (int i = 0; i < 25; i++) {
            aux->prox = new ListaExterna;
            aux = aux->prox;
            inicializarListaInterna(aux->listaI);
            aux->prox = NULL;
        }
    }

    namespace utils {
        /*
         * Ponteiro para ListaExterna foi enviado por ser mais conviente para percorrer a lista.
         * ListaExterna é percorrida em busca do nó que representa a primeira letra da String.
         *
         * Retorna um ponteiro para ListaInterna.
         */
        ListaInterna *buscaIndiceAlfabetico(ListaExterna *listaPtr, string_lista::String &palavra) {
            int caractere = palavra.primeiro->prox->val;

            for (int i = caractere - 'A'; i > 0; i--)
                listaPtr = listaPtr->prox;

            return &listaPtr->listaI;
        }

        /*
         * Ponteiro para ListaInterna foi enviado por ser mais conviente para percorrer a lista.
         * ListaInterna é percorrida em busca do nó que representa a segunda letra da String.
         *
         * Retorna um ponteiro para Palavra (que é a lista de palavras).
         */
        palavra_lista::ListaPalavra *buscaIndiceAlfabetico(ListaInterna *listaPtr, string_lista::String &palavra) {
            int caractere = palavra.primeiro->prox->prox->val;

            for (int i = caractere - 'A'; i > 0; i--)
                listaPtr = listaPtr->prox;

            return &listaPtr->lista;
        }

        void inserirPalavra(ListaExterna &listaE, string_lista::String &palavra) {
            ListaInterna *listaIPtr = buscaIndiceAlfabetico(&listaE, palavra);
            palavra_lista::ListaPalavra *palavraPtr = buscaIndiceAlfabetico(listaIPtr, palavra);
            palavra_lista::insereFinal(*palavraPtr, palavra);
        }

        void imprimir(ListaExterna *lista) {
            for (int i = 'a'; i <= 'z'; i++) {
                ListaInterna *listaIPtr = &lista->listaI;
                for (int j = 'a'; j <= 'z'; j++) {
                    palavra_lista::NodoPalavra *palavraPtr = listaIPtr->lista.primeiro->prox;
                    while (palavraPtr != NULL) {
                        //string_lista::utils::imprimir(palavraPtr->palavra);
                        palavraPtr = palavraPtr->prox;
                    }
                    listaIPtr = listaIPtr->prox;
                }
                lista = lista->prox;
            }
        }

        bool palavraInseridaExiste(string_lista::String &entrada, ListaExterna *listaPtr) // passo a palavra inserida e a lista externa (que contem a letra inicial de cada palavra da lista)
        {
            ListaInterna* endereco1 = buscaIndiceAlfabetico(listaPtr,entrada);
            palavra_lista::ListaPalavra* endereco2 = buscaIndiceAlfabetico(endereco1,entrada);
            palavra_lista::NodoPalavra* palavra_no = endereco2->primeiro->prox;
            while (palavra_no != NULL)
            {
                if (string_lista::utils::comparaString(entrada,palavra_no->palavra))
                    return true;
                palavra_no = palavra_no->prox;
            }
            return false;
        }

        void escolherPalavra(dicionario::ListaExterna *lista, string_lista::String &palavra) {
            int totalPalavras = 0;
            int numAleatorio;
            dicionario::ListaInterna *listaI;
            palavra_lista::NodoPalavra *atual;

            while (totalPalavras == 0) {
                dicionario::ListaExterna *auxL = lista;
                numAleatorio = rand() % 26;
                for (int i = 0; i < numAleatorio; i++)
                    auxL = auxL->prox;

                listaI = &auxL->listaI;
                numAleatorio = rand() % 26;
                for (int i = 0; i < numAleatorio; i++)
                    listaI = listaI->prox;

                atual = listaI->lista.primeiro->prox;
                totalPalavras = 0;
                while (atual != NULL) {
                    totalPalavras++;
                    atual = atual->prox;
                }

            }
            numAleatorio = rand() % totalPalavras;
            atual = listaI->lista.primeiro->prox;
            for (int i = 0; i < numAleatorio; i++)
                atual = atual->prox;

            palavra = atual->palavra;
        }
    }
}
