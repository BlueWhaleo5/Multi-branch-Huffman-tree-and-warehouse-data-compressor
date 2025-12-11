/*
 * DSA1 - HK242
 * file : main.cpp
 * SRC template
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 25.02.2024
 */
//g++ -std=c++17 -g -o build\Debug\outDebug.exe -Iinclude -Itest -Itest\unit_test_hash main.cpp test\unit_test_hash\unit_test_hash.cpp test\unit_test.cpp src\Point.cpp src\hash.cpp test\unit_test_hash\test_case\*.cpp
#include "main.hpp"
#include "UNIT_TEST_Huffman.hpp"

string TEST_CASE = "Huffman";
int main(int argc, char *argv[])
{
  cout << "-------------------------------------------------------------"
       << endl;
  cout << GREEN << BOLD << TEST_CASE << " - DSA1 - HK242 - VO TIEN" << endl;
  cout << CYAN << BOLD << "Vo Tien : https://www.facebook.com/Shiba.Vo.Tien" << endl
       << endl;
  if (argc < 1)
  {
    printTestCase();
    return 1;
  }

  handleTestUnit(argc, argv);
  cout << "-------------------------------------------------------------"
       << endl;
}

void handleTestUnit(int argc, char *argv[])
{
  UNIT_TEST_Huffman unitTest;

  if (argc == 1 || (argc == 2 && std::string(argv[1]) == "all"))
  {
    std::cout << GREEN << BOLD << "Running unit_test/unit_test_" << TEST_CASE << RESET << "\n";
    unitTest.runAllTests();
  }
  else if (argc == 2)
  {
    std::cout << GREEN << BOLD << "Running unit_test/unit_test_" << TEST_CASE << RESET << "\n";
    unitTest.runTest(argv[1]);
  }
  else
  {
    printTestCase();
  }
}
