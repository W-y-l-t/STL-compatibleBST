#pragma once

#include <memory>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <functional>

const uint16_t kOneNode = 1;

struct InOrderTag {} in;
struct PreOrderTag {} pre;
struct PostOrderTag {} post;

template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
class BinarySearchTree {
 private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;

        explicit Node(const T& value) :
            value(value), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(const T& value, Node* parent) :
            value(value), parent(parent) {}
        Node(const T& value, Node* left, Node* right, Node* parent) :
            value(value), left(left), right(right), parent(parent) {}
    };

 public:
    template<bool IsConst>
    class InOrderIterator;

    template<bool IsConst>
    class PreOrderIterator;

    template<bool IsConst>
    class PostOrderIterator;

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    BinarySearchTree() : root_(nullptr), allocator_{}, compare_{} {}
    BinarySearchTree(const BinarySearchTree& binary_search_tree);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree& binary_search_tree);
    explicit BinarySearchTree(const Allocator& alloc) noexcept : allocator_(alloc), root_(nullptr) {}
    explicit BinarySearchTree(const Compare& comp, const Allocator& alloc = Allocator())
        : compare_(comp), allocator_(alloc), root_(nullptr) {}
    BinarySearchTree(const BinarySearchTree& other, const Allocator& alloc) : allocator_(alloc), root_(nullptr) {
        root_ = Copy(other.root_);
    }

    class value_compare {
     public:
        bool operator()(const T& lhs, const T& rhs) const {
            return comp(lhs, rhs);
        }

     protected:
        Compare comp;

        explicit value_compare(Compare c) : comp(c) {}
    };

    value_compare value_comp() const { return value_compare(compare_); }
    Compare key_comp() const { return compare_; }
    Allocator get_allocator() const noexcept { return allocator_; }

    void Destroy(Node* node);
    Node* Copy(const Node* node);
    bool IsEqual(Node* first, Node* second);

    bool operator==(const BinarySearchTree& binary_search_tree);
    bool operator!=(const BinarySearchTree& binary_search_tree);

    InOrderIterator<false> begin() { return begin(in); }
    InOrderIterator<false> begin(InOrderTag);
    PreOrderIterator<false> begin(PreOrderTag);
    PostOrderIterator<false> begin(PostOrderTag);

    InOrderIterator<false> end() { return end(in); }
    InOrderIterator<false> end(InOrderTag);
    PreOrderIterator<false> end(PreOrderTag);
    PostOrderIterator<false> end(PostOrderTag);

    InOrderIterator<true> cbegin() const { return cbegin(in); }
    InOrderIterator<true> cbegin(InOrderTag) const;
    PreOrderIterator<true> cbegin(PreOrderTag);
    PostOrderIterator<true> cbegin(PostOrderTag);

    InOrderIterator<true> cend() const { return cend(in); }
    InOrderIterator<true> cend(InOrderTag) const;
    PreOrderIterator<true> cend(PreOrderTag);
    PostOrderIterator<true> cend(PostOrderTag);

    std::reverse_iterator<InOrderIterator<false>> rbegin() { return rbegin(in); }
    std::reverse_iterator<InOrderIterator<false>> rbegin(InOrderTag);
    std::reverse_iterator<PreOrderIterator<false>> rbegin(PreOrderTag);
    std::reverse_iterator<PostOrderIterator<false>> rbegin(PostOrderTag);

    std::reverse_iterator<InOrderIterator<false>> rend() { return rend(in); }
    std::reverse_iterator<InOrderIterator<false>> rend(InOrderTag);
    std::reverse_iterator<PreOrderIterator<false>> rend(PreOrderTag);
    std::reverse_iterator<PostOrderIterator<false>> rend(PostOrderTag);

    std::reverse_iterator<InOrderIterator<true>> crbegin() { return crbegin(in); }
    std::reverse_iterator<InOrderIterator<true>> crbegin(InOrderTag) const;
    std::reverse_iterator<PreOrderIterator<true>> crbegin(PreOrderTag) const;
    std::reverse_iterator<PostOrderIterator<true>> crbegin(PostOrderTag) const;

    std::reverse_iterator<InOrderIterator<true>> crend() { return crend(in); }
    std::reverse_iterator<InOrderIterator<true>> crend(InOrderTag) const;
    std::reverse_iterator<PreOrderIterator<true>> crend(PreOrderTag) const;
    std::reverse_iterator<PostOrderIterator<true>> crend(PostOrderTag) const;

    void swap(BinarySearchTree& binary_search_tree);

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;

    T& front() { return front(in); }
    T& front(InOrderTag);
    T& front(PreOrderTag);
    T& front(PostOrderTag);

    const T& front() const { return front(in); }
    const T& front(InOrderTag) const;
    const T& front(PreOrderTag) const;
    const T& front(PostOrderTag) const;

    T& back() { return back(in); }
    T& back(InOrderTag);
    T& back(PreOrderTag);
    T& back(PostOrderTag);

    const T& back() const { return back(in); }
    const T& back(InOrderTag) const;
    const T& back(PreOrderTag) const;
    const T& back(PostOrderTag) const;

    InOrderIterator<false> find(const T& data) { return find(data, in); }
    InOrderIterator<false> find(const T& data, InOrderTag);
    PreOrderIterator<false> find(const T& data, PreOrderTag);
    PostOrderIterator<false> find(const T& data, PostOrderTag);

    T extract(const T& data);
    void extract(const T& data, Node* &root, T& node);

    std::pair<InOrderIterator<false>, bool> insert(const T& data) { return insert(data, InOrderTag{}); };
    std::pair<InOrderIterator<false>, bool> insert(const T& data, InOrderTag);
    std::pair<PreOrderIterator<false>, bool> insert(const T& data, PreOrderTag);
    std::pair<PostOrderIterator<false>, bool> insert(const T& data, PostOrderTag);
    void erase(const T& data);
    void erase(const T& data, Node* &root);

    void clear();
    bool contains(const T& data);
    size_t count(const T& key);

    InOrderIterator<false> lower_bound(const T& key) { return lower_bound(key, InOrderTag{}); };
    InOrderIterator<false> lower_bound(const T& key, InOrderTag);
    PreOrderIterator<false> lower_bound(const T& key, PreOrderTag);
    PostOrderIterator<false> lower_bound(const T& key, PostOrderTag);
    Node* lower_bound_node(const T& key);

    InOrderIterator<false> upper_bound(const T& key) { return upper_bound(key, InOrderTag{}); };
    InOrderIterator<false> upper_bound(const T& key, InOrderTag);
    PreOrderIterator<false> upper_bound(const T& key, PreOrderTag);
    PostOrderIterator<false> upper_bound(const T& key, PostOrderTag);
    Node* upper_bound_node(const T& key);

    std::pair<InOrderIterator<false>, InOrderIterator<false>> equal_range(const T& key) { return equal_range(key, InOrderTag{}); };
    std::pair<InOrderIterator<false>, InOrderIterator<false>> equal_range(const T& key, InOrderTag);
    std::pair<PreOrderIterator<false>, PreOrderIterator<false>> equal_range(const T& key, PreOrderTag);
    std::pair<PostOrderIterator<false>, PostOrderIterator<false>> equal_range(const T& key, PostOrderTag);

    friend std::ostream& operator<<(std::ostream& out, const Node node) {
        out << (T)node.value;

        return out;
    }

 private:
    Node* root_;
    Compare compare_;
    NodeAllocator allocator_;
};

