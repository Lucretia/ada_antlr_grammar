#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "AdaLexer.hpp"
#include "AdaParser.hpp"

int main(int argc, char *argv[])
{
   ANTLR_USING_NAMESPACE(std);
   // ANTLR_USING_NAMESPACE(antlr);

   if (argc < 2)
   {
      cerr << "Provide Ada input file name as command line argument" << endl;
      return 1;
   }
   string f(argv[1]);
   ifstream s(f);
   
   // Create a scanner that reads from the input stream
   AdaLexer lexer(s);
   lexer.setFilename(f);

   // Create a parser that reads from the scanner
   AdaParser parser(lexer);
   parser.setFilename(f);

   // make an ast factory
   antlr::ASTFactory ast_factory;

   // initialize and put it in the parser...
   parser.initializeASTFactory(ast_factory);
   parser.setASTFactory(&ast_factory);

   // start parsing at the compilationUnit rule
   parser.compilation_unit();

   antlr::RefAST t = parser.getAST();
   if (t)
   {
      const char *print_tree = getenv ("ANTLR_TREE");
      if (print_tree && *print_tree && *print_tree != '0')
      {
         // Print the resulting tree out in LISP notation
         cout << t->toStringList() << endl;
      }
      cout << "Tree was produced" << endl;
   }
   else
      cout << "No tree produced" << endl;

   return 0;
}

