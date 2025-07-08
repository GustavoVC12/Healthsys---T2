#include "bdpacientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////// ESTRUTURAS ////////////////////////////////////
typedef struct paciente { // Define a estrutura de um paciente
  int id;
  char cpf[15];
  char nome[100];
  int idade;
  char data_cadastro[11];
  struct paciente *next;
} Paciente;

typedef struct bdpacientes { // Define a estrutura do banco de dados
  int total;
  Paciente *front; // início da lista
  Paciente *rear; // fim da lista
} BDPacientes;

BDPacientes *criar_banco(){
  BDPacientes *bd = malloc(sizeof(BDPacientes));
  if(bd==NULL){
    printf("Erro ao alocar memória para banco de dados.\n");
    exit(1);
  }
  bd->total = 0;
  bd->front = NULL;
  bd->rear = NULL;
  return bd;
}


//////////////////////////////////// MANIPULAÇÃO DA LISTA ////////////////////////////////////
void carregar_csv(BDPacientes *bd){ // Insere os dados do CSV na lista
  FILE *f = fopen("bd_pacientes.csv", "r");
  if(f==NULL){
    printf("Erro ao abrir o arquivo CSV.\n");
    return;
  }

  char linha[256];
  fgets(linha, sizeof(linha), f); // Ignora o cabeçalho

  while (fgets(linha, sizeof(linha), f)){
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data[11];

    // Remove quebra de linha no final (opcional, segurança)
    linha[strcspn(linha, "\n")] = 0;

    if (sscanf(linha, " %d,%14[^,],%99[^,],%d,%10s", &id, cpf, nome, &idade, data)==5){
      criar_paciente(bd, id, cpf, nome, idade, data, 0);
    } else {
      printf("Linha mal formatada: %s\n", linha);
    }
  }

  fclose(f);
}

void inserir_dados_paciente(BDPacientes *bd){ // Coleta os dados de um novo paciente
  char cpf[15];
  printf("Insira o CPF do paciente (xxx.xxx.xxx-xx): ");
  scanf(" %14s", cpf);
  getchar(); // limpar o \n após o scanf

  char nome[100];
  printf("Insira o nome do paciente: ");
  if (fgets(nome, sizeof(nome), stdin)) {
    nome[strcspn(nome, "\n")] = 0; // remove o '\n' final
  }

  int idade;
  printf("Insira a idade do paciente: ");
  scanf(" %d", &idade);
  getchar(); // limpar o \n

  char data_cadastro[11];
  printf("Insira a data do cadastro do paciente (xxxx-xx-xx): ");
  if (fgets(data_cadastro, sizeof(data_cadastro), stdin)) {
    data_cadastro[strcspn(data_cadastro, "\n")] = 0;
  }

  int id = 1;
  Paciente *q = bd->front;
  while(q!=NULL){
    if(q->id >= id){
      id = q->id+1;
    }
    q = q->next;
  }
  criar_paciente(bd, id, cpf, nome, idade, data_cadastro, 1);
}


void criar_paciente(BDPacientes *bd, int pId, const char *pCpf, const char *pNome, int pIdade, const char *pData, int flagprint){ // Insere um novo paciente ao final da lista
  Paciente *p = malloc(sizeof(Paciente));
  if (p == NULL){
    printf("Erro ao alocar memória.\n");
    exit(1);
  }
  p->id = pId;
  strcpy(p->cpf, pCpf);
  strcpy(p->nome, pNome);
  p->idade = pIdade;
  strcpy(p->data_cadastro, pData);
  p->next = NULL;

  if (bd->rear == NULL) {    // lista vazia
    bd->front = p;
    bd->rear = p;
  } else {
    bd->rear->next = p;
    bd->rear = p;
  }
  bd->total++;
  if(flagprint){
    printf("Paciente inserido com sucesso.\n");
  }
}


