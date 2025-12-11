#include"unit_test_Huffman.hpp"
int charHashFunc(char& key, int tablesize) {
    return (int)key % tablesize;
}