#include <stdio.h>
#include "bdpacientes.h"

int main(void) {
  BDPacientes *bd = criar_banco(); // inicializa banco
  carregar_csv(bd); // carrega pacientes do CSV

  // menu
  char opcao;
  while(1){
    printFrame();
    printf("HealthSys\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf(">>");
    (void)scanf(" %c", &opcao); // input da ação

    switch(opcao){
      case '1':{ // Consultar paciente
        if(!vazia(bd)){
          clearConsole();
          consulta_paciente(bd);
          confirma();
          clearConsole();
        }
        else{
          clearConsole();
          printf("Nenhum paciente está cadastrado no momento.");
          confirma();
          clearConsole();
        }
        break;
      }

      case '2':{ // Atualizar paciente
        if(!vazia(bd)){
          clearConsole();
          atualizar_paciente(bd);
          confirma();
          clearConsole();
        }
        else{
          clearConsole();
          printf("Nenhum paciente está cadastrado no momento.");
          confirma();
          clearConsole();
        }
        break;
      }

      case '3':{ // Remover paciente
        if(!vazia(bd)){
          clearConsole();
          remover_paciente(bd);
          clearConsole();
        }
        else{
          clearConsole();
          printf("Nenhum paciente está cadastrado no momento.");
          confirma();
        }
        clearConsole();
        break;
      }

      case '4':{ // Inserir paciente
        inserir_dados_paciente(bd);
        confirma();
        clearConsole();
        break;
      }
      
      case '5': // imprimir lista de pacientes
        imprimir_todos_pacientes(bd);
        confirma();
        clearConsole();
        break;
      
      case 'Q':
      case 'q':
        printf("Encerrando programa...\n"); // sair
        clearConsole();
        salvar_csv(bd);
        finalizar(bd);
        return 0;
      default:
        printf("Opção inválida. Tente novamente."); // valor incorreto inserido
        clearConsole();
    }
  }
  return 0;
}