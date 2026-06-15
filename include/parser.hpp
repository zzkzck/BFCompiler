#pragma once

#include "./lexer.hpp"
#include <cstddef>
#include <unordered_map>
#include <vector>

class Parser
{
  public:
    Parser(std::vector<Token> tokens);

    std::unordered_map<size_t, size_t> parse();
    std::vector<Token> move_tokens();

  private:
    [[nodiscard]] std::optional<Token> peek(size_t offset = 0) const;
    void consume();

    const std::vector<Token> m_tokens;
    size_t m_index = 0;
};