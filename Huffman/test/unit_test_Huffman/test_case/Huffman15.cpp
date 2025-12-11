#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman15()
{
    string name = "Huffman15";
    stringstream output;
    //! data ------------------------------------

    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('B', 0));

    HTreeTow tree;
    tree.build(symbolFreqs);

    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    output << codeTable.remove('\0');
    output << codeTable.toString();
    //! remove data -----------------------------

    //! expect ----------------------------------
    string expect = R"(1==================================================
capacity:   10
size:       1
0   : 
1   : 
2   : 
3   : 
4   : 
5   : 
6   :  (B,0)
7   : 
8   : 
9   : 
==================================================
)";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}