#ifndef UNIT_TEST_Huffman_HPP
#define UNIT_TEST_Huffman_HPP

#include"list/DLinkedList.h"
#include"list/XArrayList.h"
#include "app/inventory_compressor.h"
#include "unit_test.hpp"

// Macro to simplify test registration
#define REGISTER_TEST(func) registerTest(#func, [this]() { return func(); })

class UNIT_TEST_Huffman : public UNIT_TEST
{
public:
  UNIT_TEST_Huffman()
  {
    REGISTER_TEST(Huffman01);

    REGISTER_TEST(Huffman02);

    REGISTER_TEST(Huffman03);

    REGISTER_TEST(Huffman04);

    REGISTER_TEST(Huffman05);

    REGISTER_TEST(Huffman06);

    REGISTER_TEST(Huffman07);

    REGISTER_TEST(Huffman08);

    REGISTER_TEST(Huffman09);

    REGISTER_TEST(Huffman10);

    REGISTER_TEST(Huffman11);

    REGISTER_TEST(Huffman12);

    REGISTER_TEST(Huffman13);

    REGISTER_TEST(Huffman14);

    REGISTER_TEST(Huffman15);
  }

private:
  bool Huffman01();

  bool Huffman02();

  bool Huffman03();

  bool Huffman04();

  bool Huffman05();

  bool Huffman06();

  bool Huffman07();

  bool Huffman08();

  bool Huffman09();

  bool Huffman10();

  bool Huffman11();

  bool Huffman12();

  bool Huffman13();

  bool Huffman14();

  bool Huffman15();
};
int charHashFunc(char& key, int tablesize);
typedef HuffmanTree<2> HTreeTow;
typedef HuffmanTree<3> HTree;
typedef HuffmanTree<4> HTreeFour;
typedef HuffmanTree<5> HTreeFive;
typedef HuffmanTree<6>  HTreeSix;
typedef HuffmanTree<7>  HTreeSeven;
typedef HuffmanTree<8>  HTreeEight;
typedef HuffmanTree<9>  HTreeNine;
typedef HuffmanTree<10> HTreeTen;
typedef HuffmanTree<11> HTreeEleven;
typedef HuffmanTree<12> HTreeTwelve;
typedef HuffmanTree<13> HTreeThirteen;
typedef HuffmanTree<14> HTreeFourteen;
typedef HuffmanTree<15> HTreeFifteen;
typedef HuffmanTree<16> HTreeSixteen;
typedef HTree::HuffmanNode HNode;

typedef InventoryCompressor<2>  InvCompressorTwo;
typedef InventoryCompressor<3>  InvCompressorThree;
typedef InventoryCompressor<4> InvCompressor;
typedef InventoryCompressor<5>  InvCompressorFive;
typedef InventoryCompressor<6>  InvCompressorSix;
typedef InventoryCompressor<7>  InvCompressorSeven;
typedef InventoryCompressor<8>  InvCompressorEight;
typedef InventoryCompressor<9>  InvCompressorNine;
typedef InventoryCompressor<10> InvCompressorTen;
typedef InventoryCompressor<11> InvCompressorEleven;
typedef InventoryCompressor<12> InvCompressorTwelve;
typedef InventoryCompressor<13> InvCompressorThirteen;
typedef InventoryCompressor<14> InvCompressorFourteen;
typedef InventoryCompressor<15> InvCompressorFifteen;
typedef InventoryCompressor<16> InvCompressorSixteen;

#endif // UNIT_TEST_Huffman_HPP
