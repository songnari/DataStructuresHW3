//Input : heap operations of size n from the file (n : 1~150)
//        input.txt 파일로 입력받음.
//        1~9 & a~z & A~Z 입력가능.
//		  I 5 -> heap에 5 입력
//        D -> heap의 root노드 삭제
//Output : the final shape of the constructed heap in given three forms
//         1:rotated form
//		   2:non-rotated form
//		   3:H-tree form

#include<iostream>
#include<fstream>
#include<iomanip>

class heap {
public:
	heap();

	int parent(int i) { return (i - 1)/2; }
	int left(int i) {return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }
	int depth(int i);
	int ldepth(int i);

	char showData(int i);
	char showUsed() { return used; }

	void rotated(int i);
	void nonRotated(int i);
	void Htree(int i);
	void h(int node, char c, char** tree,int i, int j, int d[], int u[], int r[], int l[]);

	void insert(char newData);
	void del();

	void swap(int a, int b); 
	void infix(int i);
	void delfix(int i); //test필요

private:
	char* data;
	int capacity;
	int used; //number of elements
};

heap::heap() : capacity(10) {
	data = new char[capacity];
	used = 0;
}

char heap::showData(int i){
	if (data[i] > 64) {
		if (data[i] > 96) {
			return data[i]- 32;
		}
		else {
			return data[i]+ 32;
		}

	}
	else
		return data[i];
}

int heap::depth(int i) {
	int temp = i;
	int depth = 0;
	while (temp!=0) {
		depth++;
		temp = parent(temp);
	}
	return depth;
}

int heap::ldepth(int i) {
	int temp = i;
	int ldepth = 0;
	while (temp < capacity) {
		ldepth++;
		temp = left(temp);
	}
	return ldepth;
}

void heap::rotated(int i) {
	if (i < used) {
		rotated(right(i));
		std::cout << std::setw(ldepth(0) * depth(i)) << showData(i) << "\n";
		rotated(left(i));
	}
}

void heap::nonRotated(int i) {
	if (i <used) {
		int count=1;
		for (int k = 0; k < depth(i); k++) {
			count *= 2;
		}
		for (int k = 0; k < count; k++) {
			if (i + k >= used)
				break;
			std::cout << std::setw(depth(used)*ldepth(i)) << showData(i+k);
		}
		std::cout << "\n";
		nonRotated(left(i));
	}
}

void heap::Htree(int i) {
	char** htree=new char*[25];
	for (int j = 0; j < 25; j++) {
		htree[j] = new char[25];
	}
	for (int j = 0; j < 25; j++) {
		for (int k = 0; k < 25; k++) {
			htree[j][k] = ' ';
		}
	}
	int v[4][2] = { { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } }; // 남,북,동,서

	h(0, showData(0), htree, 12, 15, v[0], v[1], v[2], v[3]);

	for (int j = 0; j < 25; j++) {
		for (int k = 0; k < 25; k++) {
			std :: cout << htree[j][k] << " ";
		}
		std::cout << "\n";
	}
	for(int j=0;j<25;j++)
		delete[] htree[j];
	delete[] htree;
}

void heap::h(int node, char c, char** tree, int i, int j, int d[], int u[], int r[], int l[]) {
	if (node < used) {
		if (node!=0 && ldepth(node)>2 && used > 7) {
			for (int k = 0; k < ldepth(node)/ 2; k++) {
				tree[i][j] = '#';
				i += u[0];
				j += u[1];
			}
			if (ldepth(node) > 4) {
				tree[i][j] = '#';
				i += u[0];
				j += u[1];
			}
			if (used>127 && node ==1) {
				tree[i][j] = '#';
				i += u[0];
				j += u[1];
			}
			if(used > 131 && node ==1) {
				tree[i][j] = '#';
				i += u[0];
				j += u[1];
			}
			if (used > 132 && node ==1) {
				tree[i][j] = '#';
				i += u[0];
				j += u[1];
			}
			tree[i][j] = showData(node);
		}
		else {
			tree[i][j] = c;
		}
		h(left(node), showData(left(node)), tree, i + l[0], j + l[1], r, l, u, d);
		h(right(node), showData(right(node)), tree, i + r[0], j + r[1], l, r, d, u);
	}
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
	if (newData > 64) {
		if (newData > 96) {
			newData -= 32;
		}
		else {
			newData += 32;
		}
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
	if (used > 0) {
		swap(0, used-1);
		used--;
		delfix(0);
	}
	else if (used==0)
		data[0] = ' ';
}

void heap::delfix(int i) {
	if (i < used){
		if (data[i] < data[left(i)]) {
			swap(i, left(i));
			delfix(left(i));
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
	heap h;
	int num;
	char buf;

	if (!read.good()) {
		exit(1);
	}

	read >> num; // 첫 숫자 저장

	for (int i = 0; i < num;) {
		read >> buf;
		if (buf == 'I') {
			i++;
			read >> buf;
			h.insert(buf);
		}
		else if (buf == 'D') {
			i++;
			h.del();
			cout << "del" << endl;
		}
	}

	cout << "1.rotated form " << endl;
	h.rotated(0);
		
	cout << "2.not-rotated form" << endl;
	h.nonRotated(0);
		
	cout << "3.H - tree form" << endl;
	h.Htree(0);

	read.close();
	return 0;

}


