#include<iostream>
#include<fstream>
using namespace std;


struct Data{
    int freq;
    char alpha;
    Data(){
        freq = 0;
        alpha = '\0';
    }
    Data(int f, char a){
        freq = f;
        alpha = a;
    }
    Data(int f){
        freq = f;
        alpha = '\0';
    }
    void datashow(){
        cout<<freq<<"|"<<alpha;
    }
};

struct StrData{
    int freq;
    string alpha;
    StrData(){
        freq = 0;
        alpha = '\0';
    }
    StrData(int f, string a){
        freq = f;
        alpha = a;
    }
    StrData(int f){
        freq = f;
        alpha = '\0';
    }
    void StrDatashow(){
        cout<<freq<<"|"<<alpha;
    }
};

struct Paths{
    string path;
    char alpha;
    Paths(){
        path = '\0';
        alpha = '\0';
    }
    Paths(string f, char a){
        path = f;
        alpha = a;
    }
    Paths(char f){
        path = '\0';
        alpha = f;
    }
    void Pathsshow(){
        cout<<path<<"|"<<alpha;
    }
};


struct Node{
    Data data;
    Node *left;
    Node *right;
    StrData strdata;
    Paths pathcode;

    Node(){
        data = Data();
        left = NULL;
        right = NULL;
        strdata = StrData();
    }

    Node(int f, char a){
        data.alpha = a;
        data.freq = f;
        left = NULL;
        right = NULL;
    }

    Node(int f, string a){
        strdata.alpha = a;
        strdata.freq = f;
        left = NULL;
        right = NULL;
    }

    Node(int f){
        data.alpha = '\0';
        data.freq = f;
        left = NULL;
        right = NULL;
    }

    Node(Data d){
        data =d;
        left = NULL;
        right = NULL;
    }

    Node(StrData strd){
        strdata = strd;
        left = NULL;
        right = NULL;
    }

    Node(Paths p){
        pathcode = p;
        left = NULL;
        right = NULL;
    }
    
    Node(string a, char b){
        pathcode.alpha = b;
        pathcode.path = a;
        left = NULL;
        right = NULL;
    }
    void print(){
        if(left == NULL  || right == NULL)
        cout<<data.alpha<<"|"<<data.freq<<" "<<left<<" "<<right<<endl;
        else
        cout<<data.alpha<<"|"<<data.freq<<" "<<left->data.alpha<<"|"<<left->data.freq<<" "<<right->data.alpha<<"|"<<right->data.freq<<endl;
    }
};


struct node{
    Node* data;
    node* next;
    node(){
        data = NULL;
        next = NULL;
    }
    node(Node* d){
        data = d;
        next = NULL;
    }
};

class List{
    node* head;
    public:
    List(){
        head = NULL;
    }
    List(Node*r){
        head = new node(r);
    }

    node* getHead(){
        return head;
    }
    bool isEmpty(){
        return head == NULL;
    }

    void pop_front(){
        if(isEmpty()){
            cout<<"Empty list\n";
            return;
        }
        node * temp = head;
        head = head->next;
        delete temp;
    }

    void push_back(Node* n){
        if(isEmpty()){
            head = new node(n);
            return;
        }
        node * temp = head;
        node *nn = new node(n);
        while(temp->next != NULL){
            temp = temp->next;
        }
        nn->next = temp->next;
        temp->next = nn;
    }

    void sort() {
        if (isEmpty() || head->next == NULL) {
            // List is empty or has only one element, no need to sort
            return;
        }

        bool swapped;
        node* temp;
        node* end = NULL;

        do {
            swapped = false;
            temp = head;

            while (temp->next != end) {
                if (temp->data->data.freq > temp->next->data->data.freq) {
                    // Swap nodes if they are in the wrong order
                    Node* tempData = temp->data;
                    temp->data = temp->next->data;
                    temp->next->data = tempData;
                    swapped = true;
                }

                temp = temp->next;
            }
            // The largest element is now at the end, move end pointer back
            end = temp;

        } while (swapped);
    }

    string getCode(char a){
        node * temp = head;
        while(temp != NULL){
            if(temp->data->pathcode.alpha == a){
                return temp->data->pathcode.path;
            }
            temp = temp->next;
        }
        return "";
    }
};


class Tree{
    Node* root;
    public:
    Tree(){
    root = NULL;
    }
    Tree(Node* r){
        root = r;
    }

    void show(Node* temp, int level = 0, char branch = ' ') {
    // if (temp != nullptr) {
    //     show(temp->right, level + 1, '/');
    //     for (int i = 0; i < level; i++) {
    //         cout << "    ";
    //     }
    //     cout << branch;
    //     temp->data.datashow();
    //     cout <<endl;
    //     show(temp->left, level + 1, '\\');
    // }

        if (temp == NULL){
            return;
        }

        show(temp->left);
        cout<<"root: ";
        temp->print();
        show(temp->right);
    }
    
};



Node* insert(Node*p, Node*q){
    int a = p->data.freq + q->data.freq;
    Node* nn = new Node (a);

    if (p->data.freq <= q->data.freq) {
        nn->left = p;
        nn->right = q;
    }
    else {
        nn->left = q;
        nn->right = p;
    }
    // nn->left = (p->data.freq <= q->data.freq) ? p : q;
    // nn->right = (p->data.freq > q->data.freq) ? p : q;
    return nn;
}

