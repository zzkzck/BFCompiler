#include "../include/generation.hpp"

Generator::Generator(std::vector<Token> tokens, std::unordered_map<size_t, size_t> jump_table)
    : m_tokens(std::move(tokens)), m_jump(std::move(jump_table))
{
}

std::optional<Token> Generator::peek(size_t offset) const
{
    if (m_index + offset >= m_tokens.size())
    {
        return std::nullopt;
    }
    return m_tokens[m_index + offset];
}

void Generator::consume()
{
    m_index++;
}

std::string Generator::generate()
{
    std::stringstream output;

    output << "    .zerofill __DATA,__bss,bf_array,30000,4\n\n";
    output << ".section __TEXT,__text,regular,pure_instructions\n";
    output << "    .global _main\n";
    output << "    .p2align 2\n";
    output << "_main:\n";
    output << "    adrp x19, bf_array@PAGE\n";
    output << "    add x19, x19, bf_array@PAGEOFF\n\n";

    while (peek())
    {
        const Token &token = *peek();

        switch (token.type)
        {
        case TokenType::ptr_inc:
            output << "    add x19, x19, " << token.count << "\n";
            break;
        case TokenType::ptr_dec:
            output << "    sub x19, x19, " << token.count << "\n";
            break;
        case TokenType::val_inc:
            output << "    ldrb w20, [x19]" << " \n";
            output << "    add w20, w20, " << token.count << "\n";
            output << "    strb w20, [x19]" << " \n";
            break;
        case TokenType::val_dec:
            output << "    ldrb w20, [x19]" << "\n";
            output << "    sub w20, w20, " << token.count << "\n";
            output << "    strb w20, [x19]" << "\n";
            break;
        case TokenType::output:
            output << "    mov x0, #1\n";
            output << "    mov x1, x19\n";
            output << "    mov x2, #1\n";
            output << "    mov x16, #0x2000000\n";
            output << "    movk x16, #4\n";
            output << "    svc #0\n";
            break;
        case TokenType::input:
            output << "    mov x0, #0\n";
            output << "    mov x1, x19\n";
            output << "    mov x2, #1\n";
            output << "    mov x16, #0x2000000\n";
            output << "    movk x16, #3\n";
            output << "    svc #0\n";
            break;
        case TokenType::loop_start:
            output << "L_START_" << m_index << ":\n";
            output << "    ldrb w20, [x19]\n";
            output << "    cmp w20, #0\n";
            output << "    b.eq L_END_" << m_jump.at(m_index) << "\n";
            break;
        case TokenType::loop_end:
            output << "    b L_START_" << m_jump.at(m_index) << "\n";
            output << "L_END_" << m_index << ":\n";
            break;
        }
        consume();
    }

    output << "    mov x0, #0\n";
    output << "    mov x16, #0x2000000\n";
    output << "    movk x16, #1\n";
    output << "    svc #0\n";

    return output.str();
}