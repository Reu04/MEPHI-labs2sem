#include <iostream>
#include <cassert>

//// Binary Search Tree

template<typename T>
struct TreeNode {
    T data_;
    TreeNode<T>* left_;
    TreeNode<T>* right_;

    explicit TreeNode(const T& data)
            : data_(data), left_(nullptr), right_(nullptr) {}

    bool operator==(const TreeNode<T>& other) const {
        return data_ == other.data_;
    }
};

template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root_;
    size_t size_;

    void copyNodes(TreeNode<T>* node1, TreeNode<T>* node2) const { // копирует элементы из node2 в node1
        node1->data_ = node2->data_;
        if (node2->left_ != nullptr) {
            node1->left_ = new TreeNode<T>(node2->left_->data_);
            copyNodes(node1->left_, node2->left_);
        }
        if (node2->right_ != nullptr) {
            node1->right_ = new TreeNode<T>(node2->right_->data_);
            copyNodes(node1->right_, node2->right_);
        }
    }

    void InsertNode(TreeNode<T>* &node, const T& value) {
        if (node == nullptr) { // т.к. все листья хранят nullptr в полях left, right
            node = new TreeNode<T>(value);
            size_++;
            return;
        }
        if (node->data_ > value) {
            InsertNode(node->left_, value);
        } else if (node->data_ < value) {
            InsertNode(node->right_, value);
        }
    }

    void PrintTreeLNR(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            PrintTreeLNR(node->left_, std::cout);
            buff << node->data_ << '\t';
            PrintTreeLNR(node->right_, std::cout);
        }
    }
    void PrintTreeRNL(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            PrintTreeRNL(node->right_, std::cout);
            buff << node->data_ << '\t';
            PrintTreeRNL(node->left_, std::cout);
        }
    }
    void PrintTreeLRN(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            PrintTreeLRN(node->left_, std::cout);
            PrintTreeLRN(node->right_, std::cout);
            buff << node->data_ << '\t';
        }
    }
    void PrintTreeRLN(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            PrintTreeRLN(node->right_, std::cout);
            PrintTreeRLN(node->left_, std::cout);
            buff << node->data_ << '\t';
        }
    }
    void PrintTreeNRL(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            buff << node->data_ << '\t';
            PrintTreeNRL(node->right_, std::cout);
            PrintTreeNRL(node->left_, std::cout);
        }
    }
    void PrintTreeNLR(TreeNode<T>* node, std::ostream& buff) const {
        if (node != nullptr) {
            buff << node->data_ << '\t';
            PrintTreeNLR(node->left_, std::cout);
            PrintTreeNLR(node->right_, std::cout);
        }
    }

    bool isEqual(const TreeNode<T>* node, const TreeNode<T>* otherNode) const {
        if (node == nullptr && otherNode == nullptr) {
            return true;
        }
        if (node == nullptr || otherNode == nullptr) {
            return false;
        }
        if (node->data_ != otherNode->data_) {
            return false;
        }
        return isEqual(node->left_, otherNode->left_) && isEqual(node->right_, otherNode->right_);
    }

    bool FindElement(TreeNode<T>* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->data_ == value) {
            return true;
        }
        return FindElement(node->left_, value) || FindElement(node->right_, value);
    }
    TreeNode<T>* GetNodeByValue(TreeNode<T>* node, const T& value) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == value) {
            return node;
        }
        auto leftFind = GetNodeByValue(node->left_, value);
        auto rightFind = GetNodeByValue(node->right_, value);
        if (leftFind) return leftFind;
        return rightFind;
    }

    TreeNode<T>* minValueNode(TreeNode<T> *node) { // for Inorder Successor
        TreeNode<T> *curr = node;
        while (curr->left_ != nullptr) {
            curr = curr->left_;
        }
        return curr;
    }

    // Функция DeleteElement удаляет узел с заданным значением из дерева и возвращает указатель на корень дерева после удаления.
    TreeNode<T>* DeleteElement(TreeNode<T>* node, const T& value) {
        if (node == nullptr) {
            return node;
        }
        if (node->data_ > value) {
            node->left_ = DeleteElement(node->left_, value);
            return node;
        } else if (node->data_ < value) {
            node->right_ = DeleteElement(node->right_, value);
            return node;
        } else { // дошли до нужного узла
            if (node->left_ == nullptr) { // Если только один дочерний элемент
                TreeNode<T>* temp = node->right_;
                delete node;
                size_--;
                return temp;
            } else if (node->right_ == nullptr) {
                TreeNode<T>* temp = node->left_;
                delete node;
                size_--;
                return temp;
            }
            // Если 2 дочерних элемента

            // ищем inorder-приемника, т.е. тот узел, на который заменим удаляемый
            TreeNode<T>* temp = minValueNode(node->right_);
            node->data_ = temp->data_;
            node->right_ = DeleteElement(node->right_, temp->data_); // удаляем элемент, на который заменили
        }
        return node;
    }

    TreeNode<T>* Map(TreeNode<T>* node, T (*func)(T)) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode<T>* newNode = new TreeNode<T>(func(node->data_));
        newNode->left_ = Map(node->left_, func);
        newNode->right_ = Map(node->right_, func);

        return newNode;
    }

    void Where(TreeNode<T>* node, BinarySearchTree<T>* filtered, bool (*func)(T)) {
        if (node == nullptr) {
            return;
        }
        Where(node->left_, filtered, func);
        if (func(node->data_) == true) {
            filtered->Insert(node->data_);
        }
        Where(node->right_, filtered, func);
    }

    void Concat(TreeNode<T>* otherNode) {
        if (otherNode->left_ != nullptr) {
            Concat(otherNode->left_);
        }
        this->Insert(otherNode->data_);
        if (otherNode->right_ != nullptr) {
            Concat(otherNode->right_);
        }
    }

