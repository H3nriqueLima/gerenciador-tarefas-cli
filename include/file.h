#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <task.h>
#include <libcds/linked_list.h>

static inline void write_task_to_file(void* value, void* context) {
	Task* task = (Task*)value;
	FILE* file = (FILE*)context;

	fwrite(task, sizeof(Task), 1, file);
}

static inline void save_tasks(LinkedList* task_list) {
	FILE* file = fopen("data/data.bin", "wb");
	if (file == NULL) {
		printf("Erro ao criar o arquivo de dados!");
		return;
	}

	ll_for_each(task_list, write_task_to_file, file);

	fclose(file);
}

static inline void load_tasks(LinkedList* task_list) {
	FILE* file = fopen("data/data.bin", "rb");
	if (file == NULL) return;

	while (true) {
		Task* task = create_task();
		if (task == NULL) break;

		if (fread(task, sizeof(Task), 1, file) != 1) {
			free_task(task);
			break;
		}

		ll_add_last(task_list, task);
	}

	fclose(file);
}

