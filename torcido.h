#ifndef TORCIDO_H
#define TORCIDO_H

#include "interface.h"
#include "string_lista.h"
#include "mouse.h"
#include "palavras_lista.h"

//void telaJogo(bool &janelaAtiva, dicionario::ListaExterna &dicionario);
void telaJogo(bool &janelaAtiva, tbl_indxd::TabelaIndexada &tabela);
void telaAjuda();

#endif // TORCIDO_H
