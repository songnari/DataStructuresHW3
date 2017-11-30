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
	void nonRotated(int i); // 간격 조정 필요
	void Htree(int i);

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
			if (i + k == used)
				break;
			std::cout << std::setw(depth(used)*ldepth(i)) << showData(i+k);
		}
		std::cout << "\n";
		nonRotated(left(i));
	}
	std::cout << "\n";
	
}

void heap::Htree(int i) {
	//홀수일때 세로, 짝수일때 가로.
	//mxn매트릭스?
	//(ldepth(0)인 가로세로 메트릭스에 하나씩 저장..?


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
	heap h;
	int format;
	int num;
	char buf;

	if (!read.good()) {
		cout << "not good" << endl;
		exit(1);
	}
	else{
		cout << "good" << endl;
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

	cout << "1.rotated form  2.not-rotated form  3.H-tree form" << endl;

	cin >> format;
	switch (format)
	{
	case 1: h.rotated(0); break;
	case 2: h.nonRotated(0); break;
	case 3: h.Htree(0); break;
	default:
		break;
	}

	cin >> format;
	switch (format)
	{
	case 1: h.rotated(0); break;
	case 2: h.nonRotated(0); break;
	case 3: h.Htree(0); break;
	default:
		break;
	}


	cin >> format;
	switch (format)
	{
	case 1: h.rotated(0); break;
	case 2: h.nonRotated(0); break;
	case 3: h.Htree(0); break;
	default:
		break;
	}

	read.close();
	return 0;

}


