#ifndef INVENTORY_COMPRESSOR_H
#define INVENTORY_COMPRESSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include "inventory.h"
#include "hash/xMap.h"
#include "heap/Heap.h"
#include "list/XArrayList.h"
#include "list/DLinkedList.h"

template<int treeOrder>
class HuffmanTree {
public:
    struct HuffmanNode {
        char ch;
        int freq;
        int order;      // Added to track leaf order
        XArrayList<HuffmanNode*> children;

        static int huffmanCompare(HuffmanNode*& nodeA, HuffmanNode*& nodeB) {
            if (nodeA->freq != nodeB->freq)
                return (nodeA->freq < nodeB->freq) ? -1 : 1;

            if (nodeA->order != nodeB->order)
                return (nodeA->order < nodeB->order) ? -1 : 1;

            return 0;
        }
        
        HuffmanNode(char ch, int freq)
            : ch(ch), freq(freq), order(1), children() {}

        HuffmanNode(int freq, const XArrayList<HuffmanNode*>& childrens)
            : ch('\0'), freq(freq), order(1), children(childrens) {}

        ~HuffmanNode(){}

    };

    HuffmanTree();
    ~HuffmanTree();
    
    void generateCodes(xMap<char, std::string>& table);
    std::string decode(const std::string& huffmanCode);
    void build(XArrayList<pair<char, int>>& symbolsFreqs);

private:
    HuffmanNode* root;
    void traverse(HuffmanNode *node, std::string code, xMap<char, std::string> &table);
};

template<int treeOrder>
class InventoryCompressor {
public:
    InventoryCompressor(InventoryManager* manager);
    ~InventoryCompressor();

    void buildHuffman();
    void printHuffmanTable();
    std::string productToString(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string encodeHuffman(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string decodeHuffman(const std::string& huffmanCode, List1D<InventoryAttribute>& attributesOutput, std::string& nameOutput);

private:
    static int charHashFunc(char &key, int tableSize) {
        return static_cast<int>(key) % tableSize;
    }
    xMap<char, std::string>* huffmanTable;
    InventoryManager* invManager;
    HuffmanTree<treeOrder>* tree;
};


#endif // INVENTORY_COMPRESSOR_H

template <int treeOrder>
HuffmanTree<treeOrder>::HuffmanTree() {
    root = nullptr;
}

template <int treeOrder>
HuffmanTree<treeOrder>::~HuffmanTree() {
    if (root != nullptr) {
        XArrayList<HuffmanNode*> toDelete;
        toDelete.add(root);

        while (!toDelete.empty()) {
            HuffmanNode* node = toDelete.removeAt(0);

            for (int i = 0; i < node->children.size(); ++i) {
                toDelete.add(node->children.get(i));
            }

            delete node;
        }
    }
}

template <int treeOrder>
void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>>& symbolsFreqs) {
    if (root) {
        XArrayList<HuffmanNode*> queue;
        queue.add(root);

        while (!queue.empty()) {
            HuffmanNode* current = queue.removeAt(queue.size() - 1);
            
            for (int j = 0; j < current->children.size(); ++j) {
                queue.add(current->children.get(j));
            }

            delete current;
        }
        root = nullptr;
    }

    if (symbolsFreqs.size() == 0) return;

    Heap<HuffmanNode *> heap(HuffmanNode::huffmanCompare);
    int count = 0;

    for (int i = 0; i < symbolsFreqs.size(); ++i) {
        HuffmanNode *leaf = new HuffmanNode(symbolsFreqs.get(i).first, symbolsFreqs.get(i).second);
        leaf->order = count++;
        heap.push(leaf);
    }

    int padNeeded = (heap.size() - 1) % (treeOrder - 1);
    if (padNeeded != 0) {
        padNeeded = (treeOrder - 1) - padNeeded;
        for (int i = 0; i < padNeeded; i++) {
            HuffmanNode *padNode = new HuffmanNode('\0', 0);
            padNode->order = count++;
            heap.push(padNode);
        }
    }

    while (heap.size() >= treeOrder) {
        int combinedFrequency = 0;
        XArrayList<HuffmanNode*> childCollection;
        
        for (int nodeIndex = 0; nodeIndex < treeOrder; nodeIndex++) {
            if (heap.empty()) break;

            HuffmanNode* extractedNode = heap.pop();
            
            combinedFrequency += extractedNode->freq;     
            childCollection.add(extractedNode);
        }
        
        HuffmanNode* internalNode = new HuffmanNode(combinedFrequency, childCollection);
        internalNode->order = count++;
        heap.push(internalNode);
    }

    if (heap.size() > 1) {
        XArrayList<HuffmanNode*> mergeNodes;
        int totalWeight = 0;
        
        while (heap.size() > 0) {
            HuffmanNode* nextNode = heap.pop();
            totalWeight += nextNode->freq;
            mergeNodes.add(nextNode);
        }
        
        HuffmanNode* rootNode = new HuffmanNode(totalWeight, mergeNodes);
        rootNode->order = count++;
        root = rootNode;

    } else if (heap.size() == 1) {
        root = heap.pop();
    } else {
        root = nullptr;
    }
}

template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table) {
    if (root == nullptr) return;
    traverse(root, "", table);
}

