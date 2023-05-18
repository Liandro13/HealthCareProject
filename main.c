#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "headers/funcoes.h"
#include "headers/menus.h"



int main(int argc, const char * argv[])
{

    setlocale(LC_ALL, "PORTUGUESE");
    
    // Criação de uma fila de utentes e de médicos
    
    Utente* utentes = NULL;
    Medico* medicos = NULL;
    Utente* fila_espera = NULL;
    
    carregar_tudo(&medicos, &utentes, &fila_espera);
    menuprincipal(&utentes, &medicos, &fila_espera);

    return 0;
}




