#ifndef RESERVA_H
#define RESERVA_H

//Estrutura que representa uma reserva
typedef struct {
    char nome_responsavel[100]; 
    char horario_inicio[6];     
    char horario_saida[6];      
    int numero_mesa;          
    float consumo;              
} Reserva;

//Função para criar uma nova reserva
Reserva* criar_reserva(char* nome_responsavel, char* horario_inicio, char* horario_saida, int numero_mesa, float consumo);

//Função para validar o nome do responsável (não pode conter números ou caracteres especiais)
int validar_nome(char* nome);

//Função para validar os horários de início e saída (formato 24h)
int validar_horarios(char* horario_inicio, char* horario_saida);

//Função para validar o consumo (deve ser maior ou igual a zero)
int validar_consumo(float consumo);

#endif 
