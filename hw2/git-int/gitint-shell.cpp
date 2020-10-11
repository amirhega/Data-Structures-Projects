#include <iostream>
#include "gitint.h"
// Add any necessary headers
#include <iostream>
using namespace std;


const std::string DIVIDER = "-------------------------------------------\n";
const std::string SM_DIV = "---\n";

void print_exception_message(const std::string& what_msg);

int main()
{

    GitInt g;
    string cmd_line;
    bool quit = false;
    const string PROMPT_STARTER = "$ ";

    g.print_menu();

    //while command given is not quit
    while(!quit) {
        cout << PROMPT_STARTER;
        getline(cin, cmd_line);

        //look for errors or just run normally
        try {
            quit = g.process_command(cmd_line);
        } catch(const runtime_error& e) {
            print_exception_message(e.what());
        } catch(const invalid_argument& e) {
            print_exception_message(e.what());
        } 
        
    }


    
    return 0;

} 

void print_exception_message(const std::string& what_msg)
{
  cout << "Error - " << what_msg << endl;
}
