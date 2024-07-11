#include <gtest/gtest.h>

#include "../lib/BinarySearchTree.hpp"
#include "../lib/InOrderIterator.hpp"
#include "../lib/PreOrderIterator.hpp"
#include "../lib/PostOrderIterator.hpp"



TEST(InOrderIteratorTestSuite, ForwardIterator) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    BinarySearchTree<char>::InOrderIterator<false> it = bst.begin();

    ASSERT_TRUE(std::find(bst.begin(), bst.end(), 'e') != bst.end());

    std::string result;
    while (it != bst.end()) {
        result += *it;
        ++it;
    }

    ASSERT_EQ(result, "adefoqr");
}

TEST(InOrderIteratorTestSuite, BackwardIterator) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    BinarySearchTree<char>::InOrderIterator<false> it = bst.end();

    std::string result;
    while (it != bst.begin()) {
        --it;
        result += *it;
    }

    ASSERT_EQ(result, "rqofeda");
}

TEST(InOrderIteratorTestSuite, ConstForwardIterator) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    BinarySearchTree<char>::InOrderIterator<true> it = bst.cbegin();

    std::string result;
    while (it != bst.cend()) {
        result += *(it++);
    }

    ASSERT_EQ(result, "adefoqr");
}

TEST(InOrderIteratorTestSuite, ConstBackwardIterator) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    BinarySearchTree<char>::InOrderIterator<true> it = bst.cend();

    std::string result;
    while (it != bst.cbegin()) {
        --it;
        result += *it;
    }

    ASSERT_EQ(result, "rqofeda");
}

TEST(InOrderIteratorTestSuite, ReverseIterator) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    auto it = bst.rbegin();

    std::string result;
    while (it != bst.rend()) {
        result += *it;
        ++it;
    }

    ASSERT_EQ(result, "rqofeda");
}

TEST(InOrderIteratorTestSuite, OtherMethods1) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    auto it = bst.begin();

    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*(it++), 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*(++it), 'e');
    ASSERT_EQ(*it, 'e');
    ASSERT_EQ(*(it--), 'e');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*(--it), 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(*it++, 'a');
    ASSERT_EQ(*it, 'd');
    ASSERT_EQ(*it--, 'd');
    ASSERT_EQ(*it, 'a');
}

TEST(InOrderIteratorTestSuite, OtherMethods2) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    auto it1 = bst.begin();
    auto it2 = bst.begin();

    it2++;
    ASSERT_TRUE(it1 < it2);

    ++it1;
    ++it1;
    ASSERT_TRUE(it1 >= it2);

    it1++;
    ASSERT_TRUE((it1 - it2) == 2);
    ASSERT_TRUE((it2 - it1) == -2);
}

TEST(InOrderIteratorTestSuite, OtherMethods3) {
    BinarySearchTree<char> bst;

    bst.insert('e');
    bst.insert('o');
    bst.insert('r');
    bst.insert('q');
    bst.insert('d');
    bst.insert('a');
    bst.insert('f');

    ASSERT_TRUE(bst.find('a') != bst.end());
    ASSERT_TRUE(*bst.find('e') == 'e');
    ASSERT_TRUE(bst.find('x') == bst.end());

    ASSERT_TRUE(bst.size() == 7);
    ASSERT_TRUE(!bst.empty());

    bst.erase('r');
    bst.erase('d');

    ASSERT_TRUE(bst.size() == 5);
    ASSERT_TRUE(bst.find('d') == bst.end());

    ASSERT_EQ(bst.front(), 'a');
    ASSERT_EQ(bst.back(), 'q');
}

TEST(PreOrderIteratorTestSuite, ForwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.begin(PreOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90};

    while (it != bst.end(PreOrderTag{})) {
        result.push_back(*it);
        ++it;
    }

    ASSERT_EQ(result, predict);
}

