#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman02()
{
    string name = "Huffman02";
    //! data ------------------------------------
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 5));
    symbolFreqs.add(make_pair('B', 3));
    symbolFreqs.add(make_pair('C', 7));
    symbolFreqs.add(make_pair('D', 2));
    stringstream output;
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    output << "Generated codes:" << endl;
    for (char ch = 'A'; ch <= 'D'; ++ch) {
        string code = codeTable.get(ch);
        output << "Code for " << ch << ": " << code << endl;
    }

    //! expect ----------------------------------
    string expect = "Generated codes:\n\
Code for A: 0\n\
Code for B: 12\n\
Code for C: 2\n\
Code for D: 11\n";

    //! output ----------------------------------
   

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
