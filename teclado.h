#ifndef TECLADO_H
#define TECLADO_H

#include "raylib.h"
#include <cstring>
#include "interface.h"
#include "string_lista.h"

void lerEntradaTeclado(string_lista::String &listaS, lista_grafica::ListaLetra &listaV, int maxTam) {
    int tecla = toupper(GetCharPressed());

    while (tecla > 0) {
        if (tecla >= 'A' && tecla <= 'Z' && listaS.primeiro->val < maxTam) {
            string_lista::insereFinal(listaS, tecla);
            lista_grafica::insereFinal(listaV, listaS.ultimo);
        }
        tecla = toupper(GetCharPressed());
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        string_lista::removeFinal(listaS);
        lista_grafica::removeFinal(listaV);
    }
}


#endif // TECLADO_H
