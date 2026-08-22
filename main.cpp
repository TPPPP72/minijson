#include <Format.hpp>
#include <Lexer.hpp>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: minijson <json>\n";
        return 1;
    }

    Lexer lexer;
    auto token_viewer = lexer.tokenize(argv[1]);
    while (!token_viewer.atEnd())
    {
        std::cout << formatToken(token_viewer.getToken()) << '\n';
        token_viewer.skipToken();
    }
}
