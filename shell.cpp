#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <vector>
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

int main(){

    while(true){
        struct passwd* pw = getpwuid(getuid());
        std::string username = pw->pw_name;
        //pw_dir, entrega el directorio home del usuario
        std::string dir = pw->pw_dir;
        std::string command, command_index, word;
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

        if(parse_command.empty()) continue;
        
        //Verifica que el comando exista
        bool isCorrect = false;
        for( int i=0 ; i < num_commands ; i++){
            if(parse_command[0] == commands[i]) {
                command_index = i;
                isCorrect = true;
            }   
        }

        //Si el comando no existe devuelve un mensaje de error por la terminal
        if(!isCorrect) {
            command = "";
            int parse_command_size = parse_command.size();
            for(int i = 0 ; i < parse_command_size ; i++){
                if(i!=parse_command_size-1){
                    command += parse_command[i] + " ";
                }else{
                    command += parse_command[i];
                }
                
            }
            std::cerr << command << ":" << "no se encontró la orden" << std::endl;
            continue;
        }

        if(parse_command[0] == "exit"){
            exit(0);
        }else if(parse_command[0] == "ls"){

        }
    }

}

