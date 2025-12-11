#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman12()
{
    string name = "Huffman12";
    //! data ------------------------------------
    stringstream output;

    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('M', 3));
    symbolFreqs.add(make_pair('N', 5));

    HTree tree;
    tree.build(symbolFreqs);

    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    string decoded = tree.decode("0");
    output << "Decoded string from invalid code: " << decoded << endl;
    //! expect ----------------------------------
    string expect = "Decoded string from invalid code: \\x00\n";

    //! output ----------------------------------

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}