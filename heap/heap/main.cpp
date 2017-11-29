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
	heap();

	int parent(int i) { return (i - 1)/2; }
	int left(int i) {return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }

	char showData(int i) { return data[i]; }
	char showUsed() { return used; }

	void insert(char newData);
	void del();

	void swap(int a, int b); 
	void infix(int i);
	void delfix(int i); //test�ʿ�

private:
	char* data;
	int capacity;
	int used; //number of elements
};

heap::heap() : capacity(10) {
	data = new char[capacity];
	used = 0;
}

void heap::insert(char newData) {
	if (used == capacity) {
		char* temp=new char[++capacity];
		for (int i = 0; i < used; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}
	data[used] = newData;
	infix(used);
	used++;
}

void heap::infix(int i) {
	if (i != 0){
		if (data[parent(i)] < data[i]) {
			swap(i, parent(i));
			infix(parent(i));
		}
	}
}

void heap::del() {
	if (used != 0) {
		swap(0, used);
		used--;
		delfix(0);
	}
}

void heap::delfix(int i) {
	if (i != used){
		if (data[i] < data[left(i)]) {
			swap(i, left(i));
			delfix(left(i));
		}
		if (data[i] < data[right(i)]) {
			swap(i, right(i));
			delfix(right(i));
		}
	}
}


void heap::swap(int a, int b) {
	char temp;
	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}

using namespace std;
int main (){
	ifstream read;
	read.open("input.txt");
	char arr[sizeof(read)] = { '\0' }; 
	heap h;
	
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
						h.insert(arr[i + 2]);   // i+2 �ٲ����
					}
				}
			}
			for (int i = 0; i < h.showUsed(); i++) {
				cout << h.showData(i) << " ";
			}
		}
	}
	else {
		cout << "����" << endl;
	}
	

	read.close();
	return 0;

}