template <int treeOrder>
void HuffmanTree<treeOrder>::traverse(HuffmanNode *node, std::string code, xMap<char, std::string> &table) {
    if (!node) return;

    if (node->children.empty()) {
        if (node->ch != '\0') {
            table.put(node->ch, code);
            return;
        }
    }
    
    for (int i = 0; i < node->children.size(); ++i) {
        char next = (i < 10) ? ('0' + i) : ('a' + (i - 10));
        traverse(node->children.get(i), code + next, table);
    }
}

template <int treeOrder>
std::string HuffmanTree<treeOrder>::decode(const std::string &huffmanCode)
{
    if (root == nullptr || huffmanCode.empty()) return "\\x00";

    std::string result;
    HuffmanNode *node = root;

    for (size_t i = 0; i < huffmanCode.length(); ++i) {
        char c = huffmanCode[i];

        if (node == nullptr) return "\\x00";

        int idx = (c >= '0' && c <= '9') ? (c - '0') :
                  (c >= 'a' && c <= 'f') ? (c - 'a' + 10) : -1;

        if (idx < 0 || idx >= treeOrder || idx >= node->children.size()) return "\\x00";
        
        node = node->children.get(idx);
        
        if (node->children.empty()) {
            if (node->ch == '\0') return "\\x00";
            result.push_back(node->ch);
            node = root;
        }
    }
    return result;
}

template <int treeOrder>
InventoryCompressor<treeOrder>::InventoryCompressor(InventoryManager* manager) {
    this->huffmanTable = new xMap<char, string>(&charHashFunc);
    this->tree = new HuffmanTree<treeOrder>();
    this->invManager = manager;
}

template <int treeOrder>
InventoryCompressor<treeOrder>::~InventoryCompressor()
{
    delete tree;
    delete huffmanTable;
}

template <int treeOrder>
void InventoryCompressor<treeOrder>::buildHuffman()
{
    xMap<char, int> freqMap(&charHashFunc);

    for (int i = 0; i < invManager->size(); ++i) {
        std::string str = productToString(invManager->getProductAttributes(i), invManager->getProductName(i));
        
        for (char chars : str) {
            int count = freqMap.containsKey(chars) ? freqMap.get(chars) + 1 : 1;
            freqMap.put(chars, count);
        }
    }

    DLinkedList<char> keys = freqMap.keys();
    XArrayList<pair<char, int>> freqList;

    for (int i = 0; i < keys.size(); ++i) {
        char c = keys.get(i);
        int freq = freqMap.get(c);
        freqList.add({c, freq});
    }

    for (int i = 1; i < freqList.size(); i++) {
        pair<char, int> current = freqList.get(i);
        int j = i - 1;
        
        while (j >= 0 && freqList.get(j).first > current.first) {
            j--;
        }
        
        if (j < i - 1) {
            freqList.add(j + 1, current);
            freqList.removeAt(i + 1);
        }
    }

    HuffmanTree<treeOrder>* oldTree = this->tree;
    this->tree = nullptr; 
    this->tree = new HuffmanTree<treeOrder>();
    
    if (oldTree != nullptr) {
        delete oldTree;
    }

    this->tree->build(freqList);
    xMap<char, string>* prevTable = this->huffmanTable;
    this->huffmanTable = nullptr;
    
    this->huffmanTable = new xMap<char, string>(&charHashFunc);
    this->tree->generateCodes(*this->huffmanTable);
    
    if (prevTable != nullptr) {
        delete prevTable;
    }
}

