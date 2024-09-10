#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "favs.h"
#define MAX_FAVS 100
#define MAX_CMD_LENGTH 256




Favorite favorites[MAX_FAVS];
int fav_count = 0;
char fav_file[256] = "";



void favs_create(char *path){
    strcpy(fav_file, path);
    FILE *file = fopen(fav_file, "w");
    if(file == NULL){
        printf("Error al crear el archivo de favs \n");
        return;
    }
    fclose(file);
    printf("Archivo favs creado: %s \n", fav_file);
}
// favs mostar
void show_favs(){
    if(fav_count == 0){
        std::cout << "Error: No hay favoritos guardados" << std::endl;
    }
    for(int i = 0; i < fav_count; i++){
        printf("%d: %s\n", favorites[i].id, favorites[i].cmd);
    }
}

void favs_eliminar(char *nums) {
    char *token = strtok(nums, ",");
    while (token != NULL) {
        int num = atoi(token);
        for (int i = 0; i < fav_count; i++) {
            if (favorites[i].id == num) {
                for (int j = i; j < fav_count - 1; j++) {
                    favorites[j] = favorites[j + 1];
                }
                fav_count--;
                break;
            }
        }
        token = strtok(NULL, ",");
    }

    for (int i=0 ; i < fav_count; i++){
        favorites[i].id = i + 1;
    }
}

void favs_buscar(char *cmd) {
    for (int i = 0; i < fav_count; i++) {
        if (strstr(favorites[i].cmd, cmd) != NULL) {
            printf("%d: %s\n", favorites[i].id, favorites[i].cmd);
        }
    }
}
void favs_borrar() {
    fav_count = 0;
    printf("Todos los favoritos han sido borrados.\n");
}

std::string favs_ejecutar(int num) {
    std::string cmd;
    for (int i = 0; i < fav_count; i++) {
        if (favorites[i].id == num) {
            std::string cmd(favorites[i].cmd);
            return cmd;
        }
    }
    printf("Comando favorito no encontrado.\n");
    return cmd;
}

void favs_cargar() {
    FILE *file = fopen(fav_file, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de favoritos.\n");
        return;
    }
    fav_count = 0;
    while (fscanf(file, "%d %[^\n]", &favorites[fav_count].id, favorites[fav_count].cmd) == 2) {
        fav_count++;
    }
    fclose(file);
    if(fav_count == 0){
        std::cout << "Archivo sin favoritos guardados abierto." << std::endl;
    }else{
        std::cout << fav_count << std::endl;
        show_favs();
    }
}

void favs_cargar(char* path) {
    strcpy(fav_file, path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de favoritos.\n");
        return;
    }
    fav_count = 0;
    while (fscanf(file, "%d %[^\n]", &favorites[fav_count].id, favorites[fav_count].cmd) == 2) {
        fav_count++;
    }
    fclose(file);
    if(fav_count == 0){
        std::cout << "Archivo sin favoritos guardados abierto." << std::endl;
    }else{
        std::cout << fav_count << std::endl;
        show_favs();
    }
}

void favs_guardar() {
    FILE *file = fopen(fav_file, "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de favoritos.\n");
        return;
    }
    for (int i = 0; i < fav_count; i++) {
        fprintf(file, "%d %s\n", favorites[i].id, favorites[i].cmd);
    }
    fclose(file);
    printf("Favoritos guardados en %s\n", fav_file);
}

void favs_guardar(char* path) {
    strcpy(fav_file, path);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de favoritos.\n");
        return;
    }
    for (int i = 0; i < fav_count; i++) {
        fprintf(file, "%d %s\n", favorites[i].id, favorites[i].cmd);
    }
    fclose(file);
    printf("Favoritos guardados en %s\n", fav_file);
}

void add_favorite(char *cmd) {
    if (fav_count < MAX_FAVS) {
        for (int i = 0; i < fav_count; i++) {
            if (strcmp(favorites[i].cmd, cmd) == 0) {
                return; // El comando ya existe en favoritos
            }
        }
        strcpy(favorites[fav_count].cmd, cmd);
        favorites[fav_count].id = fav_count + 1;
        fav_count++;
    }
}
