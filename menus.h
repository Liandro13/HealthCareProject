#ifndef MENUS_H
#define MENUS_H

#include "funcoes.h"

extern int codigomedico;
extern int codigoutente;
extern int opcao;


// Funções frontend
void menuprincipal(Utente** utentes, Medico** medicos, Utente** fila_espera);
void menugerirmedicos(Utente** utentes, Medico** medicos, Utente** fila_espera);
void menugerirutentes(Utente** utentes, Medico** medicos, Utente** fila_espera);


#endif