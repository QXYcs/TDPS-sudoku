#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
char mat[5][5];
int region_mat[5][5];
int x[5][5], y[5][5];
//char block[5][5];
vector<char> Posibility[25];//ʹ��C++Ϊ�˷���ʹ��stl
char letter[5] = { 'A', 'B', 'C', 'D', 'E' };
//int positionGroupForErase[5] = { 0, 1, 2, 3, 4 };

void initializeVector(){
	for (int i = 0; i < 25; i++){
		for (int j = 0; j < 5; j++){
			Posibility[i].resize(5);
			Posibility[i][j] = letter[j];
			//printf("%d %c ", i, Posibility[i][j]);
		}
	//printf("\n");
	}
}

void printPosibilityVector() {
	for (int i = 0; i < 25; i++){
		for (int j = 0; j < Posibility[i].size(); j++)
			printf("%c ", Posibility[i][j]);
		printf("\n");
	}
}

void Posibility_ini() {//�ѿ�ʼ��֪��λ������
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (mat[i][j] != '*') {
				Posibility[i * 5 + j].resize(1);
				Posibility[i * 5 + j][0] = mat[i][j];
				//printf("%d", Posibility[i * 5 + j].size());
			}
		}
}

int searchforPosibility() {//����������һ�ֿ����Ե�λ�ò������������λ�õĿ�������洢����
	int prop = 0;//�����ķ���ֵ��������ĳ��λ������'1'
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////1.��ͬ������
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////2.��ͬ������
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////3.��ͬ������
	for(int search = 0; search < 3; search++){
		/***************************/
		//printf("\ntest1:");/******/
	    //system("pause");/***********/
	   /***************************/
	for (int i = 0; i < 5; i++) {
		vector<int> common[5];//, flag(5, 1);
		//common��ά�����洢�͵�һ��������ͬ��λ�õ���� |  flagһά�����洢ֵΪ��0��ʱ����ʱ������λ��

		for (int j = 0; j < 5; j++) {
			common[j].push_back(j);//���뱻�Ƚ�Ԫ�ص����
			//size.push_back(Posibility[5 * i + j].size());//���Ƚ�Ԫ�صĿ����Կռ��С
			//if (flag[j] == 0) continue;//˵����Ԫ���Ѿ���ǰ��ĳһԪ����ȣ������Ϊ���Ƚ�Ԫ��

			for (int k = j + 1; k < 5; k++) {//�ӱ��Ƚ�Ԫ��������+1��ʼ�������Ƚϱ���
				//if (flag[k] == 0) continue;//ͬ��
				if ((search == 0 && Posibility[5 * i + k] == Posibility[5 * i + j]) ||
					 (search ==1 && Posibility[5 * k + i] == Posibility[5 * j + i])||
					 (search == 2 && Posibility[5 * (x[i][k] - 1) + y[i][k] - 1] == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1])) common[j].push_back(k);//��Ԫ�����,д�����
			}

			if ((search == 0 && common[j].size() == Posibility[5 * i + j].size())||
				(search == 1 && common[j].size() == Posibility[5 * j + i].size()) ||
				(search == 2 && common[j].size() == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1].size()))//�㷨��ϵ�����ȥ��ͬ��/��/��������Ԫ����Ƚϡ����Ƚ�Ԫ�صĽ���
			{
				for (int l = 0; l < 5; l++) {
					if ((search == 0 && Posibility[5 * i + l] == Posibility[5 * i + j]) || 
						(search == 1 && Posibility[5 * l + i] == Posibility[5 * j + i]) ||
						(search == 2 && Posibility[5 * (x[i][l] - 1) + (y[i][l] - 1)] == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1])) continue;//��Ԫ��Ϊ�Ƚϻ򱻱Ƚ�Ԫ��

					/***************************/
					//printf("\ntest3: %d, %d %d %d\n", common[j].size(), Posibility[5 * i + j].size(), l, search);/******/
					//system("pause");/***********/
					/***************************/

                    vector<char>::iterator it;//������
					vector<char> buff(5);//��������
					vector<char> a, b;//set_intersection�޷����ڶ�ά�����������м������������
					//���´���ο�reference
					if (search == 0) {
					    a = Posibility[5 * i + j];
			            b = Posibility[5 * i + l];
					}
					else if (search == 1) {
					    a = Posibility[5 * j + i];
					    b = Posibility[5 * l + i];
					}
					else if (search == 2){
						a = Posibility[5 * (x[i][j] - 1) + y[i][j] - 1];
						b = Posibility[5 * (x[i][l] - 1) + y[i][l] - 1];
					}

					it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), buff.begin());//�ҽ���
					buff.resize(it - buff.begin());//�����Сȥ"0"

					for (vector<char>::iterator n = buff.begin();n != buff.end(); n++) {
						vector<char>::iterator p = find(b.begin(), b.end(), *n);//��b������û�в����е���ĸ
						if (p != b.end()) {//�ҵ���
							b.erase(b.begin() + (p - b.begin()));//�����λ��ɾ������ĸ
							
							if (search == 0) b = Posibility[5 * i + l] = b;//ֵ���м��������ȥ
							
							else if (search == 1) Posibility[5 * l + i] = b;
							
							else if (search == 2) Posibility[5 * (x[i][l] - 1) + y[i][l] - 1] = b;
							prop = 1;
						} 
					}
				}
				//printPosibilityVector();///////////////// 
			}
		}
	}
	//printPosibilityVector();
	}
	
					
		
	return prop;
}

