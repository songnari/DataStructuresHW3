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

using namespace std;
int main (){
	ifstream read;
	read.open("input.txt");
	char arr[sizeof(read)] = { '\0' };
	int n;
	
	if (read.good()) {
		cout << "!!!" << endl;
		while (!read.eof()) {  //파일 끝까지 읽기
			read.getline(arr, sizeof(read));
			for (int i = 0; i < sizeof(read); i++)
				cout << arr[i] << " ";
		}
	}
	else {
		cout << "실패" << endl;
	}

	read.close();
	return 0;

}