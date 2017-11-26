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

using namespace std;
int main (){
	ifstream read;
	read.open("input.txt");
	char arr[sizeof(read)] = { '\0' };
	int n;
	
	if (read.good()) {
		cout << "!!!" << endl;
		while (!read.eof()) {  //���� ������ �б�
			read.getline(arr, sizeof(read));
			for (int i = 0; i < sizeof(read); i++)
				cout << arr[i] << " ";
		}
	}
	else {
		cout << "����" << endl;
	}

	read.close();
	return 0;

}