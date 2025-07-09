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
        if (vazia(lista))
            return ;
        NodoPalavra *aux = lista.primeiro->prox, *tmp = lista.primeiro;

        while (aux->prox != NULL) {
            tmp = aux;
            aux = aux->prox;
        }
        tmp->prox = NULL;
        lista.ultimo = tmp;
        delete aux;
    }

    void removeInicio(ListaPalavra &lista) {
        if (vazia(lista))
            return;
        NodoPalavra *aux = lista.primeiro->prox;
        lista.primeiro->prox = aux->prox;
        if (lista.primeiro->prox == NULL)
            lista.ultimo = lista.primeiro;
        delete aux;
    }

    bool pesquisa(ListaPalavra &lista, string_lista::String &listaS) {
        NodoPalavra *no = lista.primeiro->prox;

        while (no != NULL) {
            if (string_lista::utils::comparaString(no->palavra, listaS))
                return true;
            no = no->prox;
        }

        return false;
    }

    namespace utils {
        void inserePalavra(ListaPalavra &lista, string_lista::String &palavra) {
            string_lista::String copia;
            string_lista::criarLista(copia);
            string_lista::utils::strcpy(copia, palavra);
            insereFinal(lista, copia);
        }

        void salvarEmDisco(ListaPalavra &lista) {
            NodoPalavra *no = lista.primeiro->prox;
            std::ofstream arquivo;

            arquivo.open("acertos.txt");

            while (no != NULL) {
                string_lista::utils::salvarLinha(no->palavra, arquivo);
                no = no->prox;
            }
            arquivo.close();
        }

        void deletar(ListaPalavra &lista) {
            while (!vazia(lista))
                removeInicio(lista);
        }

        void deletarConteudo(ListaPalavra &lista) {
            NodoPalavra *no = lista.primeiro->prox;

            while (no != NULL) {
                string_lista::utils::destruir(no->palavra);
                no = no->prox;
            }
        }

        void destruicaoProfunda(ListaPalavra &lista) {
            deletarConteudo(lista);
            destruir(lista);
        }


        void destruir(ListaPalavra &lista) {
            deletar(lista);
            delete lista.primeiro;
        }
    }
}

namespace tbl_indxd {
    void criarTabela(TabelaIndexada &tabela) {
        tabela.dados = new PrimeiroIndice;
        PrimeiroIndice *no = tabela.dados;
        no->celula = NULL;

        int i = 25;
        while (i > 0) {
            no->prox = new PrimeiroIndice;
            no = no->prox;
            no->celula = NULL;
            no->prox = NULL;
            i--;
        }
    }

    namespace utils {
        PrimeiroIndice *buscaIndice(TabelaIndexada &tabela, string_lista::String &palavra) {
            int caractere = palavra.primeiro->prox->val;
            PrimeiroIndice *indice = tabela.dados;

            for (int i = caractere - 'A'; i > 0; i--)
                indice = indice->prox;

            return indice;
        }

        palavra_lista::NodoPalavra *buscaProximoIndice(PrimeiroIndice *indice) {
            palavra_lista::NodoPalavra *proximo_indice = NULL;

            while (indice->prox != NULL && indice->prox->celula == NULL)
                indice = indice->prox;
            if (indice->prox)
                proximo_indice = indice->prox->celula;

            return proximo_indice;
        }

        bool palavraInseridaExiste(string_lista::String &entrada, TabelaIndexada &tabela) // passo a palavra inserida e a lista externa (que contem a letra inicial de cada palavra da lista)
        {
            palavra_lista::NodoPalavra *palavra_no, *proximo_indice;
            PrimeiroIndice *indice = buscaIndice(tabela, entrada);

            if (indice->celula == NULL)
                return false;

            palavra_no = indice->celula;
            proximo_indice = buscaProximoIndice(indice);

            while (palavra_no != proximo_indice)
            {
                if (string_lista::utils::comparaString(entrada, palavra_no->palavra))
                    return true;
                palavra_no = palavra_no->prox;
            }
            return false;
        }

        void escolherPalavra(TabelaIndexada &tabela, string_lista::String &palavra) {
            int totalPalavras = 0;
            int numAleatorio;
            palavra_lista::NodoPalavra *atual, *prox;
            PrimeiroIndice *auxL;

            do {
                auxL = tabela.dados;
                numAleatorio = rand() % 26;
                for (int i = 0; i < numAleatorio; i++)
                    auxL = auxL->prox;
            } while (auxL->celula == NULL);

            atual = auxL->celula;
            prox = buscaProximoIndice(auxL);
            totalPalavras = 0;
            char c = atual->palavra.primeiro->prox->val;
            while (atual != prox) {
                totalPalavras++;
                atual = atual->prox;
            }

            numAleatorio = rand() % totalPalavras;
            atual = auxL->celula;
            for (int i = 0; i < numAleatorio; i++)
                atual = atual->prox;

            palavra = atual->palavra;
        }

        void indexarTabela(TabelaIndexada &tabela, palavra_lista::ListaPalavra &listaPalavra) {
            palavra_lista::NodoPalavra *no = listaPalavra.primeiro->prox;
            PrimeiroIndice *indice = tabela.dados;
            char primeiroCaractere;

            while (no != NULL) {
                primeiroCaractere = no->palavra.primeiro->prox->val;

                indice = buscaIndice(tabela, no->palavra);
                indice->celula = no;
                while (no != NULL && primeiroCaractere == no->palavra.primeiro->prox->val) {
                    no = no->prox;
                }
            }
        }

        void destruir(TabelaIndexada &tabela) {
            PrimeiroIndice *indice1 = tabela.dados;

            while (indice1 != NULL) {
                PrimeiroIndice *aux = indice1->prox;
                delete indice1;
                indice1 = aux->prox;
            }
        }
    }
}

