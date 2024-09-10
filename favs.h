#ifndef FAVS_H
#define FAVS_H
#define MAX_CMD_LENGTH 256
typedef struct {
    int id;
    char cmd[MAX_CMD_LENGTH];
} Favorite;


void favs_create(char *path);

void show_favs();
void favs_eliminar(char *nums);
void favs_buscar(char *cmd);
void favs_borrar();
std::string favs_ejecutar(int num);
void favs_cargar();
void favs_cargar(char* path);
void favs_guardar();
void favs_guardar(char* path);
void add_favorite(char *cmd);
#endif