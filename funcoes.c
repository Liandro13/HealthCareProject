#include "headers/funcoes.h"
#include "headers/menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

Utente* criar_utente (char *nome, int codigo_medico)
{
    Utente* novo_utente = (Utente*) malloc (sizeof(Utente));
    
    if (!novo_utente)
    {
        printf("Erro ao alocar memória para novo utente.\n");
        return NULL;
    }
    
    strcpy(novo_utente->nome, nome);
    novo_utente->codigo_medico = codigo_medico;
    novo_utente->codigo = codigoutente;
       
    novo_utente->prox = NULL;
       
    ++codigoutente;
    
    return novo_utente;
}



void inserir_utente(Utente** lista_utentes, char* nome, int codigo_medico, int codigo)
{
    // Cria o novo nó da lista de utentes
    Utente* novo_utente = criar_utente(nome, codigo_medico);
    
    if (novo_utente == NULL)
    {
        return;
    }
    
    novo_utente->codigo = codigo;

    // Adiciona o novo nó à lista de utentes
    if (*lista_utentes == NULL)
    {
        *lista_utentes = novo_utente;
    }
    else
    {
        Utente* atual = *lista_utentes;
        Utente* anterior = NULL;
        while (atual != NULL && atual->codigo < codigo)
        {
            anterior = atual;
            atual = atual->prox;
        }
        if (anterior == NULL)
        {
            novo_utente->prox = *lista_utentes;
            *lista_utentes = novo_utente;
        }
        else
        {
            novo_utente->prox = atual;
            anterior->prox = novo_utente;
        }
    }
}



Medico* criar_medico(int codigo, char* nome)
{
    Medico* novo_medico = (Medico*) malloc (sizeof(Medico));
    
    if (!novo_medico)
    {
        printf("Erro ao alocar memória para novo médico.\n");
        return NULL;
    }

    novo_medico->codigo = codigo;
    strncpy(novo_medico->nome, nome, sizeof(novo_medico->nome) - 1);
    novo_medico->nome[sizeof(novo_medico->nome) - 1] = '\0';
    novo_medico->fila_espera = NULL;
    novo_medico->prox = NULL;

    ++codigomedico;
    
    return novo_medico;
}



void inserir_medico(Medico** medicos, int codigo, char* nome)     //Insere no final da lista
{
    Medico* novo_medico = criar_medico(codigo, nome);
    
    if (novo_medico == NULL)
    {
        printf("Erro ao criar novo médico.\n");
        return;
    }

    if (*medicos == NULL)
    {
        *medicos = novo_medico;
    }
    else
    {
        Medico* atual = *medicos;
        Medico* anterior = NULL;
        
        while (atual != NULL && atual->codigo < codigo)
        {
            anterior = atual;
            atual = atual->prox;
        }
        
        if (anterior == NULL)
        {
            novo_medico->prox = *medicos;
            *medicos = novo_medico;
        }
        else
        {
            novo_medico->prox = atual;
            anterior->prox = novo_medico;
        }
    }
}

void inserir_utente_fila(Utente** fila_espera_geral, Medico** lista_medicos, Utente* novo_utente)
{
    if (fila_espera_geral == NULL || lista_medicos == NULL || novo_utente == NULL)
    {
        printf("Erro: argumentos inválidos.\n");
        return;
    }

    // Adiciona o novo utente à fila de espera geral
    if (*fila_espera_geral == NULL)
    {
        *fila_espera_geral = novo_utente;
        novo_utente->prox = NULL;
    }
    else
    {
        Utente* atual_geral = *fila_espera_geral;
        while (atual_geral->prox != NULL)
        {
            atual_geral = atual_geral->prox;
        }
        atual_geral->prox = novo_utente;
        novo_utente->prox = NULL;
    }

    // Adiciona o novo utente à fila de espera do médico correspondente
    int codigo_medico = novo_utente->codigo_medico;
    Medico* medico = *lista_medicos;
    while (medico != NULL && medico->codigo != codigo_medico)
    {
        medico = medico->prox;
    }
    if (medico == NULL)
    {
        printf("Erro: médico não encontrado.\n");
        return;
    }
    Utente* fila_medico = medico->fila_espera;
    if (fila_medico == NULL)
    {
        medico->fila_espera = novo_utente;
        novo_utente->prox = NULL;
    }
    else
    {
        Utente* atual_medico = fila_medico;
        while (atual_medico->prox != NULL)
        {
            atual_medico = atual_medico->prox;
        }
        atual_medico->prox = novo_utente;
        novo_utente->prox = NULL;
    }
}


