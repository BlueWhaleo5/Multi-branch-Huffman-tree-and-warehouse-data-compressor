#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();
    List1D<T> &operator=(const List1D<T> &other); 
    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);

    //! thêm hàm này 
    void add(int index ,const T &value);
    void removeAt(int index);
    string toString() const;
    template <typename U> //! thêm vào  để chạy test 
    friend ostream &operator<<(ostream &os, const List1D<T> &list);
};

template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();
    List2D<T> &operator=(const List2D<T> &other);
    int rows() const;
    //! thêm hàm này 
    void removeAt(int index);
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;
    template <typename U> //! thêm vào  để chạy test 
    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
};
struct InventoryAttribute
{
    string name;
    double value;
    //! thêm
    InventoryAttribute() : name(""), value(0.0) {}  // Constructor mặc định
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
     //! thêm
     // Định nghĩa toán tử so sánh ==
     bool operator==(const InventoryAttribute& other) const {
        return name == other.name && value == other.value;
    }
      // Toán tử in ra ostream
      friend std::ostream &operator<<(std::ostream &os, const InventoryAttribute &attr) {
        return os << attr.toString();
    }
};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
       
    
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
                     
                     
    InventoryManager(const InventoryManager &other);

    int size() const;
       
    
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};


















// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    this->pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    this->pList = new XArrayList<T>(nullptr, nullptr, num_elements);
    for (int i = 0; i < num_elements; i++){
        this->pList->add(T());
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    this->pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++){
        this->pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    this->pList = new XArrayList<T>();
    for (int i = 0; i < other.size(); i++){
        this->pList->add(other.get(i));
    }
}

template <typename T>
List1D<T>::~List1D()
{
    delete this->pList;
}

template <typename T>
List1D<T> &List1D<T>::operator=(const List1D<T> &other)
{
    if (this != &other) {
        delete pList;

        this->pList = new XArrayList<T>();
        for (int i = 0; i < other.size(); ++i) {
            this->pList->add(other.get(i));
        }
    }
    return *this;
}

template <typename T>
int List1D<T>::size() const
{
    return this->pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    if (index < 0 || index >= this->pList->size()) {
            throw out_of_range("Index is out of range!");
    }

    return this->pList->get(index); 
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    if(index == this->size()) this->pList->add(value);
    else{
        T& ref = this->pList->get(index);
        ref = value;
    }
}

template <typename T>
void List1D<T>::add(const T &value)
{
    this->pList->add(value);
}

template <typename T>
void List1D<T>::add(int index,const T &value)
{
    this->pList->add(index,value);
}

