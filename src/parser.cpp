#include "../include/parser.hpp"
#include <iostream>
#include <vector>

Parser::Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

std::optional<Token> Parser::peek(size_t offset) const
{
    if (m_index + offset >= m_tokens.size())
    {
        return std::nullopt;
    }
    return m_tokens[m_index + offset];
}

void Parser::consume()
{
    m_index++;
}

std::unordered_map<size_t, size_t> Parser::parse()
{
    std::unordered_map<size_t, size_t> jump_table;

    std::vector<size_t> bracket_stack;
    bracket_stack.reserve(m_tokens.size() / 4);

    while (peek())
    {
        Token current_token = *peek();

        if (current_token.type == TokenType::loop_start)
        {
            bracket_stack.push_back(m_index);

            consume();
            continue;
        }
        if (current_token.type == TokenType::loop_end)
        {
            if (bracket_stack.empty())
            {
                std::cerr << "Invalid loopping: ']' without any '['" << std::endl;
                exit(EXIT_FAILURE);
            }

            size_t start_index = bracket_stack.back();
            bracket_stack.pop_back();

            jump_table[start_index] = m_index;
            jump_table[m_index] = start_index;

            consume();
            continue;
        }
        consume();
    }

    if (!bracket_stack.empty())
    {
        std::cerr << "Parser Error: Unterminated '[' detected at end of file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return jump_table;
}

std::vector<Token> Parser::move_tokens()
{
    return std::move(m_tokens);
}