void remover_utente(Utente** utentes, Medico** medicos, int codigo_utente)
{
    if (*utentes == NULL)
    {
        printf("Lista de utentes vazia.\n");
        return;
    }

    Utente* atual = *utentes;
    Utente* anterior = NULL;

    while (atual != NULL && atual->codigo != codigo_utente)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Utente com código %d não encontrado.\n", codigo_utente);
        return;
    }

    // Remover o utente da lista geral de utentes
    if (anterior == NULL)
    {
        *utentes = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    // Remover o utente da lista de utentes do médico correspondente
    Medico* medico = procurar_medico(medicos, atual->codigo_medico);
    
    if (medico != NULL)
    {
        remover_utente(&(medico->fila_espera), NULL, atual->codigo);
    }

    free(atual);
}

void remover_medico(Medico** medicos, int codigo)
{
    if (medicos == NULL || *medicos == NULL)
    {
        printf("Lista de médicos vazia.\n");
        return;
    }

    Medico* atual = *medicos;
    Medico* anterior = NULL;

    while (atual != NULL && atual->codigo != codigo)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Médico com código %d não encontrado.\n", codigo);
        return;
    }

    if (anterior == NULL)
    {
        *medicos = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}


void listar_utentes(Utente** utentes)
{
    system("cls"); // Limpa a tela

    if (*utentes == NULL)
    {
        printf("\n\nAinda não há utentes inseridos.\n\n");
        return;
    }

    printf("\n\nLista de utentes:\n");
    printf("Código\tNome\t\t\tCódigo médico\n");
    printf("--------------------------------------------------\n");
    
    Utente* atual = *utentes;
    
    while (atual != NULL)
    {
        printf("%d\t%-20s\t%d\n", atual->codigo, atual->nome, atual->codigo_medico);
        atual = atual->prox;
    }
    printf("\n\n");
}



void listar_medicos(Medico** medicos)
{
    if (*medicos == NULL)
    {
        printf("\nNão há médicos cadastrados.\n");
        return;
    }

    printf("\nLista de médicos:\n\n");
    printf("-----------------------------\n");
    printf("Código ->  Nome\n");
    printf("-----------------------------\n");
    Medico* atual = *medicos;
    while (atual != NULL)
    {
        printf("%d    ->   %s\n", atual->codigo, atual->nome);
        atual = atual->prox;
    }
    printf("-----------------------------\n");
}



void carregar_utentes(Utente** utentes, Medico** medicos)
{
    FILE* file = fopen("data/utentes.txt", "r");
    
    if (file == NULL)
    {
        printf("Não foi possível carregar os utentes.\n");
        return;
    }

    int codigo;
    char nome[100];
    int codigo_medico;
    
    while (fscanf(file, "%d,%[^,],%d\n", &codigo, nome, &codigo_medico) == 3)
    {
        inserir_utente(utentes, nome, codigo_medico, codigo);
    }

    fclose(file);
}



void carregar_medicos(Medico** medicos)
{
    FILE* file = fopen("data/medicos.txt", "r");
    
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo medicos.txt.\n");
        return;
    }

    int codigo;
    char nome[100];
    while (fscanf(file, "%d,%[^\n]\n", &codigo, nome) == 2)
    {
        inserir_medico(medicos, codigo, nome);
    }

    fclose(file);
}

void carregar_fila_espera(Utente** fila_espera, Utente** utentes, Medico** medicos)
{
    FILE* file = fopen("data/fila_espera.txt", "r");

    if (file == NULL)
    {
        printf("Não foi possível carregar a fila de espera.\n");
        return;
    }

    int codigo;
    char nome[100];
    int codigo_medico;

    while (fscanf(file, "%d,%[^,],%d\n", &codigo, nome, &codigo_medico) == 3)
    {
        registar_entrada(fila_espera, utentes, medicos, codigo);
    }

    fclose(file);
}


