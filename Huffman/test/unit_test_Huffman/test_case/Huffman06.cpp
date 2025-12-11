#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman06()
{
    string name = "Huffman06";
    //! data ------------------------------------
    InventoryManager manager;
    List1D<InventoryAttribute> attrs;
    attrs.add(InventoryAttribute("weight", 2.5));
    attrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(attrs, "Gadget", 50);
    
    InvCompressor compressor(&manager);
    compressor.buildHuffman();
     //! output ----------------------------------
     stringstream output;
     
    string encoded = compressor.encodeHuffman(attrs, "Gadget");
    List1D<InventoryAttribute> attributesOutput;
     std::string nameOutput;
    output << "Encoded product: " << encoded << endl;
    output << "decoded product: " <<  compressor.decodeHuffman(encoded,attributesOutput,nameOutput) << endl;

    //! expect ----------------------------------
    string expect = "Encoded product: 313033202322302133333222322233213021200201312111110031020333331330323300323222120311020111111100\n\
decoded product: Gadget:(weight: 2.500000), (voltage: 12.000000)\n";

   

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
