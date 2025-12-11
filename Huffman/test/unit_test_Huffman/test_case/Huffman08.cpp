#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman08()
{
    string name = "Huffman08";
     //! data ------------------------------------
     XArrayList<pair<char, int>> symbolFreqs;
     const string symbols = "ABCDEFGHIJKLMNOP";
     int n = symbols.size();
     for (int i = 0; i < n; ++i) {
         symbolFreqs.add(make_pair(symbols[i], (i + 1) * 3));
     }
     
    HTreeFour tree;
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
     string expect = "A with code 220 decodes as: A\n\
B with code 221 decodes as: B\n\
C with code 222 decodes as: C\n\
D with code 223 decodes as: D\n\
E with code 10 decodes as: E\n\
F with code 11 decodes as: F\n\
G with code 12 decodes as: G\n\
H with code 13 decodes as: H\n\
I with code 20 decodes as: I\n\
J with code 21 decodes as: J\n\
K with code 23 decodes as: K\n\
L with code 30 decodes as: L\n\
M with code 31 decodes as: M\n\
N with code 32 decodes as: N\n\
O with code 33 decodes as: O\n\
P with code 0 decodes as: P\n";
     return printResult(output.str(), expect, name);
}
