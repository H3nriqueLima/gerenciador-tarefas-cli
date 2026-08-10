#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <libcds/linked_list.h>
#include <utils.h>
#include <task.h>
#include <menu.h>
#include <input.h>

int main(void) {
	srand((unsigned int)time(NULL));

	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	LinkedList *task_list = ll_create();

	while (true) {
		show_menu();

		char option[8] = "";

		printf("Opção: ");
		read_input(option, sizeof(option));

		system("cls");

		if (strcmp(option, "1") == 0) {
			Task *new_task = create_task();

			create_id(new_task->id);

			printf("---------- Nova Tarefa ----------\n");
			printf("Descrição da Tarefa: ");
			fgets(new_task->description, sizeof(new_task->description), stdin);
			
			new_task->description[strcspn(new_task->description, "\n")] = '\0';
			
			new_task->status.is_completed = false;

			ll_add_first(task_list, new_task);

			printf("Tarefa adicionada com sucesso! ID: %s\n\n", new_task->id);

			system("pause");
			system("cls");
		} else if (strcmp(option, "2") == 0) {
			printf("---------- Lista de Tarefas ----------\n");
			ll_for_each(task_list, print_task, NULL);

			system("pause");
			system("cls");
		} else if (strcmp(option, "3") == 0) {
			printf("---------- Check de Tarefas ----------\n");
			printf("Qual o ID da sua tarefa? ID: ");

			char id_field[ID_LENGTH] = "";
			read_input(id_field, sizeof(id_field));
		}
	}

	//ll_destroy_with_values(task_list, free_task);
}