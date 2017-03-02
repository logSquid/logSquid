/* 
 * File:   config.h
 * Author: Mauro Marssola
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <confuse.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef CONFIG_H
#define CONFIG_H

extern char *__progname;

/*
 * Carrega as configurações padrão para o agent
 * Não retorna nenhum valor, apenas atribui os valores lidos do arquivo de configuração para suas respectivas variaveis
 */
void lgsqd_agent_load();

/*
 * Carrega as configurações padrão para o server
 * Não retorna nenhum valor, apenas atribui os valores lidos do arquivo de configuração para suas respectivas variaveis
 */
void lgsqd_server_load();

/*
 * Verifica se o arquivo de configuração existe no sistema de arquivos.
 * Chamado pela função getParameters ao ser comparado com o switch no caractere 'c'.
 * Recebe variavel com o nome do arquivo inserido pelo usuário na linha de comando.
 *  Se não existir: encerra o programa e exibe uma mensagem de erro.
 *  Se Existir: Atribui o parametro recebido na função para a variavel ConfFile, utilizada nas funções: lgsqd_agent_load() e lgsqd_server_load().
 */
void check_ConfFile(char *file);

/*
 * Mensagem de Help para o Agent
 */
void lgsqd_help_agent();

/*
 * Mensagem de Help para o Server
 */
void lgsqd_help_server();

/*
 * Chama a função correspondente ao programa que está sendo executado, para ler o arquivo conf correspondente.
 * Recebe o valor da variavel __progname para comparação.
 * Se ConfFile não foi denifido, determina o caminho padrão do conf.
 */
void lgsqd_load_config(void);

/*
 * Recebe os parametros inseridos pelo usuário e executa as funções correspondente.
 * Chamada da função: getParameters(argc, argv);
 * Recebe Parametros: int argc, char **argv
 */
void getParameters(int argc, char **argv);


#endif /* CONFIG_H */

