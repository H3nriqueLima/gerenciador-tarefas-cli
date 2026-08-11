#pragma once

#include <stdio.h>

static inline void show_menu(void) {
	printf("---------- Gerenciador de Tarefas ----------\n");
	printf("1. Adicionar Tarefa.\n");
	printf("2. Listar Tarefas.\n");
	printf("3. Marcar Tarefa como Concluída.\n");
	printf("4. Remover Tarefa.\n");
	printf("5. Sair do programa.\n");
	printf("--------------------------------------------\n");
}