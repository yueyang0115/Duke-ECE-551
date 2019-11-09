#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert((this->left == NULL) && (this->right == NULL));
    theMap.insert(std::pair<unsigned, BitString>(this->sym, b));
  }
  else {
    assert((this->left != NULL) && (this->right != NULL));
    BitString b_left = b.plusZero();
    this->left->buildMap(b_left, theMap);
    BitString b_right = b.plusOne();
    this->right->buildMap(b_right, theMap);
  }
}
