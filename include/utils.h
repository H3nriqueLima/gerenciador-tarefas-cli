#pragma once

#include <stdlib.h>
#include <constants.h>

static inline void create_id(char* id_field) {
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int charset_size = sizeof(charset) - 1;

	for (int i = 0; i < ID_LENGTH; i++) {
		int key = rand() % charset_size;
		id_field[i] = charset[key];
	}

	id_field[ID_LENGTH] = '\0';
}