#include "parser.hpp"

// ---------------------------------------------------

int main(int argc, const char* argv[]) {

    if (argc != 2) {
        cout << "Incorrect number of arguments" << endl;
        exit(1);
    }

    Scanner scanner(argv[1]);

    Token* tk = scanner.nextToken();
    while (tk->type != Token::END) {
      cout << "next token " << tk << endl;
      delete tk;
      tk =  scanner.nextToken();
    }
    cout << "last token " << tk << endl;
    delete tk;

    Parser parser(&scanner);
    parser.parse();

    cout << parser.reportParse() << endl;

}