TEST(PreOrderIteratorTestSuite, BackwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.end(PreOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {90, 66, 70, 44, 31, 35, 50, 24, 18, 22, 12, 4, 10, 15, 25};

    while (it != bst.begin(PreOrderTag{})) {
        --it;
        result.push_back(*it);
    }

    ASSERT_EQ(result, predict);
}

TEST(PreOrderIteratorTestSuite, ConstForwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.cbegin(PreOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90};

    while (it != bst.cend(PreOrderTag{})) {
        result.push_back(*it);
        ++it;
    }

    ASSERT_EQ(result, predict);
}

TEST(PreOrderIteratorTestSuite, ConstBackwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.cend(PreOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {90, 66, 70, 44, 31, 35, 50, 24, 18, 22, 12, 4, 10, 15, 25};

    while (it != bst.cbegin(PreOrderTag{})) {
        --it;
        result.push_back(*it);
    }

    ASSERT_EQ(result, predict);
}

TEST(PreOrderIteratorTestSuite, ReverseIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.rbegin(PreOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {90, 66, 70, 44, 31, 35, 50, 24, 18, 22, 12, 4, 10, 15, 25};

    while (it != bst.rend(PreOrderTag{})) {
        result.push_back(*it);
        ++it;
    }

    ASSERT_EQ(result, predict);
}

TEST(PreOrderIteratorTestSuite, OtherMethods1) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.begin(PreOrderTag{});

    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*(it++), 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*(++it), 10);
    ASSERT_EQ(*it, 10);
    ASSERT_EQ(*(it--), 10);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*(--it), 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
    ASSERT_EQ(*it--, 15);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it, 25);
    ASSERT_EQ(*it++, 25);
    ASSERT_EQ(*it, 15);
}

TEST(PreOrderIteratorTestSuite, OtherMethods2) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it1 = bst.begin(PreOrderTag{});
    auto it2 = bst.begin(PreOrderTag{});

    it2++;
    ASSERT_TRUE(it1 < it2);

    ++it1;
    ++it1;
    ASSERT_TRUE(it1 >= it2);

    it1++;
    ASSERT_TRUE((it1 - it2) == 2);
    ASSERT_TRUE((it2 - it1) == -2);
}

TEST(PreOrderIteratorTestSuite, OtherMethods3) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    ASSERT_TRUE(bst.find(4, PreOrderTag{}) != bst.end(PreOrderTag{}));
    ASSERT_TRUE(*bst.find(25, PreOrderTag{}) == 25);
    ASSERT_TRUE(bst.find(100, PreOrderTag{}) == bst.end(PreOrderTag{}));

    ASSERT_TRUE(bst.size() == 15);
    ASSERT_TRUE(!bst.empty());

    bst.erase(15);
    bst.erase(25);

    ASSERT_TRUE(bst.size() == 13);
    ASSERT_TRUE(bst.find(25, PreOrderTag{}) == bst.end(PreOrderTag{}));

    ASSERT_EQ(bst.front(PreOrderTag{}), 31);

    ASSERT_EQ(bst.back(PreOrderTag{}), 90);

    ASSERT_TRUE(bst.contains(31));

    bst.clear();
    ASSERT_TRUE(bst.empty());
}

TEST(PostOrderIteratorTestSuite, ForwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.begin(PostOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {4, 12, 10, 18, 24, 22, 15, 31, 44, 35, 66, 90, 70, 50, 25};

    while (it != bst.end(PostOrderTag{})) {
        result.push_back(*it);
        ++it;
    }

    ASSERT_EQ(result, predict);
}

TEST(PostOrderIteratorTestSuite, BackwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.end(PostOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {25, 50, 70, 90, 66, 35, 44, 31, 15, 22, 24, 18, 10, 12, 4};

    while (it != bst.begin(PostOrderTag{})) {
        --it;
        result.push_back(*it);
    }

    ASSERT_EQ(result, predict);
}

TEST(PostOrderIteratorTestSuite, ConstForwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.cbegin(PostOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {4, 12, 10, 18, 24, 22, 15, 31, 44, 35, 66, 90, 70, 50, 25};

    while (it != bst.cend(PostOrderTag{})) {
        result.push_back(*it);
        ++it;
    }

    ASSERT_EQ(result, predict);
}

TEST(PostOrderIteratorTestSuite, ConstBackwardIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.cend(PostOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {25, 50, 70, 90, 66, 35, 44, 31, 15, 22, 24, 18, 10, 12, 4};

    while (it != bst.cbegin(PostOrderTag{})) {
        --it;
        result.push_back(*it);
    }

    ASSERT_EQ(result, predict);
}

TEST(PostOrderIteratorTestSuite, ReverseIterator) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.rbegin(PostOrderTag{});

    std::vector<int32_t> result;
    std::vector<int32_t> predict = {25, 50, 70, 90, 66, 35, 44, 31, 15, 22, 24, 18, 10, 12, 4};

    while (it != bst.rend(PostOrderTag{})) {
        result.push_back(*it);
        it++;
    }

    ASSERT_EQ(result, predict);
}

TEST(PostOrderIteratorTestSuite, OtherMethods1) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it = bst.begin(PostOrderTag{});

    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*(it++), 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*(++it), 10);
    ASSERT_EQ(*it, 10);
    ASSERT_EQ(*(it--), 10);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*(--it), 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
    ASSERT_EQ(*it--, 12);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it, 4);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it, 12);
}