void carregar_tudo(Medico** medicos, Utente** utentes, Utente** fila_espera)
{
    carregar_medicos(medicos);
    carregar_utentes(utentes, medicos);
    carregar_fila_espera(fila_espera, utentes, medicos);

    FILE* file = fopen("data/variaveis.txt", "r");
    
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo variaveis.txt.\n");
        return;
    }

    fscanf(file, "%d,%d\n", &codigomedico, &codigoutente);
    fclose(file);
}


void salvar_utentes(Utente** ptr_utentes)
{
    FILE* file = fopen("data/utentes.txt", "w");
    
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo utentes.txt.\n");
        return;
    }

    Utente* atual = *ptr_utentes;
    
    while (atual != NULL)
    {
        fprintf(file, "%d,%s,%d\n", atual->codigo, atual->nome, atual->codigo_medico);
        atual = atual->prox;
    }

    fclose(file);
}



void salvar_medicos(Medico** medicos)
{
    FILE* file = fopen("data/medicos.txt", "w");
    
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo medicos.txt.\n");
        return;
    }

    Medico* atual = *medicos;
    
    while (atual != NULL)
    {
        fprintf(file, "%d,%s\n", atual->codigo, atual->nome);
        atual = atual->prox;
    }

    fclose(file);
}

void salvar_fila_espera(Utente** fila_espera)
{
    FILE* file = fopen("data/fila_espera.txt", "w");

    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo fila_espera.txt.\n");
        return;
    }

    Utente* atual = *fila_espera;

    while (atual != NULL)
    {
        fprintf(file, "%d,%s,%d\n", atual->codigo, atual->nome, atual->codigo_medico);
        atual = atual->prox;
    }

    fclose(file);
}



void salvar_tudo(Medico** medicos, Utente** utentes, Utente** fila_espera)
{
    salvar_medicos(medicos);
    salvar_utentes(utentes);
    salvar_fila_espera(fila_espera);

    FILE* file = fopen("data/variaveis.txt", "w");
    
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo variaveis.txt.\n");
        return;
    }

    fprintf(file, "%d,%d\n", codigomedico, codigoutente);
    fclose(file);
}



void registar_entrada(Utente** fila_utentes, Utente** utentes, Medico** medicos, int codigo_utente)
{
    Utente* utente_original = procurar_utente(utentes, codigo_utente);

    if (utente_original == NULL)
    {
        printf("Erro: Utente não encontrado.\n");
        return;
    }

    Utente* novo_utente = criar_utente(utente_original->nome, utente_original->codigo_medico);
    novo_utente->codigo = utente_original->codigo;

    // Verifica se o utente já está na fila de utentes
    Utente* atual = *fila_utentes;
    while (atual != NULL)
    {
        if (atual->codigo == novo_utente->codigo)
        {
            printf("Erro: O utente já está na fila de utentes.\n");
            return;
        }
        atual = atual->prox;
    }

    // Adiciona o novo utente no final da lista de utentes
    if (*fila_utentes == NULL)
    {
        novo_utente->prox = NULL;
        *fila_utentes = novo_utente;
    }
    else
    {
        atual = *fila_utentes;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        novo_utente->prox = NULL;
        atual->prox = novo_utente;
    }

    // Adiciona o novo utente no final da fila de utentes do médico correspondente
    Medico* medico = procurar_medico(medicos, novo_utente->codigo_medico);
    if (medico != NULL)
    {
        // Verifica se o paciente já está na fila de espera do médico
        Utente* atual_medico = medico->fila_espera;
        while (atual_medico != NULL)
        {
            if (atual_medico->codigo == novo_utente->codigo)
            {
                printf("Erro: O paciente já está na fila de espera do médico.\n");
                return;
            }
            atual_medico = atual_medico->prox;
        }

        // Adiciona o novo paciente à fila de espera do médico
        Utente* novo_utente_medico = criar_utente(novo_utente->nome, novo_utente->codigo_medico);
        novo_utente_medico->codigo = novo_utente->codigo;

        if (medico->fila_espera == NULL)
        {
            novo_utente_medico->prox = NULL;
            medico->fila_espera = novo_utente_medico;
        }
        else
        {
            atual_medico = medico->fila_espera;
            while (atual_medico->prox != NULL)
            {
                atual_medico = atual_medico->prox;
            }
            novo_utente_medico->prox = NULL;
            atual_medico->prox = novo_utente_medico;
        }
    }
    else
    {
        printf("Erro: Médico não encontrado.\n");
    }
}




