#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

int postfixEvaluation(string s){
	stack<int> st;
	for(int i=0; i<s.length(); i++){
		
// condition for checking if a character is an operand
		if(isdigit(s[i])){
			st.push(s[i]-'0');   //int main convert karne k liye 0 ki asii value minus karado
		}
		//jab opeartor ho
		else{
			int op2 = st.top();   //stack k top ko op2 main save karwaya 
			st.pop();             //phr usy pop karwaya
			int op1 = st.top();
			st.pop();
			
//			operation karne k liye switch case 
			switch (s[i]){
				case '+':
					st.push(op1+op2);
					break;
				case '-':
					st.push(op1-op2);
					break;
				case '*':
					st.push(op1*op2);
					break;
				case '/':
					st.push(op1/op2);
					break;
				case '^':
					st.push(pow(op1, op2));  //power function import library math.h
					break;
			}
		}
	}
	return st.top();        // jo value bacg gayi loop k bad woh return
}

int main(){
	cout<<postfixEvaluation("46+2/5*7+")<<endl;
	return 0;
}