void fillmat() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (Posibility[5 * i + j].size() == 1)
				mat[i][j] = Posibility[5 * i + j][0];
}

/*void exclusion_judgement(vector<char> buf, vector<int> buf_x, vector<int> buf_y){//�ж����2�е�һ�У�һ�л�һ���������������ֿ��ܵ�λ���Ƿ��ɻ�����ȷ������һ��λ�õ����
	if ((buf[0] == buf[2]) && (buf[1] == buf[3])) {//ǰ����λ�ÿ�������ͬ			
		if (buf[0] == buf[4] || buf[1] == buf[4]) {
			Posibility[5 * buf_x[2] + buf_y[2]].resize(1);
			Posibility[5 * buf_x[2] + buf_y[2]][0] = buf[5];
		}
		if (buf[0] == buf[5] || buf[1] == buf[5]) {
			Posibility[5 * buf_x[2] + buf_y[2]].resize(1);
			Posibility[5 * buf_x[2] + buf_y[2]][0] = buf[4];
		}
	}

	if ((buf[0] == buf[4] && buf[1] == buf[5])) {//һ��λ�ÿ�������ͬ			
		if (buf[0] == buf[2] || buf[1] == buf[2]) {
			Posibility[5 * buf_x[1] + buf_y[1]].resize(1);
			Posibility[5 * buf_x[1] + buf_y[1]][0] = buf[3];
		}
		if (buf[0] == buf[3] || buf[1] == buf[3]) {
			Posibility[5 * buf_x[1] + buf_y[1]].resize(1);
			Posibility[5 * buf_x[1] + buf_y[1]][0] = buf[2];
		}
	}

	if ((buf[2] == buf[4] && buf[3] == buf[5])) {//����λ�ÿ�������ͬ			
		if (buf[2] == buf[0] || buf[3] == buf[0]) {
			Posibility[5 * buf_x[0] + buf_y[0]].resize(1);
			Posibility[5 * buf_x[0] + buf_y[0]][0] = buf[1];
		}
		if (buf[2] == buf[1] || buf[3] == buf[1]) {
			Posibility[5 * buf_x[0] + buf_y[0]].resize(1);
			Posibility[5 * buf_x[0] + buf_y[0]][0] = buf[0];
		}
	}
}*/

/*int searchforPosibility2() {//���2
	int prop = 0;
	vector<char> buf(3);
	vector<int> buf_x(3);//���������
	vector<int> buf_y(3);//����������
	for (int i = 0; i < 5; i++) {//////////////////////////////////////////////////////////////////////��������

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//������һ�г�ʼ��������bufλ�õı���
		buf.clear(), buf_x.clear(), buf_y.clear();//������һ�г�ʼ����buf

		for (int j = 0; j < 5; j++) {//��������
			if (Posibility[5 * i + j].size() == 2) {//����һ�������������λ��
				if(buf_y.size() == 3)  break; //���ֵ��ĸ������������λ�ã�������Ψһ��
				else{//ע��size�õ������Ѿ��������ݵĿռ��С
					buf.push_back(Posibility[5 * i + j][0]);
					buf.push_back(Posibility[5 * i + j][1]);
					buf_x.push_back(i);//�洢��λ��
					buf_y.push_back(j);//�洢��λ��
				}
			}
			
		}
		//printf("\nNext Line\n");
		/*for (int o = 0; o < buf_y.size(); o++)////////////////////////////////////////////////
			printf("buf: %c %c; buf_y: %d\n", buf[2 * o], buf[2 * o + 1], buf_y[o]);////////////
		system("pause");/////////////////////////////////////////////////////////////////////
		
		if (buf.size() == 6) { //�������һ���ڸպ��������������ֿ��ܵ�λ��
			exclusion_judgement(buf, buf_x, buf_y);
			prop = 1;
		}
	}

	for (int j = 0; j < 5; j++) {/////////////////////////////////////////////////////////////////////////��������

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//������һ�г�ʼ��������bufλ�õı���
		buf.clear(), buf_x.clear(), buf_y.clear();//������һ�г�ʼ����buf

		for (int i = 0; i < 5; i++) {//��������
			if (Posibility[5 * i + j].size() == 2) {//����һ�������������λ��
				if (buf_y.size() == 3)  break; //���ֵ��ĸ������������λ�ã�������Ψһ��
				else {//ע��size�õ������Ѿ��������ݵĿռ��С
					buf.push_back(Posibility[5 * i + j][0]);
					buf.push_back(Posibility[5 * i + j][1]);
					//buf[buf_pos++] = Posibility[5 * i + j][1];�������±������
					buf_x.push_back(i);//�洢��λ��
					buf_y.push_back(j);//�洢��λ��
				}
			}

		}
		if (buf.size() == 6) { //�������һ���ڸպ��������������ֿ��ܵ�λ��
			exclusion_judgement(buf, buf_x, buf_y);
			prop = 1;
		}
	}
	
	int a, b;
	//vector<int> buf_x(3);
	for (int i = 0; i < 5; i++) {///////////////////////////////////////////////////////////////////////////��������

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//������һ���ʼ��������bufλ�õı���
		buf.clear(), buf_x.clear(), buf_y.clear();//������һ���ʼ����buf
		//mat[x[i][j] - 1][y[i][j] - 1]
		for (int j = 0; j < 5; j++) {//��������

			a = x[i][j] - 1;///x[][]��y[][]�ֱ�洢��λ�õĺ������꣬һ��Ϊһ�����
		    b = y[i][j] - 1;///��������ֵ��һ��Ϊ��Ҫ������λ�õ�mat�±�;�˴�a,b����������������������i,j
			
			if (Posibility[5 * a + b].size() == 2) {//����һ�������������λ��
				if (buf_y.size() == 3)  break; //���ֵ��ĸ������������λ�ã��򱾿���Ψһ��
				else {//ע��size�õ������Ѿ��������ݵĿռ��С
					buf.push_back(Posibility[5 * a + b][0]);
					buf.push_back(Posibility[5 * a + b][1]);
					//buf[buf_pos++] = Posibility[5 * i + j][1];�������±������
					buf_x.push_back(a);//�洢��λ��
					buf_y.push_back(b);//�洢��λ��
				}
			}

		}
		if (buf.size() == 6) { //�������һ���ڸպ��������������ֿ��ܵ�λ��
			exclusion_judgement(buf, buf_x, buf_y);
			prop = 1;
		}
	}
	return prop;
}*/

