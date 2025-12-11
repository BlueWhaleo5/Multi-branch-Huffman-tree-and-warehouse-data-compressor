# Overview
This repository contains the full implementation for the Data Structures & Algorithms Assignment, including a custom `HashMap`, a generic `Heap`, an N-ary `HuffmanTree`, and an `InventoryCompressor` used to encode/decode warehouse product data. The project follows the original specification and folder structure provided in the assignment.

The goal is to build core data structures from scratch (no external libraries), then apply them to a realistic scenario: compressing and decompressing inventory information using N-ary Huffman coding. All modules are implemented in modern **C++17**, with clear separation of headers, implementations, and test drivers.

---

## Features

### 1. xMap — Custom Hash Map
A templated hash table using separate chaining.
Includes:
- Insert, remove, search operations
- Dynamic resizing
- Custom iterator
- Support for arbitrary key–value types

---

### 2. Generic Heap
A fully templated binary heap structure.
Supports:
- Min-heap / Max-heap
- Heapify
- Push/pop operations
- Heap sort
- Efficient priority queue operations

---

### 3. N-ary Huffman Tree (`HuffmanTree<treeOrder>`)
Builds an N-branch Huffman coding tree.
Provides:
- Frequency table construction
- Encoding tree generation
- Codeword lookup
- Decode traversal
- Supports any branching factor (`treeOrder ≥ 2`)

---

### 4. Inventory Compressor
A complete compression/decompression pipeline:
- Build Huffman codes from item frequencies
- Encode product IDs into compressed form
- Decode back to original data

---

## Repository Structure
```
/include
    /hash/                  # xMap (hash table)
    /heap/                  # Heap implementation
    /list/                  # Supporting list structures
    /app/
        HuffmanTree/        # N-ary Huffman tree
        inventory_compressor.h
/src
    main.cpp                # Main tester / demo
/test
    # Provided and custom testcases
README.md
```

---

## Build & Run
Compile using g++17:
```
g++ -g -I include -I src -std=c++17 src/test/* src/main.cpp -o main
./main [testcase_name]
```

---

## Submission Checklist
- Completed:
  - `/include/hash/xMap.h`
  - `/include/heap/Heap.h`
  - `/include/app/inventory_compressor.h`
- All sample tests pass
- Follows required folder structure
- No external libraries used

---

## License
MIT (or adjust per course requirement)