TEST(PostOrderIteratorTestSuite, OtherMethods2) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    auto it1 = bst.begin(PostOrderTag{});
    auto it2 = bst.begin(PostOrderTag{});

    it2++;
    ASSERT_TRUE(it1 < it2);

    ++it1;
    ++it1;
    ASSERT_TRUE(it1 >= it2);

    it1++;
    ASSERT_TRUE((it1 - it2) == 2);
    ASSERT_TRUE((it2 - it1) == -2);
}

TEST(PostOrderIteratorTestSuite, OtherMethods3) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    ASSERT_TRUE(bst.find(4, PostOrderTag{}) != bst.end(PostOrderTag{}));
    ASSERT_TRUE(*bst.find(25, PostOrderTag{}) == 25);
    ASSERT_TRUE(bst.find(100, PostOrderTag{}) == bst.end(PostOrderTag{}));

    ASSERT_TRUE(bst.size() == 15);
    ASSERT_TRUE(!bst.empty());

    bst.erase(15);

    ASSERT_TRUE(bst.size() == 14);
    ASSERT_TRUE(bst.find(15, PostOrderTag{}) == bst.end(PostOrderTag{}));

    ASSERT_EQ(bst.front(PostOrderTag{}), 4);

    ASSERT_EQ(bst.back(PostOrderTag{}), 25);

    ASSERT_TRUE(bst.contains(31));

    bst.clear();
    ASSERT_TRUE(bst.empty());
}

TEST(BinarySearchTreeTestSuite, OtherMethods) {
    BinarySearchTree<int32_t> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(4);
    bst.insert(12);
    bst.insert(22);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);

    ASSERT_TRUE(bst.find(4) != bst.end());
    ASSERT_TRUE(*bst.find(25) == 25);
    ASSERT_TRUE(bst.find(100) == bst.end());

    ASSERT_TRUE(bst.upper_bound(25) != bst.end());
    ASSERT_EQ(bst.lower_bound(25), bst.find(25));
    ASSERT_EQ(bst.upper_bound(25), bst.find(31));

    ASSERT_EQ(bst.count(25), 1);
    ASSERT_TRUE(bst.count(100) == 0);

    BinarySearchTree<int32_t> bst_2;

    bst_2.insert(25);
    bst_2.insert(15);
    bst_2.insert(10);
    bst_2.insert(4);
    bst_2.insert(12);
    bst_2.insert(22);
    bst_2.insert(18);
    bst_2.insert(24);
    bst_2.insert(50);
    bst_2.insert(35);
    bst_2.insert(31);
    bst_2.insert(44);
    bst_2.insert(70);
    bst_2.insert(66);
    bst_2.insert(90);

    ASSERT_TRUE(bst == bst_2);

    ASSERT_TRUE(bst.extract(15) == 15);

    ASSERT_TRUE(bst != bst_2);

    ASSERT_TRUE(bst_2.extract(15) == 15);

    ASSERT_TRUE(bst == bst_2);
}
