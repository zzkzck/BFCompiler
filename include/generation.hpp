#pragma once

#include "parser.hpp"
#include <sstream>

class Generator
{
  public:
    explicit Generator(std::vector<Token> tokens, std::unordered_map<size_t, size_t> jump_table);

    [[nodiscard]] std::string generate();

  private:
    [[nodiscard]] std::optional<Token> peek(size_t offset = 0) const;
    void consume();

    size_t m_index = 0;
    const std::vector<Token> m_tokens;
    const std::unordered_map<size_t, size_t> m_jump;
};