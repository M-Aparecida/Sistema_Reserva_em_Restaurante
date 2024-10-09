#ifndef RESERVA_H
#define RESERVA_H

typedef struct reserva Reserva;

Reserva* criar_reserva(char* nome_responsavel, char* horario_inicio, char* horario_saida, int numero_mesa, float consumo);
int validar_nome(char* nome);
int validar_horarios(char* horario_inicio, char* horario_saida);
int validar_consumo(float consumo);
int validar_numero_mesa(Restaurante* restaurante, int numero_mesa);

#endif
