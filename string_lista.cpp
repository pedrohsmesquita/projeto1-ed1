#include "string_lista.h"

namespace string_lista {
    /**
     * Inicializa a nossa String (id�ntico a como listas s�o criadas). Utilizamos
     * a c�lula cabe�a para armazenar o tamanho da String.
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
     * Insere um novo n� (caractere) ao final da nossa String.
     */
    void insereFinal(String &lista, char c) {
        NodoString *no = new NodoString;
        no->val = c;
        no->null = 0;
        no->prox = NULL;
        if (lista.ultimo == lista.primeiro)
            no->ant = NULL;
        else no->ant = lista.ultimo;
        lista.ultimo->prox = no;
        lista.ultimo = no;
        lista.primeiro->val += 1;
    }

    void insereInicio(String &lista, char c) {
        NodoString *no = new NodoString;
        no->val = c;
        no->null = 0;
        no->prox = lista.primeiro->prox;
        no->ant = NULL;
        if (no->prox == NULL)
            lista.ultimo = no;
        else lista.primeiro->prox->ant = no;
        lista.primeiro->prox = no;
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
        lista.ultimo->prox = NULL;
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
         * L� linha de um arquivo at� encontrar o caractere de quebra de linha.
         * Retorna uma String da linha lida.
         */
        string_lista::String lerLinha(std::ifstream &arquivo) {
            char c;
            string_lista::String linha;

            criarLista(linha);
            while (arquivo.get(c) && c != '\n') {
                if (c == '-' || c == '\'') {
                    linha.primeiro->val = 0;
                    break;
                }
                string_lista::insereFinal(linha, toupper(c));
            }
            return linha;
        }

        /**
         * Deleta toda a String, deixando apenas a cabe�a da String.
         */
        void deletar(String &linha) {
            while (!vazia(linha))
                removeFinal(linha);
            linha.primeiro->val = 0;
        }

        void destruir(String &lista) {
            deletar(lista);
            delete lista.primeiro;
        }

        void strcpy(String &dest, String &orig) {
            NodoString *no = orig.primeiro->prox;

            while (no != NULL) {
                insereFinal(dest, no->val);
                no = no->prox;
            }
        }

        void intStr(String &dest, int n, int zeros) {
            deletar(dest);
            while (n > 0) {
                int resto = n % 10;
                insereInicio(dest, '0' + resto);
                n = n / 10;
                zeros--;
            }
            while (zeros > 0) {
                insereInicio(dest, '0');
                zeros--;
            }
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

                if(ContadorPalavras < ContadorEntrada){
                    return false;
                }
                 while (letraEntrada != NULL && letraEntrada->val == letraAtual) {
                    letraEntrada = letraEntrada->prox;  // Avan�a para pr�xima letra diferente
                }
            }
            return true;
        }

        void embaralhar(String &palavra) {
            int tamanho = palavra.primeiro->val;
            if (tamanho <= 1) return;

            for (int i = 0; i < tamanho; i++) {
                int pos1 = rand() % tamanho;
                int pos2 = rand() % tamanho;

                NodoString *n1 = palavra.primeiro->prox;
                for (int j = 0; j < pos1; j++) {
                    n1 = n1->prox;
                }

                NodoString *n2 = palavra.primeiro->prox;
                for (int j = 0; j < pos2; j++) {
                    n2 = n2->prox;
                }

                char temp = n1->val;
                n1->val = n2->val;
                n2->val = temp;
            }
        }
    }
}