public:
    BinarySearchTree() : root_(nullptr), size_(0) {}
    BinarySearchTree(size_t size, T* arr) : root_(nullptr), size_(0) {
        if (arr != nullptr) {
            root_ = new TreeNode<T>(arr[0]);
            size_++;
            for (size_t i = 1; i < size; i++) {
                InsertNode(root_, arr[i]);
            }
        }
    }
    BinarySearchTree(TreeNode<T>* root, size_t size) : root_(root), size_(size) {}
    BinarySearchTree(const BinarySearchTree<T> &other) : root_(nullptr), size_(other.size_) {
        if (other.root_ != nullptr) {
            root_ = new TreeNode<T>(other.root_->data_);
            copyNodes(root_, other.root_);
        }
    }


    ~BinarySearchTree() {
        DeleteTree(root_);
    }

    void DeleteTree(TreeNode<T>* tree) {
        if (tree != nullptr) {
            DeleteTree(tree->left_);
            DeleteTree(tree->right_);
            delete tree;
        }
    }

    void Insert(const T& value) {
        InsertNode(root_, value);
    }

    void Print(std::ostream& buff, const std::string& type = "LNR") const {
        if (type == "LNR") PrintTreeLNR(root_, buff);
        else if (type == "RNL") PrintTreeRNL(root_, buff);
        else if (type == "NRL") PrintTreeNRL(root_, buff);
        else if (type == "NLR") PrintTreeNLR(root_, buff);
        else if (type == "LRN") PrintTreeLRN(root_, buff);
        else if (type == "RLN") PrintTreeRLN(root_, buff);
        else throw std::runtime_error("Unknown traversal");
    }

    bool operator==(const BinarySearchTree<T>& other) const {
        if (size_ != other.size_) {
            return false;
        }
        return isEqual(root_, other.root_);
    }

    size_t GetSize() const {
        return size_;
    }

    bool Find(const T& value) {
        return FindElement(root_, value);
    }

    TreeNode<T>* Delete(const T& value) {
        return DeleteElement(root_, value);
    }

    BinarySearchTree<T>* Map(T (*func)(T), size_t size) {
        return new BinarySearchTree<T>(Map(root_, func), size);
    }

    BinarySearchTree<T>* Where(bool (*func)(T)) {
        BinarySearchTree<T>* filtered = new BinarySearchTree<T>();
        Where(root_, filtered, func);
        return filtered;
    }

    void Concat(BinarySearchTree<T>* other) {
        Concat(other->root_);
    }

    BinarySearchTree<T>* SubTree(const T& element) const {
        auto subNode = GetNodeByValue(root_, element);
        auto subNodecopy = new TreeNode<T>(subNode->data_);
        copyNodes(subNodecopy, subNode);
        return new BinarySearchTree<T>(subNodecopy, getNodeSize(subNodecopy));
    }

    static size_t getNodeSize(TreeNode<T>* node) {
        size_t size = 1;
        if (node->left_) size += getNodeSize(node->left_);
        if (node->right_) size += getNodeSize(node->right_);
        return size;
    }

    TreeNode<T>* getRoot() const {
        return this->root_;
    }
};