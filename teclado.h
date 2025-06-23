#ifndef TECLADO_H
#define TECLADO_H

#include "raylib.h"
#include <cstring>
#include "interface.h"
#include "string_lista.h"

void lerEntradaTeclado(string_lista::String &listaS, letra_lista::ListaLetra &listaV, int maxTam) {
    int tecla = toupper(GetCharPressed());

    while (tecla > 0) {
        if (tecla >= 'A' && tecla <= 'Z' && listaS.primeiro->val < maxTam) {
            string_lista::insereFinal(listaS, tecla);
            letra_lista::insereFinal(listaV, listaS.ultimo);
        }
        tecla = toupper(GetCharPressed());
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        string_lista::removeFinal(listaS);
        letra_lista::removeFinal(listaV);
    }
}


#endif // TECLADO_H
