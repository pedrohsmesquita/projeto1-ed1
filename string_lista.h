#ifndef STRING_LISTA_H
#define STRING_LISTA_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

namespace string_lista {
    struct NodoString {
        char val;
        char null;
        NodoString *prox;
        NodoString *ant;
    };

    struct String {
        NodoString *primeiro;
        NodoString *ultimo;
    };

    typedef NodoString *Apontador;

    /**
     * Inicializa a nossa String (id�ntico a como listas s�o criadas). Utilizamos
     * a c�lula cabe�a para armazenar o tamanho da String.
     */
    void criarLista(String &lista);

    /**
     * Insere um novo n� (caractere) ao final da nossa String.
     */
    void insereFinal(String &lista, char c);

    void removeFinal(String &lista);

    namespace utils {
        /**
         * Percorre toda a string imprimindo os caracteres na tela.
         */
        void imprimir(String &lista);

        /**
         * L� linha de um arquivo at� encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo);

        /**
         * Deleta toda a String, deixando apenas a cabe�a da String.
         */
        void deletar(String &valStr);
        /**
         * Deleta toda a String, incluindo a cabe�a.
         */
        void destruir(String &lista);

        void strcpy(String &dest, String &orig);

        void intStr(String &dest, int n, int zeros);

        bool comparaString(String &entrada, String &palavra_dicionario);

        bool LetrasContidasNaPalavra(string_lista::String &entrada, string_lista::String &palavra);

        void embaralhar(String &palavra);
    }
}

#endif // STRING_LISTA_H
