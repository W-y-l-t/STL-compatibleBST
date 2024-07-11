add_library(StlBstContainer
            BinarySearchTree.hpp
            InOrderIterator.hpp
            PreOrderIterator.hpp
            PostOrderIterator.hpp
)

set_target_properties(StlBstContainer PROPERTIES LINKER_LANGUAGE CXX)