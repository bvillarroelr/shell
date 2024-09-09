#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "favs.h"

// Colores para probar con prompt, excepciones, mensajes, etc
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


void exec_cd(char* arg) {
    // hay que usar la funcion de c chdir(), que hace exactamente lo que hace cd. Retorna 0 si se hizo bien y -1 si hubo un error
    if (chdir(arg) != 0) {
        perror("chdir failed");
    }else {
        char cmd[256] = "cd ";
        strcat(cmd, arg);
        add_favorite(cmd);
    }

}
void set_remember(int seg, const std::vector<std::string>& parse_command){
    std::string msg = "";
    for(int i = 3; i < parse_command.size();i++ ){
        msg += " " + parse_command[i];
    }
    
    if(seg > 0){
        //std::cout << "\n Iniciando temporizador de " << seg << " segundos... \n";
        sleep(seg);
        std::cout << msg;
        //std::cout << "\n Temporizador terminado \n ";
    }else{
        std::cout << "entrada no valida";
    }

}
void execute_command(const std::vector<std::string>& parse_command) {
    int parse_command_size = parse_command.size();
    if(parse_command[0]=="favs"){
        //para crear
        if (parse_command[1]=="crear"){
            if(parse_command.size() < 3){
                std::cerr << "Error: Faltan argumentos. Debe usar: favs crear <ruta/nombre_archivo.txt>" << std::endl;
                exit(1);
            }else if(parse_command.size() > 3){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs crear <ruta/nombre_archivo.txt>" << std::endl;
                exit(1);
            }else{
                favs_create(strdup(parse_command[2].c_str()));// pasar el path
                exit(0);
            } 

        }else if (parse_command[1]=="mostrar"){
            if(parse_command_size > 2){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs mostrar" << std::endl;
                exit(1);
            }else{
                show_favs(); //mostrar favs
                exit(0);
            }
            

        }else if (parse_command[1]=="eliminar"){
            if (parse_command_size < 3){
                std::cerr << "Error: Faltan argumentos. Debe usar: favs eliminar <num1,num2,...,numN>" << std::endl;
                exit(1);
            }else if(parse_command_size > 3){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs eliminar <num1,num2,...,numN>" << std::endl;
                exit(1);

            }else{
                favs_eliminar(strdup(parse_command[2].c_str())); //Transformar string a char*
                exit(0);
            }
        
        }else if (parse_command[1]=="buscar"){
            if (parse_command_size < 3){
                std::cerr << "Error: Faltan argumentos. Debe usar: favs buscar <criterio>" << std::endl;
                exit(1);
            }else if(parse_command_size > 3){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs buscar <criterio>" << std::endl;
                exit(1);
            }else{
                favs_buscar(strdup(parse_command[2].c_str()));    
                exit(0);
            }

        }else if (parse_command[1]=="ejecutar"){
            if (parse_command_size < 3){
                std::cerr << "Error: Faltan argumentos. Debe usar: favs ejecutar  <num>" << std::endl;
                exit(1);
            }else if(parse_command_size > 3){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs ejecutar  <num>" << std::endl;
                exit(1);
            }
            else{
                favs_ejecutar(std::stoi(parse_command[2]));
                exit(0);
            }
        }else if (parse_command[1] == "cargar"){
            if(parse_command_size == 2){
                favs_cargar();
                exit(0);
            } else if(parse_command_size == 3){
                favs_cargar(strdup(parse_command[2].c_str()));
                exit(0);
            } else{
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs cargar <ruta/nombre_archivo.txt> o favs cargar" << std::endl;
                exit(1);
            }
        } else if(parse_command[1] == "guardar"){
            if(parse_command_size == 2){
                favs_guardar();
                exit(0);
            } else if(parse_command_size == 3){
                favs_guardar(strdup(parse_command[2].c_str()));
                exit(0);
            } else{
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs guardar <ruta/nombre_archivo.txt> o favs guardar" << std::endl;
                exit(1);
            }

        } else if(parse_command[1] == "borrar"){
            if(parse_command_size > 2){
                std::cerr << "Error: Demasiados argumentos. Debe usar: favs borrar" << std::endl;
                exit(1);
            } else{
                favs_borrar();
                exit(0);
            }

        } else{
            std::cerr << "Error: El Comando 'favs " << parse_command[1] << "' no se reconoce." << std::endl;
            exit(1);
        }       
    }else{
        char* myargs[parse_command_size + 1];
    
        for(int i = 0 ; i < parse_command_size ; i++) {
            myargs[i] = strdup(parse_command[i].c_str());
        }
        myargs[parse_command_size] = NULL;
        if (execvp(myargs[0], myargs) == -1) {
            std::cerr << parse_command[0] << ": no se encontró la orden" << std::endl;
            exit(1);
        }   
        exit(0);
    } 
}

