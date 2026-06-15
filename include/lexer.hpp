#pragma once

#include <iostream>

enum class TokenType
{
    ptr_inc,    // >
    ptr_dec,    // <
    val_inc,    // +
    val_dec,    // -
    output,     // .
    input,      // ,
    loop_start, // [
    loop_end,   // ]
};

struct Token
{
    TokenType type;
    int count = 1;
};

class Lexer
{
  public:
    Lexer(std::string_view contents);

    std::vector<Token> tokenize();

  private:
    [[nodiscard]] std::optional<char> peek(size_t offset = 0) const;
    void consume();

    const std::string_view m_contents;
    size_t m_index = 0;
};