add_executable(${PROJECT_NAME}
                main.cpp
        ../lib/BinarySearchTree.hpp
                ../lib/InOrderIterator.hpp
                ../lib/PreOrderIterator.hpp
                ../lib/PostOrderIterator.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE StlBstContainer)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})