void retirar_entrada(Utente** fila_utentes, Medico** medicos)
{
    // Verifica se a lista de utentes está vazia
    if (*fila_utentes == NULL)
    {
        printf("Erro: Lista de utentes está vazia.\n");
        return;
    }

    // Primeiro utente da fila é o que será retirado
    Utente* primeiro = *fila_utentes;

    // Remove o primeiro utente da lista de utentes
    *fila_utentes = primeiro->prox;

    // Remove o utente da fila de espera do médico correspondente
    Medico* medico = procurar_medico(medicos, primeiro->codigo_medico);

    if (medico != NULL)
    {
        Utente* atual_medico = medico->fila_espera;
        Utente* anterior_medico = NULL;

        while (atual_medico != NULL && atual_medico->codigo != primeiro->codigo)
        {
            anterior_medico = atual_medico;
            atual_medico = atual_medico->prox;
        }

        if (atual_medico != NULL)
        {
            if (anterior_medico == NULL)
            {
                // O utente a ser retirado é o primeiro da fila de espera do médico
                medico->fila_espera = atual_medico->prox;
            }
            else
            {
                anterior_medico->prox = atual_medico->prox;
            }

            free(atual_medico);
        }
        else
        {
            printf("Erro: Utente não encontrado na fila de espera do médico.\n");
        }
    }
    else
    {
        printf("Erro: Médico não encontrado.\n");
    }

    free(primeiro);
}





Utente* proximo_utente_atendido(Medico** ptr_medicos, int codigo_medico) //Retorna o próximo utente que será atendido por determinado médico - SE RETORNADA NULL, COLOCAR ERRO.
{
    // Encontrar o médico correspondente ao código do médico informado.
    Medico* medico = NULL;
    Medico* atual = *ptr_medicos;
    
    while (atual != NULL)
    {
        if (atual->codigo == codigo_medico)
        {
            medico = atual;
            break;
        }
        atual = atual->prox;
    }

    if (medico == NULL)
    {
        printf("Médico não encontrado.\n");
        return NULL;
    }

    // Retorna o próximo utente da fila de espera do médico.
    Utente* proximo = medico->fila_espera;
    
    if (proximo != NULL)
    {
        medico->fila_espera = proximo->prox;
    }
    else
    {
        printf("Nenhum utente na fila de espera para o médico %s.\n", medico->nome);
    }

    return proximo;
}


void listar_fila_espera_medico(Medico** ptr_medicos, int codigo_medico)
{
    system("cls"); // Limpa a tela

    // Encontra o médico correspondente ao código do médico informado.
    Medico* medico = NULL;
    Medico* atual = *ptr_medicos;
    while (atual != NULL)
    {
        if (atual->codigo == codigo_medico)
        {
            medico = atual;
            break;
        }
        atual = atual->prox;
    }

    if (medico == NULL)
    {
        printf("Médico não encontrado.\n");
        return;
    }

    // Lista os utentes na fila de espera do médico.
    printf("Fila de espera para o médico %s:\n", medico->nome);
    printf("Código\tNome\n");
    printf("-----------------------------\n");

    const Utente* utente = medico->fila_espera;
    while (utente != NULL) {
        printf("%d\t%-20s\n", utente->codigo, utente->nome);
        utente = utente->prox;
    }
}




int contar_doentes_espera(Medico** medicos, int codigo_medico)
{
    // Encontra o médico correspondente ao código do médico informado.
    Medico* medico = NULL;
    Medico* atual = *medicos;
    while (atual != NULL) {
        if (atual->codigo == codigo_medico) {
            medico = atual;
            break;
        }
        atual = atual->prox;
    }

    if (medico == NULL) {
        printf("Médico não encontrado.\n");
        return -1;
    }

    // Conta os utentes na fila de espera do médico.
    int count = 0;
    const Utente* utente = medico->fila_espera;
    while (utente != NULL) {
        count++;
        utente = utente->prox;
    }

    return count;
}



