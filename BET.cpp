#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
public:
    Node* root;

    ExpressionTree() : root(nullptr) {}

    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    int OperatorPrecedence(char oper) {
        if (oper == '+' || oper == '-') {
            return 1;
        } else if (oper == '*' || oper == '/') {
            return 2;
        } else {
            return -1;
        }
    }

    bool isOperand(char ch) {
        return isalnum(ch);
    }

    Node* BuildExpressionTree(const string& postfixExp) {
        stack<Node*> st;
//sari values stack pe ja rahi hotin phr check karty hain k agar operator agaay to us main se pehlay pop ki gayi value right pe ja rahi hoti or dosri left main 
        for (char currChar : postfixExp) {
            if (isOperand(currChar)) {
                st.push(new Node(currChar));
            } else if (isOperator(currChar)) {
                Node* treeNode = new Node(currChar);
                treeNode->right = st.top();
                st.pop();
                treeNode->left = st.top();
                st.pop();
                st.push(treeNode);
            }
        }
        return st.top();
    }

    void PrintInOrder(Node* node) {
        if (node != nullptr) {
            PrintInOrder(node->left);
            cout << node->data << ' ';
            PrintInOrder(node->right);
        }
    }
};

int main() {
    string infix;
    string postfix;

    cout << "Enter the Infix Expression (with spaces): ";
    getline(cin, infix);

    ExpressionTree tree;  // Create an ExpressionTree object

    stack<Node*> st;
    int len = infix.length();
    string postfixExp;

    for (int i = 0; i < len; i++) {
        char currChar = infix[i];
        if (tree.isOperand(currChar)) {  // Call isOperand from the ExpressionTree object
            postfixExp += currChar;
        } else if (currChar == '(') {
            st.push(new Node(currChar));
        } else if (currChar == ')') {
            while (!st.empty() && st.top()->data != '(') {
                postfixExp += st.top()->data;
                st.pop();
            }
            if (!st.empty() && st.top()->data == '(') {
                st.pop();
            }
        } else if (tree.isOperator(currChar)) {  // Call isOperator from the ExpressionTree object
            while (!st.empty() && tree.OperatorPrecedence(st.top()->data) >= tree.OperatorPrecedence(currChar)) {
                postfixExp += st.top()->data;
                st.pop();
            }
            st.push(new Node(currChar));
        }
    }

    while (!st.empty()) {
        postfixExp += st.top()->data;
        st.pop();
    }

    cout << "PostFix Expression: " << postfixExp << endl;

    tree.root = tree.BuildExpressionTree(postfixExp);

    cout << "In-Order Traversal of the Expression Tree: ";
    tree.PrintInOrder(tree.root);

    return 0;
}

