#ifndef TECLADO_H
#define TECLADO_H

#include "raylib.h"
#include <cstring>
#include "interface.h"
#include "string_lista.h"

struct TecladoStatus {
    bool insercao;
    bool exclusao;
};

TecladoStatus lerEntradaTeclado(string_lista::String &listaS, lista_grafica::ListaLetra &listaV, int maxTam) {
    int tecla = toupper(GetCharPressed());
    TecladoStatus status = {false, false};

    while (tecla > 0) {
        if (tecla >= 'A' && tecla <= 'Z' && listaS.primeiro->val < maxTam) {
            string_lista::insereFinal(listaS, tecla);
            lista_grafica::utils::inserirLetra(listaV, listaS.ultimo, true, 2.0f);
            status.insercao = true;
        }
        tecla = toupper(GetCharPressed());
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        string_lista::removeFinal(listaS);
        lista_grafica::removeFinal(listaV);
        status.exclusao = true;
    }

    return status;
}


#endif // TECLADO_H
