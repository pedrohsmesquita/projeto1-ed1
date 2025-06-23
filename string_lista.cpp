#include "string_lista.h"

namespace string_lista {
    /**
     * Inicializa a nossa String (idêntico a como listas são criadas). Utilizamos
     * a célula cabeça para armazenar o tamanho da String.
     */
    void criarLista(String &lista) {
        lista.primeiro = new NodoString;
        lista.primeiro->val = 0;
        lista.primeiro->prox = NULL;
        lista.primeiro->ant = NULL;
        lista.ultimo = lista.primeiro;
    }

    bool vazia(String &lista) {
        return lista.primeiro == lista.ultimo;
    }

    /**
     * Insere um novo nó (caractere) ao final da nossa String.
     */
    void insereFinal(String &lista, char c) {
        NodoString *no = new NodoString;
        no->val = c;
        no->prox = NULL;
        no->ant = lista.ultimo;
        if (lista.ultimo == lista.primeiro)
            no->ant = NULL;
        else no->ant = lista.ultimo;
        lista.ultimo->prox = no;
        lista.ultimo = no;
        lista.primeiro->val += 1;
    }

    void removeFinal(String &lista) {
        if (vazia(lista))
            return;
        NodoString *no = lista.ultimo;
        lista.ultimo = no->ant;
        if (lista.ultimo == NULL)
            lista.ultimo = lista.primeiro;
        else lista.ultimo->prox = NULL;
        lista.primeiro->val--;
        delete no;
    }

    namespace utils {
        /**
         * Percorre toda a string imprimindo os caracteres na tela.
         */
        void imprimir(String &lista) {
            NodoString *aux = lista.primeiro->prox;

            while (aux != NULL) {
                printf("%c", aux->val);
                aux = aux->prox;
            }
            printf("\n");
        }

        /**
         * Lê linha de um arquivo até encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo) {
            char c;
            string_lista::String linha;

            criarLista(linha);
            while (arquivo.get(c) && c != '\n') {
                if (c == '-') {
                    linha.primeiro->val = 0;
                    break;
                }
                string_lista::insereFinal(linha, c);
            }
            return linha;
        }

        /**
         * Deleta toda a String, deixando apenas a cabeça da String.
         */
        void deletar(String &linha) {
            NodoString *aux = linha.primeiro->prox;

            while (aux != NULL) {
                linha.primeiro->prox = aux->prox;
                delete aux;
                aux = linha.primeiro->prox;
            }
            linha.ultimo = linha.primeiro;
        }

        bool comparaString(String &entrada, String &palavra_dicionario)
        {
            if (entrada.primeiro->val != palavra_dicionario.primeiro->val)
                return false;
            NodoString* palavra1 = entrada.primeiro->prox;
            NodoString* palavra2 = palavra_dicionario.primeiro->prox;
            while (palavra1 != NULL && palavra2 != NULL && palavra1->val == palavra2->val)
            {
                palavra1 = palavra1->prox;
                palavra2 = palavra2->prox;
            }
            return palavra1 == NULL && palavra2 == NULL && palavra1 == palavra2; // retorna true se for verdade e false se nao for
        }

        bool LetrasContidasNaPalavra(string_lista::String &entrada, string_lista::String &palavra){
            string_lista::Apontador letraEntrada = entrada.primeiro->prox;
            while(letraEntrada!=NULL){
                //LetraAtual assume a letra
                char letraAtual = letraEntrada->val;

                //ficara responsavel por contar quantas letras tem na entrada
                int ContadorEntrada=0;

                string_lista::Apontador auxEntrada = entrada.primeiro->prox; //contar quantas letras tem na entrada;
                while(auxEntrada!=NULL){
                    if(letraAtual == auxEntrada->val){
                        ContadorEntrada++;
                    }
                    auxEntrada = auxEntrada->prox;
                }
                int ContadorPalavras= 0;
                string_lista::Apontador auxPalavra = palavra.primeiro->prox;
                while(auxPalavra!=NULL){
                    if(letraAtual == auxPalavra->val){
                        ContadorPalavras++;
                    }
                    auxPalavra =auxPalavra->prox;
                }

                if(ContadorPalavras > ContadorEntrada){
                    return false;
                }
                 while (letraEntrada != NULL && letraEntrada->val == letraAtual) {
                    letraEntrada = letraEntrada->prox;  // Avança para próxima letra diferente
                }
            }
            return true;
        }
    }
}
