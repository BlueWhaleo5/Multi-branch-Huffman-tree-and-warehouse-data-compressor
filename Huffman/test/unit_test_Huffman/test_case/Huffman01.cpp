#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman01()
{
    string name = "Huffman01";
    //! data ------------------------------------
    stringstream output;

    //! expect ----------------------------------
    string expect = "Code for A: 2\n\
Decoded string: A\n";
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 5));
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
   
    string codeA = codeTable.get('A');
    output << "Code for A: " << codeA << endl;
    
    string decoded = tree.decode(codeA);
    output << "Decoded string: " << decoded << endl;
    //! output ----------------------------------

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
