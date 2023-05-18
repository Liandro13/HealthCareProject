// funçoes.h

#ifndef FUNCOES_H
#define FUNCOES_H

//          BACKEND

typedef struct utente
{
    int codigo;
    char nome[100];
    int codigo_medico;
    struct Utente* prox;
    
} Utente;

typedef struct medico
{
    int codigo;
    char nome[100];
    Utente* fila_espera;
    struct Medico* prox;
}Medico;


// FunÃ§Ãµes backend
// Funções backend
Utente* criar_utente(char *nome, int codigo_medico);
void inserir_utente(Utente** lista_utentes, char* nome, int codigo_medico, int codigo);
Medico* criar_medico(int codigo, char* nome);
void inserir_medico(Medico** medicos, int codigo, char* nome);
void remover_utente(Utente** utentes, Medico** medicos, int codigo_utente);
void remover_medico(Medico** medicos, int codigo);
void listar_utentes(Utente** utentes);
void listar_medicos(Medico** medicos);
void carregar_utentes(Utente** utentes, Medico** medicos);
void carregar_medicos(Medico** medicos);
void carregar_fila_espera(Utente** fila_espera, Utente** utentes, Medico** medicos);
void carregar_tudo(Medico** medicos, Utente** utentes, Utente** fila_espera);
void salvar_utentes(Utente** utentes);
void salvar_medicos(Medico** medicos);
void salvar_fila_espera(Utente** fila_espera);;
void salvar_tudo(Medico** medicos, Utente** utentes, Utente** fila_espera);
void registar_entrada(Utente** fila_utentes, Utente** utentes, Medico** medicos, int codigo_utente);
void retirar_entrada(Utente** fila_utentes, Medico** medicos);
int contar_doentes_espera(Medico** medicos, int codigo_medico);
Utente* proximo_utente_atendido(Medico** medicos, int codigo_medico);
void listar_fila_espera_medico(Medico** medicos, int codigo_medico);
int contar_doentes_espera(Medico** medicos, int codigo_medico);
Medico* medico_mais_doentes(Medico** medicos);
void listar_utentes_por_medico(Utente** utentes, Medico** medicos);
Medico* procurar_medico(Medico** medicos, int codigo);
Utente* procurar_utente(Utente** utentes, int codigo);
void editar_utente(Utente** utentes, Medico** medicos, int codigo, char* novo_nome);
void editar_medico(Medico** medicos, int codigo, char* novo_nome);
void consultar_medico(Medico** medicos, Utente** utentes, int codigo);
void consultar_utente(Medico** medicos, Utente** utentes, Utente** fila_espera, int codigo_utente);
Utente* ultimo_utente(Utente** fila_utentes);
void listar_utentes_fila(Utente** fila_utentes);
void utentes_por_medico(Medico** medicos, Utente** utentes);
void listar_doentes_sem_espera(Utente** fila_espera, Utente** utentes);
void listar_medicos_toda_informacao(Utente** utentes, Medico** medicos);


int contar_doentes_espera_medico(Utente** fila_utentes, int codigo_medico);
void apresentar_medico_com_mais_doentes(Medico** medicos, Utente** fila_utentes);
#endif
