#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << number;
    return sstream.str();
  }
  virtual long evaluate() const { return number; }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression {
  const char * op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(const char * op, Expression * lhs, Expression * rhs) :
      op(op),
      lhs(lhs),
      rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << '(' << lhs->toString() << ' ' << *op << ' ' << rhs->toString() << ')';
    return sstream.str();
  }
  virtual long evaluate() const {
    switch (*op) {
      case '+':
        return lhs->evaluate() + rhs->evaluate();
      case '-':
        return lhs->evaluate() - rhs->evaluate();
      case '*':
        return lhs->evaluate() * rhs->evaluate();
      case '/':
        return lhs->evaluate() / rhs->evaluate();
      default:
        std::cerr << "Impossible op char: " << *op << "\n";
        abort();
    }
  }
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression("+", lhs, rhs) {}
};

class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression("-", lhs, rhs) {}
};

class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression("*", lhs, rhs) {}
};

class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression("/", lhs, rhs) {}
};
