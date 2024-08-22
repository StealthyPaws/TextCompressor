#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

struct Encoded{
    string alpha;
    string code;
    Encoded(){
        alpha = '\0';
        code = '\0';
    }
    Encoded(string alp, string c){
        alpha = alp;
        code = c;
    }

    void show(){
        cout<<code<<"\t"<<alpha<<endl;
    }
};


struct Node{
    Encoded data;
    Node*next;
    Node(){
        data = Encoded();
        next = NULL;
    }
    Node(Encoded e){
        data = e;
        next = NULL;
    }
    Node(string al, string c){
        data.alpha = al;
        data.code = c;
        next = NULL;
    }
};

class List{
    Node* head;
    public:
    int length = 0;
    List(){
        head = NULL;
    }
    List(Node* h){
        head = h;
        length++;
    }
    Node* getHead(){
        return head;
    }
    void insert(Encoded e){
        Node* n = new Node(e);
        if(head == NULL){
            head = n;
            return;
        }
        Node* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = n;
        length++;
    }

    void display(){
        Node*temp = head;
        while(temp != NULL){
            temp->data.show();
            temp = temp->next;
        }

    }
};

string read_file(string filename){
    ifstream In(filename);
    string line;
    string text;
    // int c = 0;
    while (getline(In, line)){
        text += line + "\n";
    }
    // cout<<"TEXT WAS : "<<text<<endl;
    In.close();
    return text;
}

bool inCodes(string chars, Encoded arr[], int size){
    for(int i=0; i<size; i++){
        // cout<<"CHARS: "<<chars<<" CODE IN ARR: "<<arr[i].code<<endl;
        if(chars == arr[i].code){
            // cout<<"IN TRUE: "<<chars<<endl;
            return true;
        }
    }
    // cout<<"IN FALSE: "<<chars<<endl;
    return false;
}

string getAlpha(string chars, Encoded arr[], int size){
    for(int i=0; i<size; i++){
        if(chars == arr[i].code){
            // cout<<"IN GETALPHA: "<<arr[i].alpha<<endl;
            return arr[i].alpha;
        }
    }
    // cout<<"IN EMPTY: "<<chars<<endl;
    return "";
}

string decoder(string encoded, Node* head, int size) {
    string decoded;
    size +=1;
    Encoded arr[size];
    Node* current = head;
    int i =0;
    while (current != NULL and i < size) {
        arr[i].alpha = current->data.alpha;
        arr[i].code = current->data.code;
        current = current->next;
        i++;
    }        
    i = 0;
    // for(int i = 0; i < size; i++) {
    //     cout<<arr[i].alpha<<" "<<arr[i].code<<endl;
    // }
     
    string decode_char = "";
    do{
        if(! inCodes(decode_char, arr, size)){
            decode_char += encoded[i];
            // cout<<"IN IF: "<<decode_char<<endl;
        }
        else{
            decoded += getAlpha(decode_char, arr, size);
        // cout<<"ADDING"
            decode_char = encoded[i];
            // cout<<"IN ELSE: "<<decode_char<<endl;

        }
        i++;
    }while(i < encoded.length());
    
    return decoded;
}
int main() {
    string encoded = read_file("output.txt");
    cout <<"\nENCODED TEXT: " <<encoded;
    string codes = read_file("codes.txt");
    cout <<  endl;

    List L;

    istringstream iss(codes);
    string line;
    while (getline(iss, line)) {
        string alpha, code;
        istringstream lineStream(line);
        getline(lineStream, alpha, '\t');
        getline(lineStream, code, '\t');

        L.insert(Encoded(code, alpha));
    }

    cout<<"CODES: "<<endl;
    L.display();
    // cout << "done" << endl;

    string decoded = "";
    int length = L.length;
    Node* head= L.getHead();
    decoded = decoder(encoded, head, length);
    cout<<"DECODED TEXT : "<<decoded<<endl;


    return 0;
}

// int main(){
//     string encoded = read_file("output.txt");
//     cout<<encoded;
//     string codes = read_file("codes.txt");
//     cout<<endl<<codes<<endl;

//     List L;

//     int i = 0;
//     int line_count = 0;
//     bool tab_passed = 0;
//     while(codes[i] !='\0'){
//         Node* n = new Node();
//         if(line_count == 0){
//             if((codes[i] == '0' || codes[i] == '1') && tab_passed == false){
//                 n->data.code += codes[i];
//             }
//             else if(codes[i] == '\t'){
//                 tab_passed = true;
//                 // continue;
//             }
//             else if(codes[i]!='\t'){
//                 n->data.alpha = codes[i];
//             }
//         }
//         if(codes[i]=='\n'){
//             line_count++;
//             tab_passed = false;
//             continue;
//         }

//         if((codes[i] == '0' || codes[i] == '1') && tab_passed == false){
//             n->data.code += codes[i];
//         }
//         else if(codes[i] == '\t'){
//             tab_passed = true;
//             continue;
//         }
//         else{
//             n->data.alpha = codes[i];
//         }
//     L.insert(n->data);
//     i++;
//     }
//     L.display();
//     cout<<"done"<<endl;
//     return 0;
// }