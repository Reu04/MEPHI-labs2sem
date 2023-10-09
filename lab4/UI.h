#pragma once
#include <iostream>
#include "BinarySearchTree.h"

template<typename T>
BinarySearchTree<T>* ObjectCreating() {
    std::cout << "Enter the number of items:\n";
    size_t num;
    std::cin >> num;
    if (num <= 0) {
        throw std::out_of_range("The number of items must be positive.");
    }

    T* items = new T[num];

    std::cout << "Enter the items:\n";
    for (size_t i = 0; i < num; i++) {
        T item;
        std::cin >> item;
        items[i] = item;
    }

    BinarySearchTree<T>* tree = new BinarySearchTree<T>(num, items);

    std::cout << "Binary Search Tree created.\n";
    std::cout << "Elements of Binary Search Tree: ";

    std::cout << std::endl;
    tree->Print(std::cout);
    return tree;
}

template<typename T>
void ObjectDeletion(T object) {
    delete object;
    std::cout << "Object deleted.\n";
}

template<typename T>
void UIBase() {
    BinarySearchTree<T>* tree = ObjectCreating<T>();

    std::cout << "\nIf you want to continue: enter 0.\n";
    int exit;
    std::cin >> exit;

    while (exit == 0) {
        std::cout << "Which function do you want to use?\n1. Insert\t2. Find\t3. GetSize\n"
                     "4. Delete\t5. Print\t6. Concat\t7. SubTree\n";
        int func;
        std::cin >> func;
        switch (func) {
            case 1:
                std::cout << "Enter the item:\n";
                T item;
                std::cin >> item;
                tree->Insert(item);
                std::cout << "Item inserted.\n";
                std::cout << "Elements of Binary Search Tree: ";
                tree->Print(std::cout);
                break;
            case 2:
                std::cout << "Enter the item:\n";
                T item2;
                std::cin >> item2;
                if (tree->Find(item2)) {
                    std::cout << "Item found.\n";
                } else {
                    std::cout << "Item not found.\n";
                }
                break;
            case 3:
                std::cout << "Size of Binary Search Tree: " << tree->GetSize() << std::endl;
                break;
            case 4:
                std::cout << "Enter the item:\n";
                T item3;
                std::cin >> item3;
                tree->Delete(item3);
                std::cout << "Item deleted.\n";
                std::cout << "Elements of Binary Search Tree: ";
                tree->Print(std::cout);
                break;
            case 5:
                std::cout << "Choose the type of binary search tree: \n1. NLR\t2. LNR(Sorted)\t3. LRN\t4. NRL\t5. RNL\t6. RLN\n";
                int type;
                std::cin >> type;
                switch (type) {
                    case 1:
                        tree->Print(std::cout, "NLR");
                        break;
                    case 2:
                        tree->Print(std::cout, "LNR");
                        break;
                    case 3:
                        tree->Print(std::cout, "LRN");
                        break;
                    case 4:
                        tree->Print(std::cout, "NRL");
                        break;
                    case 5:
                        tree->Print(std::cout, "RNL");
                        break;
                    case 6:
                        tree->Print(std::cout, "RLN");
                        break;
                    default:
                        std::cout << "Wrong type.\n";
                        break;
                }
                break;
            case 6:
            {
                std::cout << "Create the second Binary Search Tree:\n";
                BinarySearchTree<T>* tree2 = ObjectCreating<T>();
                tree->Concat(tree2);
                std::cout << "Concatenated.\n";
                tree->Print(std::cout);
                break;
            }
            case 7:
            {
                std::cout << "Enter the item:\n";
                T item4;
                std::cin >> item4;
                BinarySearchTree<T>* tree3 = tree->SubTree(item4);
                std::cout << "SubTree created.\n";
                std::cout << "Elements of SubTree: ";
                tree3->Print(std::cout);
                break;
            }
            default:
                std::cout << "Wrong function.\n";
                break;
        }
        std::cout << "\nIf you want to continue: enter 0.\n";
        std::cin >> exit;
    }
    ObjectDeletion(tree);
}

void UserInterface() {
    std::cout << "What type of elements will be in your Binary Search Tree?\n1. int\n2. double\n3. char\n";
    int type;
    std::cin >> type;
    switch (type) {
        case 1:
            UIBase<int>();
            break;
        case 2:
            UIBase<double>();
            break;
        case 3:
            UIBase<char>();
            break;
        default:
            std::cout << "Wrong type.\n";
            break;
    }
}