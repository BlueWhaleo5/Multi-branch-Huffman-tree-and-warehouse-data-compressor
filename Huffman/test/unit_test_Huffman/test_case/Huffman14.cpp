#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman14()
{
    string name = "Huffman14";
    stringstream output;
    //! data ------------------------------------

    XArrayList<pair<char, int>> symbolFreqs;
    HTreeTow tree;
    tree.build(symbolFreqs);

    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    output << codeTable.toString();
    output << tree.decode("");
    //! remove data -----------------------------

    //! expect ----------------------------------
    string expect = R"(==================================================
capacity:   10
size:       0
0   : 
1   : 
2   : 
3   : 
4   : 
5   : 
6   : 
7   : 
8   : 
9   : 
==================================================
\x00)";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}