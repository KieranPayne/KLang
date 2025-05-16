#pragma once
#include "TreeNode.hpp"
namespace KLang{
    class Transpiler{
        public:
        TreeNode::Node* tree;
        std::string output;
        Transpiler();
        void GenerateCode(TreeNode::Node* tree, std::string path);
    };
}