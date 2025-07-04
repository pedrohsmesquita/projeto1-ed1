#ifndef TORCIDO_H
#define TORCIDO_H

#include "interface.h"
#include "string_lista.h"
#include "mouse.h"
#include "palavras_lista.h"

enum Dicionario {INVLD, PORTUGUES, INGLES};

void telaJogo(bool &janelaAtiva, tbl_indxd::TabelaIndexada &tabela);

Dicionario telaSelecaoDicionario(bool &janelaAtiva);

void telaAjuda();

#endif // TORCIDO_H
