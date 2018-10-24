#include<iostream>

using namespace std;

template<class T>
struct Node{
 	T data;
	Node<T>* next;

};

template<class T>
class List{
	Node<T>* head;
	public:
	Node<T>* createNode(T t_data);
	Node<T>* insertNode(T t_data, Node<T>* root);
	Node<T>* insertByPosition(T t_data,int pos, Node<T>* root);
	void display(Node<T>* root);
	Node<T> *deleteByPosition(int pos, Node<T>* root);
	void getHead(Node<T>* root);
	~List();
};

template<class T>
Node<T>* List<T>::createNode(T t_data){
	Node<T>* newNode = new Node<T>;
	newNode->data = t_data;
	newNode->next = NULL;
	return newNode;
}

template<class T>
Node<T>* List<T>:: insertNode(T t_data, Node<T>* root){
	if(root == NULL){root = createNode(t_data);}
	else{	
		root->next = insertNode(t_data,root->next);
	}
	return root;
}

template<class T>
Node<T>* List<T>:: insertByPosition(T t_data,int pos, Node<T>* root){

	if(root == NULL){root = createNode(t_data);}
	else if(pos == 0){
		Node<T>* tempNode = createNode(t_data);
		tempNode->next = root;
		root = tempNode;
	}
	else{
		Node<T>* tempNode = createNode(t_data);
		Node<T>* curr = root;
		Node<T>* prev = root;
		int count = 0;
		while(curr!=NULL && pos > count){
			prev = curr;
			curr = curr->next;
			count++;
		}	
		tempNode->next = curr;
		prev->next = tempNode;
	}
	return root;
} 

template<class T>
void List<T>:: display(Node<T>* root){
	if(root!=NULL){
		cout << root->data << endl;
		display(root->next);
	}
}

template<class T>
Node<T>* List<T>::deleteByPosition(int pos, Node<T>* root){
	if(root==NULL){
		cout << "Empty List!!" << endl;
	}
	else if(pos == 0){
		Node<T>* temp =root;
		root = root->next;
		delete temp;
	}
	else{
		Node<T>* prev = root;
		Node<T>* curr = root;
		int count = 1;
		while(curr->next!=NULL && count<pos){
			prev = curr;
			curr = curr->next;
			count++;
		}
		prev->next = curr->next;
		delete curr;
	}
	return root;
}

template<class T>
void List<T>::getHead(Node<T>* root){
	head = root;
}

template<class T>
List<T>::~List(){
	Node<T>* tempNode;
	while(head!=NULL){
		tempNode = head;
		head = head->next;
		delete tempNode;
	}
}
int main(){

	Node<string>* strRoot = NULL;
	List<string> employeeList;
	
	strRoot = employeeList.insertNode("A",strRoot);
	strRoot = employeeList.insertNode("B",strRoot);
	strRoot = employeeList.insertNode("C",strRoot);
    
 	strRoot = employeeList.insertByPosition("D",2,strRoot);
	employeeList.display(strRoot);

	Node<float>* floatRoot = NULL;
	List<float> salaryList;

	floatRoot = salaryList.insertNode(2.5,floatRoot);
	floatRoot = salaryList.insertNode(3.6, floatRoot);
	floatRoot = salaryList.insertNode(10.5,floatRoot);
  
	floatRoot = salaryList.deleteByPosition(2,floatRoot);
	salaryList.display(floatRoot); 

	employeeList.getHead(strRoot);
	salaryList.getHead(floatRoot);	
return 0;
}
