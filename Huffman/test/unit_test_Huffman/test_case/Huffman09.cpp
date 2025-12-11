#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman09()
{
    string name = "Huffman09";
    //! data ------------------------------------
    XArrayList<pair<char, int>> symbolFreqs;
    const string symbols = "AB";
    int n = symbols.size();
    for (int i = 0; i < n; ++i) {
        symbolFreqs.add(make_pair(symbols[i],  (int)symbols[i]));
    }
    
    HTreeSixteen tree;
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
    string expect = "A with code e decodes as: A\n\
B with code f decodes as: B\n";
    return printResult(output.str(), expect, name);
}
