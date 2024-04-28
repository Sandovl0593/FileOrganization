#include "scanner.hpp"


class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    string report;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    void advance();
    bool isAtEnd();
    void throwParser(string err);

    bool parseSentence();
    bool parseValue();
    bool parseValues();
    
    bool parseCreateSent();
    bool parseInsertSent();
    bool parseSelectSent();
    bool parseAtributes();

    bool parseUsingIndexSent();
    bool parseTypeIndex();

    bool parseCondition();
    bool parseBetweenCond();
    bool parseFilterCond();
    bool parseBoolOp();

    bool parseDeleteSent();

public:
    Parser(Scanner* scanner);
    void parse();
    string reportParse();
};

void Parser::throwParser(string err) {
    scanner->resetScanner();
    report = err;
}

string Parser::reportParse() { return report; }

// match and consume next token
bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    //if (isAtEnd()) return false;
    return current->type == ttype;
}

void Parser::advance() {
    if (!isAtEnd()) {
        Token* temp =current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Parse error, unrecognised character: " << current->lexema << endl;
            exit(0);
        }
    }
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}

Parser::Parser(Scanner* sc):scanner(sc) {
    previous = current = NULL;
    return;
};


bool Parser::parseValue() {
    if (match(Token::STRING) || match(Token::NUM))
        return true;
        
    throwParser("Parser error - Se espera un valor");
    return false;
}

bool Parser::parseValues() {
    if (!parseValue()) return false;
    while (match(Token::COMMA))
        if (!parseValue()) return false;

    return true;
}

bool Parser::parseFilterCond() {
    if (!match(Token::ID)) {
        throwParser("Parser error - Se espera un campo");
        return false;
    } 
    if (match(Token::LESS) || match(Token::LESSEQUAL) || match(Token::GREATER) || match(Token::GREATEREQUAL)) {
        if (parseValue()) return true;
        return false;
    }
    throwParser("Parser error - Se espera un signo");
    return false;
}


void Parser::parse() {
    // get first token
    current = scanner->nextToken();
    if (check(Token::ERR)) {
        cout << "Error en scanner - caracter invalido" << endl;
        return;
    }
    bool res = parseSentence();

    if (!res) { cout << report << endl;  return; }

    if (!match(Token::END)) {
        cout << "Error: Esperaba fin de input, encontro: " << current<< endl;
        return;
    }

    report = "Ejecución completada";
    if (current) delete current;
}
