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
#include <file.h>

int main(void) {
	srand((unsigned int)time(NULL));

	SetConsoleOutputCP(CP_UTF8);

	system("cls");

	LinkedList *task_list = ll_create();

	load_tasks(task_list);

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

			save_tasks(task_list);

			printf("\nTarefa adicionada com sucesso! ID: %s\n\n", new_task->id);

			system("pause");
			system("cls");
		} else if (strcmp(option, "2") == 0) {
			printf("---------- Lista de Tarefas ----------\n");
			ll_for_each(task_list, print_task, NULL);

			printf("\n");

			system("pause");
			system("cls");
		} else if (strcmp(option, "3") == 0) {
			printf("---------- Check de Tarefas ----------\n");
			
			char id_field[ID_LENGTH + 1] = "";

			printf("Qual o ID da sua tarefa? ID: ");
			read_input(id_field, sizeof(id_field));

			TaskSearchContext search = { .search_id = id_field, .found_task = NULL };
			ll_for_each(task_list, find_task_by_id, &search);

			if (search.found_task != NULL) {
				printf("\nTarefa concluída!\n");

				search.found_task->status.is_completed = true;

				save_tasks(task_list);
				
				printf("[%s] %s (%s)\n\n", search.found_task->id, search.found_task->description, search.found_task->status.is_completed ? "Concluída" : "Pendente");
			} else {
				printf("\nTarefa não encontrada!\n\n");
			}

			system("pause");
			system("cls");
		} else if (strcmp(option, "4") == 0) {
			printf("---------- Remover Tarefa ----------\n");

			char id_field[ID_LENGTH + 1] = "";

			printf("Qual o ID da sua tarefa? ID: ");
			read_input(id_field, sizeof(id_field));

			TaskSearchContext search = { .search_id = id_field, .found_task = NULL, .found_index = -1, .current_index = 0 };
			ll_for_each(task_list, find_task_by_id, &search);

			if (search.found_task != NULL) {
				Task* removed = (Task*)ll_remove_at(task_list, (size_t)search.found_index);
				free_task(removed);

				save_tasks(task_list);

				printf("\nTarefa removida com sucesso!\n\n");
			}
			else {
				printf("\nTarefa não encontrada!\n\n");
			}

			system("pause");
			system("cls");
		} else if (strcmp(option, "5") == 0) {
			printf("Finalizando programa...");
			ll_destroy_with_values(task_list, free_task);
			break;
		}
	}
}