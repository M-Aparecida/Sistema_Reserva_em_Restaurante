#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"
#include "reserva.h"

void menu() {
    printf("1. Adicionar reserva\n");
    printf("2. Excluir reserva\n");
    printf("3. Listar reservas marcadas\n");
    printf("4. Buscar reserva\n");
    printf("5. Editar cadastro de reserva\n");
    printf("6. Consultar reserva para um cliente\n");
    printf("7. Sair\n");
    printf("Digite uma opção: ");
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Restaurante* restaurante = criar_restaurante("Rua Exemplo, 123", "08:00", "22:00", 20);
    carregar_dados(restaurante, "reservas.txt");
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        limpar_buffer();
        switch (opcao) {
            case 1: {
                char nome[100], horario_inicio[6], horario_saida[6];
                int numero_mesa;
                float consumo;
                printf("Nome do responsável: ");
                scanf("%99[^\n]", nome);
                limpar_buffer();
                printf("Horário de início (HH:MM): ");
                scanf("%5s", horario_inicio);
                limpar_buffer();
                printf("Horário de saída (HH:MM): ");
                scanf("%5s", horario_saida);
                limpar_buffer();
                printf("Número da mesa: ");
                scanf("%d", &numero_mesa);
                limpar_buffer();
                printf("Consumo: ");
                scanf("%f", &consumo);
                limpar_buffer();
                if (validar_nome(nome) && validar_horarios(horario_inicio, horario_saida) && validar_consumo(consumo) && validar_numero_mesa(restaurante, numero_mesa, horario_inicio, horario_saida)) {
                    Reserva* reserva = criar_reserva(nome, horario_inicio, horario_saida, numero_mesa, consumo);
                    adicionar_reserva(restaurante, reserva);
                } else {
                    printf("Dados inválidos para a reserva.\n");
                }
                break;
            }
            case 2: {
                int numero_mesa;
                printf("Número da mesa da reserva a ser excluída: ");
                scanf("%d", &numero_mesa);
                limpar_buffer();
                excluir_reserva(restaurante, numero_mesa);
                break;
            }
            case 3:
                listar_reservas(restaurante);
                break;
            case 4: {
                int numero_mesa;
                printf("Número da mesa da reserva a ser buscada: ");
                scanf("%d", &numero_mesa);
                limpar_buffer();
                Reserva* reserva = buscar_reserva(restaurante, numero_mesa);
                if (reserva != NULL) {
                    printf("Nome: %s, Início: %s, Saída: %s, Mesa: %d, Consumo: %.2f\n",
                           reserva->nome_responsavel, reserva->horario_inicio, reserva->horario_saida,
                           reserva->numero_mesa, reserva->consumo);
                } else {
                    printf("Reserva não encontrada.\n");
                }
                break;
            }
            case 5: {
                int numero_mesa;
                printf("Número da mesa da reserva a ser editada: ");
                scanf("%d", &numero_mesa);
                limpar_buffer();
                char novo_nome[100], horario_inicio[6], horario_saida[6];
                int novo_numero_mesa;
                float consumo;
                printf("Novo nome do responsável: ");
                scanf("%99[^\n]", novo_nome);
                limpar_buffer();
                printf("Novo horário de início (HH:MM): ");
                scanf("%5s", horario_inicio);
                limpar_buffer();
                printf("Novo horário de saída (HH:MM): ");
                scanf("%5s", horario_saida);
                limpar_buffer();
                printf("Novo número da mesa: ");
                scanf("%d", &novo_numero_mesa);
                limpar_buffer();
                printf("Novo consumo: ");
                scanf("%f", &consumo);
                limpar_buffer();
                if (validar_nome(novo_nome) && validar_horarios(horario_inicio, horario_saida) && validar_consumo(consumo) && validar_numero_mesa(restaurante, novo_numero_mesa, horario_inicio, horario_saida)) {
                    Reserva* nova_reserva = criar_reserva(novo_nome, horario_inicio, horario_saida, novo_numero_mesa, consumo);
                    editar_reserva(restaurante, numero_mesa, nova_reserva);
                } else {
                    printf("Dados inválidos para a reserva.\n");
                }
                break;
            }
            case 6: {
                int numero_mesa;
                printf("Número da mesa da reserva a ser consultada: ");
                scanf("%d", &numero_mesa);
                limpar_buffer();
                consultar_reserva(restaurante, numero_mesa);
                break;
            }
            case 7:
                salvar_dados(restaurante, "reservas.txt");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);
    return 0;
}