template <typename T>
string List1D<T>::toString() const
{
   stringstream ss;
    ss << "[";
    for (int i = 0; i < this->size(); i++) {
        ss << this->get(i);
        if (i < this->size() - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

template<typename T>
void List1D<T>::removeAt(int index){
    this->pList->removeAt(index);
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    os << list.toString();
    return os;
}





















// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    this->pMatrix = new XArrayList<IList<T>*>();
}

template <typename T>
List2D<T> &List2D<T>::operator=(const List2D<T> &other)
{
    if (this != &other) {
        for (int i = 0; i < this->pMatrix->size(); ++i) delete pMatrix->get(i);
        delete pMatrix;
        
        this->pMatrix = new XArrayList<IList<T>*>();
        for (int i = 0; i < other.rows(); i++) {
            XArrayList<T>* rowList = new XArrayList<T>();
            List1D<T> row = other.getRow(i);

            for (int j = 0; j < row.size(); j++) rowList->add(row.get(j));
            this->pMatrix->add(rowList);
        }
    }
    return *this;
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    this->pMatrix = new XArrayList<IList<T>*>();
    
    for (int i = 0; i < num_rows; i++) {
        XArrayList<T>* rowList = new XArrayList<T>();
        for (int j = 0; j < array[i].size(); j++) {
            rowList->add(array[i].get(j));
        }
        this->pMatrix->add(rowList);
    }
}


template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    this->pMatrix = new XArrayList<IList<T>*>();
    
    for (int i = 0; i < other.rows(); i++) {
        XArrayList<T>* rowList = new XArrayList<T>();
        List1D<T> row = other.getRow(i);
        for (int j = 0; j < row.size(); j++) {
            rowList->add(row.get(j));
        }
        this->pMatrix->add(rowList);
    }
}

template <typename T>
List2D<T>::~List2D()
{
    for(int i = 0; i < this->rows(); i++) delete this->pMatrix->get(i);
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
    return this->pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    if (rowIndex < 0 || rowIndex > this->rows()) {
        throw out_of_range("Index is out of range!");
    }

    while (rowIndex >= this->rows()) this->pMatrix->add(new XArrayList<T>());
    
    // Create a new row with copied data
    XArrayList<T>* newRow = new XArrayList<T>();
    for (int i = 0; i < row.size(); i++) {
        newRow->add(row.get(i));
    }
    
    // Delete old row
    delete this->pMatrix->get(rowIndex);
    this->pMatrix->get(rowIndex) = newRow;
}

template <typename T>
void List2D<T>::removeAt(int index){
    delete this->pMatrix->get(index);
    this->pMatrix->removeAt(index);
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    return pMatrix->get(rowIndex)->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    if (rowIndex < 0 || rowIndex > this->rows()) {
        throw out_of_range("Index is out of range!");
    }
    List1D<T> result;
    IList<T>* row = this->pMatrix->get(rowIndex);
    
    for (int i = 0; i < row->size(); i++) {
        result.add(row->get(i));
    }
    
    return result;
}

template <typename T>
string List2D<T>::toString() const
{
    stringstream ss;
    ss << "[";
    
    for (int i = 0; i < this->rows(); i++) {
        List1D<T> row = this->getRow(i);
        ss << row.toString();
        
        if (i < this->rows() - 1) {
            ss << ", ";
        }
    }
    
    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    os << matrix.toString();
    return os;
}





















// // -------------------- InventoryManager Method Definitions --------------------
// InventoryManager::InventoryManager()
// {
//     attributesMatrix = List2D<InventoryAttribute>();
//     productNames = List1D<string>();
//     quantities = List1D<int>();
// }

// InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
//                                    const List1D<string> &names,
//                                    const List1D<int> &quantities)
// {
//     this->attributesMatrix = matrix;
//     this->productNames = names;
//     this->quantities = quantities;
// }

// InventoryManager::InventoryManager(const InventoryManager &other)
// {
//     this->attributesMatrix = other.attributesMatrix;
//     this->productNames = other.productNames;
//     this->quantities = other.quantities;
// }

// int InventoryManager::size() const
// {
//     return productNames.size();
// }

// List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
// {
//     if (index < 0 || index >= size()) {
//         throw out_of_range("Index is invalid!");
//     }
//     List1D<InventoryAttribute> attributes;
//     List1D<InventoryAttribute> rowAttributes = attributesMatrix.getRow(index);
    
//     for (int i = 0; i < rowAttributes.size(); i++) {
//         attributes.add(rowAttributes.get(i));
//     }

//     return attributes;
// }

// string InventoryManager::getProductName(int index) const
// {
//     if (index < 0 || index >= size()) {
//         throw out_of_range("Index is invalid!");
//     }
//     return productNames.get(index);
// }

// int InventoryManager::getProductQuantity(int index) const
// {
//     if (index < 0 || index >= size()) {
//         throw out_of_range("Index is invalid!");
//     }
//     return quantities.get(index);
// }

// void InventoryManager::updateQuantity(int index, int newQuantity)
// {
//     if (index < 0 || index >= size()) {
//         throw out_of_range("Index is invalid!");
//     }
//     quantities.set(index, newQuantity);
// }

// void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
// {
//     attributesMatrix.setRow(attributesMatrix.rows(), attributes);
//     productNames.add(name);
//     quantities.add(quantity);
// }

// void InventoryManager::removeProduct(int index)
// {
//     if (index < 0 || index >= size()) {
//         throw out_of_range("Index is invalid!");
//     }

//     List2D<InventoryAttribute> newAttributesMatrix;
//     List1D<string> newProductNames;
//     List1D<int> newQuantities;

//     for (int i = 0; i < size(); i++) {
//         if (i != index) {
//             newAttributesMatrix.setRow(newAttributesMatrix.rows(), attributesMatrix.getRow(i));
//             newProductNames.add(productNames.get(i));
//             newQuantities.add(quantities.get(i));
//         }
//     }

//     attributesMatrix = newAttributesMatrix;
//     productNames = newProductNames;
//     quantities = newQuantities;
// }

// List1D<string> InventoryManager::query(string attributeName, const double &minValue,
//                                        const double &maxValue, int minQuantity, bool ascending) const
// {
//     List1D<int> validIndices;
//     List1D<double> attributeValues;
//     List1D<int> productQuantities;

//     for (int i = 0; i < attributesMatrix.rows(); i++) {
//         List1D<InventoryAttribute> productAttrs = attributesMatrix.getRow(i);
//         int quantity = quantities.get(i);

//         if (quantity < minQuantity) {
//             continue;
//         }

//         bool found = false;
//         double attrValue = 0.0;
//         for (int j = 0; j < productAttrs.size(); j++) {
//             InventoryAttribute attr = productAttrs.get(j);
//             if (attr.name == attributeName) {
//                 attrValue = attr.value;
//                 found = true;
//                 break;
//             }
//         }

//         if (found && attrValue >= minValue && attrValue <= maxValue) {
//             validIndices.add(i);
//             attributeValues.add(attrValue);
//             productQuantities.add(quantity);
//         }
//     }

//     typedef bool (*SortCondition)(double, double, double, double);
//     SortCondition compareAscending = [](double val2, double val1, double qty2, double qty1) {
//         return (val2 < val1) || ((val2 == val1) && (qty2 < qty1));
//     };

//     SortCondition compareDescending = [](double val2, double val1, double qty2, double qty1) {
//         return (val2 > val1) || ((val2 == val1) && (qty2 >= qty1));
//     };


//     bool swapped;
//     for (int i = 0; i < validIndices.size() - 1; i++) {
//         swapped = false;
//         for (int j = 0; j < validIndices.size() - i - 1; j++) {
//             double val1 = attributeValues.get(j);
//             double val2 = attributeValues.get(j + 1);
//             int qty1 = productQuantities.get(j);
//             int qty2 = productQuantities.get(j + 1);

//             // Compare attribute values first; if equal, compare quantities as tiebreaker
//             bool shouldSwap;
//             if (ascending) {
//                 shouldSwap = compareAscending(val2, val1, qty2, qty1);
//             } else {
//                 shouldSwap = compareDescending(val2, val1, qty2, qty1);
//             }


//             if (shouldSwap) {
//                 // Swap the indices
//                 int tempIndex = validIndices.get(j);
//                 validIndices.set(j, validIndices.get(j + 1));
//                 validIndices.set(j + 1, tempIndex);

//                 // Swap the attribute values to keep them aligned
//                 double tempValue = attributeValues.get(j);
//                 attributeValues.set(j, attributeValues.get(j + 1));
//                 attributeValues.set(j + 1, tempValue);

//                 // Swap the quantities to keep them aligned
//                 int tempQty = productQuantities.get(j);
//                 productQuantities.set(j, productQuantities.get(j + 1));
//                 productQuantities.set(j + 1, tempQty);

//                 swapped = true;
//             }
//         }
//         if (!swapped) break; // If no swaps occurred, the list is sorted
//     }

//     List1D<string> result;
//     for (int i = 0; i < validIndices.size(); i++) {
//         int index = validIndices.get(i);
//         result.add(productNames.get(index));
//     }

//     return result;
// }

// void InventoryManager::removeDuplicates()
// {
//     int i = 0;
//     while (i < size()) {
//         int j = i + 1;
//         while (j < size()) {
//             if (productNames.get(i) != productNames.get(j)) {
//                 j++;
//                 continue;
//             }

//             List1D<InventoryAttribute> attrs1 = attributesMatrix.getRow(i);
//             List1D<InventoryAttribute> attrs2 = attributesMatrix.getRow(j);

//             if (attrs1.size() != attrs2.size()) {
//                 j++;
//                 continue;
//             }

//             bool same = true;
//             for (int t = 0; t < attrs1.size(); t++) {
//                 if (!(attrs1.get(t) == attrs2.get(t))) {
//                     same = false;
//                     break;
//                 }
//             }

//             if (same) {
//                 int newQuantity = quantities.get(i) + quantities.get(j);
//                 quantities.set(i, newQuantity);
//                 attributesMatrix.removeAt(j);
//                 productNames.removeAt(j);
//                 quantities.removeAt(j);
//             } else {
//                 j++;
//             }
//         }
//         i++;
//     }
// }

// InventoryManager InventoryManager::merge(const InventoryManager &inv1,
//                                          const InventoryManager &inv2)
// {
//     InventoryManager mergedInventory;

//     for (int i = 0; i < inv1.size(); i++) {
//         mergedInventory.addProduct(
//             inv1.getProductAttributes(i), 
//             inv1.getProductName(i), 
//             inv1.getProductQuantity(i)
//         );
//     }

//     for (int i = 0; i < inv2.size(); i++) {
//         mergedInventory.addProduct(
//             inv2.getProductAttributes(i), 
//             inv2.getProductName(i), 
//             inv2.getProductQuantity(i)
//         );
//     }

//     return mergedInventory;
// }

// void InventoryManager::split(InventoryManager &section1,
//                              InventoryManager &section2,
//                              double ratio) const
// {
//     double product = size() * ratio;
//     double diff = product - (int)product;
//     if (diff < 0)  
//         diff = -diff;
//     int splitPoint = (int)product + ((product > 0 && diff > 1e-9) ? 1 : 0);

//     List2D<InventoryAttribute> matrix1, matrix2;
//     List1D<string> names1, names2;
//     List1D<int> quant1, quant2;

//     for (int i = 0; i < size(); i++) {
//         if (i < splitPoint) {
//             matrix1.setRow(matrix1.rows(), attributesMatrix.getRow(i));
//             names1.add(productNames.get(i));
//             quant1.add(quantities.get(i));
//         } else {
//             matrix2.setRow(matrix2.rows(), attributesMatrix.getRow(i));
//             names2.add(productNames.get(i));
//             quant2.add(quantities.get(i));
//         }
//     }

//     section1 = InventoryManager(matrix1, names1, quant1);
//     section2 = InventoryManager(matrix2, names2, quant2);
// }

// List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
// {
//     return attributesMatrix;
// }

// List1D<string> InventoryManager::getProductNames() const
// {
//     return productNames;
// }

// List1D<int> InventoryManager::getQuantities() const
// {
//     return quantities;
// }

// string InventoryManager::toString() const
// {
//     // TODO
//     stringstream ss;
//     ss << "InventoryManager[\n";
    
//     ss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";
    
//     ss << "  ProductNames: " << productNames.toString() << ",\n";
    
//     ss << "  Quantities: " << quantities.toString() << "\n";

//     ss << "]";
    
//     return ss.str();
// }


#endif /* INVENTORY_MANAGER_H */