template <int treeOrder>
void InventoryCompressor<treeOrder>::printHuffmanTable() {
    DLinkedList<char> keys = huffmanTable->keys();
    for (char chars : keys) {
        std::cout << "'" << chars << "' : " << huffmanTable->get(chars) << std::endl;
    }
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::productToString(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    std::ostringstream result;
    result << name << ":";

    int count = attributes.size();
    int index = 0;
    while (index < count) {
        const InventoryAttribute& attr = attributes.get(index);
        result << "(" << attr.name << ": " << std::fixed << std::setprecision(6) << attr.value << ")";
        if (index < count - 1) { result << ", ";}
        ++index;
    }

    return result.str();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    std::string str = productToString(attributes, name);
    std::string code;
    for (char c : str) {
        if (!huffmanTable->containsKey(c)) {
            throw std::runtime_error("key (" + std::string(1, c) + ") is not found");
        }
        code += huffmanTable->get(c);
    }
    return code;
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, List1D<InventoryAttribute> &attributesOutput, std::string &nameOutput)
{   
    attributesOutput = List1D<InventoryAttribute>();
    nameOutput = "";

    std::string decoded = tree->decode(huffmanCode);
    if (decoded.find("\\x00") != std::string::npos)  return "\\x00";

    size_t nameDelimiter = decoded.find(':');
    if (nameDelimiter == std::string::npos) return "\\x00";

    nameOutput = decoded.substr(0, nameDelimiter);
    if (nameOutput.empty()) return "";

    size_t firstAttrPos = decoded.find('(', nameDelimiter);
    
    if (firstAttrPos == std::string::npos) {
        if (nameDelimiter != decoded.length() - 1)
            return "";
            
        return decoded; 
    }
    
    std::string attrPart = decoded.substr(nameDelimiter + 1);
    size_t pos = 0;
    
    while (pos < attrPart.length()) {
        size_t openParen = attrPart.find('(', pos);
        if (openParen == std::string::npos)
            break;
            
        size_t closeParen = attrPart.find(')', openParen);
        if (closeParen == std::string::npos)
            return ""; 
            
        std::string attrStr = attrPart.substr(openParen + 1, closeParen - openParen - 1);
        
        enum ParseState { KEY_SECTION, VALUE_SECTION };
        ParseState state = KEY_SECTION;
        
        std::string attributeName;
        std::string attributeValue;
        
        for (size_t i = 0; i < attrStr.length(); i++) {
            char currentChar = attrStr[i];
            
            if (currentChar == ':' && state == KEY_SECTION) {
                state = VALUE_SECTION;
                attributeName = attributeName.substr(0, attributeName.find_last_not_of(" \t") + 1);
                continue;
            }
            
            if (state == KEY_SECTION) {
                attributeName += currentChar;
            } else {
                attributeValue += currentChar;
            }
        }
        
        if (attributeName.empty()) {
            return decoded;
        }
        
        while (!attributeValue.empty() && (attributeValue[0] == ' ' || attributeValue[0] == '\t')) {
            attributeValue.erase(0, 1);
        }
        
        try {
            double numericValue = 0.0;
            std::stringstream ss(attributeValue);
            ss >> numericValue;
            
            if (ss.fail()) {
                throw std::runtime_error("Invalid format");
            }
            
            attributesOutput.add(InventoryAttribute(attributeName, numericValue));
        } catch (...) {
            return "";
        }
        
        pos = closeParen + 1;
        
        if (pos < attrPart.length() && attrPart[pos] == ',') {
            pos++;
            while (pos < attrPart.length() && attrPart[pos] == ' ')
                pos++;
        }
    }
    
    return decoded;
}
