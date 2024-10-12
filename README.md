# Sistema de Reserva em Restaurante

## Sumário:
- Utilidade
- Funcionalidades
- Organização do repositório
- Tecnologia utilizada
- Execução
- Desenvolvedor

## Utilidade
Tem como principal utilidade a automação do processo de gerenciamento de reservas, tornando mais fácil para o restaurante controlar a ocupação das mesas, evitar conflitos de horários e gerenciar os dados dos clientes e suas preferências de forma eficiente. Através do sistema, o restaurante pode adicionar, remover e consultar reservas, bem como verificar o consumo dos clientes, mantendo os dados em um arquivo de texto.

## Funcionalidades: 

| Menu               | 
| ----------------- | 
| [1] - Adicionar reserva 
| [2] - Excluir reserva
| [3] - Listar reservas marcadas
| [4] - Buscar reserva
| [5] - Editar cadastro de reserva
| [6] - Consultar reserva para um cliente
| [7] - Sair

## Organização do repositório
```
📁 - Sistema_Reserva_em_Restaurante


|
└─── data
│
└─── include
        │
        ├──reserva.h
        ├──restaurante.h    
│
└─── src
        │
        ├──main.c
        ├──reserva.c
        ├──restaurante.c
│
└───test
│
└───README.md
```

## Tecnologia utilizada
___

![c](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)


## Execução:
Primeiro clone o repositório na sua máquina, com o seguinte comando:
```
git clone https://github.com/M-Aparecida/Sistema_Reserva_em_Restaurante.git

```
No seu terminal, use o comando:
```
gcc -o main.exe .\src\reserva.c .\src\restaurante.c .\src\main.c

```
- Para Windows execute com `./main` e para Linux `./main.exe`

## Desenvolvedor 
Maria Aparecida

