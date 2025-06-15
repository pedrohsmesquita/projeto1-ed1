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
     * Inicializa a nossa String (idêntico a como listas são criadas). Utilizamos
     * a célula cabeça para armazenar o tamanho da String.
     */
    void criarLista(String &valStr);

    /**
     * Insere um novo nó (caractere) ao final da nossa String.
     */
    void insereFinal(String &valStr, char c);

    namespace utils {
        /**
         * Lê linha de um arquivo até encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo);

        /**
         * Deleta toda a String, deixando apenas a cabeça da String.
         */
        void deletar(String &valStr);

        // TODO: Função para comparar se duas String são iguais
        // TODO: Função para checar se todas as letras contidas em uma String estão na outra String
        // TODO: Função para retornar embaralhar uma String embaralhada
    }
}

#endif // STRING_LISTA_H
