#include "../include/lexer.hpp"

Lexer::Lexer(std::string_view contents) : m_contents(contents) {}

std::optional<char> Lexer::peek(size_t offset) const
{
    if (m_index + offset >= m_contents.length())
    {
        return std::nullopt;
    }
    return m_contents[m_index + offset];
}

void Lexer::consume()
{
    m_index++;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens{};
    tokens.reserve(m_contents.length());

    while (peek())
    {
        char c = peek().value();

        if (c == '>' || c == '<' || c == '+' || c == '-')
        {
            int count = 0;

            while (peek() && peek().value() == c)
            {
                count++;
                consume();
            }

            TokenType type;
            if (c == '>')
                type = TokenType::ptr_inc;
            else if (c == '<')
                type = TokenType::ptr_dec;
            else if (c == '+')
                type = TokenType::val_inc;
            else
                type = TokenType::val_dec;

            tokens.push_back(Token{.type = type, .count = count});

            continue;
        }

        if (c == '.')
        {
            tokens.push_back(Token{.type = TokenType::output});
            consume();
            continue;
        }
        if (c == ',')
        {
            tokens.push_back(Token{.type = TokenType::input});
            consume();
            continue;
        }
        if (c == '[')
        {
            tokens.push_back(Token{.type = TokenType::loop_start});
            consume();
            continue;
        }
        if (c == ']')
        {
            tokens.push_back(Token{.type = TokenType::loop_end});
            consume();
            continue;
        }
        consume();
    }
    return tokens;
}