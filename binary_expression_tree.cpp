#include <iostream>
#include <stack>
#include <cctype>                  //char or str k sath kam karne main use hoti

using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;


//constructor define Node
    Node(char val) : data(val), left(NULL), right(NULL) {}
};

class ExpressionTree {
public:
    Node* root;

//constructor of the expression tree
    ExpressionTree() : root(NULL) {}
//checking the given operator perform. If yes ? return true else false
    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

//checking precedence
    int OperatorPrecedence(char oper) {
        if (oper == '+' || oper == '-') {
            return 1;
        } else if (oper == '*' || oper == '/') {
            return 2;
        } else {
            return -1;
        }
    }

    bool isOperand(char ch) {             // isalnum jab tak true hai jab tak alphanumeric ya numeric value pass ho rahi warna false 
        return isalnum(ch);               //isalnum  library function hai jo character ki classification karta hai kk woh numeric hai ya alphabetic
    }

    Node* BuildExpressionTree(const string& postfixExp) {
        stack<Node*> st;                 //create stack

        for (char currChar : postfixExp) {   //range-base-loop ka use kar k currChar ko pori potfixExp main iterate karwana
            if (isOperand(currChar)) {
                Node* treeNode = new Node(currChar);   //agar koi numeric ya alphabetic value pass ho jati currChar main  to usy new node main bana kar stack main push karwa detay 
                st.push(treeNode);                     //reason yeh hai k bad main track karne main kaam aye ga 
            } else if (isOperator(currChar)) {
                Node* treeNode = new Node(currChar);   //creating var
                treeNode->right = st.top();            //tree k right node pr stack ki jo last vaklue enter hoi (top value) woh nikalni hai
                st.pop();                              //or phr usy remove karwa dena
                treeNode->left = st.top();  
                st.pop();
                st.push(treeNode);    //phr trenode ko hi stacjk main push kia jo ab left or right chil k sath araha  yeh loop chalta rahy ga or expression tree build hoti rahy gi        
            } //matlab operand ki value ek stack main ja kar save ho rahi lkn jese hi koi operator ajata to woh pehli pop value ko tree k right pe shift karta or or dosri pop ko tree k left pe push kardeta 
        }     //eg: ab+  agaya to b right side pe or a left side pe 
        return st.top();             //loop se bahar akar top(last stack value tree node ki jo hogi woh return kardo)
    }

    void PrintInOrder(Node* node) {
        if (node != NULL) {
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
    getline(cin, infix);   // input le kar infix main store kardeta getline function

    ExpressionTree tree;  // Create an ExpressionTree object

    stack<Node*> st;
    int len = infix.length();
    string postfixExp;

    for (int i = 0; i < len; i++) {
        char currChar = infix[i];
        if (tree.isOperand(currChar)) {  // Call isOperand from the ExpressionTree object
            postfixExp += currChar;      //operand mil jaye to usy postfix main add kia jaye 
        } else if (currChar == '(') {    //agar openeing paranthesis ajaye expression main to usy stack main push kardia jaye or closing mily to pop karden stack se
            st.push(new Node(currChar));
        } else if (currChar == ')') {
            while (!st.empty() && st.top()->data != '(') {    //jab tak yeh stack empty na ho or or top me ( yeh na ajaye to loop chalta rahy ga 
                postfixExp += st.top()->data;                  //top elements ko postfix expression  mai push kardete 
                st.pop();                                     // or wahan se stack remove kardete
            }
            if (!st.empty() && st.top()->data == '(') {       // ) isy stack main search karne tak ( isy stack se nikalna zaruri hai
                st.pop();
            }
        } else if (tree.isOperator(currChar)) {  // Call isOperator from the ExpressionTree object
            while (!st.empty() && tree.OperatorPrecedence(st.top()->data) >= tree.OperatorPrecedence(currChar)) {     //checking top operator precedence
                postfixExp += st.top()->data;                 // bara hai to usy postfix main daldo or pop karwa do stack se
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