void findPaths(Node* root, List& paths, string currentPath = "") {
    if (root == NULL) {
        return;
    }

    // Append '0' for left child and '1' for right child
    if (root->left != NULL) {
        findPaths(root->left, paths, currentPath + "0");
    }

    // Append '1' for right child
    if (root->right != NULL) {
        findPaths(root->right, paths, currentPath + "1");
    }

    // If it's a leaf node, add the path to the list
    if (root->left == NULL && root->right == NULL) {
        // currentPath += root->data.alpha; // Append the alpha at the end
        paths.push_back(new Node(Paths(currentPath, root->data.alpha))); // Create a new node for the path and add it to the list
    }
}

string encode(string text, List& pathsList) {
    string encoded = "";

    for (char ch : text) {
        encoded += pathsList.getCode(ch);
    }

    return encoded;
}

int main(){
    //Array of characters and frequencies, initialize frequency to 0
    int size = 101;  // 95 + 6
    Data alphabets[size];
    int a = 8;   //8-13, 32
    for(int i =0; i <size; i++){
        alphabets[i].alpha = char(a);
        alphabets[i].freq = 0;
        a++;
        if(a == 13){
            a = 32;
        }
    }

    ifstream In("input.txt");
    string line;
    string text;
    int c = 0;
    while (getline(In, line)){
        if(c == 0){
        text += line ;
        }
        else{
            text += line + "\n";
        }
        c++;
    }
    cout<<"TEXT WAS : "<<text<<endl;
    In.close();
    // string Text = "go get a life";
    // string Text = "AABBAACDDD";

    // string text = "";
    // int i = 0;
    // while(Text[i] != '\0'){
    //     text += toupper(Text[i]);
    //     i++;
    // }
    // cout<<text<<endl;

    //initializing the frequency of each character wrt the text provided
    int i = 0;
    while(text[i] != '\0'){
        for(int j =0; j <size; j++){
            if(text[i] == alphabets[j].alpha){
                alphabets[j].freq++;
                break;
            }
        }
        i++;
    }

    //creating a node for each DataPoint, and storing in an array of type Node
    Node *Data_in_nodes = new Node[size];
    for(int i =0; i <size; i++){
        Data_in_nodes[i].data = alphabets[i];
        // Data_in_nodes[i].print();
    }

    //sorting the array based on the frequencies of characters in text, descending order(lowest freq char to highest freq character)
    Data temp;
    for (i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
        if (alphabets[i].freq > alphabets[j].freq) {
            temp = alphabets[i];
            alphabets[i] = alphabets[j];
            alphabets[j] = temp;
        }
        }
    }

    
    // for(int i =0; i <size; i++){
    //     cout<<alphabets[i].alpha<<" "<<alphabets[i].freq<<endl;
    // }


    // Node* root = nullptr;
    //OR
    //creating a tree structure by inserting nodes based on their hierarchy
    Node* root = new Node();
    // for (int i = 0; i < size; i++){
    //     if(alphabets[i].freq != 0){    
    //         if (i == 0){
    //             Node* p = new Node(alphabets [i]);
    //             // Node* q = new Node(alphabets [i+1]);
    //             // root = insert (p,q);
    //             root = p;
    //             // i++;
    //             continue;
    //         }
    //         Node* n = new Node(alphabets [i]);
    //         root = insert(root, n);
    //     }
    // }


   List nsList;

    // Populate the nsList with nodes for characters having non-zero frequency
    for (int i = 0; i < size; i++) {
        if (alphabets[i].freq != 0) {
            Node* n = new Node(alphabets[i]);
            nsList.push_back(n);
        }
    }

    //building tree using the nsList
    while (!nsList.isEmpty() && nsList.getHead()->next != NULL) {
        // Sort the nsList based on frequencies of nodes
        nsList.sort();

        // Extract the two nodes with the lowest frequencies
        Node* p = nsList.getHead()->data;
        nsList.pop_front();

        Node* q = nsList.getHead()->data;
        nsList.pop_front();

        // Merge the two nodes and insert the new node back into the nsList
        root = insert(p, q);
        nsList.push_back(root);
    }


    Tree T(root);
    // T.show(root);
    
    ofstream Code("codes.txt");

    //list to store paths
    List pathsList; 
    findPaths(root, pathsList);

    node* tt = pathsList.getHead();
    while (tt != NULL) {
        cout << tt->data->pathcode.path << "\t" << tt->data->pathcode.alpha << endl;
        Code << tt->data->pathcode.path << "\t" << tt->data->pathcode.alpha << endl;
        tt = tt->next;
    }
    Code.close();
    cout<<"Codes have been stored in 'codes.txt'"<<endl;

    string encoded = encode(text, pathsList);
    cout << "Encoded Text: " << encoded << endl;

    ofstream Out("output.txt");
    Out<<encoded<<endl;
    Out.close();
    cout<<"Encoded Text has been stored in 'output.txt'"<<endl;



}