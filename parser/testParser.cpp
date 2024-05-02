#include "parser.hpp"

// ---------------------------------------------------

int main(int argc, const char* argv[]) {

    // string argc;
    // getline(cin, argc);
    if (argc != 2) {
      cout << "Incorrect number of arguments" << endl;
      exit(1);
    } 

    Scanner scanner(argv[1]);
    
    Parser parser(&scanner);
    parser.parse();
    
}