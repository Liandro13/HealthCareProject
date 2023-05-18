#include "funcoes.h"
#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
// --------------------------------------------FRONTEND---------------------------------------------
int codigomedico=0;
int codigoutente=0;
int opcao;

void menuprincipal(Utente** utentes, Medico** medicos, Utente** fila_espera)
{
    opcao=1;
    printf("Centro de Saúde HealthCare.\n\n");
    printf("Insira a opção pretendida: \n\n");
    do{
        if(opcao < 1 || opcao > 7) printf("\nOpção inválida, insira novamente.\n");
        printf("\n+------------------------------------------+\n");
                printf("|             Centro de Saúde              |\n");
                printf("|               HealthCare                 |\n");
                printf("+------------------------------------------+\n");
                printf("| 1. Registar entrada de um doente         |\n");
                printf("| 2. Registar saída de um doente           |\n");
                printf("| 3. Listar utentes da fila de espera      |\n");
                printf("| 4. Gerir utentes                         |\n");
                printf("| 5. Gerir médicos                         |\n");
                printf("| 6. Lista de utentes por médico           |\n");
                printf("| 7. Sair do programa                      |\n");
                printf("+------------------------------------------+\n");
                printf(" Insira a opção pretendida (1-7): ");
                scanf("%d", &opcao);
    } while(opcao < 1 || opcao > 7);
    
    int codigod;
    
    switch(opcao)
    {
        case 1:
            
            listar_doentes_sem_espera(fila_espera, utentes);
            
            printf("Codigo do doente:");
            scanf("%d", &codigod);
            
            registar_entrada(fila_espera, utentes, medicos, codigod);
            salvar_tudo(medicos, utentes, fila_espera);
           
            getchar();
            
            menuprincipal(utentes, medicos, fila_espera);
            
        break;
            
        case 2:
                        
            printf("Confirma que pretende retirar o próximo doente da fila?");
            printf("Próximo doente: ");                //COLOCAR AQUI A MOSTRAR O PRÓXIMO DOENTE
            
            opcao=1;
            do{
                if(opcao < 1 || opcao > 2) printf("\nOpção inválida, insira novamente.\n");
                
                printf("\n1- Sim\n");
                printf("2- Não\n");
                scanf("%d", &opcao);
                
            }while(opcao<1 || opcao >2);
            
            switch(opcao)
            {
                case 1:
                    retirar_entrada(fila_espera, medicos);
                    salvar_tudo(medicos, utentes, fila_espera);
                    menuprincipal(utentes, medicos, fila_espera);
                break;
                
                case 2:
                    menuprincipal(utentes, medicos, fila_espera);
                break;
            }
        break;
            
            
        case 3:
            listar_utentes_fila(fila_espera);
            getchar();
            getchar();
            menuprincipal(utentes, medicos, fila_espera);
        break;

            
        case 4:
            menugerirutentes(utentes, medicos, fila_espera);
        break;
            
            
        case 5:
            menugerirmedicos(utentes, medicos, fila_espera);
        break;
            
        case 6:
            utentes_por_medico(medicos, utentes);
            getchar();
            menuprincipal(utentes, medicos, fila_espera);
        break;
            
        case 7:
            exit(0);
        break;
    }
    
}

void menugerirmedicos(Utente** utentes, Medico** medicos, Utente** fila_espera)
{
    int codigoaalterar=0;
    int numeromedico;
    char nomemedico[50];
    opcao=1;
    
    do{
        if(opcao < 1 || opcao > 7) printf("\n\nSeleção inválida\n\n");
        
            printf("\n+---------------------------------+\n");
            printf("|        Gerir Médicos            |\n");
            printf("+---------------------------------+\n");
            printf("| 1. Inserir médico               |\n");
            printf("| 2. Editar médico                |\n");
            printf("| 3. Consultar médicos            |\n");
            printf("| 4. Listar médicos               |\n");
            printf("| 5. Remover médico               |\n");
            printf("| 6. Listar medicos + informações |\n");
            printf("| 7. Voltar atrás                 |\n");
            printf("+---------------------------------+\n");
            printf("  Insira a opção pretendida (1-7): ");
            scanf("%d", &opcao);
    
    } while(opcao <  1 || opcao > 7);
    
    switch(opcao)
    {
        case 1:
            printf("\nNome do novo medico: ");
            scanf("%s", nomemedico);
            //fflush(stdin);
            //fgets(nomemedico, sizeof(nomemedico), stdin);
            nomemedico[strcspn(nomemedico, "\n")] = '\0';
            inserir_medico(medicos, codigomedico, nomemedico);
            salvar_tudo(medicos, utentes, fila_espera);
            getchar();
            menugerirmedicos(utentes, medicos, fila_espera);
        break;
            
        case 2:
       
            printf("Código do médico a editar: ");
            scanf("%d", &codigoaalterar);

            printf("Novo nome: ");
            scanf("%s", nomemedico);

            printf ("Tem a certeza que pretende editar o médico %s [%d]?", procurar_medico(medicos, codigoaalterar)->nome, codigoaalterar);
            int opcao = 1;
            do {
                if (opcao < 1 || opcao > 2) printf("\n\nSeleção inválida\n\n");

                printf("\n\n1- Sim\n");
                printf("2- Não\n");
                scanf("%d", &opcao);
            } while (opcao < 1 || opcao > 2);

            switch (opcao)
            {
                case 1:
                    editar_medico(medicos, codigoaalterar, nomemedico);
                    salvar_tudo(medicos, utentes, fila_espera);
                    getchar();
                    menugerirmedicos(utentes, medicos, fila_espera);
                break;

                case 2:
                    menugerirmedicos(utentes, medicos, fila_espera);
                break;
            }

        break;
            
        case 3:
            
            listar_medicos(medicos);
            
            printf("\n\nCodigo do medico que pretende consultar: ");
            scanf("%d", &codigomedico);
            
            consultar_medico(medicos, utentes, codigomedico);
            getchar();
            getchar();
            menugerirmedicos(utentes, medicos, fila_espera);
        break;
            
        case 4:
            listar_medicos(medicos);
            getchar();
            getchar();
            menugerirmedicos(utentes, medicos, fila_espera);
        break;
            
        case 5:
            printf("Código do medico a remover: ");
            scanf("%d", &numeromedico);
            
            if(procurar_medico(medicos, numeromedico) == NULL)
            {
                printf("Médico não existente.");
            }
            else
            {
                printf("Tem a certeza que pretende remover o médico %s [%d]?", procurar_medico(medicos, numeromedico)->nome, numeromedico);
                
                opcao=1;
                do{
                    if(opcao < 1 || opcao > 2) printf("\n\nSeleção inválida\n\n");
                    
                    printf("\n\n1- Sim\n");
                    printf("2- Não\n");
                    scanf("%d", &opcao);
                    
                } while(opcao <  1 || opcao > 2);
                
                switch(opcao)
                {
                    case 1:
                        remover_medico(medicos, numeromedico);
                        salvar_tudo(medicos, utentes, fila_espera);
                        getchar();
                        menugerirmedicos(utentes, medicos, fila_espera);
                    break;
                    
                    case 2:
                        menugerirmedicos(utentes, medicos, fila_espera);
                    break;
                    
                }
                
            }
            break;
            
        
        case 6:
            listar_medicos_toda_informacao(utentes, medicos);
            getchar();
            getchar();
            menugerirmedicos(utentes, medicos, fila_espera);
        break;
        
        case 7:
            menuprincipal(utentes, medicos, fila_espera);
        break;
            
    }
}


