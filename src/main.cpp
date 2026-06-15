#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/generation.hpp"
#include "../include/lexer.hpp"
#include "../include/parser.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Incorrect Usage." << std::endl;
        std::cerr << "Correct Usage: BF <input.bf>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Can not open the file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();

    std::string contents = contents_stream.str();

    Lexer lexer(contents);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(std::move(tokens));
    std::unordered_map<size_t, size_t> jump_table = parser.parse();
    tokens = parser.move_tokens();

    Generator generator(std::move(tokens), std::move(jump_table));

    std::ofstream output("out.s");
    output << generator.generate();
    output.close();

    std::cout << "Compiling out.s to native Apple Silicon binary..." << std::endl;

    int compile_status =
        system("clang -arch arm64 -isysroot $(xcrun --show-sdk-path) out.s -o brainfuck_run");

    if (compile_status == 0)
    {
        std::cout << "🎉 Compilation Successful! Created executable: ./brainfuck_run" << std::endl;
    }
    else
    {
        std::cerr << "❌ Clang compilation failed!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}