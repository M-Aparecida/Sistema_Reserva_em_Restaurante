#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "reserva.h"

// Estrutura que representa um restaurante
typedef struct {
    char localizacao[100];      
    char horario_abertura[6];   
    char horario_fechamento[6]; 
    int total_mesas;            
    int total_reservas;         
    Reserva** reservas;        
} Restaurante;

//Função para criar um novo restaurante
Restaurante* criar_restaurante(char* localizacao, char* horario_abertura, char* horario_fechamento, int total_mesas);

//Função para adicionar uma reserva ao restaurante
void adicionar_reserva(Restaurante* restaurante, Reserva* reserva);

//Função para excluir uma reserva do restaurante
void excluir_reserva(Restaurante* restaurante, int numero_mesa);

//Função para listar todas as reservas do restaurante
void listar_reservas(Restaurante* restaurante);

//Função para buscar uma reserva específica pelo número da mesa
Reserva* buscar_reserva(Restaurante* restaurante, int numero_mesa);

//Função para editar uma reserva existente
void editar_reserva(Restaurante* restaurante, int numero_mesa, Reserva* nova_reserva);

//Função para consultar uma reserva específica pelo número da mesa
void consultar_reserva(Restaurante* restaurante, int numero_mesa);

//Função para carregar dados de reservas a partir de um arquivo
void carregar_dados(Restaurante* restaurante, char* arquivo);

//Função para salvar dados de reservas em um arquivo
void salvar_dados(Restaurante* restaurante, char* arquivo);

//Função para validar se uma mesa está disponível no horário especificado
int validar_numero_mesa(Restaurante* restaurante, int numero_mesa, char* horario_inicio, char* horario_saida);

#endif 
