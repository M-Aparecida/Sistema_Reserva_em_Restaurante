#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#include "restaurante.h"

struct reserva{
    char nome_responsavel[100];
    char horario_inicio[6];
    char horario_saida[6];
    int numero_mesa;
    float consumo;
};

Reserva* criar_reserva(char* nome_responsavel, char* horario_inicio, char* horario_saida, int numero_mesa, float consumo) {
    Reserva* reserva = (Reserva*) malloc(sizeof(Reserva));
    strcpy(reserva->nome_responsavel, nome_responsavel);
    strcpy(reserva->horario_inicio, horario_inicio);
    strcpy(reserva->horario_saida, horario_saida);
    reserva->numero_mesa = numero_mesa;
    reserva->consumo = consumo;
    return reserva;
}

// Função para validar o nome, permitindo apenas letras e espaços
int validar_nome(char* nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        // Verifica se os caracteres estão dentro do intervalo de letras ou se é um espaço
        if (!((nome[i] >= 'A' && nome[i] <= 'Z') || (nome[i] >= 'a' && nome[i] <= 'z') || nome[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}

// Função para validar um horário no formato HH:MM usando tabela ASCII
int validar_horario(char* horario) {
    // Verifica se o formato é exatamente HH:MM (5 caracteres) e se tem ':'
    if (strlen(horario) != 5 || horario[2] != ':') {
        return 0;
    }

    // Verifica se cada caractere está dentro dos limites ASCII de dígitos
    if (!(horario[0] >= '0' && horario[0] <= '2') || 
        !(horario[1] >= '0' && horario[1] <= '9') ||
        !(horario[3] >= '0' && horario[3] <= '5') || 
        !(horario[4] >= '0' && horario[4] <= '9')) {
        return 0;
    }

    // Converte os primeiros dois dígitos em horas
    int hora = (horario[0] - '0') * 10 + (horario[1] - '0');
    int minuto = (horario[3] - '0') * 10 + (horario[4] - '0');

    // Verifica se a hora está entre 00 e 23 e os minutos entre 00 e 59
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        return 0;
    }

    return 1;
}

// Função para validar os horários de início e saída
int validar_horarios(char* horario_inicio, char* horario_saida) {
    if (!validar_horario(horario_inicio) || !validar_horario(horario_saida)) {
        return 0;
    }

    int hora_inicio, minuto_inicio, hora_saida, minuto_saida;
    sscanf(horario_inicio, "%d:%d", &hora_inicio, &minuto_inicio);
    sscanf(horario_saida, "%d:%d", &hora_saida, &minuto_saida);

    // Verifica se o horário de início é menor que o de saída
    if (hora_inicio > hora_saida || (hora_inicio == hora_saida && minuto_inicio >= minuto_saida)) {
        return 0;
    }

    return 1;
}

// Função para validar o consumo
int validar_consumo(float consumo) {
    return consumo >= 0;
}

// Função para verificar se a mesa está disponível no horário especificado
int validar_numero_mesa(Restaurante* restaurante, int numero_mesa, char* horario_inicio, char* horario_saida) {
    int hora_inicio, minuto_inicio, hora_saida, minuto_saida;
    sscanf(horario_inicio, "%d:%d", &hora_inicio, &minuto_inicio);
    sscanf(horario_saida, "%d:%d", &hora_saida, &minuto_saida);

    for (int i = 0; i < restaurante->total_reservas; i++) {
        if (restaurante->reservas[i]->numero_mesa == numero_mesa) {
            int hora_inicio_existente, minuto_inicio_existente, hora_saida_existente, minuto_saida_existente;
            sscanf(restaurante->reservas[i]->horario_inicio, "%d:%d", &hora_inicio_existente, &minuto_inicio_existente);
            sscanf(restaurante->reservas[i]->horario_saida, "%d:%d", &hora_saida_existente, &minuto_saida_existente);

            // Verifica se os horários conflitariam
            if ((hora_inicio >= hora_inicio_existente && hora_inicio < hora_saida_existente) ||
                (hora_saida > hora_inicio_existente && hora_saida <= hora_saida_existente) ||
                (hora_inicio_existente >= hora_inicio && hora_inicio_existente < hora_saida) ||
                (hora_saida_existente > hora_inicio && hora_saida_existente <= hora_saida)) {
                return 0;  // Conflito de horário
            }
        }
    }
    return 1;  // Sem conflito
}
