#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman05()
{
    string name = "Huffman05";
    //! data ------------------------------------
    XArrayList<pair<char, int>> symbolFreqs;
    const string symbols = "ABCDEFGHIJ";
    int n = symbols.size();
    for (int i = 0; i < n; ++i) {
        symbolFreqs.add(make_pair(symbols[i], (i + 1) * 2));
    }
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
     //! output ----------------------------------
     stringstream output;

    for (char ch : symbols) {
        string code = codeTable.get(ch);
        string decoded = tree.decode(code);
        output << ch << " with code " << code << " decodes as: " << decoded << endl;
    }
    string expect = "A with code 011 decodes as: A\n\
B with code 012 decodes as: B\n\
C with code 00 decodes as: C\n\
D with code 02 decodes as: D\n\
E with code 10 decodes as: E\n\
F with code 11 decodes as: F\n\
G with code 12 decodes as: G\n\
H with code 20 decodes as: H\n\
I with code 21 decodes as: I\n\
J with code 22 decodes as: J\n";

    //! expect ----------------------------------


   

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