void mat_output(){
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++)
			printf("%c ", mat[i][j]);
		printf("\n");
	}

	/*printf("test x�ľ���:\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			printf("%d ", x[i][j]);
		printf("\n");
	}*/
	/*printf("test ��ʾ��������aaaaaaaaaaaaaaaa:\n");
	for (int i= 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
				printf("%d ", region_mat[i][j]);
		}
		printf("\n");
	}*/
	//printf("\n");
}

void block_output() {//����趨������
					 printf("Blocks of the puzzle\n");
					 for (int i= 0; i < 5; i++) {
					 for (int j = 0; j < 5; j++) {
					 printf("%d ", region_mat[i][j]);
					 }
					 printf("\n");
					 }
					 printf("\n");
}

int A = 5, B = 5, C = 5, D = 5, E = 5;

void exclusion(char a) {
	switch (a) {
	case 'A':
		A--;
		break;
	case 'B':
		B--;
		break;
	case 'C':
		C--;
		break;
	case 'D':
		D--;
		break;
	case 'E':
		E--;
		break;
}
}

void ini_Counter() {
	A = 5, B = 5, C = 5, D = 5, E = 5;
}

int judgement(int a) {
	printf("%d\n", a);
	if (A != a || B != a || C != a || D != a || E != a) {
		printf("NO solution!!\n");
		system("pause");
		return 0;
	}
	return 1;
}
int isReasonable() {
	//printf("AAAA\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			exclusion(mat[i][j]);
		}
		if (judgement(4 - i) == 0) return 0;
	}
	ini_Counter();
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			exclusion(mat[j][i]);
		}
		if (judgement(4 - i) == 0) return 0;
	}

	ini_Counter();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			exclusion(mat[x[i][j] - 1][y[i][j] - 1]);
		}
		if (judgement(4 - i) == 0) return 0;
	}
	
	return 1;
}

int main() {
	FILE *fin = fopen("../mat_input.txt","rb");
	memset(mat,'*', sizeof(mat));
	int n, a, b, region = 0;
	printf("Input the five divided region\n");
	for (int i = 0; i < 5; i++) {
		region++;
		for (int j = 0; j < 5; j++) {
		fscanf(fin, "%d%d", &x[i][j], &y[i][j]);
		//printf("%d %d\n", x[i][j], y[i][j]);
		region_mat[x[i][j] - 1][y[i][j] - 1] = region;//������1-5��ʾ������������������
		}
	}

	printf("Input the number of known character\n");
		fscanf(fin, "%d", &n);
	printf("Input the location and the corresponding character respectively\n");
	for (int i = 0; i < 2*n;i++) {
		//printf("%d\n", i);
		fscanf(fin, "%d%d", &a, &b);
		fscanf(fin, "%c", &mat[a - 1][b - 1]);  
	}
	printf("\n");
	mat_output();
	block_output();
	fclose(fin);
	initializeVector();
	printPosibilityVector();

	//printf("Begin to solve:\n");////////////////////////////////////////////////////////////////////////////////////////////
	Posibility_ini();//��ʼ��Posibility����
	int end = 1;
	do{
		end = searchforPosibility();
		mat_output();
		printPosibilityVector();
		system("pause");
		fillmat();
	} while (end == 1);

	
	if (isReasonable() == 1) {
		printf("%d, %d, %d, %d, %d\n", A, B, C, D, E);
		printf("\nFinal Result:\n");
		mat_output();
		system("pause");
	}
	
}
