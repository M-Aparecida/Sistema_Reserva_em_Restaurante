#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/reserva.h"
#include "../include/restaurante.h" 

Reserva* criar_reserva(char* nome_responsavel, char* horario_inicio, char* horario_saida, int numero_mesa, float consumo) {
    Reserva* reserva = (Reserva*) malloc(sizeof(Reserva));
    strcpy(reserva->nome_responsavel, nome_responsavel);
    strcpy(reserva->horario_inicio, horario_inicio);
    strcpy(reserva->horario_saida, horario_saida);
    reserva->numero_mesa = numero_mesa;
    reserva->consumo = consumo;
    return reserva;
}

int validar_nome(char* nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!((nome[i] >= 'A' && nome[i] <= 'Z') || (nome[i] >= 'a' && nome[i] <= 'z') || nome[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}

int validar_horario(char* horario) {
    if (strlen(horario) != 5 || horario[2] != ':') {
        return 0;
    }
    if (!(horario[0] >= '0' && horario[0] <= '2') || !(horario[1] >= '0' && horario[1] <= '9') ||
        !(horario[3] >= '0' && horario[3] <= '5') || !(horario[4] >= '0' && horario[4] <= '9')) {
        return 0;
    }
    if (horario[0] == '2' && horario[1] > '3') {
        return 0;
    }
    return 1;
}

int validar_horarios(char* horario_inicio, char* horario_saida) {
    if (!validar_horario(horario_inicio) || !validar_horario(horario_saida)) {
        return 0;
    }
    int hora_inicio, minuto_inicio, hora_saida, minuto_saida;
    sscanf(horario_inicio, "%d:%d", &hora_inicio, &minuto_inicio);
    sscanf(horario_saida, "%d:%d", &hora_saida, &minuto_saida);
    if (hora_inicio < 0 || hora_inicio > 23 || minuto_inicio < 0 || minuto_inicio > 59 ||
        hora_saida < 0 || hora_saida > 23 || minuto_saida < 0 || minuto_saida > 59) {
        return 0;
    }
    if (hora_inicio == hora_saida && minuto_inicio == minuto_saida) {
        return 0;
    }
    if (hora_inicio < hora_saida || (hora_inicio == hora_saida && minuto_inicio < minuto_saida)) {
        return 1;
    }
    return 0;
}

int validar_consumo(float consumo) {
    return consumo >= 0;
}

int validar_numero_mesa(Restaurante* restaurante, int numero_mesa, char* horario_inicio, char* horario_saida) {
    for (int i = 0; i < restaurante->total_reservas; i++) {
        if (restaurante->reservas[i]->numero_mesa == numero_mesa) {
            int hora_inicio, minuto_inicio, hora_saida, minuto_saida;
            sscanf(horario_inicio, "%d:%d", &hora_inicio, &minuto_inicio);
            sscanf(horario_saida, "%d:%d", &hora_saida, &minuto_saida);
            int hora_inicio_existente, minuto_inicio_existente, hora_saida_existente, minuto_saida_existente;
            sscanf(restaurante->reservas[i]->horario_inicio, "%d:%d", &hora_inicio_existente, &minuto_inicio_existente);
            sscanf(restaurante->reservas[i]->horario_saida, "%d:%d", &hora_saida_existente, &minuto_saida_existente);
            if ((hora_inicio >= hora_inicio_existente && hora_inicio < hora_saida_existente) ||
                (hora_saida > hora_inicio_existente && hora_saida <= hora_saida_existente) ||
                (hora_inicio_existente >= hora_inicio && hora_inicio_existente < hora_saida) ||
                (hora_saida_existente > hora_inicio && hora_saida_existente <= hora_saida)) {
                return 0;
            }
        }
    }
    return 1;
}