Medico* medico_mais_doentes(Medico** ptr_medicos) // Função que retorna o médico com mais doentes. SE FOR NULL É PORQUE NÃO HÁ MÉDICOS.
{
    Medico* medico_com_mais_doentes = NULL;
    int max_doentes = -1;
    Medico* atual = *ptr_medicos;

    while (atual != NULL)
    {
        int doentes_espera = contar_doentes_espera(*ptr_medicos, atual->codigo);
        if (doentes_espera > max_doentes) {
            max_doentes = doentes_espera;
            medico_com_mais_doentes = atual;
        }
        atual = atual->prox;
    }

    if (medico_com_mais_doentes == NULL)
    {
        printf("Não há médicos na lista.\n");
    }
    return medico_com_mais_doentes;
}



void listar_utentes_por_medico(Utente** ptr_utentes, Medico** ptr_medicos)
{
    system("cls"); // Limpa a tela

    printf("Utentes ordenados por médico:\n");
    printf("------------------------------------\n");

    const Medico* medico_atual = *ptr_medicos;
    while (medico_atual != NULL) {
        printf("Médico: %s\n", medico_atual->nome);
        printf("Código\tNome\n");
        printf("-----------------------------\n");

        Utente* utente_atual = medico_atual->fila_espera;

        while (utente_atual != NULL)
        {
            printf("%d\t%-20s\n", utente_atual->codigo, utente_atual->nome);
            utente_atual = utente_atual->prox;
        }

        printf("\n");
        medico_atual = medico_atual->prox;
    }
}



