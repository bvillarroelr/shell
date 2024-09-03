#include <iostream>
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
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

const int num_commands = 3;
const std::string commands[num_commands] = {"ls", "cd", "wc"};

int main(){

    while(true){
        struct passwd* pw = getpwuid(getuid());
        std::string username = pw->pw_name;
        //pw_dir, entrega el directorio home del usuario
        std::string dir = pw->pw_dir;
        std::string command;
        char hostname[1024];
        gethostname(hostname, sizeof(hostname));
        std::cout <<  GREEN << username << "@" << hostname << ":" << dir << "$ " << RESET;
        std::getline(std::cin, command);

        int command_large = command.size();
        for(int i=0 ; i < command_large ; i++){
            if(!isspace(command[i])){
                command = command.substr(i);
                break;
            }else if(i == command_large - 1){
                command.clear();
            }
        }

        if(command == "") continue;

        bool isCorrect = false;
        for( int i=0 ; i < num_commands ; i++){
            if(command == commands[i]) {
                isCorrect = true;
            }   
        }

        if(!isCorrect) {
            std::cerr << command << ":" << "no se encontró la orden" << std::endl;
            continue;
        }
    }

}