//Input : heap operations of size n from the file (n : 1~150)
//        input.txt ���Ϸ� �Է¹���.
//        1~9 & a~z & A~Z �Է°���.
//		  I 5 -> heap�� 5 �Է�
//        D -> heap�� root��� ����
//Output : the final shape of the constructed heap in given three forms
//         1:rotated form
//		   2:non-rotated form
//		   3:H-tree form

#include<iostream>
#include<fstream>

class heap {
public:
	heap(char d, heap* l, heap* r) { data = d; lnode = l; rnode = r; }

	void set_data(const char& newData) { data = newData; }
	void set_left(heap* newL) { lnode = newL;  }
	void set_right(heap* newR) { rnode = newR; }

	const char& show_data() { return data; }
	const heap* left() { return lnode; }
	const heap* right() { return rnode; }
	
	bool is_leaf() const { return (lnode == NULL && rnode == NULL); }
	//void clear(heap*& root); //�����߻�

	heap* search_insert(heap* root);
	void insert(char newData);


private:
	char data;
	heap* lnode;
	heap* rnode;
};

/*void heap::clear(heap*& root)
{
	if (root != NULL) {
		clear(root->left());
		clear(root->right());
		delete root;
		root = NULL;
	}
}
*/
heap* heap::search_insert(heap* root) {
	if (!root->is_leaf()){
		if (root->left() == NULL)
			search_insert(root->lnode);
		else if(root->right() == NULL)
			search_insert(root->rnode);
	}
	else{
		return root;
	}
}

void heap::insert(char newData) {
	heap* target = search_insert(this);
	if (target->left() == NULL) {
		target = new heap(newData, NULL, NULL);
	}
	else if(target->right() == NULL) {
		target = new heap(newData, NULL, NULL);
	}
}

using namespace std;
int main (){
	ifstream read;
	read.open("input.txt");
	char arr[sizeof(read)] = { '\0' }; 
	heap h('5', NULL, NULL);
	h.insert(2);

	if (read.good()) {
		while (!read.eof()) {  //���� ������ �б�
			read.getline(arr, sizeof(read));
			for (int i = 0; i < sizeof(read); i++) {
				if (arr[i] != ' ')
					cout << arr[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < sizeof(read); i++) {
				if (arr[i] == 'I') {
					if (arr[i + 1] == ' ') {
						h.insert(arr[i + 2]);   // i+2 �ٲ����.
					}
				}
			}
		}
	}
	else {
		cout << "����" << endl;
	}

	read.close();
	return 0;

}