Medico* procurar_medico(Medico** medicos, int codigo)
{
    Medico* atual = *medicos;
    int i = 0;
    
    for (i = 0; atual != NULL; i++)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


Utente* procurar_utente(Utente** utentes, int codigo)
{
    Utente* atual = *utentes;
    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}



void editar_utente(Utente** utentes, Medico** medicos, int codigo, char* novo_nome)
{
    Utente* utente = procurar_utente(utentes, codigo);
    
    if (utente == NULL)
    {
        printf("Utente com código %d não encontrado.\n", codigo);
        return;
    }

    strcpy(utente->nome, novo_nome);

    Medico* medico = *medicos;
    
    while (medico != NULL)
    {
        Utente* fila_espera = medico->fila_espera;
        
        while (fila_espera != NULL)
        {
            if (fila_espera->codigo == codigo)
            {
                strcpy(fila_espera->nome, novo_nome);
            }
            fila_espera = fila_espera->prox;
        }
        medico = medico->prox;
    }
}

void editar_medico(Medico** medicos, int codigo, char* novo_nome)
{
    Medico* medico = procurar_medico(medicos, codigo);
    if (medico == NULL)
    {
        printf("Médico com código %d não encontrado.\n", codigo);
        return;
    }

    // Atualiza o nome do médico
    strcpy(medico->nome, novo_nome);
}
/*
void consultar_medico(Medico** medicos, Utente** utentes, int codigo)
{
    Medico* medico = procurar_medico(medicos, codigo);

    // procurar o médico com o código indicado
    if (medico == NULL)
    {
        printf("Médico com código %d não encontrado.\n", codigo);
        return;
    }
    
    printf("----------------------------\n");
    printf("\n\nCódigo: %d\n", medico->codigo);
    printf("Nome: %s\n", medico->nome);
    
    printf("\nUtentes com este médico:\n");

    printf("----------------------------\n");
    printf("Código\t->  Nome\n");
    printf("----------------------------\n");
    Utente* utente_atual = *utentes;
    while (utente_atual != NULL)
    {
        if (utente_atual->codigo_medico == codigo)
        {
            printf("%d\t->  %s\n", utente_atual->codigo, utente_atual->nome);
        }
        utente_atual = utente_atual->prox;
    }

    printf("\n\nUtentes em fila de espera:\n\n");
    printf("----------------------------\n");
    printf("Código\t->  Nome\n");
    printf("----------------------------\n");

    utente_atual = medico->fila_espera;
    while (utente_atual != NULL)
    {
        printf("%d\t->  %s\n", utente_atual->codigo, utente_atual->nome);
        utente_atual = utente_atual->prox;
    }

}
*/

void consultar_medico(Medico** medicos, Utente** utentes, int codigo)
{
    system("cls"); // Limpa a tela

    Medico* medico = procurar_medico(medicos, codigo);

    // Procurar o médico com o código indicado
    if (medico == NULL)
    {
        printf("Médico com código %d não encontrado.\n", codigo);
        return;
    }
    
    printf("----------------------------\n");
    printf("\nCódigo: %d\n", medico->codigo);
    printf("Nome: %s\n", medico->nome);
    
    printf("\nUtentes com este médico:\n");

    printf("----------------------------\n");
    printf("Código\t->  Nome\n");
    printf("----------------------------\n");
    Utente* utente_atual = *utentes;
    int contador_utentes = 0;
    while (utente_atual != NULL)
    {
        if (utente_atual->codigo_medico == codigo)
        {
            printf("%d\t->  %s\n", utente_atual->codigo, utente_atual->nome);
            contador_utentes++;
        }
        utente_atual = utente_atual->prox;
    }
    printf("----------------------------\n");
    if (contador_utentes == 1) {
        printf("Total: 1 utente\n");
    } else {
        printf("Total: %d utentes\n", contador_utentes);
    }

    printf("\nUtentes em fila de espera:\n");

    printf("----------------------------\n");
    printf("Código\t->  Nome\n");
    printf("----------------------------\n");

    utente_atual = medico->fila_espera;
    int contador_fila = 0;
    while (utente_atual != NULL)
    {
        printf("%d\t->  %s\n", utente_atual->codigo, utente_atual->nome);
        utente_atual = utente_atual->prox;
        contador_fila++;
    }
    printf("----------------------------\n");
    if (contador_fila == 1) {
        printf("Total: 1 utente em fila de espera\n");
    } else {
        printf("Total: %d utentes em fila de espera\n", contador_fila);
    }
}




void consultar_utente(Medico** medicos, Utente** utentes, Utente** fila_espera, int codigo_utente)
{
    system("cls"); // Limpa a tela
    // Procurar o utente com o código indicado
    Utente* utente = procurar_utente(utentes, codigo_utente);

    if (utente == NULL)
    {
        printf("Utente com código %d não encontrado.\n", codigo_utente);
        return;
    }

    // Procurar o médico correspondente ao utente
    Medico* medico = procurar_medico(medicos, utente->codigo_medico);

    if (medico == NULL)
    {
        printf("Médico com código %d não encontrado.\n", utente->codigo_medico);
        return;
    }

    printf("----------------------------\n");
    printf("\n\nCódigo do Utente: %d\n", utente->codigo);
    printf("Nome do Utente: %s\n", utente->nome);
    printf("Código do Médico: %d\n", medico->codigo);
    printf("Nome do Médico: %s\n", medico->nome);

    // Verificar se o utente está na fila de espera
    Utente* utente_atual = *fila_espera;
    int esta_na_fila = 0; // 0 significa 'não está na fila'
    while (utente_atual != NULL)
    {
        if (utente_atual->codigo == codigo_utente)
        {
            esta_na_fila = 1; // 1 significa 'está na fila'
            break;
        }
        utente_atual = utente_atual->prox;
    }

    if (esta_na_fila)
        printf("O Utente está na fila de espera para ser atendido.\n");
    else
        printf("O Utente não está na fila de espera para ser atendido.\n");
}



Utente* ultimo_utente(Utente** fila_utentes)
{
    // Verifica se a lista de utentes está vazia
    if (*fila_utentes == NULL)
    {
        printf("A lista de utentes está vazia.\n");
        return NULL;
    }

    Utente* atual = *fila_utentes;

    // Percorre a lista até o último nó
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }

    // Retorna o último utente na lista de utentes
    return atual;
}

