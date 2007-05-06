 
#include "AnyScalar.h"
#include "ExpressionParser.h"

#include <iostream>

using namespace stx;

int main(int argc, char *argv[])
{
    std::string args;
    for(int i = 1; i < argc; i++) {
	if (!args.empty()) args += " ";
	args += argv[i];
    }

    std::cout << "string: " << args << "\n";

    const ParseNode* pn;

    try
    {
	pn = parseExpressionString(args);
	
	std::cout << "parsed: " << pn->toString() << "\n";
    }
    catch (ExpressionParserException &e)
    {
	std::cout << "ExpressionParserException: " << e.what() << "\n";
	return 0;
    }


    BasicSymbolTable bst;
    bst.setVariable("x", 42);

    try
    {
	AnyScalar val = pn->evaluate(bst);

	std::cout << "evaluated: " << val << "\n";
    }
    catch (UnknownSymbolException &e)
    {
	std::cout << "UnknownSymbolException: " << e.what() << "\n";
	return 0;
    }

    delete pn;
}
