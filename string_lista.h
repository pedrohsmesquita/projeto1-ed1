#ifndef STRING_LISTA_H
#define STRING_LISTA_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

namespace string_lista {
    struct NodoString {
        char val;
        NodoString *prox;
    };

    struct String {
        NodoString *primeiro;
        NodoString *ultimo;
    };

    /**
     * Inicializa a nossa String (id�ntico a como listas s�o criadas). Utilizamos
     * a c�lula cabe�a para armazenar o tamanho da String.
     */
    void criarLista(String &valStr);

    /**
     * Insere um novo n� (caractere) ao final da nossa String.
     */
    void insereFinal(String &valStr, char c);

    namespace utils {
        /**
         * L� linha de um arquivo at� encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo);

        /**
         * Deleta toda a String, deixando apenas a cabe�a da String.
         */
        void deletar(String &valStr);

        // TODO: Fun��o para comparar se duas String s�o iguais
        // TODO: Fun��o para checar se todas as letras contidas em uma String est�o na outra String
        // TODO: Fun��o para retornar embaralhar uma String embaralhada
    }
}

#endif // STRING_LISTA_H