void listar_utentes_fila(Utente** fila_espera)
{
    if(*fila_espera == NULL)
    {
        printf("Não há utentes na fila de espera.\n");
        return;
    }
    system("cls"); // Limpa a tela
    
    Utente* atual = *fila_espera;
    
    printf("Lista de utentes na fila de espera:\n\n");
    printf("Código\tNome\t\tCódigo médico\n");
    printf("--------------------------------------------\n");
    
    while(atual != NULL)
    {
        printf("%d\t%s\t\t%d\n", atual->codigo, atual->nome, atual->codigo_medico);
        atual = atual->prox;
    }
    
    printf("\n");
}


void utentes_por_medico(Medico** medicos, Utente** utentes)
{
    system("cls"); // Limpa a tela
    printf("Lista de médicos e seus utentes:\n\n");

    Medico* medico_atual = *medicos;

    while (medico_atual != NULL) {
        printf("Médico: %s (Código: %d)\n", medico_atual->nome, medico_atual->codigo);
        printf("Utentes atribuídos a este médico:\n");

        Utente* utente_atual = *utentes;
        int utentes_encontrados = 0;

        while (utente_atual != NULL) {
            if (utente_atual->codigo_medico == medico_atual->codigo) {
                printf("  - %s (Código: %d)\n", utente_atual->nome, utente_atual->codigo);
                utentes_encontrados++;
            }
            utente_atual = utente_atual->prox;
        }

        if (utentes_encontrados == 0) {
            printf("  Nenhum utente atribuído.\n");
        }

        printf("Utentes em fila de espera:\n");

        utente_atual = medico_atual->fila_espera;
        int utentes_em_fila = 0;

        while (utente_atual != NULL) {
            printf("  - %s (Código: %d)\n", utente_atual->nome, utente_atual->codigo);
            utente_atual = utente_atual->prox;
            utentes_em_fila++;
        }

        if (utentes_em_fila == 0) {
            printf("  Nenhum utente em fila de espera.\n");
        } else {
            printf("  Utentes em espera: %d\n", utentes_em_fila);
        }

        printf("\n");
        medico_atual = medico_atual->prox;
    }
}




void listar_doentes_sem_espera(Utente** fila_espera, Utente** utentes)
{
    system("cls"); // Limpa a tela
    printf("\n\nLista de utentes não presentes:\n");
    printf("Código\tNome\t\t\tCódigo médico\n");
    printf("--------------------------------------------------\n");

    Utente* atual = *utentes;
    int contador = 0;

    while (atual != NULL)
    {
        int codigo = atual->codigo;
        int possui_espera = 0;

        // Verificar se o doente está na fila de espera
        Utente* utente_espera = *fila_espera;
        while (utente_espera != NULL)
        {
            if (utente_espera->codigo == codigo)
            {
                possui_espera = 1;
                break;
            }
            utente_espera = utente_espera->prox;
        }

        if (!possui_espera)
        {
            printf("%d\t%-20s\t%d\n", atual->codigo, atual->nome, atual->codigo_medico);
            contador++;
        }

        atual = atual->prox;
    }

    if (contador == 0)
    {
        printf("Todos os doentes estão em listas de espera.\n");
    }
    printf("\n\n");
}
/*
void listar_medicos_toda_informacao(Utente** utentes, Medico** medicos)
{
    Medico* medico_atual = *medicos;
    Medico* medico_mais_utentes = NULL;
    Medico* medico_mais_fila_espera = NULL;
    int max_utentes = 0;
    int max_fila_espera = 0;

    while (medico_atual != NULL)
    {
        printf("\n\n-----------------------------\n");
        printf("Médico: %d - %s\n", medico_atual->codigo, medico_atual->nome);
        printf("-----------------------------\n");
        consultar_medico(medicos, utentes, medico_atual->codigo);
        printf("\n");

        // Verificar se é o médico com mais utentes
        int contador_utentes = contar_utentes_medico(utentes, medico_atual->codigo);
        if (contador_utentes > max_utentes)
        {
            max_utentes = contador_utentes;
            medico_mais_utentes = medico_atual;
        }

        // Verificar se é o médico com mais utentes em fila de espera
        int contador_fila_espera = contar_fila_espera_medico(medico_atual->fila_espera);
        if (contador_fila_espera > max_fila_espera)
        {
            max_fila_espera = contador_fila_espera;
            medico_mais_fila_espera = medico_atual;
        }

        medico_atual = medico_atual->prox;
    }
    
    printf("Chega aqui 1");
    
    printf("\n\n-----------------------------\n");
    printf("Médico com mais utentes:\n");
    printf("Código: %d - %s\n", medico_mais_utentes->codigo, medico_mais_utentes->nome);
    printf("Total de utentes: %d\n", max_utentes);
    printf("-----------------------------\n");
    printf("Chega aqui 2");
    printf("\n\n-----------------------------\n");
    printf("Médico com mais utentes em fila de espera:\n");
    printf("Código: %d - %s[%d]\n", medico_mais_fila_espera->codigo, medico_mais_fila_espera->nome, max_fila_espera);
    printf("-----------------------------\n");
}*/

