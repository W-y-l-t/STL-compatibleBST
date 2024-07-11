#include "BinarySearchTree.hpp"

template <typename T, typename Compare, typename Allocator>
template <bool IsConst>
class BinarySearchTree<T, Compare, Allocator>::PreOrderIterator {
 public:

    using size_type	                     = size_t;
    using key_compare	                 = Compare;
    using allocator_type                 = Allocator;
    using node_type                      = Node;
    using iterator_category              = std::bidirectional_iterator_tag;
    using difference_type                = std::ptrdiff_t;
    using value_type                     = node_type;
    using pointer                        = node_type*;
    using reference                      = node_type&;
    using conditional_pointer            = std::conditional_t<IsConst, const pointer, pointer>;
    using conditional_reference          = std::conditional_t<IsConst, const T&, T&>;
    using conditional_binary_search_tree = std::conditional_t<IsConst, const BinarySearchTree<T>*, BinarySearchTree<T>*>;

    PreOrderIterator() = delete;
    PreOrderIterator(conditional_pointer ptr, conditional_binary_search_tree bst) :
        ptr_(ptr), bst_(bst) {}
    explicit PreOrderIterator(BinarySearchTree<T, std::less<T>, std::allocator<T>>::Node* pre_order_iterator) :
        ptr_(pre_order_iterator) {}
    PreOrderIterator(const PreOrderIterator& pre_order_iterator) {
        this->ptr_ = pre_order_iterator.ptr_;
        this->bst_ = pre_order_iterator.bst_;
    };

    PreOrderIterator operator++(int32_t) {
        PreOrderIterator temp = *this;
        ++(*this);

        return temp;
    }

    PreOrderIterator& operator++() {
        Node* max = this->bst_->root_;
        while (max->right != nullptr) {
            max = max->right;
        }

        if (max == ptr_) {
            ptr_ = nullptr;

            return *this;
        }

        if (ptr_->left != nullptr) {
            ptr_ = ptr_->left;
        } else if (ptr_->right != nullptr) {
            ptr_ = ptr_->right;
        } else {
            while (ptr_->parent->right == ptr_) {
                ptr_ = ptr_->parent;
            }
            while (ptr_->parent == nullptr || ptr_->parent->left == ptr_) {
                ptr_ = ptr_->parent;
                if (ptr_->parent == nullptr || ptr_->parent->right != nullptr) {
                    ptr_ = ptr_->right;
                    break;
                }
            }
        }

        return *this;
    }

    PreOrderIterator operator--(int32_t) {
        PreOrderIterator temp = *this;
        --(*this);

        return temp;
    }

    PreOrderIterator& operator--() {
        if (ptr_ == nullptr) {
            Node* max = bst_->root_;
            while (max->right) {
                max = max->right;
            }

            ptr_ = max;

            return *this;
        }

        if (ptr_ == ptr_->parent->right && ptr_->parent->left) {
            pointer node = ptr_->parent->left;

            while (node) {
                ptr_ = node;
                if (node->right) {
                    node = node->right;
                } else if (node->left) {
                    node = node->left;
                } else {
                    break;
                }
            }
        } else {
            ptr_ = ptr_->parent;
        }

        return *this;
    }

    conditional_pointer operator->() {
        return ptr_;
    }
    conditional_reference operator*() {
        return (*ptr_).value;
    }

    bool operator<(const PreOrderIterator& pre_order_iterator) const {
        auto temp = *this;
        while (temp != this->bst_->end(pre) &&
            temp != pre_order_iterator) {
            std::cout << *temp << " ";
            ++temp;
        }

        return temp == pre_order_iterator;
    }

    bool operator >=(const PreOrderIterator& pre_order_iterator) const {
        return !(*this < pre_order_iterator);
    }

    bool operator>(const PreOrderIterator& pre_order_iterator) const {
        return (pre_order_iterator < *this);
    }

    bool operator<=(const PreOrderIterator& pre_order_iterator) const {
        return !(*this > pre_order_iterator);
    }

    bool operator==(const PreOrderIterator& pre_order_iterator) const {
        return (ptr_ == pre_order_iterator.ptr_ &&
                bst_ == pre_order_iterator.bst_);
    }

    bool operator!=(const PreOrderIterator& pre_order_iterator) const {
        return !(*this == pre_order_iterator);
    }

    void swap(PreOrderIterator& pre_order_iterator) {
        std::swap(ptr_, pre_order_iterator.ptr_);
        std::swap(bst_, pre_order_iterator.bst_);
    }

    difference_type operator-(const PreOrderIterator& other) const {
        auto temp = *this;
        difference_type cnt = 0;

        while (temp != this->bst_->end(pre) &&
            temp != other) {

            ++temp;
            cnt += 1;
        }

        if (temp == other) {
            return (-cnt);
        } else {
            return -(other - *this);
        }
    }

    pointer Get() {
        return ptr_;
    }

 private:
    pointer ptr_;
    conditional_binary_search_tree bst_;
};