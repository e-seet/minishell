/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:48:32 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/08 16:20:35 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char* value;
} Token;

// Parser structure
typedef struct {
    const char* input;
    int pos;
    Token* current_token;
} Parser;

// Function to create a new token
Token* create_token(TokenType type, const char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    return token;
}

// Function to destroy a token
void destroy_token(Token* token) {
    free(token->value);
    free(token);
}

// Function to get the next token from input string
Token* get_next_token(const char* input, int* pos) {
    while (isspace(input[*pos])) {
        (*pos)++;
    }

    if (input[*pos] == '\0') {
        return create_token(TOKEN_EOF, "");
    }

    // Handle integer tokens
    if (isdigit(input[*pos])) {
        char value[20];
        int i = 0;
        while (isdigit(input[*pos])) {
            value[i++] = input[(*pos)++];
        }
        value[i] = '\0';
        return create_token(TOKEN_INT, value);
    }

    // Handle floating point tokens
    if (input[*pos] == '.') {
        char value[20];
        int i = 0;
        while (isdigit(input[*pos]) || input[*pos] == '.') {
            value[i++] = input[(*pos)++];
        }
        value[i] = '\0';
        return create_token(TOKEN_FLOAT, value);
    }

    // Handle identifier tokens
    if (isalpha(input[*pos])) {
        char value[20];
        int i = 0;
        while (isalnum(input[*pos])) {
            value[i++] = input[(*pos)++];
        }
        value[i] = '\0';
        return create_token(TOKEN_IDENTIFIER, value);
    }

    // Handle operator tokens
    switch (input[*pos]) {
        case '+':
            (*pos)++;
            return create_token(TOKEN_PLUS, "+");
        case '-':
            (*pos)++;
            return create_token(TOKEN_MINUS, "-");
        case '*':
            (*pos)++;
            return create_token(TOKEN_MULTIPLY, "*");
        case '/':
            (*pos)++;
            return create_token(TOKEN_DIVIDE, "/");
        case '(':
            (*pos)++;
            return create_token(TOKEN_LPAREN, "(");
        case ')':
            (*pos)++;
            return create_token(TOKEN_RPAREN, ")");
        default:
            printf("Error: Invalid character '%c'\n", input[*pos]);
            exit(EXIT_FAILURE);
    }
}

// Function to initialize the parser
Parser* init_parser(const char* input) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->input = input;
    parser->pos = 0;
    parser->current_token = NULL;
    return parser;
}

// Function to advance to the next token
void advance(Parser* parser) {
    parser->current_token = get_next_token(parser->input, &(parser->pos));
}

// Function to parse a factor
double factor(Parser* parser);

// Function to parse a term
double term(Parser* parser);

// Function to parse an expression
double expression(Parser* parser);

// Function to parse an integer
double parse_int(const char* value) {
    return atoi(value);
}

// Function to parse a float
double parse_float(const char* value) {
    return atof(value);
}

// Function to parse an identifier
void parse_identifier(const char* value) {
    // For now, just print the identifier
    printf("Identifier: %s\n", value);
}

// Function to parse a factor
double factor(Parser* parser) {
    Token* token = parser->current_token;
    double result;

    if (token->type == TOKEN_INT) {
        result = parse_int(token->value);
        advance(parser);
    } else if (token->type == TOKEN_FLOAT) {
        result = parse_float(token->value);
        advance(parser);
    } else if (token->type == TOKEN_IDENTIFIER) {
        parse_identifier(token->value);
        advance(parser);
    } else if (token->type == TOKEN_LPAREN) {
        advance(parser);
        result = expression(parser);
        if (parser->current_token->type != TOKEN_RPAREN) {
            printf("Error: Expected ')'\n");
            exit(EXIT_FAILURE);
        }
        advance(parser);
    } else {
        printf("Error: Unexpected token type\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

// Function to parse a term
double term(Parser* parser) {
    double result = factor(parser);

    while (parser->current_token->type == TOKEN_MULTIPLY || parser->current_token->type == TOKEN_DIVIDE) {
        Token* token = parser->current_token;
        advance(parser);

        if (token->type == TOKEN_MULTIPLY) {
            result *= factor(parser);
        } else if (token->type == TOKEN_DIVIDE) {
            double divisor = factor(parser);
            if (divisor == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            result /= divisor;
        }
    }

    return result;
}

// Function to parse an expression
double expression(Parser* parser) {
    double result = term(parser);

    while (parser->current_token->type == TOKEN_PLUS || parser->current_token->type == TOKEN_MINUS) {
        Token* token = parser->current_token;
        advance(parser);

        if (token->type == TOKEN_PLUS) {
            result += term(parser);
        } else if (token->type == TOKEN_MINUS) {
            result -= term(parser);
        }
    }

    return result;
}

int main() {
    const char* input = "3 + 4 * (10 - 2)";
    Parser* parser = init_parser(input);
    advance(parser);

    double result = expression(parser);

    printf("Result: %lf\n", result);

    return 0;
}