void listar_medicos_toda_informacao(Utente** utentes, Medico** medicos) {

    
    Medico* medico_atual = *medicos;
    Medico* medico_mais_utentes = NULL;
    Medico* medico_mais_fila_espera = NULL;
    int max_utentes = 0;
    int max_fila_espera = 0;

    while (medico_atual != NULL) {
        printf("\n\n-----------------------------\n");
        printf("Médico: %d - %s\n", medico_atual->codigo, medico_atual->nome);
        printf("-----------------------------\n");
        consultar_medico(medicos, utentes, medico_atual->codigo);
        printf("\n");

        // Contar o número de utentes do médico atual
        int contador_utentes = 0;
        Utente* utente_atual = *utentes;
        while (utente_atual != NULL) {
            if (utente_atual->codigo_medico == medico_atual->codigo) {
                contador_utentes++;
            }
            utente_atual = utente_atual->prox;
        }

        // Verificar se é o médico com mais utentes
        if (contador_utentes > max_utentes) {
            max_utentes = contador_utentes;
            medico_mais_utentes = medico_atual;
        }

        // Contar o número de utentes em fila de espera do médico atual
        int contador_fila_espera = 0;
        Utente* fila_espera_atual = medico_atual->fila_espera;
        while (fila_espera_atual != NULL) {
            contador_fila_espera++;
            fila_espera_atual = fila_espera_atual->prox;
        }

        // Verificar se é o médico com mais utentes em fila de espera
        if (contador_fila_espera > max_fila_espera) {
            max_fila_espera = contador_fila_espera;
            medico_mais_fila_espera = medico_atual;
        }

        medico_atual = medico_atual->prox;
    }

    printf("\n\n-----------------------------\n");
    printf("Médico com mais utentes:\n");
    printf("Código: %d - %s\n", medico_mais_utentes->codigo, medico_mais_utentes->nome);
    printf("Total de utentes: %d\n", max_utentes);
    printf("-----------------------------\n");

    printf("\n-----------------------------\n");
    printf("Médico com mais utentes em fila de espera:\n");
    printf("Código: %d - %s\n", medico_mais_fila_espera->codigo, medico_mais_fila_espera->nome);
    printf("Total de utentes: %d\n", max_fila_espera);
    printf("-----------------------------\n");
}

void apresentar_medico_com_mais_doentes(Medico** medicos, Utente** fila_utentes)
{
    system("cls"); // Limpa a tela
    if (*medicos == NULL) {
        printf("Não há médicos cadastrados.\n");
        return;
    }

    int maxCount = 0;      // Variable to store the maximum number of patients
    Medico* medicoMax = NULL;   // Pointer to the doctor with the maximum number of patients

    Medico* atual = *medicos;

    while (atual != NULL) {
        int count = 0;  // Counter for the number of patients for the current doctor

        Utente* utenteAtual = atual->fila_espera;

        while (utenteAtual != NULL) {
            count++;
            utenteAtual = utenteAtual->prox;
        }

        if (count > maxCount) {
            maxCount = count;
            medicoMax = atual;
        }

        atual = atual->prox;
    }

    if (medicoMax != NULL) {
        printf("Médico com mais doentes em espera:\n");
        printf("Código: %d\n", medicoMax->codigo);
        printf("Nome: %s\n", medicoMax->nome);
        printf("Número de doentes em espera: %d\n", maxCount);
    } else {
        printf("Não há médicos com doentes em espera.\n");
    }
}
