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

const int num_commands = 4;
const std::string commands[num_commands] = {"ls", "cd", "wc", "exit"};
const std::string commands_args[num_commands] = {{}, {}, {}, {}};

void exec_cd( char* arg) {
    // hay que usar la funcion de c chdir(), que hace exactamente lo que hace cd. Retorna 0 si se hizo bien y -1 si hubo un error
    if (chdir(arg) != 0) {
        perror("chdir failed");
    }
    else {
        chdir(arg);
    }
}

int main(){

    while(true){
        struct passwd* pw = getpwuid(getuid());
        //pw_dir, entrega el directorio home del usuario
        std::string username = pw->pw_name, dir = pw->pw_dir, command, word;
        int command_index, parse_command_size;
        char hostname[1024];
        gethostname(hostname, sizeof(hostname));
        std::cout <<  GREEN << username << "@" << hostname << ":" << dir << "$ " << RESET;
        std::getline(std::cin, command);

        //Parsea el comando ingresado y lo divide en el comando como tal y sus argumentos
        std::istringstream iss(command);
        std::vector<std::string> parse_command;

        while(iss >> word){
            parse_command.push_back(word);
        }
        parse_command_size = parse_command.size();

        if(parse_command.empty()) continue;
        
        //Verifica que el comando exista
        // bool isCorrect = false;
        // for( int i=0 ; i < num_commands ; i++){
        //     if(parse_command[0] == commands[i]) {
        //         command_index = i;
        //         isCorrect = true;
        //     }   
        // }

        // //Si el comando no existe devuelve un mensaje de error por la terminal
        // if(!isCorrect) {
        //     command = "";
        //     for(int i = 0 ; i < parse_command_size ; i++){
        //         if(i!=parse_command_size-1){
        //             command += parse_command[i] + " ";
        //         }else{
        //             command += parse_command[i];
        //         }
                
        //     }
        //     std::cerr << command << ":" << "no se encontró la orden" << std::endl;
        //     continue;
        // }

        //Ejecuta el comando ingresado mediante 'execvp'
        char* myargs[parse_command_size + 1];
        pid_t cmd_pid = fork();
        if(cmd_pid == 0){
            for(int i=0 ; i<parse_command_size ; i++){
                myargs[i] = strdup(parse_command[i].c_str());   // convierte caracter por caracter un string de c++ a un string de c??
            }
            myargs[parse_command_size] = NULL;
            execvp(myargs[0], myargs);
        }else{
            wait(NULL);
        }

        if(parse_command[0] == "exit"){
            exit(0);
        }else if(parse_command[0] == commands[1]){ // commands [1] == "cd"
            // exec_cd() // hay que pasarle como parámetro el argumento del cd: cd .. por ejemplo, pero aun no se donde se almacenan
        }

        
   /*     else if(parse_command[0] == "ls"){

        }
    */
    }

}

