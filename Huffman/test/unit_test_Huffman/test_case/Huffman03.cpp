#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman03()
{
    string name = "Huffman03";
    //! data ------------------------------------
    stringstream output;

    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('X', 4));
    symbolFreqs.add(make_pair('Y', 6));
    symbolFreqs.add(make_pair('Z', 2));
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    string codeZ = codeTable.get('Z');
    output << "Code for Z: " << codeZ << endl;
    
    string decoded = tree.decode(codeZ);
    output << "Decoded string: " << decoded << endl;
    string result = "!";

    //! output ----------------------------------
   
    //! remove data -----------------------------
    string expect = "Code for Z: 0\n\
Decoded string: Z\n";
    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
