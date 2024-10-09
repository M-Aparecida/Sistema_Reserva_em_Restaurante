#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "reserva.h"

typedef struct {
    char localizacao[100];
    char horario_abertura[6];
    char horario_fechamento[6];
    int total_mesas;
    int total_reservas;
    Reserva** reservas;
} Restaurante;

Restaurante* criar_restaurante(char* localizacao, char* horario_abertura, char* horario_fechamento, int total_mesas);
void adicionar_reserva(Restaurante* restaurante, Reserva* reserva);
void excluir_reserva(Restaurante* restaurante, int numero_mesa);
void listar_reservas(Restaurante* restaurante);
Reserva* buscar_reserva(Restaurante* restaurante, int numero_mesa);
void editar_reserva(Restaurante* restaurante, int numero_mesa, Reserva* nova_reserva);
void consultar_reserva(Restaurante* restaurante, int numero_mesa);
void carregar_dados(Restaurante* restaurante, char* arquivo);
void salvar_dados(Restaurante* restaurante, char* arquivo);

#endif
