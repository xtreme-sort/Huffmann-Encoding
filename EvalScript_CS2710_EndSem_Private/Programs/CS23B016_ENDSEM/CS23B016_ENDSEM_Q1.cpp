#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

class Node{
    private:
        char ch;
        int freq;
        Node* left;
        Node* right;
        int time;
    public:
        Node(char ch_, int freq_, int time_){
            ch = ch_;
            freq = freq_;
            time = time_;
            left = NULL;
            right = NULL;
        }

    friend class Comparator;
    friend class HuffmannEncoding;
    friend class Tree;
};


class Tree{
    private:
        Node* root;

    public:
        Tree(Node* root_ = NULL){
            root = root_;
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



class Comparator{
    public:
        bool operator () (Node* a, Node* b){
            if(a->freq == b->freq){
                return a->time > b->time;
            }   
            else return a->freq > b->freq;
        }
};


class HuffmannEncoding{
    private:
        string inp;
        map<char, int> frequencyTable;
        Tree HuffmannTree;
        string newwickFormat;

    public:
        HuffmannEncoding(string& inp_){
            buildFrequencyTable(inp_);
        }

        HuffmannEncoding(map<char,int>& frequencyTable_){
            frequencyTable = frequencyTable_;
            HuffmannTree = buildTreeFromFrequencyTable(frequencyTable);
            newwickFormat = buildNewwickFormat(HuffmannTree);
        }

        void buildFrequencyTable(string& s){
            for(auto& x : s){
                frequencyTable[x]++;
            }
        }

        Tree buildTreeFromFrequencyTable(map<char,int>& frequencyTable){
            priority_queue<Node*,vector<Node*>, Comparator> pq;

            int time = 0;
            for(auto x : frequencyTable){
                time++;
                pq.push(new Node(x.first, x.second, time));
            }
            
            while(pq.size() > 1){
                Node* node_1 = pq.top();
                pq.pop();
                Node* node_2 = pq.top();
                pq.pop();

                int freq_1 = node_1->freq;
                int freq_2 = node_2->freq;

                time++;
                Node* new_node = new Node(',', freq_1 + freq_2, time);
                new_node->left = node_1;
                new_node->right = node_2;
                pq.push(new_node);
            }

            Node* root = pq.top();
            Tree HuffmannTree(root);
            return HuffmannTree;
        }

        string buildNewwickFormat(Tree& HuffamnnTree){
            return HuffamnnTree.inorderTraversal();
        }

        map<char,int>& getFrequencyTable(){
            return frequencyTable;
        }


        string& getNewwickFormat(){
            return newwickFormat;
        }

};


int main(){
    string command;
    cin >> command;

    if(command == "BuildFrequencyTable"){
        string inp;
        cin >> inp;
        
        string Quit;
        cin >> Quit;

        HuffmannEncoding huffmannEncoding(inp);
        map<char,int>& FrequencyTable = huffmannEncoding.getFrequencyTable();

        for(auto& x : FrequencyTable){
            cout << x.first << " " << x.second << endl;
        }

    }
    else if(command == "BuildTreeFromFrequencyTable"){
        int N;
        cin >> N;

        map<char, int> FrequencyTable;
        while(N--){
            char c;
            int x;
            cin >> c >> x;
            FrequencyTable[c] = x;
        }

        string Quit;
        cin >> Quit;

        HuffmannEncoding huffmannEncoding(FrequencyTable);
        
        cout << huffmannEncoding.getNewwickFormat() << ";" << endl;
    }
    
    return 0;
}