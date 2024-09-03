#include <iostream>
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>

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
        std::cout << username << "@" << hostname << ":" << dir << "$ ";
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