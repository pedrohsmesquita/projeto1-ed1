#include "string_lista.h"

namespace string_lista {
    /**
     * Inicializa a nossa String (id�ntico a como listas s�o criadas). Utilizamos
     * a c�lula cabe�a para armazenar o tamanho da String.
     */
    void criarLista(String &valStr) {
        valStr.primeiro = new NodoString;
        valStr.primeiro->val = 0;
        valStr.primeiro->prox = NULL;
        valStr.ultimo = valStr.primeiro;
    }

    /**
     * Insere um novo n� (caractere) ao final da nossa String.
     */
    void insereFinal(String &valStr, char c) {
        NodoString *no = new NodoString;
        no->val = c;
        no->prox = NULL;

        valStr.ultimo->prox = no;
        valStr.ultimo = valStr.ultimo->prox;
        valStr.primeiro->val += 1;
    }

    namespace utils {
        /**
         * L� linha de um arquivo at� encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo) {
            char c;
            string_lista::String linha;

            criarLista(linha);
            while (arquivo.get(c) && c != '\n')
                string_lista::insereFinal(linha, c);
            return linha;
        }

        /**
         * Deleta toda a String, deixando apenas a cabe�a da String.
         */
        void deletar(String &valStr) {
            NodoString *aux = valStr.primeiro->prox;

            while (aux != NULL) {
                valStr.primeiro->prox = aux->prox;
                delete aux;
                aux = valStr.primeiro->prox;
            }
            valStr.ultimo = valStr.primeiro;
        }
    }
}
