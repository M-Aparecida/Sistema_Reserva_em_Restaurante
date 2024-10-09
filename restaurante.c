#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurante.h"

struct restaurante{
    char localizacao[100];
    char horario_abertura[6];
    char horario_fechamento[6];
    int total_mesas;
    int total_reservas;
    Reserva** reservas;
};

Restaurante* criar_restaurante(char* localizacao, char* horario_abertura, char* horario_fechamento, int total_mesas) {
    Restaurante* restaurante = (Restaurante*) malloc(sizeof(Restaurante));
    strcpy(restaurante->localizacao, localizacao);
    strcpy(restaurante->horario_abertura, horario_abertura);
    strcpy(restaurante->horario_fechamento, horario_fechamento);
    restaurante->total_mesas = total_mesas;
    restaurante->total_reservas = 0;
    restaurante->reservas = (Reserva**) malloc(total_mesas * sizeof(Reserva*));
    return restaurante;
}

void adicionar_reserva(Restaurante* restaurante, Reserva* reserva) {
    if (validar_horarios(reserva->horario_inicio, reserva->horario_saida) && validar_nome(reserva->nome_responsavel) &&
        validar_consumo(reserva->consumo) && validar_numero_mesa(restaurante, reserva->numero_mesa, reserva->horario_inicio, reserva->horario_saida)) {
        restaurante->reservas[restaurante->total_reservas] = reserva;
        restaurante->total_reservas++;
    } else {
        printf("Dados inválidos para a reserva.\n");
    }
}

void excluir_reserva(Restaurante* restaurante, int numero_mesa) {
    for (int i = 0; i < restaurante->total_reservas; i++) {
        if (restaurante->reservas[i]->numero_mesa == numero_mesa) {
            free(restaurante->reservas[i]);
            for (int j = i; j < restaurante->total_reservas - 1; j++) {
                restaurante->reservas[j] = restaurante->reservas[j + 1];
            }
            restaurante->total_reservas--;
            printf("Reserva excluída.\n");
            return;
        }
    }
    printf("Reserva não encontrada.\n");
}

void listar_reservas(Restaurante* restaurante) {
    for (int i = 0; i < restaurante->total_reservas; i++) {
        Reserva* reserva = restaurante->reservas[i];
        printf("Nome: %s, Início: %s, Saída: %s, Mesa: %d, Consumo: %.2f\n",
               reserva->nome_responsavel, reserva->horario_inicio, reserva->horario_saida,
               reserva->numero_mesa, reserva->consumo);
    }
}

Reserva* buscar_reserva(Restaurante* restaurante, int numero_mesa) {
    for (int i = 0; i < restaurante->total_reservas; i++) {
        if (restaurante->reservas[i]->numero_mesa == numero_mesa) {
            return restaurante->reservas[i];
        }
    }
    return NULL;
}

void editar_reserva(Restaurante* restaurante, int numero_mesa, Reserva* nova_reserva) {
    Reserva* reserva = buscar_reserva(restaurante, numero_mesa);
    if (reserva != NULL) {
        strcpy(reserva->nome_responsavel, nova_reserva->nome_responsavel);
        strcpy(reserva->horario_inicio, nova_reserva->horario_inicio);
        strcpy(reserva->horario_saida, nova_reserva->horario_saida);
        reserva->numero_mesa = nova_reserva->numero_mesa;
        reserva->consumo = nova_reserva->consumo;
    } else {
        printf("Reserva não encontrada.\n");
    }
}

void consultar_reserva(Restaurante* restaurante, int numero_mesa) {
    Reserva* reserva = buscar_reserva(restaurante, numero_mesa);
    if (reserva != NULL) {
        printf("Nome: %s, Início: %s, Saída: %s, Mesa: %d, Consumo: %.2f\n",
               reserva->nome_responsavel, reserva->horario_inicio, reserva->horario_saida,
               reserva->numero_mesa, reserva->consumo);
    } else {
        printf("Reserva não encontrada.\n");
    }
}

void carregar_dados(Restaurante* restaurante, char* arquivo) {
    FILE* file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    while (!feof(file)) {
        Reserva* reserva = (Reserva*) malloc(sizeof(Reserva));
        fscanf(file, "%99s %5s %5s %d %f\n", reserva->nome_responsavel, reserva->horario_inicio, reserva->horario_saida, &reserva->numero_mesa, &reserva->consumo);
        adicionar_reserva(restaurante, reserva);
    }
    fclose(file);
}

void salvar_dados(Restaurante* restaurante, char* arquivo) {
    FILE* file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < restaurante->total_reservas; i++) {
        Reserva* reserva = restaurante->reservas[i];
        fprintf(file, "%s %s %s %d %.2f\n", reserva->nome_responsavel, reserva->horario_inicio, reserva->horario_saida, reserva->numero_mesa, reserva->consumo);
    }
    fclose(file);
}
