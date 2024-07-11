#include "BinarySearchTree.hpp"
#include <stack>

template <typename T, typename Compare, typename Allocator>
template <bool IsConst>
class BinarySearchTree<T, Compare, Allocator>::PostOrderIterator {
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

    PostOrderIterator() = delete;
    PostOrderIterator(conditional_pointer ptr, conditional_binary_search_tree bst) :
        ptr_(ptr), bst_(bst) {}
    explicit PostOrderIterator(BinarySearchTree<T, std::less<T>, std::allocator<T>>::Node* post_order_iterator) :
        ptr_(post_order_iterator) {}
    PostOrderIterator(const PostOrderIterator& post_order_iterator) {
        this->ptr_ = post_order_iterator.ptr_;
        this->bst_ = post_order_iterator.bst_;
    };

    PostOrderIterator operator++(int32_t) {
        PostOrderIterator temp = *this;
        ++(*this);

        return temp;
    }

    PostOrderIterator& operator++() {
        if (ptr_->parent == nullptr) {
            ptr_ = nullptr;

            return *this;
        }

        if (ptr_ == ptr_->parent->left && ptr_->parent->right) {
            pointer node = ptr_->parent->right;

            while (node) {
                ptr_ = node;
                if (node->left) {
                    node = node->left;
                } else if (node->right) {
                    node = node->right;
                } else {
                    break;
                }
            }
        } else {
            ptr_ = ptr_->parent;
        }

        return *this;
    }

    PostOrderIterator operator--(int32_t) {
        auto temp = *this;
        --(*this);

        return temp;
    }

    PostOrderIterator& operator--() {
        if (ptr_ == nullptr) {
            ptr_ = this->bst_->root_;

            return *this;
        }

        if (ptr_->right != nullptr) {
            ptr_ = ptr_->right;
        } else if (ptr_->left != nullptr) {
            ptr_ = ptr_->left;
        } else {
            while (ptr_->parent->left == ptr_) {
                ptr_ = ptr_->parent;
            }
            while (ptr_->parent == nullptr || ptr_->parent->right == ptr_) {
                ptr_ = ptr_->parent;
                if (ptr_->parent == nullptr || ptr_->parent->left != nullptr) {
                    ptr_ = ptr_->left;
                    break;
                }
            }
        }

        return *this;
    }

    conditional_pointer operator->() {
        return ptr_;
    }
    conditional_reference operator*() {
        return (*ptr_).value;
    }

    bool operator<(const PostOrderIterator& post_order_iterator) const {
        auto temp = *this;
        while (temp != this->bst_->end(post) &&
            temp != post_order_iterator) {

            ++temp;
        }

        return temp == post_order_iterator;
    }

    bool operator >=(const PostOrderIterator& post_order_iterator) const {
        return !(*this < post_order_iterator);
    }

    bool operator>(const PostOrderIterator& post_order_iterator) const {
        return (post_order_iterator < *this);
    }

    bool operator<=(const PostOrderIterator& post_order_iterator) const {
        return !(*this > post_order_iterator);
    }

    bool operator==(const PostOrderIterator& post_order_iterator) const {
        return (ptr_ == post_order_iterator.ptr_ &&
                bst_ == post_order_iterator.bst_);
    }

    bool operator!=(const PostOrderIterator& post_order_iterator) const {
        return !(*this == post_order_iterator);
    }

    void swap(PostOrderIterator& post_order_iterator) {
        std::swap(ptr_, post_order_iterator.ptr_);
        std::swap(bst_, post_order_iterator.bst_);
    }

    difference_type operator-(const PostOrderIterator& other) const {
        auto temp = *this;
        difference_type cnt = 0;

        while (temp != this->bst_->end(post) &&
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

    pointer GetPointer() {
        return ptr_;
    }


 private:
    pointer ptr_;
    conditional_binary_search_tree bst_;
};