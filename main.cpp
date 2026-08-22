#include <Format.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: minijson <json> <--dump-tokens|--dump-ast>\n";
        return 1;
    }

    Lexer lexer;
    auto token_viewer = lexer.tokenize(argv[1]);
    Parser parser{token_viewer};

    std::string option = argv[2];
    if (option == "--dump-tokens")
    {
        while (!token_viewer.atEnd())
        {
            std::cout << formatToken(token_viewer.getToken()) << '\n';
            token_viewer.skipToken();
        }
    }
    else if (option == "--dump-ast")
    {
        std::cout << formatValue(static_cast<ValueNode *>(parser.parse()))
                  << '\n';
    }
}
