#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

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
        std::cout <<  GREEN << username << "@" << hostname << ":" << cwd << "$ " << RESET;
        std::getline(std::cin, command);

        //Parsea el comando ingresado y lo divide en el comando como tal y sus argumentos
        std::istringstream iss(command);
        std::vector<std::string> parse_command;

        while(iss >> word){
            parse_command.push_back(word);
        }
        parse_command_size = parse_command.size();

        if(parse_command.empty()) continue;

        if(parse_command[0] == "exit"){
            break;
        }

        //Ejecuta el comando ingresado mediante 'execvp'
        char* myargs[parse_command_size + 1];
        pid_t cmd_pid = fork();
        if(cmd_pid == 0){
            for(int i=0 ; i<parse_command_size ; i++){
                myargs[i] = strdup(parse_command[i].c_str());   // convierte caracter por caracter un string de c++ a un string de c??
            }
            myargs[parse_command_size] = NULL;
            if(parse_command[0] == "cd"){
            }else{
                if(execvp(myargs[0], myargs) == -1){
                command = "";
                for(int i = 0 ; i < parse_command_size ; i++){
                    if(i!=parse_command_size-1){
                        command += parse_command[i] + " ";
                    }else{
                        command += parse_command[i];
                    }
                }
                std::cerr << command << ":" << "no se encontró la orden" << std::endl;
                exit(4);
                }

            }
            
        }else{
            int status;
            if(parse_command[0] == "cd"){
                exec_cd(strdup(parse_command[1].c_str()));
            }
            waitpid(cmd_pid, &status, 0);
        }
    }
}