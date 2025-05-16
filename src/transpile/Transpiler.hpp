#pragma once
#include "../TreeNode.hpp"
namespace KLang{
    class Transpiler{
        public:
        TreeNode::Node* tree;
        Transpiler();
        void AddIndent(std::string& str, int level);
        void GenerateCode(TreeNode::Node* tree, std::string path);
        std::string TranspileStatement(TreeNode::Node* statement);
    };
}