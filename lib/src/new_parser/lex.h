/*
 Copyright (c) 2014, Nicola Gigante
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * The names of its contributors may not be used to endorse or promote
 products derived from this software without specific prior written
 permission.
 */

#ifndef LEX_H_
#define LEX_H_

#include <istream>
#include <ostream>
#include <cassert>
#include <cctype>

#include <optional.hpp>

namespace LTL {
namespace detail {

using std::experimental::optional;
using std::experimental::make_optional;
using std::experimental::nullopt;

struct Token {
  enum Type {
    // Punctuation and atoms
    Atom = 0,
    LParen,
    RParen,

    // Binary operators and connectives
    And,
    Or,
    Implies,
    Iff,
    Until,
    Release,
    Since,
    Triggered,

    // Unary operators and connectives
    Not,
    Tomorrow,
    Always,
    Eventually,
    Yesterday,
    Past,
    Historically,
  };

  static const int NumberOfTokenTypes = Historically + 1;
  static const int FirstBinaryOp = And;
  static const int LastBinaryOp = Triggered;
  static const int FirstUnaryOp = Not;
  static const int LastUnaryOp = Historically;


  Token(Type t) : type(t) {}
  Token(std::string a) : type(Type::Atom), atom(std::move(a)) {}

  Type type;
  optional<std::string> atom = nullopt;
};

class Lexer
{
public:
  explicit Lexer(std::istream &stream) : _stream(stream) {}
  optional<Token> get() { return _token = _lex(); }
  optional<Token> peek() const { return _token; }

private:
  optional<Token> _lex();

  optional<Token> _token = nullopt;
  std::istream &_stream;
};

std::ostream &operator<<(std::ostream &s, Token const &t);
}

using detail::Lexer;
using detail::Token;
}

#endif // LEX_H_