void atualizar_paciente(BDPacientes *bd){ // Atualiza um paciente específico
  Paciente *p = encontrar_paciente(bd);
  if(p==NULL){
    return;
  }

  char opcao;
  char buffer[120];

  printf("Alterar Nome? (Y/N): ");
  scanf(" %c", &opcao);
  getchar(); // limpa o '\n' do buffer
  if(opcao == 'Y' || opcao == 'y'){
    printf("Nome atualizado: ");
    if(fgets(buffer, sizeof(buffer), stdin)){
      buffer[strcspn(buffer, "\n")] = 0; // remove '\n'
      strncpy(p->nome, buffer, sizeof(p->nome)-1);
      p->nome[sizeof(p->nome)-1] = '\0';
    }
  }

  printf("Alterar CPF? (Y/N): ");
  scanf(" %c", &opcao);
  getchar();
  if(opcao=='Y' || opcao=='y'){
    printf("CPF atualizado: ");
    if (fgets(buffer, sizeof(buffer), stdin)){
      buffer[strcspn(buffer, "\n")] = 0;
      strncpy(p->cpf, buffer, sizeof(p->cpf)-1);
      p->cpf[sizeof(p->cpf)-1] = '\0';
    }
  }

  printf("Alterar idade? (Y/N): ");
  scanf(" %c", &opcao);
  getchar();
  if(opcao=='Y' || opcao=='y'){
    int idade2;
    printf("Idade atualizada: ");
    scanf("%d", &idade2);
    getchar();
    p->idade = idade2;
  }

  printf("Alterar data do cadastro? (Y/N): ");
  scanf(" %c", &opcao);
  getchar();
  if(opcao=='Y' || opcao=='y'){
    printf("Data de cadastro atualizada: ");
    if (fgets(buffer, sizeof(buffer), stdin)){
      buffer[strcspn(buffer, "\n")] = 0;
      strncpy(p->data_cadastro, buffer, sizeof(p->data_cadastro)-1);
      p->data_cadastro[sizeof(p->data_cadastro)-1] = '\0';
    }
  }
  printf("Paciente atualizado com sucesso.\n");
}

void remover_paciente(BDPacientes *bd) { // Remove um paciente específico
  Paciente *p = encontrar_paciente(bd);
  if(p==NULL){
    return;
  }

  printf("Tem certeza que deseja remover esse paciente? Essa ação não pode ser desfeita. (Y/N)\n");
  char opcao;
  scanf(" %c", &opcao);

  if(opcao=='Y' || opcao=='y'){
    // Caso: paciente é o primeiro da lista
    if(bd->front == p) {
      bd->front = p->next;
    } else {
      // Caso: paciente está no meio ou no fim
      Paciente *q = bd->front;
      while(q!=NULL && q->next!=p){
        q = q->next;
      }
      if(q!=NULL){
        q->next = p->next;
      }
    }

    // Atualiza o ponteiro 'rear' se o paciente removido for o último
    if(bd->rear == p){
        // Se a lista ficou vazia, zera o rear também
        if(bd->front == NULL){
          bd->rear = NULL;
        } else {
          // Encontra o novo último elemento
          Paciente *q = bd->front;
          while(q->next != NULL){
            q = q->next;
          }
          bd->rear = q;
        }
    }

    free(p);
    bd->total--;
    printf("Paciente removido com sucesso.\n");
  } else {
      printf("Remoção cancelada.\n");
  }
  confirma(); // Aguarda Enter
  clearConsole();
}



//////////////////////////////////// BUSCA DE PACIENTES ////////////////////////////////////
Paciente *encontrar_paciente(BDPacientes *bd){
  printf("1 - Busca por nome.\n2 - Busca por CPF.\n3 - Voltar ao menu principal.\n");
  int busca;
  scanf(" %d", &busca);
  getchar(); // limpar \n residual

  if(busca==3){
    printf("Consulta cancelada.\n");
    confirma();
    return NULL;
  }

  int encontrou = 0;
  if(busca==1){
    char nome[100];
    printf("Insira o nome a ser buscado: ");
    if(fgets(nome, sizeof(nome), stdin)){
      nome[strcspn(nome, "\n")]=0;
      encontrou = consulta_nome(bd, nome);
    }
  } else if(busca==2){
    char cpf[15];
    printf("Insira o CPF a ser buscado: ");
    if(fgets(cpf, sizeof(cpf), stdin)){
      cpf[strcspn(cpf, "\n")]=0;
      encontrou = consulta_cpf(bd, cpf);
    }
  }

  if(!encontrou){
    confirma();
    return NULL;
  }

  printf("Insira o ID do paciente: ");
  int paciente;
  scanf(" %d", &paciente);
  getchar();

  Paciente *p = bd->front;
  while(p!=NULL && p->id!=paciente){
    p = p->next;
  }
  if(p==NULL){
      printf("ID não encontrado. Retornando ao menu principal.\n");
      confirma();
      return NULL;
  }
  return p;
}


