#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman13()
{
    string name = "Huffman13";
    //! data ------------------------------------
    InventoryManager manager;
    List1D<InventoryAttribute> attrs;
    attrs.add(InventoryAttribute("weight", 2.5));
    attrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(attrs, "Gadget", 50);

    InvCompressor compressor(&manager);
    //! output ----------------------------------
    stringstream output;

    string encoded = "";
    try
    {
        encoded = compressor.encodeHuffman(attrs, "Gadget");
        output << "Encoded Gadget: " << encoded << endl;
    }
    catch (const std::exception &e)
    {
        output << "Encoding Gadget failed: " << e.what() << endl;
    }
    List1D<InventoryAttribute> attributesOutput;
    std::string nameOutput;
    output << "Encoded product: " << encoded << endl;
    output << "decoded product: " << compressor.decodeHuffman(encoded, attributesOutput, nameOutput) << endl;

    //! expect ----------------------------------
    string expect = "Encoding Gadget failed: key (G) is not found\n\
Encoded product: \n\
decoded product: \\x00\n";

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}