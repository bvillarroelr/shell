#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"

void execute_command(const std::vector<std::string>& parse_command) {
    int parse_command_size = parse_command.size();
    char* myargs[parse_command_size + 1];
    
    for(int i = 0 ; i < parse_command_size ; i++) {
        myargs[i] = strdup(parse_command[i].c_str());
    }
    myargs[parse_command_size] = NULL;
    
    if (execvp(myargs[0], myargs) == -1) {
        std::cerr << parse_command[0] << ": no se encontró la orden" << std::endl;
        exit(4);
    }
}

int main() {
    while (true) {
        struct passwd* pw = getpwuid(getuid());
        std::string username = pw->pw_name, command;
        char hostname[1024], cwd[1024];
        getcwd(cwd, sizeof(cwd));
        gethostname(hostname, sizeof(hostname));
        std::cout << GREEN << username << "@" << hostname << ":" << cwd << "$ " << RESET;
        std::getline(std::cin, command);
        
        std::istringstream iss(command);
        std::vector<std::string> parse_command;
        std::string word;
        
        while (iss >> word) {
            parse_command.push_back(word);
        }

        if (parse_command.empty()) continue;
        if (parse_command[0] == "exit") break;
        
        // Detectar comandos con pipes
        std::vector<std::vector<std::string>> commands;
        std::vector<std::string> current_command;

        for (int i = 0; i < parse_command.size(); i++) {
            if (parse_command[i] == "|") {
                commands.push_back(current_command);
                current_command.clear();
            } else {
                current_command.push_back(parse_command[i]);
            }
        }
        commands.push_back(current_command); // Agregar el último comando
        
        int num_pipes = commands.size() - 1;
        int pipefds[2 * num_pipes];  // Crear el número necesario de pipes

        // Crear los pipes
        for (int i = 0; i < num_pipes; i++) {
            if (pipe(pipefds + i * 2) == -1) {
                perror("pipe failed");
                return 1;
            }
        }

        // Crear los procesos para cada comando
        for (int i = 0; i < commands.size(); i++) {
            pid_t pid = fork();
            if (pid == 0) {
                // Hijos
                
                // Si no es el primer comando, redirigir stdin al pipe de lectura
                if (i > 0) {
                    if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) == -1) {
                        perror("dup2 failed");
                        exit(1);
                    }
                }

                // Si no es el último comando, redirigir stdout al pipe de escritura
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

                // Ejecutar el comando
                execute_command(commands[i]);
            }
        }

        // Cerrar todos los pipes en el proceso padre
        for (int i = 0; i < 2 * num_pipes; i++) {
            close(pipefds[i]);
        }

        // Esperar a que todos los hijos terminen
        for (int i = 0; i < commands.size(); i++) {
            wait(NULL);
        }
    }
}