void consulta_paciente(BDPacientes *bd){ // Unifica a busca por nome ou CPF em uma "única" chamada
  clearConsole();
  printFrame();
  printf("1 - Busca por nome.\n2 - Busca por CPF.\n3 - Voltar ao menu principal.\n");
  int busca;
  scanf(" %d", &busca);

  if(busca == 3){
    printf("Consulta cancelada.\n");
    return NULL;
  }
  if(busca == 1){
    char nome[100];
    printf("Insira o nome a ser buscado: ");
    scanf(" %s", &nome);
    consulta_nome(bd, nome);
  }
  if(busca == 2){
    char cpf[15];
    printf("Insira o CPF a ser buscado: ");
    scanf(" %s", &cpf);
    consulta_cpf(bd, cpf);
  }
}

int consulta_nome(BDPacientes *bd, const char *nomeconsulta){
  Paciente *p = bd->front;
  size_t len = strlen(nomeconsulta);
  int encontrou = 0;
  while(p!=NULL){
    if(strncmp(p->nome, nomeconsulta, len)==0){
      imprimir_paciente(p);
      encontrou = 1;
    }
    p = p->next;
  }
  if(!encontrou){
    printf("Nenhum paciente encontrado com esse nome.\n");
  }
  return encontrou;
}

int consulta_cpf(BDPacientes *bd, const char *cpfconsulta){
  Paciente *p = bd->front;
  size_t len = strlen(cpfconsulta);
  int encontrou = 0;
  while(p!=NULL){
    if(strncmp(p->cpf, cpfconsulta, len)==0){
      imprimir_paciente(p);
      encontrou = 1;
    }
    p = p->next;
  }
  if(!encontrou){
    printf("Nenhum paciente encontrado com esse CPF.\n");
  }
  return encontrou;
}


void salvar_csv(BDPacientes *bd){
  FILE *f = fopen("bd_pacientes.csv", "w");
  if(f==NULL){
    printf("Erro ao salvar o arquivo CSV.\n");
    return;
  }

  // Cabeçalho
  fprintf(f, "Id,CPF,Nome,Idade,Data_Cadastro\n");

  Paciente *p = bd->front;
  while(p!=NULL){
    fprintf(f, "%d,%s,%s,%d,%s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
    p = p->next;
  }

  fclose(f);
  printf("Dados salvos com sucesso.\n");
}



//////////////////////////////////// PRINTS ////////////////////////////////////
void imprimir_cabecalho(){ // Imprime um cabeçalho para a tabela de pacientes
    printf("%-5s | %-20s | %-15s | %-5s | %-12s\n",
           "ID", "Nome", "CPF", "Idade", "Data Cadastro");
    printf("---------------------------------------------------------------\n");
}

void imprimir_paciente(const Paciente *p){ // Imprime os dados de um paciente específico
    printf("%-5d | %-20s | %-15s | %-5d | %-12s\n",
           p->id, p->nome, p->cpf, p->idade, p->data_cadastro);
}

void imprimir_todos_pacientes(BDPacientes *bd){ // Imprime todos os pacientes chamando a função acima para cada um
  if (vazia(bd)){
      printf("Nenhum paciente cadastrado.\n");
      return;
  }
  Paciente *p = bd->front;
  imprimir_cabecalho();
  while(p!=NULL){
    imprimir_paciente(p);
    p = p->next;
  }
}



//////////////////////////////////// UTILIDADES ////////////////////////////////////
int vazia(BDPacientes *bd){
  if(bd->front == NULL){
    return 1;
  }
  return 0;
}

void printFrame(){
    printf("\n====================================================================\n");
}

void finalizar(BDPacientes *bd){
  Paciente *p = bd->front;
  while(p != NULL){
    Paciente *tmp = p;
    p = p->next;
    free(tmp);
  }
  bd->front = NULL;
  bd->rear = NULL;
  bd->total = 0;
  free(bd);
}

void confirma(){
  printf("Confirmar [Enter]");
  while(getchar()!='\n');
  getchar();
}

void clearConsole(){
  printf("\n\n\n");
}