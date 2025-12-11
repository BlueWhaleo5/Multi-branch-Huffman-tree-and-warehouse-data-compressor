
#include "app/inventory.h"
// // -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    attributesMatrix = List2D<InventoryAttribute>();
    productNames = List1D<string>();
    quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO
    this->attributesMatrix = matrix;
    this->productNames = names;
    this->quantities = quantities;
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
    this->attributesMatrix = other.attributesMatrix;
    this->productNames = other.productNames;
    this->quantities = other.quantities;
}

int InventoryManager::size() const
{
    // TODO
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    List1D<InventoryAttribute> attributes;
    List1D<InventoryAttribute> rowAttributes = attributesMatrix.getRow(index);
    
    for (int i = 0; i < rowAttributes.size(); i++) {
        attributes.add(rowAttributes.get(i));
    }

    return attributes;
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    attributesMatrix.setRow(attributesMatrix.rows(), attributes);
    productNames.add(name);
    quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }

    List2D<InventoryAttribute> newAttributesMatrix;
    List1D<string> newProductNames;
    List1D<int> newQuantities;

    for (int i = 0; i < size(); i++) {
        if (i != index) {
            newAttributesMatrix.setRow(newAttributesMatrix.rows(), attributesMatrix.getRow(i));
            newProductNames.add(productNames.get(i));
            newQuantities.add(quantities.get(i));
        }
    }

    attributesMatrix = newAttributesMatrix;
    productNames = newProductNames;
    quantities = newQuantities;
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<int> validIndices;
    List1D<double> attributeValues;
    List1D<int> productQuantities;

    for (int i = 0; i < attributesMatrix.rows(); i++) {
        List1D<InventoryAttribute> productAttrs = attributesMatrix.getRow(i);
        int quantity = quantities.get(i);

        if (quantity < minQuantity) {
            continue;
        }

        bool found = false;
        double attrValue = 0.0;
        for (int j = 0; j < productAttrs.size(); j++) {
            InventoryAttribute attr = productAttrs.get(j);
            if (attr.name == attributeName) {
                attrValue = attr.value;
                found = true;
                break;
            }
        }

        if (found && attrValue >= minValue && attrValue <= maxValue) {
            validIndices.add(i);
            attributeValues.add(attrValue);
            productQuantities.add(quantity);
        }
    }

    typedef bool (*SortCondition)(double, double, double, double);
    SortCondition compareAscending = [](double val2, double val1, double qty2, double qty1) {
        return (val2 < val1) || ((val2 == val1) && (qty2 < qty1));
    };

    SortCondition compareDescending = [](double val2, double val1, double qty2, double qty1) {
        return (val2 > val1) || ((val2 == val1) && (qty2 >= qty1));
    };


    bool swapped;
    for (int i = 0; i < validIndices.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < validIndices.size() - i - 1; j++) {
            double val1 = attributeValues.get(j);
            double val2 = attributeValues.get(j + 1);
            int qty1 = productQuantities.get(j);
            int qty2 = productQuantities.get(j + 1);

            // Compare attribute values first; if equal, compare quantities as tiebreaker
            bool shouldSwap;
            if (ascending) {
                shouldSwap = compareAscending(val2, val1, qty2, qty1);
            } else {
                shouldSwap = compareDescending(val2, val1, qty2, qty1);
            }


            if (shouldSwap) {
                // Swap the indices
                int tempIndex = validIndices.get(j);
                validIndices.set(j, validIndices.get(j + 1));
                validIndices.set(j + 1, tempIndex);

                // Swap the attribute values to keep them aligned
                double tempValue = attributeValues.get(j);
                attributeValues.set(j, attributeValues.get(j + 1));
                attributeValues.set(j + 1, tempValue);

                // Swap the quantities to keep them aligned
                int tempQty = productQuantities.get(j);
                productQuantities.set(j, productQuantities.get(j + 1));
                productQuantities.set(j + 1, tempQty);

                swapped = true;
            }
        }
        if (!swapped) break; // If no swaps occurred, the list is sorted
    }

    List1D<string> result;
    for (int i = 0; i < validIndices.size(); i++) {
        int index = validIndices.get(i);
        result.add(productNames.get(index));
    }

    return result;
}

void InventoryManager::removeDuplicates()
{
    int i = 0;
    while (i < size()) {
        int j = i + 1;
        while (j < size()) {
            if (productNames.get(i) != productNames.get(j)) {
                j++;
                continue;
            }

            List1D<InventoryAttribute> attrs1 = attributesMatrix.getRow(i);
            List1D<InventoryAttribute> attrs2 = attributesMatrix.getRow(j);

            if (attrs1.size() != attrs2.size()) {
                j++;
                continue;
            }

            bool same = true;
            for (int t = 0; t < attrs1.size(); t++) {
                if (!(attrs1.get(t) == attrs2.get(t))) {
                    same = false;
                    break;
                }
            }

            if (same) {
                int newQuantity = quantities.get(i) + quantities.get(j);
                quantities.set(i, newQuantity);
                attributesMatrix.removeAt(j);
                productNames.removeAt(j);
                quantities.removeAt(j);
            } else {
                j++;
            }
        }
        i++;
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO
    InventoryManager mergedInventory;

    for (int i = 0; i < inv1.size(); i++) {
        mergedInventory.addProduct(
            inv1.getProductAttributes(i), 
            inv1.getProductName(i), 
            inv1.getProductQuantity(i)
        );
    }

    for (int i = 0; i < inv2.size(); i++) {
        mergedInventory.addProduct(
            inv2.getProductAttributes(i), 
            inv2.getProductName(i), 
            inv2.getProductQuantity(i)
        );
    }

    return mergedInventory;
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    double product = size() * ratio;
    double diff = product - (int)product;
    if (diff < 0)  
        diff = -diff;
    int splitPoint = (int)product + ((product > 0 && diff > 1e-9) ? 1 : 0);

    List2D<InventoryAttribute> matrix1, matrix2;
    List1D<string> names1, names2;
    List1D<int> quant1, quant2;

    for (int i = 0; i < size(); i++) {
        if (i < splitPoint) {
            matrix1.setRow(matrix1.rows(), attributesMatrix.getRow(i));
            names1.add(productNames.get(i));
            quant1.add(quantities.get(i));
        } else {
            matrix2.setRow(matrix2.rows(), attributesMatrix.getRow(i));
            names2.add(productNames.get(i));
            quant2.add(quantities.get(i));
        }
    }

    section1 = InventoryManager(matrix1, names1, quant1);
    section2 = InventoryManager(matrix2, names2, quant2);
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return quantities;
}

string InventoryManager::toString() const
{
    // TODO
    stringstream ss;
    ss << "InventoryManager[\n";
    
    ss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";
    
    ss << "  ProductNames: " << productNames.toString() << ",\n";
    
    ss << "  Quantities: " << quantities.toString() << "\n";

    ss << "]";
    
    return ss.str();
}