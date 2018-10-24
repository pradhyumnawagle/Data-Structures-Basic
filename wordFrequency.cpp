#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

template<class T, class U>
struct Node {
	T word;
	U frequency;
	Node<T, U>* next;

};

template<class T, class U>
class List {
	Node<T, U>* head;
public:
	Node<T, U>* createNode(T t_word, U t_frequency);
	Node<T, U>* insertNode(T t_word, U t_frequency, Node<T, U>* root);
	int getFreq(T t_data, Node<T,U>* root);
	void display(Node<T, U>* root);
	Node<T, U>* findMax(Node<T, U>* root);
	void getMaxFrequency(Node<T, U>* root);
	void getHead(Node<T, U>* root);
	~List();
};

string removeChar(string str) {

	for (int i = 0; i < str.length(); i++) {
		if (str[i] < 'A' || str[i] > 'Z') {
			if ((str[i] < 'a' || str[i] > 'z') && str[i] != ' ') {
				str.erase(i, 1);
			}
		}
	}
	return str;
}

string makeLowerCase(string str) {

	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A'  && str[i] <= 'Z') {
			str[i] = tolower(str[i]);
		}
	}
	return str;
}

void processText(string inputFile) {
	string buff1, finalStr;

	ifstream infile;
	ofstream outfile;

	infile.open(inputFile);
	getline(infile, finalStr);
	while (getline(infile, buff1)) {
		finalStr = finalStr + " " + buff1;
	}

	finalStr = removeChar(finalStr);
	//finalStr = makeLowerCase(finalStr);Do not store lower case alphabets, just make lower when you compare


	outfile.open("processed.txt");
	outfile << finalStr;


}

int giveWordNum(string str) {
	int len1 = str.length();
	int wordCount = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if ((isalpha(str[i])) && (i == 0 || !(isalpha(str[i - 1])))) {
			wordCount++;
		}
	}
	return wordCount;
}

string giveWord(string str) {
	int len1 = str.length();
	static int num = 0;
	int i;
	int strCount = 0;
	for (i = num; str[i] != ' ' && i<len1; i++) {
		strCount++;
	}
	string temp = str.substr(num, strCount);
	num = i + 1;
	return temp;
}

string readFileToString(string inputFile) {
	ifstream infile;
	string finalStr,str;
	infile.open(inputFile);
	getline(infile, finalStr);
	while (getline(infile, str)) {
		finalStr = finalStr + " " + str;
	}
	return finalStr;
}

template<class T, class U>
Node<T, U>* List<T, U>::createNode(T t_word, U t_frequency) {
	Node<T, U>* newNode = new Node<T, U>;
	newNode->word = t_word;
	newNode->frequency = t_frequency;
	newNode->next = NULL;
	return newNode;
}

template<class T, class U>
Node<T, U>* List<T, U>::insertNode(T t_word, U t_frequency, Node<T, U>* root) {
	if (root == NULL) { root = createNode(t_word, t_frequency); }
	else {
		root->next = insertNode(t_word, t_frequency, root->next);
	}
	return root;
}

template<class T,class U>
int List<T,U>::getFreq(T t_data, Node<T,U>* root) {
	int count = 0;
	while (root != NULL) {
		if (makeLowerCase(root->word) == makeLowerCase(t_data)) {
			count++;
			}
		root = root->next;
	}
	return count;
}

template<class T, class U>
void List<T, U>::display(Node<T, U>* root) {
	if (root != NULL) {
		cout << root->word << "|"<< root->frequency << " --> ";
		display(root->next);
	}
}

template<class T, class U>
Node<T,U>* List<T, U>::findMax(Node<T, U>* root) {
	Node<T, U>* tempMax = root;
	while (root != NULL) {
		if ((root->frequency) >= (tempMax->frequency)) {
			tempMax = root;
		}
		root = root->next;
	}
	return tempMax;
}

template<class T, class U>
void List<T, U>::getMaxFrequency(Node<T, U>* root) {
	Node<T, U>* max = findMax(root);
	vector<Node<T, U>*> maxFreq;
		while (root != NULL) {
			if ((root->frequency) >= max->frequency) {
				maxFreq.push_back(root);
			}
			root = root->next;
		}
		cout << endl;
		cout << "-----Words with maximum frequency-----" << endl;
		for (vector<Node<T, U>*>::iterator it = maxFreq.begin(); it != maxFreq.end();++it) {
			cout << (*it)->word << "|" << (*it)->frequency << endl;
	}
}

template<class T, class U>
void List<T, U>::getHead(Node<T, U>* root) {
	head = root;
}

template<class T, class U>
List<T, U>::~List() {
	Node<T, U>* tempNode;
	while (head != NULL) {
		tempNode = head;
		head = head->next;
		delete tempNode;
	}
}

int main() {

	
	string str,temp;

	Node<string, int>* root = NULL;
	Node<string, int>* tempRoot = root;
	List<string, int> myList;

	processText("input.txt");
	str = readFileToString("processed.txt");

	
	for (int i = 0; i < giveWordNum(str); i++) {
		temp = giveWord(str);
		root = myList.insertNode(temp, (myList.getFreq(temp, root) + 1), root);
	}
	
	myList.display(root);
	myList.getMaxFrequency(root);
	myList.getHead(root);
	system("pause");
	return 0;
}
