#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman11()
{
    string name = "Huffman11";
    //! data ------------------------------------
    InventoryManager manager;
    List1D<InventoryAttribute> attrs;
    manager.addProduct(attrs, "a", 1);

    InvCompressorEight compressor(&manager);
    compressor.buildHuffman();
    //! output ----------------------------------
    stringstream output;

    string encoded = compressor.encodeHuffman(attrs, ":");
    List1D<InventoryAttribute> attributesOutput;
    std::string nameOutput;
    output << "Encoded product: " << encoded << endl;
    output << "decoded product: " << compressor.decodeHuffman(encoded, attributesOutput, nameOutput) << endl;

    //! expect ----------------------------------
    string expect = R"(Encoded product: 66
decoded product: ::
)";

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}