template<typename T, typename Compare, typename Allocator>
size_t BinarySearchTree<T, Compare, Allocator>::count(const T &key) {
    size_t count = 0;

    for (auto it = this->begin(); it != this->end(); ++it) {
        if (!compare_(key, *it) && !compare_(*it, key)) {
            count += 1;
        }
    }

    return count;
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::Node*
    BinarySearchTree<T, Compare, Allocator>::lower_bound_node(const T &key) {

    Node* current = root_;
    Node* last = nullptr;

    while (current != nullptr) {
        if (compare_(current->value, key)) {
            current = current->right;
        } else {
            last = current;
            current = current->left;
        }
    }

    return last;
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::Node*
    BinarySearchTree<T, Compare, Allocator>::upper_bound_node(const T &key) {

    Node* current = root_;
    Node* last = nullptr;

    while (current != nullptr) {
        if (!compare_(key, current->value)) {
            current = current->right;
        } else {
            last = current;
            current = current->left;
        }
    }

    return last;
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<false>,
          typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::equal_range(const T &key, InOrderTag) {

    return std::make_pair(lower_bound(key, in), upper_bound(key, in));
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<false>,
          typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::equal_range(const T &key, PreOrderTag) {

    return std::make_pair(lower_bound(key, pre), upper_bound(key, pre));
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<false>,
          typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::equal_range(const T &key, PostOrderTag) {

    return std::make_pair(lower_bound(key, post), upper_bound(key, post));
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::upper_bound(const T &key, InOrderTag) {

    return InOrderIterator<false>(upper_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::upper_bound(const T &key, PreOrderTag) {

    return PreOrderIterator<false>(upper_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::upper_bound(const T &key, PostOrderTag) {

    return PostOrderIterator<false>(upper_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::lower_bound(const T &key, InOrderTag) {

    return InOrderIterator<false>(lower_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::lower_bound(const T &key, PreOrderTag) {

    return PreOrderIterator<false>(lower_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::lower_bound(const T &key, PostOrderTag) {

    return PostOrderIterator<false>(lower_bound_node(key), this);
}

template<typename T, typename Compare, typename Allocator>
T BinarySearchTree<T, Compare, Allocator>::extract(const T &data) {
    T node = T();
    extract(data, root_, node);

    return node;
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::extract(const T &data, BinarySearchTree::Node* &root, T& node) {

    if (root == nullptr) {
        return;
    }

    if (compare_(data, root->value)) {
        extract(data, root->left, node);
    } else if (compare_(root->value, data)) {
        extract(data, root->right, node);
    } else {
        if (node == T()) {
            node = root->value;
        }

        if (root->left == nullptr) {
            Node* temp = root->right;
            if (temp) {
                temp->parent = root->parent;
            }

            std::allocator_traits<NodeAllocator>::destroy(allocator_, root);
            std::allocator_traits<NodeAllocator>::deallocate(allocator_, root, kOneNode);

            root = temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            if (temp) {
                temp->parent = root->parent;
            }

            std::allocator_traits<NodeAllocator>::destroy(allocator_, root);
            std::allocator_traits<NodeAllocator>::deallocate(allocator_, root, kOneNode);

            root = temp;
        } else {
            Node* min_node = root->right;
            while (min_node && min_node->left != nullptr) {
                min_node = min_node->left;
            }
            root->value = min_node->value;

            extract(min_node->value, root->right, node);
        }
    }
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::clear() {
    Destroy(this->root_);

    this->root_ = nullptr;
}

template<typename T, typename Compare, typename Allocator>
bool BinarySearchTree<T, Compare, Allocator>::contains(const T& data) {
    return this->find(data) != this->end(in);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::find(const T &data, InOrderTag) {

    Node* temp = root_;
    while (temp != this->end(in).Get()) {
        if (compare_(data, temp->value)) {
            temp = temp->left;
        } else if (compare_(temp->value, data)) {
            temp = temp->right;
        } else {
            return InOrderIterator<false>(temp, this);
        }
    }

    return this->end(in);
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::erase(const T &data) {
    erase(data, root_);
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::erase(const T& data, Node* &root) {
    if (root == nullptr) {
        return;
    }

    if (compare_(data, root->value)) {
        erase(data, root->left);
    } else if (compare_(root->value, data)) {
        erase(data, root->right);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            if (temp) {
                temp->parent = root->parent;
            }

            std::allocator_traits<NodeAllocator>::destroy(allocator_, root);
            std::allocator_traits<NodeAllocator>::deallocate(allocator_, root, kOneNode);

            root = temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            if (temp) {
                temp->parent = root->parent;
            }

            std::allocator_traits<NodeAllocator>::destroy(allocator_, root);
            std::allocator_traits<NodeAllocator>::deallocate(allocator_, root, kOneNode);

            root = temp;
        } else {
            Node* min_node = root->right;
            while (min_node && min_node->left != nullptr) {
                min_node = min_node->left;
            }
            root->value = min_node->value;

            erase(min_node->value, root->right);
        }
    }
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<false>, bool>
    BinarySearchTree<T, Compare, Allocator>::insert(const T& data, InOrderTag) {

    Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator_, kOneNode);
    std::allocator_traits<NodeAllocator>::construct(allocator_, new_node, data);

    if (root_ == nullptr) {
        root_ = new_node;
    } else {
        Node* temp = root_;
        Node* parent = nullptr;

        while (temp != nullptr) {
            parent = temp;

            if (compare_(data, temp->value)) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        new_node->parent = parent;

        if (compare_(data, parent->value)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    return std::make_pair(InOrderIterator<false>(new_node, this), true);
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<false>, bool>
    BinarySearchTree<T, Compare, Allocator>::insert(const T& data, PreOrderTag) {

    Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator_, kOneNode);
    std::allocator_traits<NodeAllocator>::construct(allocator_, new_node, data);

    if (root_ == nullptr) {
        root_ = new_node;
    } else {
        Node* temp = root_;
        Node* parent = nullptr;

        while (temp != nullptr) {
            parent = temp;

            if (compare_(data, temp->value)) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        new_node->parent = parent;

        if (compare_(data, parent->value)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    return std::make_pair(PreOrderIterator<false>(new_node, this), true);
}

template<typename T, typename Compare, typename Allocator>
std::pair<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<false>, bool>
    BinarySearchTree<T, Compare, Allocator>::insert(const T& data, PostOrderTag) {

    Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator_, kOneNode);
    std::allocator_traits<NodeAllocator>::construct(allocator_, new_node, data);

    if (root_ == nullptr) {
        root_ = new_node;
    } else {
        Node* temp = root_;
        Node* parent = nullptr;

        while (temp != nullptr) {
            parent = temp;

            if (compare_(data, temp->value)) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        new_node->parent = parent;

        if (compare_(data, parent->value)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

    return std::make_pair(PostOrderIterator<false>(new_node, this), true);
}

template<typename T, typename Compare, typename Allocator>
bool BinarySearchTree<T, Compare, Allocator>::empty() const {
    return (this->cbegin() == this->cend());
}

template<typename T, typename Compare, typename Allocator>
size_t BinarySearchTree<T, Compare, Allocator>::size() const {
    return (std::distance(this->cbegin(), this->cend()));
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::swap(BinarySearchTree &binary_search_tree) {
    std::swap(this->root_, binary_search_tree.root_);
    std::swap(this->allocator_, binary_search_tree.allocator_);
    std::swap(this->compare_, binary_search_tree.compare_);
}

template<typename T, typename Compare, typename Allocator>
bool BinarySearchTree<T, Compare, Allocator>::operator!=(const BinarySearchTree &binary_search_tree) {
    return !(*this == binary_search_tree);
}

template<typename T, typename Compare, typename Allocator>
bool BinarySearchTree<T, Compare, Allocator>::IsEqual(Node* first, Node* second) {
    if (first == nullptr && second == nullptr) {
        return true;
    }
    if (first == nullptr || second == nullptr) {
        return false;
    }

    return (first->value == second->value) &&
        IsEqual(first->left, second->left) &&
        IsEqual(first->right, second->right);
}

template<typename T, typename Compare, typename Allocator>
bool BinarySearchTree<T, Compare, Allocator>::operator==(const BinarySearchTree &binary_search_tree) {
    if (this->size() != binary_search_tree.size()) {
        return false;
    }

    Node* first = this->root_;
    Node* second = binary_search_tree.root_;

    return IsEqual(first, second);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::BinarySearchTree(const BinarySearchTree &binary_search_tree) {
    this->compare_ = binary_search_tree.compare_;
    this->allocator_ = binary_search_tree.allocator_;
    this->root_ = Copy(binary_search_tree.root_);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::~BinarySearchTree() {
    Destroy(this->root_);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>
&BinarySearchTree<T, Compare, Allocator>::operator=(const BinarySearchTree &binary_search_tree) {

    if (this != &binary_search_tree) {
        Destroy(this->root_);
        this->root_ = copy(binary_search_tree.root);
        this->compare_ = binary_search_tree.compare;
        this->allocator_ = binary_search_tree.allocator_;
    }

    return *this;
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::Node*
BinarySearchTree<T, Compare, Allocator>::Copy(const Node* node) {

    if (!node) {
        return nullptr;
    }

    Node* new_node = std::allocator_traits<NodeAllocator>::allocate(allocator_, kOneNode);
    std::allocator_traits<NodeAllocator>::construct(allocator_, new_node, node->value, node->parent);
    new_node->left = Copy(node->left);
    new_node->right = Copy(node->right);

    return new_node;
}

template<typename T, typename Compare, typename Allocator>
void BinarySearchTree<T, Compare, Allocator>::Destroy(Node* node) {
    if (node) {
        Destroy(node->left);
        Destroy(node->right);
        std::allocator_traits<NodeAllocator>::destroy(allocator_, node);
        std::allocator_traits<NodeAllocator>::deallocate(allocator_, node, kOneNode);
    }
}

template<typename T, typename Compare, typename Allocator>
const T &BinarySearchTree<T, Compare, Allocator>::front(InOrderTag) const {
    return *(this->cbegin(in));
}

template<typename T, typename Compare, typename Allocator>
T &BinarySearchTree<T, Compare, Allocator>::front(InOrderTag) {
    return *(this->begin(in));
}

template<typename T, typename Compare, typename Allocator>
const T &BinarySearchTree<T, Compare, Allocator>::back(InOrderTag) const {
    return *(--this->cend(in));
}

template<typename T, typename Compare, typename Allocator>
T &BinarySearchTree<T, Compare, Allocator>::back(InOrderTag) {
    return *(--this->end(in));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crend(InOrderTag) const {

    return std::reverse_iterator<InOrderIterator<true>>(cbegin(in));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crbegin(InOrderTag) const {

    return std::reverse_iterator<InOrderIterator<true>>(cend(in));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rend(InOrderTag) {

    return std::reverse_iterator<InOrderIterator<false>>(begin(in));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template InOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rbegin(InOrderTag) {

    return std::reverse_iterator<InOrderIterator<false>>(end(in));
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cend(InOrderTag) const {

    Node* rightmost = this->root_;
    while (rightmost) {
        rightmost = rightmost->right;
    }

    return InOrderIterator<true>(rightmost, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cbegin(InOrderTag) const {

    Node* leftmost = root_;
    while (leftmost) {
        if (leftmost->left == nullptr) {
            break;
        }

        leftmost = leftmost->left;
    }

    return InOrderIterator<true>(leftmost, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::end(InOrderTag) {

    Node* rightmost = this->root_;
    while (rightmost) {
        rightmost = rightmost->right;
    }

    return InOrderIterator<false>(rightmost, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::InOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::begin(InOrderTag) {

    Node* leftmost = root_;
    while (leftmost) {
        if (leftmost->left == nullptr) {
            break;
        }

        leftmost = leftmost->left;
    }

    return InOrderIterator<false>(leftmost, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::find(const T &data, PostOrderTag) {

    Node* temp = root_;
    while (temp != this->end(in).Get()) {
        if (compare_(data, temp->value)) {
            temp = temp->left;
        } else if (compare_(temp->value, data)) {
            temp = temp->right;
        } else {
            return PostOrderIterator<false>(temp, this);
        }
    }

    return this->end(post);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::find(const T &data, PreOrderTag) {

    Node* temp = root_;
    while (temp != this->end(in).Get()) {
        if (compare_(data, temp->value)) {
            temp = temp->left;
        } else if (compare_(temp->value, data)) {
            temp = temp->right;
        } else {
            return PreOrderIterator<false>(temp, this);
        }
    }

    return this->end(pre);
}

template<typename T, typename Compare, typename Allocator>
const T& BinarySearchTree<T, Compare, Allocator>::back(PostOrderTag) const {
    return *(--this->cend(post));
}

template<typename T, typename Compare, typename Allocator>
const T& BinarySearchTree<T, Compare, Allocator>::back(PreOrderTag) const {
    return *(--this->cend(pre));
}

template<typename T, typename Compare, typename Allocator>
T& BinarySearchTree<T, Compare, Allocator>::back(PostOrderTag) {
    return *(--this->end(post));
}

template<typename T, typename Compare, typename Allocator>
T& BinarySearchTree<T, Compare, Allocator>::back(PreOrderTag) {
    return *(--this->end(pre));
}

template<typename T, typename Compare, typename Allocator>
const T& BinarySearchTree<T, Compare, Allocator>::front(PostOrderTag) const {
    return *(this->cbegin(post));
}

template<typename T, typename Compare, typename Allocator>
const T& BinarySearchTree<T, Compare, Allocator>::front(PreOrderTag) const {
    return *(this->cbegin(pre));
}

template<typename T, typename Compare, typename Allocator>
T& BinarySearchTree<T, Compare, Allocator>::front(PostOrderTag) {
    return *(this->begin(post));
}

template<typename T, typename Compare, typename Allocator>
T &BinarySearchTree<T, Compare, Allocator>::front(PreOrderTag) {
    return *(this->begin(pre));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crend(PostOrderTag) const {

    return std::reverse_iterator<PostOrderIterator<true>>(cbegin(post));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crend(PreOrderTag) const {

    return std::reverse_iterator<PreOrderIterator<true>>(cbegin(pre));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crbegin(PostOrderTag) const {
    return std::reverse_iterator<PostOrderIterator<true>>(cend(post));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<true>>
    BinarySearchTree<T, Compare, Allocator>::crbegin(PreOrderTag) const {

    return std::reverse_iterator<PreOrderIterator<true>>(cend(pre));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rend(PostOrderTag) {

    return std::reverse_iterator<PostOrderIterator<false>>(begin(post));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rend(PreOrderTag) {

    return std::reverse_iterator<PreOrderIterator<false>>(begin(pre));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PostOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rbegin(PostOrderTag) {

    return std::reverse_iterator<PostOrderIterator<false>>(end(post));
}

template<typename T, typename Compare, typename Allocator>
std::reverse_iterator<typename BinarySearchTree<T, Compare, Allocator>::template PreOrderIterator<false>>
    BinarySearchTree<T, Compare, Allocator>::rbegin(PreOrderTag) {

    return std::reverse_iterator<PreOrderIterator<false>>(end(pre));
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cend(PostOrderTag) {

    auto it = cbegin(post);
    auto end = PostOrderIterator<true>(nullptr, this);
    while (it != end) {
        ++it;
    }

    return it;
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cend(PreOrderTag) {

    return PreOrderIterator<true>(nullptr, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cbegin(PostOrderTag) {

    Node* min = this->root_;
    while (min->left) {
        min = min->left;
    }

    return PostOrderIterator<true>(min, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<true>
    BinarySearchTree<T, Compare, Allocator>::cbegin(PreOrderTag) {

    return PreOrderIterator<true>(this->root_, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::end(PostOrderTag) {

    return PostOrderIterator<false>(nullptr, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::end(PreOrderTag) {

    return PreOrderIterator<false>(nullptr, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PostOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::begin(PostOrderTag) {

    Node* min = this->root_;
    while (min->left) {
        min = min->left;
    }

    return PostOrderIterator<false>(min, this);
}

template<typename T, typename Compare, typename Allocator>
BinarySearchTree<T, Compare, Allocator>::PreOrderIterator<false>
    BinarySearchTree<T, Compare, Allocator>::begin(PreOrderTag) {

    return PreOrderIterator<false>(this->root_, this);
}
