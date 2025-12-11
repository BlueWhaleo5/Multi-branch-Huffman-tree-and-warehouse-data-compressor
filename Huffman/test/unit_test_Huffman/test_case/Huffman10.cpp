#include "../unit_test_Huffman.hpp"

bool UNIT_TEST_Huffman::Huffman10()
{
    string name = "Huffman10";
      //! data ------------------------------------
    InventoryManager manager;
    stringstream output;

    // Car
    List1D<InventoryAttribute> carAttrs;
    carAttrs.add(InventoryAttribute("speed", 123.456));
    carAttrs.add(InventoryAttribute("fuel", 7.89));
    carAttrs.add(InventoryAttribute("engine_temp", 98.76));
    carAttrs.add(InventoryAttribute("tire_pressure", 32.5));
    manager.addProduct(carAttrs, "Car", 2);

    // Battery
    List1D<InventoryAttribute> batteryAttrs;
    batteryAttrs.add(InventoryAttribute("capacity", 250.75));
    batteryAttrs.add(InventoryAttribute("voltage", 12.45));
    batteryAttrs.add(InventoryAttribute("life", 3.5));
    batteryAttrs.add(InventoryAttribute("weight", 5.8));
    manager.addProduct(batteryAttrs, "Battery", 3);

    // Fan
    List1D<InventoryAttribute> fanAttrs;
    fanAttrs.add(InventoryAttribute("rpm", 1230.5));
    fanAttrs.add(InventoryAttribute("power", 45.75));
    fanAttrs.add(InventoryAttribute("noise", 23.33));
    fanAttrs.add(InventoryAttribute("speed_levels", 5.0));
    manager.addProduct(fanAttrs, "Fan", 5);

    // Laptop
    List1D<InventoryAttribute> laptopAttrs;
    laptopAttrs.add(InventoryAttribute("ram", 16.0));
    laptopAttrs.add(InventoryAttribute("storage", 512.5));
    laptopAttrs.add(InventoryAttribute("weight", 1.25));
    laptopAttrs.add(InventoryAttribute("cpu", 2.7));
    laptopAttrs.add(InventoryAttribute("gpu", 6.5));
    manager.addProduct(laptopAttrs, "Laptop", 4);

    // Air Conditioner
    List1D<InventoryAttribute> airconAttrs;
    airconAttrs.add(InventoryAttribute("btu", 12000.0));
    airconAttrs.add(InventoryAttribute("power", 850.5));
    airconAttrs.add(InventoryAttribute("efficiency", 3.75));
    airconAttrs.add(InventoryAttribute("noise", 32.1));
    airconAttrs.add(InventoryAttribute("filter", 2.0));
    manager.addProduct(airconAttrs, "Aircon", 3);

    // Refrigerator
    List1D<InventoryAttribute> fridgeAttrs;
    fridgeAttrs.add(InventoryAttribute("volume", 300.0));
    fridgeAttrs.add(InventoryAttribute("power", 150.0));
    fridgeAttrs.add(InventoryAttribute("noise", 28.0));
    fridgeAttrs.add(InventoryAttribute("temp_range", -18.0));
    manager.addProduct(fridgeAttrs, "Fridge", 2);

    // Output readable format
    InvCompressorTwelve compressor(&manager);
    output << compressor.productToString(carAttrs, "Car") << endl;
    output << compressor.productToString(batteryAttrs, "Battery") << endl;
    output << compressor.productToString(fanAttrs, "Fan") << endl;
    output << compressor.productToString(laptopAttrs, "Laptop") << endl;
    output << compressor.productToString(airconAttrs, "Aircon") << endl;
    output << compressor.productToString(fridgeAttrs, "Fridge") << endl;

    // Build Huffman Tree
    compressor.buildHuffman();

    // Encode
    string encodedCar = compressor.encodeHuffman(carAttrs, "Car");
    string encodedBattery = compressor.encodeHuffman(batteryAttrs, "Battery");
    string encodedFan = compressor.encodeHuffman(fanAttrs, "Fan");
    string encodedLaptop = compressor.encodeHuffman(laptopAttrs, "Laptop");
    string encodedAircon = compressor.encodeHuffman(airconAttrs, "Aircon");
    string encodedFridge = compressor.encodeHuffman(fridgeAttrs, "Fridge");

    output << "Encoded Car: " << encodedCar << endl;
    output << "Encoded Battery: " << encodedBattery << endl;
    output << "Encoded Fan: " << encodedFan << endl;
    output << "Encoded Laptop: " << encodedLaptop << endl;
    output << "Encoded Aircon: " << encodedAircon << endl;
    output << "Encoded Fridge: " << encodedFridge << endl;

    // Decode test: Fan
    string nameOutput;
    List1D<InventoryAttribute> attributesOutput;
    output << "decodeHuffman: " << compressor.decodeHuffman(encodedFan, attributesOutput, nameOutput) << endl;
    output << "decodeHuffman: " << compressor.decodeHuffman(encodedBattery, attributesOutput, nameOutput) << endl;
    output << "decodeHuffman: " << compressor.decodeHuffman(encodedAircon, attributesOutput, nameOutput) << endl;
    output << "decodeHuffman: " << compressor.decodeHuffman(encodedLaptop, attributesOutput, nameOutput) << endl;
    output << attributesOutput.toString()  << endl;


    string expect = "Car:(speed: 123.456000), (fuel: 7.890000), (engine_temp: 98.760000), (tire_pressure: 32.500000)\n\
Battery:(capacity: 250.750000), (voltage: 12.450000), (life: 3.500000), (weight: 5.800000)\n\
Fan:(rpm: 1230.500000), (power: 45.750000), (noise: 23.330000), (speed_levels: 5.000000)\n\
Laptop:(ram: 16.000000), (storage: 512.500000), (weight: 1.250000), (cpu: 2.700000), (gpu: 6.500000)\n\
Aircon:(btu: 12000.000000), (power: 850.500000), (efficiency: 3.750000), (noise: 32.100000), (filter: 2.000000)\n\
Fridge:(volume: 300.000000), (power: 150.000000), (noise: 28.000000), (temp_range: -18.000000)\n\
Encoded Car: 04a5ab63a2aa770b68a3a7a450a192bbb4283949a79b689759807bbbb42837a1a0a9a1793a8795aa68079859792bbbb4283a8a9ab793aaab7a2a29aab768a4a751bbbbb4\n\
Encoded Battery: 03a5a8a87ab916399a5aaa599a9a89168a71b5971bbbb428390a69ba8a5a0768a3a750a1bbbb42839ba994768a451bbbbb4283967a9a009a8681598bbbbb4\n\
Encoded Fan: 08a5a163abaa9568a3a7a4b51bbbbb4283aaa6967ab680a15971bbbb4283a1a6a9a2768a7a45a4a4bbbb4283a2aa770b939b79079ba26815bbbbbb4\n\
Encoded Laptop: 05a5aaa8a6aa63aba59568a3925bbbbbb4283a2a8a6aba5a07681a3a751bbbbb4283967a9a009a868a35a71bbbb428399aa9a68a7597bbbbb4283a0aa9a689251bbbbb4\n\
Encoded Aircon: 02a9ab99a6a16306a89a68a3a7bbb5bbbbbb4283aaa6967ab68981b51bbbbb428379494a999a97a1999168a45971bbbb4283a1a6a9a2768a4a75a3bbbbb428394a99ba87ab68a75bbbbbb4\n\
Encoded Fridge: 08aba90ba076390a69b9a95768a4bb5bbbbbb4283aaa6967ab68a31b5bbbbbb4283a1a6a9a2768a7985bbbbbb4283a8795aa93aba5a1a076801a3985bbbbbb4\n\
decodeHuffman: Fan:(rpm: 1230.500000), (power: 45.750000), (noise: 23.330000), (speed_levels: 5.000000)\n\
decodeHuffman: Battery:(capacity: 250.750000), (voltage: 12.450000), (life: 3.500000), (weight: 5.800000)\n\
decodeHuffman: Aircon:(btu: 12000.000000), (power: 850.500000), (efficiency: 3.750000), (noise: 32.100000), (filter: 2.000000)\n\
decodeHuffman: Laptop:(ram: 16.000000), (storage: 512.500000), (weight: 1.250000), (cpu: 2.700000), (gpu: 6.500000)\n\
[ram: 16.000000, storage: 512.500000, weight: 1.250000, cpu: 2.700000, gpu: 6.500000]\n"; 

    return printResult(output.str(), expect, name);
}
