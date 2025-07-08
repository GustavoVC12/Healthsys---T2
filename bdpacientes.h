#ifndef BDPACIENTES_H
#define BDPACIENTES_H



//////////////////////////////////// ESTRUTURAS ////////////////////////////////////
typedef struct paciente Paciente;
typedef struct bdpacientes BDPacientes;

// Cria um novo banco de dados (inicializa a lista)
BDPacientes *criar_banco();


//////////////////////////////////// MANIPULAÇÃO DA LISTA ////////////////////////////////////
// Carrega os dados de pacientes do arquivo CSV
void carregar_csv(BDPacientes *bd);

// Coleta os dados de um novo paciente
void inserir_dados_paciente(BDPacientes *bd);

// Insere um novo paciente ao final da lista
void criar_paciente(BDPacientes *bd, int pId, const char *pCpf, const char *pNome, int pIdade, const char *pData, int flagprint);

// Atualiza um paciente específico
void atualizar_paciente(BDPacientes *bd);

// Remove um paciente específico
void remover_paciente(BDPacientes *bd);

// Salva os dados atualizados no csv
void salvar_csv(BDPacientes *bd);



//////////////////////////////////// BUSCA DE PACIENTES ////////////////////////////////////
// Encontra um paciente específico
Paciente *encontrar_paciente(BDPacientes *bd);

// Unifica a busca por nome ou CPF em uma "única" chamada
void consulta_paciente(BDPacientes *bd);

// Exibe todos os pacientes com um prefixo específico no nome
int consulta_nome(BDPacientes *bd, const char *nomeconsulta);

// Exibe todos os pacientes com um prefixo específico no CPF
int consulta_cpf(BDPacientes *bd, const char *cpfconsulta);



//////////////////////////////////// PRINTS ////////////////////////////////////
// Imprime um cabeçalho para a tabela de pacientes
void imprimir_cabecalho();

// Imprime um paciente
void imprimir_paciente(const Paciente *p);

// Imprime todos os pacientes chamando a função acima para cada um
void imprimir_todos_pacientes(BDPacientes *bd);



//////////////////////////////////// UTILIDADES ////////////////////////////////////

// Funções auxiliares
int vazia(BDPacientes *bd);
void printFrame();
void finalizar(BDPacientes *bd);
void confirma();
void clearConsole();

#endif