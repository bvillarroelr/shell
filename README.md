# Shell
Implementación de intérprete de comandos en linux para el curso de Sistemas Operativos 2024-2

Colaboradores:
Ricardo Charris Jimenez
Vicente Ramírez Torrealba
Juan Umaña Silva
Benjamín Villarroel Rubio

# Instrucciones de compilación
1.- Compilar el programa:
```
 g++ shell.cpp favs.cpp
 ```
2.- Ejecutar el programa desde la terminal con el comando:
```
 ./a.out
 ```

# Lista de los comandos mas usados para ejecutar en la shell: 
1. ls 	para mostrar los los archivos
2. cd 	"nombre/del/directorio" para moverse de directorio
3. clear 	para limpiar el espacio de la shell 
4. exit 	para salir de la shell y regresar a la terminal original del sistema operativo
5. uso de pipes: "|"; permite comunicar procesos entre sí. Toma la salida de uno y se la da a la entrada del otro para ejecutarlo.
6. cd .. 	permite devolverse de directorio
7. wc    	muestra el número de líneas, palabras y caracteres de la entrada dada


# Ejecución de comando personalizado favs:

1. favs crear (ruta/nombre_archivo.txt), pide una ruta de archivo de texto
2. favs mostrar (), muestra los comandos favoritos en la shell
3. favs elimminar (conjunto de numeros separados por ","), elimina los comandos favoritos listados por numeros
4. favs buscar (palabra o letra en comun), muestra en la shell los comandos favoritos que tienen letras o palabras en comun
5. favs ejecutar (index), ejecuta el comando favorito con id=index
6. favs cargar (), carga los comandos favoritos desde un archivo creado en la ejecucion actual de la shell
7. favs cargar (ruta/nombre_archivo.txt), carga los comandos favoritos desde un archivo preexistente
8. favs guardar (), guarda los comandos favoritos en el archivo creado en la ejecucion actual de la shell
9. favs guardar (ruta/nombre_archivo.txt), guarda los comandos favoritos en la ruta de un archivo preexistentes
10. favs borrar (), elimina  todos los comandos favoritos guardados en el vector de comandos 