void menugerirutentes(Utente** utentes, Medico** medicos, Utente** fila_espera)
{
    int codigoaalterar=0;
    int numeroutente;
    int codigo_medico_utente;
    int codigo_utente=0;
    char nomeutente[50];
    opcao=1;
    
    do{
        if(opcao < 1 || opcao > 6) printf("\n\nSeleção inválida\n\n");
        
            printf("\n+---------------------------+\n");
            printf("|        Gerir Utentes      |\n");
            printf("+---------------------------+\n");
            printf("| 1. Inserir utente         |\n");
            printf("| 2. Editar utente          |\n");
            printf("| 3. Consultar utentes      |\n");
            printf("| 4. Listar utentes         |\n");
            printf("| 5. Remover utente         |\n");
            printf("| 6. Voltar atrás           |\n");
            printf("+---------------------------+\n");
            printf("  Insira a opção pretendida (1-6): ");
            scanf("%d", &opcao);
        
    } while(opcao <  1 || opcao > 6);
    
    switch(opcao)
    {
        case 1:
            printf("Nome do novo utente: ");
            scanf("%s", nomeutente);
            listar_medicos(medicos);
            printf("\nCodigo do medico do novo utente: ");
            scanf("%d", &codigo_medico_utente);
            inserir_utente(utentes, nomeutente, codigo_medico_utente, codigoutente);
            salvar_tudo(medicos, utentes, fila_espera);
            getchar();
            menugerirutentes(utentes, medicos, fila_espera);
        break;
            
        case 2:
            
            listar_utentes(utentes);
            
            printf("Codigo do utente a editar: ");
            scanf("%d", &codigoaalterar);
            
            printf("Novo nome: ");
            scanf("%s", nomeutente);
            
            do {
                if(opcao < 1 || opcao > 2) printf("\n\nSeleção inválida\n\n");
                
                printf("1- Sim\n");
                printf("2- Não\n");
                scanf("%d", &opcao);
                
            } while(opcao <  1 || opcao > 2);
            
            switch (opcao)
            {
                case 1:
                    editar_utente(utentes, medicos, codigoaalterar, nomeutente);
                    salvar_tudo(medicos, utentes, fila_espera);
                    getchar();
                    menugerirutentes(utentes, medicos, fila_espera);
                break;
                    
                case 2:
                    menugerirutentes(utentes, medicos, fila_espera);
                break;
            }
            
        break;
            
        case 3:
            
            printf("Código do utente que pretende conslutar: ");
            scanf("%d", &codigo_utente);
            consultar_utente(medicos, utentes, fila_espera, codigo_utente);
            getchar();
            menugerirutentes(utentes, medicos, fila_espera);
        break;
            
        case 4:
            listar_utentes(utentes);
            getchar();
            getchar();
            menugerirutentes(utentes, medicos, fila_espera);
        break;
            
        case 5:
            printf("Código do utente a remover: ");
            scanf("%d", &numeroutente);

            if(procurar_utente(utentes, numeroutente) == NULL)
            {
                printf("Utente não existente.");
            }
            else
            {
                printf("Tem a certeza que pretende remover o utente %s [%d]?", procurar_utente(utentes, numeroutente)->nome, numeroutente);

                opcao = 1;
                do{
                    if(opcao < 1 || opcao > 2) printf("\n\nSeleção inválida\n\n");

                    printf("\n\n1- Sim\n");
                    printf("2- Não\n");
                    scanf("%d", &opcao);

                } while(opcao <  1 || opcao > 2);

                switch(opcao)
                {
                    case 1:
                        remover_utente(utentes, medicos, numeroutente);
                        salvar_tudo(medicos, utentes, fila_espera);
                        getchar();
                        menugerirutentes(utentes, medicos, fila_espera);
                        break;

                    case 2:
                        menugerirutentes(utentes, medicos, fila_espera);
                        break;
                }
            }
            break;

            
        case 6:
            menuprincipal(utentes, medicos, fila_espera);
        break;
            
    }
}