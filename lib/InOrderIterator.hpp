#include "BinarySearchTree.hpp"

template <typename T, typename Compare, typename Allocator>
template <bool IsConst>
class BinarySearchTree<T, Compare, Allocator>::InOrderIterator {
 public:
    using size_type	                     = size_t;
    using node_type                      = Node;
    using iterator_category              = std::bidirectional_iterator_tag;
    using difference_type                = std::ptrdiff_t;
    using value_type                     = node_type;
    using pointer                        = node_type*;
    using reference                      = node_type&;
    using conditional_pointer            = std::conditional_t<IsConst, const pointer, pointer>;
    using conditional_reference          = std::conditional_t<IsConst, const T&, T&>;
    using conditional_binary_search_tree = std::conditional_t<IsConst, const BinarySearchTree<T>*, BinarySearchTree<T>*>;

    InOrderIterator() = delete;
    InOrderIterator(conditional_pointer ptr, conditional_binary_search_tree bst) :
        ptr_(ptr), bst_(bst) {}
    explicit InOrderIterator(BinarySearchTree<T, std::less<T>, std::allocator<T>>::Node* in_order_iterator) :
                ptr_(in_order_iterator) {}
    InOrderIterator(const InOrderIterator& in_order_iterator) {
        this->ptr_ = in_order_iterator.ptr_;
        this->bst_ = in_order_iterator.bst_;
    };

    InOrderIterator operator++(int32_t) {
        InOrderIterator temp = *this;
        ++(*this);

        return temp;
    }

    InOrderIterator& operator++() {
        if (this->ptr_->right) {
            this->ptr_ = this->ptr_->right;

            while (this->ptr_->left) {
                this->ptr_ = this->ptr_->left;
            }
        } else {
            while (this->ptr_->parent && this->ptr_ == this->ptr_->parent->right) {
                this->ptr_ = this->ptr_->parent;
            }

            this->ptr_ = this->ptr_->parent;
        }

        return *this;
    }

    InOrderIterator operator--(int32_t) {
        InOrderIterator temp = *this;
        --(*this);

        return temp;
    }

    InOrderIterator& operator--() {
        if (this->ptr_ == nullptr) {
            Node* temp = this->bst_->root_;
            while (temp && temp->right) {
                temp = temp->right;
            }

            this->ptr_ = temp;

            return *this;
        }

        if (this->ptr_->left) {
            this->ptr_ = this->ptr_->left;

            while (this->ptr_->right) {
                this->ptr_ = this->ptr_->right;
            }
        } else {
            while (this->ptr_->parent && this->ptr_ == this->ptr_->parent->left) {
                this->ptr_ = this->ptr_->parent;
            }

            this->ptr_ = this->ptr_->parent;
        }

        return *this;
    }

    conditional_pointer operator->() {
        return ptr_;
    }
    conditional_reference operator*() {
        return (*ptr_).value;
    }

    bool operator<(const InOrderIterator& in_order_iterator) const {
        auto temp = *this;
        while (temp != this->bst_->end(in) &&
               temp != in_order_iterator) {

            ++temp;
        }

        return temp == in_order_iterator;
    }

    bool operator>=(const InOrderIterator& in_order_iterator) const {
        return !(*this < in_order_iterator);
    }

    bool operator>(const InOrderIterator& in_order_iterator) const {
        return (in_order_iterator < *this);
    }

    bool operator<=(const InOrderIterator& in_order_iterator) const {
        return !(*this > in_order_iterator);
    }

    bool operator==(const InOrderIterator& in_order_iterator) const {
        return (ptr_ == in_order_iterator.ptr_ && bst_ == in_order_iterator.bst_);
    }

    bool operator!=(const InOrderIterator& in_order_iterator) const {
        return !(*this == in_order_iterator);
    }

    void swap(InOrderIterator& in_order_iterator) {
        std::swap(ptr_, in_order_iterator.ptr_);
        std::swap(bst_, in_order_iterator.bst_);
    }

    difference_type operator-(const InOrderIterator& other) const {
        auto temp = *this;
        difference_type cnt = 0;

        while (temp != this->bst_->end() &&
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