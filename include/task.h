#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <constants.h>

typedef struct task_status {
	bool is_completed;
} TaskStatus;

typedef struct task {
	char id[ID_LENGTH + 1];
	char description[50];
	TaskStatus status;
} Task;

static inline Task* create_task(void) {
	Task *task = (Task*)malloc(sizeof(Task));
	if (task == NULL) return NULL;

	return task;
}

static inline void free_task(void* value) {
	Task *task = (Task*)value;
	free(task);
}

static inline void print_task(void* value, void* context) {
	(void)context;
	Task* task = (Task*)value;

	printf("[%s] %s (%s)\n", task->id, task->description, task->status.is_completed ? "Concluída" : "Pendente");
}