#include <bits/stdc++.h>

using namespace std;


class Node{
    private:
        char ch;
        Node* left;
        Node* right;

    public:
        Node(char ch_){
            ch = ch_;
            left = NULL;
            right = NULL;
        }

    friend class Tree;
};



class Tree{
    private:
        Node* root;
    public:
        Tree(){
            root = new Node(',');
        }


        void build(string &newwick){
            
        }

        void addNode(char& c, string& Encode){
            Node* cur = root;

            for(auto& x : Encode){
                if(x == '1'){
                    if(cur -> right != NULL){
                        cur = cur -> right;
                    }
                    else{
                        cur -> right = new Node(',');
                        cur = cur -> right;
                    }
                }

                else{
                    if(cur -> left != NULL){
                        cur = cur -> left;
                    }
                    else{
                        cur -> left = new Node(',');
                        cur = cur -> left;
                    }
                }
            }

            cur->ch = c;
        }


        string inorderTraversal(Node* root){
            if(root->left == NULL and root->right == NULL){
                string str(1,root->ch);
                return str;
            }

            string left = inorderTraversal(root->left);
            string middle(1, root->ch);
            string right = inorderTraversal(root->right);
            return '(' + left + middle + right + ')';
        }

        string inorderTraversal(){
            return inorderTraversal(root);
        }
};



int main(){
    string command;
    cin >> command;

    if(command == "DeriveHuffmanTree"){
        int N;
        cin >> N;

        Tree huffmannTree;
        for(int i = 0 ; i < N ; i++){
            char c;
            string s;
            cin >> c >> s;
            huffmannTree.addNode(c, s);
        }

        string Quit;
        cin >> Quit;
        cout << huffmannTree.inorderTraversal() << ";" << endl;

    }
    else if(command == "DecodeMessage"){
        string newwick;
        cin >> newwick;

        Tree huffmannTree;
        huffmannTree.build(newwick);

        string encode;
        cin >> encode;

        string Quit;
        cin >> Quit;

        Tree huffmann;                          

    }

    return 0;
}