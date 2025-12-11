#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman07()
{
    string name = "Huffman07";
    //! data ------------------------------------
    InventoryManager manager;
     //! output ----------------------------------
     stringstream output;
  
    List1D<InventoryAttribute> carAttrs;
    carAttrs.add(InventoryAttribute("speed", 88.0));
    manager.addProduct(carAttrs, "Car", 1);
    
    List1D<InventoryAttribute> batteryAttrs;
    batteryAttrs.add(InventoryAttribute("capacity", 250.0));
    batteryAttrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(batteryAttrs, "Battery", 5);
    
    InvCompressor compressor(&manager);
    output<<compressor.productToString(carAttrs,"Car");
    output<<compressor.productToString(batteryAttrs, "Battery");
    compressor.buildHuffman();
   
    
    string encodedCar = compressor.encodeHuffman(carAttrs, "Car");
    string encodedBattery = compressor.encodeHuffman(batteryAttrs, "Battery");
    std::string huffmanCode;
    List1D<InventoryAttribute> attributesOutput;
    std::string nameOutput;
   
    output << "Encoded Car: " << encodedCar << endl;
    output << "Encoded Battery: " << encodedBattery << endl;
    output << "decodeHuffman: " << compressor.decodeHuffman(encodedCar,attributesOutput,nameOutput) << endl;
    output<<encodedCar<<" " <<attributesOutput.toString()<<"  "<< nameOutput<<endl;
    

    //! expect ----------------------------------
    string expect = "Car:(speed: 88.000000)Battery:(capacity: 250.000000), (voltage: 12.000000)Encoded Car: 1213133130333133330101012230033223220122222200\n\
Encoded Battery: 12031111110331332303333233133031323130113323003321023201222222000210333332013213111311231030030223210122222200\n\
decodeHuffman: Car:(speed: 88.000000)\n\
1213133130333133330101012230033223220122222200 [speed: 88.000000]  Car\n";

    //! remove data -----------------------------

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
