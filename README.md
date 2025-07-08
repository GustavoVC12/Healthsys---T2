# EP1 - Estrutura de Dados: Sistema de Clínica (HealthSys)

Este projeto é um sistema simples de gerenciamento de pacientes para uma clínica médica. O sistema faz a leitura de dados a partir de um arquivo CSV e permite a busca de pacientes pelo nome ou CPF com base em prefixos, além de possibilitar a inserção, atualização, remoção e impressão da lista de pacientes.

## Como compilar e executar

Este projeto foi desenvolvido em C e deve ser compilado em ambientes Linux com GCC 11 (como Ubuntu 22.04).

### Requisitos
- GCC (versão 11 ou compatível)  
- Make  

### Compilação e execução
No terminal, dentro do diretório do projeto:

```
make           # Compila o projeto
./healthsys    # Executa o programa
make clean     # Remove os arquivos objeto e executável
```



Organização do Projeto
| Arquivo            | Descrição                                                  |
| ------------------ | ---------------------------------------------------------- |
| `main.c`           | Função principal com o menu de opções                      |
| `bdpacientes.h`    | Definições das estruturas e declarações das funções do TAD |
| `bdpacientes.c`    | Implementação das funcionalidades do sistema               |
| `bd_pacientes.csv` | Base de dados dos pacientes (entrada do sistema)           |
| `Makefile`         | Script para compilação automática                          |
| `README.md`        | Documentação do projeto                                    |




Principais TADs e Estruturas
- Paciente: representa um paciente individual, com os campos:
-- id: inteiro
-- cpf: string (formato XXX.XXX.XXX-XX)
-- nome: string
-- idade: inteiro
-- data_cadastro: string (formato AAAA-MM-DD)

- BDPacientes: representa o banco de pacientes com uma lista encadeada, contendo:
-- Ponteiro para o primeiro paciente (front)
-- Ponteiro para o último paciente (rear)
-- Total de pacientes cadastrados (total)


Funcionalidades implementadas
- Leitura do CSV: carrega os dados do arquivo bd_pacientes.csv ao iniciar o sistema. Cada linha é convertida em uma struct Paciente e adicionada à lista.
- Inserção, Atualização e Remoção: permite gerenciar pacientes no banco de dados.
- Consulta por prefixo: busca pacientes por nome ou CPF usando prefixos, mostrando todos os resultados que combinam.
- Impressão da lista: exibe todos os pacientes cadastrados em formato tabular.
- Persistência dos dados: alterações feitas durante a execução são salvas no arquivo CSV ao sair do programa.


Decisões de implementação
- O sistema utiliza lista encadeada para facilitar inserção e remoção dinâmica de pacientes.
- Funções específicas cuidam da lógica de busca, inserção, atualização e remoção para modularizar o código.
- Uso de funções auxiliares para limpar tela, imprimir cabeçalhos e confirmar ações via Enter.