int main(){

    while(true){
        struct passwd* pw = getpwuid(getuid());
        //pw_dir, entrega el directorio home del usuario
        std::string username = pw->pw_name, command, word;
        int parse_command_size;
        char hostname[1024],cwd[1024];
        getcwd(cwd, sizeof(cwd));
        gethostname(hostname, sizeof(hostname));
        std::cout <<  GREEN << username << "@" << hostname << ":" << RED << cwd << "$ " << RESET;
        std::getline(std::cin, command);

        //Parsea el comando ingresado y lo divide en el comando como tal y sus argumentos
        std::istringstream iss(command);
        std::vector<std::string> parse_command;

        while(iss >> word){
            parse_command.push_back(word);
        }
        parse_command_size = parse_command.size();

        if(parse_command.empty()) continue;
        else if(parse_command[0] == "exit") break;
        else if(parse_command[0] == "set"){
            // llamar al archivo y ejecutarlo 
            pid_t pro = fork();

            if( pro == 0 ){

                if(parse_command[1] == "remember"){
                    if(parse_command.size() < 4){
                        std::cerr << "Error: Faltan argumentos. Debe usar: set remember <segundos> <'mensaje'>" << std::endl;
                        exit(1);
                    } else if(parse_command.size() > 4){
                        std::cerr << "Error: Demasiados argumentos. Debe usar: set remember <segundos> <'mensaje'>" << std::endl;
                        exit(1);
                    } else{
                        set_remember( std::stoi(parse_command[2]), parse_command );
                        add_favorite(strdup(command.c_str()));
                        exit(0);
                    }
                } else{
                    std::cerr << "Error: El Comando 'set " << parse_command[1] << "' no se reconoce." << std::endl;
                    exit(1);
                }
                

            }
            else if ( pro < 0 ){
                std::cerr << "Error al crear el proceso hijo\n";
            }
            else{
                continue;
            }
        }
        else if (parse_command[0] == "cd") {
            if (parse_command.size() > 1) {
                exec_cd(strdup(parse_command[1].c_str()));
            } else {
                std::cerr << "cd: falta argumento" << std::endl;
            }
            continue; // Continuar para evitar crear un proceso hijo
        }        
        
        // Detectar comandos con pipes
        std::vector<std::vector<std::string>> pipe_segments;
        std::vector<std::string> current_segment;

        for (int i = 0; i < parse_command.size(); i++) {
            if (parse_command[i] == "|") {
                pipe_segments.push_back(current_segment);
                current_segment.clear();
            } else {
                current_segment.push_back(parse_command[i]);
            }
        }
        pipe_segments.push_back(current_segment); // Agregar el último segmento de comando

        int num_pipes = pipe_segments.size() - 1;
        int pipefds[2 * num_pipes];  // Crear el número necesario de pipes

        // Crear los pipes
        for (int i = 0; i < num_pipes; i++) {
            if (pipe(pipefds + i * 2) == -1) {
                perror("pipe failed");
                return 1;
            }
        }

        // Crear los procesos para cada segmento de comando
        for (int i = 0; i < pipe_segments.size(); i++) {
            pid_t pid = fork();
            if (pid == 0) {
                // Si no es el primer segmento, redirigir stdin al pipe de lectura
                if (i > 0) {
                    if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) == -1) {
                        perror("dup2 failed");
                        exit(1);
                    }
                }
                // Si no es el último segmento, redirigir stdout al pipe de escritura
                if (i < num_pipes) {
                    if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) == -1) {
                        perror("dup2 failed");
                        exit(1);
                    }
                }
                // Cerrar todos los pipes
                for (int j = 0; j < 2 * num_pipes; j++) {
                    close(pipefds[j]);
                }
                // Ejecutar el segmento de comando
                execute_command(pipe_segments[i]);

            } if (pid < 0) {
                perror("fork failed");
            } else {
                int status;
                pid_t pid = wait(&status);
                if(pid == -1){
                    perror("wait failed");
                } else{
                    if(WIFEXITED(status)){
                        if(WEXITSTATUS(status) != 1 && parse_command[0] != "favs"){
                            add_favorite(strdup(command.c_str()));
                        }
                    }
                }
                
            }
        }

        // Cerrar todos los pipes en el proceso padre
        for (int i = 0; i < 2 * num_pipes; i++) {
            close(pipefds[i]);
        }

        // Esperar a que todos los hijos terminen
        for (int i = 0; i < pipe_segments.size(); i++) {
            wait(NULL);
        }
    }
}