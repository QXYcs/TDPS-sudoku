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
vector<char> Posibility[25];//使用C++为了方便使用stl
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

void Posibility_ini() {//把开始已知的位置填入
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (mat[i][j] != '*') {
				Posibility[i * 5 + j].resize(1);
				Posibility[i * 5 + j][0] = mat[i][j];
				//printf("%d", Posibility[i * 5 + j].size());
			}
		}
}

int searchforPosibility() {//填完所有有一种可能性的位置并把其他情况的位置的可能情况存储起来
	int prop = 0;//函数的返回值，如果填出某个位置则置'1'
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////1.按同行搜索
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////2.按同列搜索
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////3.按同块搜索
	for(int search = 0; search < 3; search++){
		/***************************/
		//printf("\ntest1:");/******/
	    //system("pause");/***********/
	   /***************************/
	for (int i = 0; i < 5; i++) {
		vector<int> common[5];//, flag(5, 1);
		//common二维向量存储和第一个向量相同的位置的序号 |  flag一维向量存储值为“0”时遍历时跳过该位置

		for (int j = 0; j < 5; j++) {
			common[j].push_back(j);//放入被比较元素的序号
			//size.push_back(Posibility[5 * i + j].size());//被比较元素的可能性空间大小
			//if (flag[j] == 0) continue;//说明该元素已经和前面某一元素相等，不会成为被比较元素

			for (int k = j + 1; k < 5; k++) {//从被比较元素纵坐标+1开始，即不比较本身
				//if (flag[k] == 0) continue;//同上
				if ((search == 0 && Posibility[5 * i + k] == Posibility[5 * i + j]) ||
					 (search ==1 && Posibility[5 * k + i] == Posibility[5 * j + i])||
					 (search == 2 && Posibility[5 * (x[i][k] - 1) + y[i][k] - 1] == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1])) common[j].push_back(k);//两元素相等,写入序号
			}

			if ((search == 0 && common[j].size() == Posibility[5 * i + j].size())||
				(search == 1 && common[j].size() == Posibility[5 * j + i].size()) ||
				(search == 2 && common[j].size() == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1].size()))//算法关系，相等去除同行/列/区块其他元素与比较、被比较元素的交集
			{
				for (int l = 0; l < 5; l++) {
					if ((search == 0 && Posibility[5 * i + l] == Posibility[5 * i + j]) || 
						(search == 1 && Posibility[5 * l + i] == Posibility[5 * j + i]) ||
						(search == 2 && Posibility[5 * (x[i][l] - 1) + (y[i][l] - 1)] == Posibility[5 * (x[i][j] - 1) + y[i][j] - 1])) continue;//此元素为比较或被比较元素

					/***************************/
					//printf("\ntest3: %d, %d %d %d\n", common[j].size(), Posibility[5 * i + j].size(), l, search);/******/
					//system("pause");/***********/
					/***************************/

                    vector<char>::iterator it;//迭代器
					vector<char> buff(5);//交集向量
					vector<char> a, b;//set_intersection无法用于二维向量，建立中间变量（？？）
					//以下代码参考reference
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

					it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), buff.begin());//找交集
					buff.resize(it - buff.begin());//重设大小去"0"

					for (vector<char>::iterator n = buff.begin();n != buff.end(); n++) {
						vector<char>::iterator p = find(b.begin(), b.end(), *n);//在b中找有没有并集中的子母
						if (p != b.end()) {//找到了
							b.erase(b.begin() + (p - b.begin()));//计算出位置删除该子母
							
							if (search == 0) b = Posibility[5 * i + l] = b;//值由中间变量传回去
							
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

/*void exclusion_judgement(vector<char> buf, vector<int> buf_x, vector<int> buf_y){//判断情况2中的一行，一列或一区的三个存在两种可能的位置是否由互斥来确定其中一个位置的情况
	if ((buf[0] == buf[2]) && (buf[1] == buf[3])) {//前两个位置可能性相同			
		if (buf[0] == buf[4] || buf[1] == buf[4]) {
			Posibility[5 * buf_x[2] + buf_y[2]].resize(1);
			Posibility[5 * buf_x[2] + buf_y[2]][0] = buf[5];
		}
		if (buf[0] == buf[5] || buf[1] == buf[5]) {
			Posibility[5 * buf_x[2] + buf_y[2]].resize(1);
			Posibility[5 * buf_x[2] + buf_y[2]][0] = buf[4];
		}
	}

	if ((buf[0] == buf[4] && buf[1] == buf[5])) {//一三位置可能性相同			
		if (buf[0] == buf[2] || buf[1] == buf[2]) {
			Posibility[5 * buf_x[1] + buf_y[1]].resize(1);
			Posibility[5 * buf_x[1] + buf_y[1]][0] = buf[3];
		}
		if (buf[0] == buf[3] || buf[1] == buf[3]) {
			Posibility[5 * buf_x[1] + buf_y[1]].resize(1);
			Posibility[5 * buf_x[1] + buf_y[1]][0] = buf[2];
		}
	}

	if ((buf[2] == buf[4] && buf[3] == buf[5])) {//二三位置可能性相同			
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

/*int searchforPosibility2() {//情况2
	int prop = 0;
	vector<char> buf(3);
	vector<int> buf_x(3);//储存横坐标
	vector<int> buf_y(3);//储存纵坐标
	for (int i = 0; i < 5; i++) {//////////////////////////////////////////////////////////////////////按行搜索

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//搜索完一行初始化各代表buf位置的变量
		buf.clear(), buf_x.clear(), buf_y.clear();//搜索完一行初始化各buf

		for (int j = 0; j < 5; j++) {//行内搜索
			if (Posibility[5 * i + j].size() == 2) {//出现一个有两种情况的位置
				if(buf_y.size() == 3)  break; //出现第四个有两种情况的位置，则本行无唯一解
				else{//注意size得到的是已经放入数据的空间大小
					buf.push_back(Posibility[5 * i + j][0]);
					buf.push_back(Posibility[5 * i + j][1]);
					buf_x.push_back(i);//存储行位置
					buf_y.push_back(j);//存储列位置
				}
			}
			
		}
		//printf("\nNext Line\n");
		/*for (int o = 0; o < buf_y.size(); o++)////////////////////////////////////////////////
			printf("buf: %c %c; buf_y: %d\n", buf[2 * o], buf[2 * o + 1], buf_y[o]);////////////
		system("pause");/////////////////////////////////////////////////////////////////////
		
		if (buf.size() == 6) { //刚搜完的一行内刚好有三个仅有两种可能的位置
			exclusion_judgement(buf, buf_x, buf_y);
			prop = 1;
		}
	}

	for (int j = 0; j < 5; j++) {/////////////////////////////////////////////////////////////////////////按列搜索

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//搜索完一列初始化各代表buf位置的变量
		buf.clear(), buf_x.clear(), buf_y.clear();//搜索完一列初始化各buf

		for (int i = 0; i < 5; i++) {//列内搜索
			if (Posibility[5 * i + j].size() == 2) {//出现一个有两种情况的位置
				if (buf_y.size() == 3)  break; //出现第四个有两种情况的位置，则本列无唯一解
				else {//注意size得到的是已经放入数据的空间大小
					buf.push_back(Posibility[5 * i + j][0]);
					buf.push_back(Posibility[5 * i + j][1]);
					//buf[buf_pos++] = Posibility[5 * i + j][1];不能用下标操作？
					buf_x.push_back(i);//存储行位置
					buf_y.push_back(j);//存储列位置
				}
			}

		}
		if (buf.size() == 6) { //刚搜完的一列内刚好有三个仅有两种可能的位置
			exclusion_judgement(buf, buf_x, buf_y);
			prop = 1;
		}
	}
	
	int a, b;
	//vector<int> buf_x(3);
	for (int i = 0; i < 5; i++) {///////////////////////////////////////////////////////////////////////////按块搜索

		int buf_pos = 0, buf_x_pos = 0, buf_y_pos = 0;//搜索完一块初始化各代表buf位置的变量
		buf.clear(), buf_x.clear(), buf_y.clear();//搜索完一块初始化各buf
		//mat[x[i][j] - 1][y[i][j] - 1]
		for (int j = 0; j < 5; j++) {//块内搜索

			a = x[i][j] - 1;///x[][]和y[][]分别存储块位置的横纵坐标，一行为一个块的
		    b = y[i][j] - 1;///其内容数值减一即为需要遍历的位置的mat下标;此处a,b即用来代替上两种搜索的i,j
			
			if (Posibility[5 * a + b].size() == 2) {//出现一个有两种情况的位置
				if (buf_y.size() == 3)  break; //出现第四个有两种情况的位置，则本块无唯一解
				else {//注意size得到的是已经放入数据的空间大小
					buf.push_back(Posibility[5 * a + b][0]);
					buf.push_back(Posibility[5 * a + b][1]);
					//buf[buf_pos++] = Posibility[5 * i + j][1];不能用下标操作？
					buf_x.push_back(a);//存储行位置
					buf_y.push_back(b);//存储列位置
				}
			}

		}
		if (buf.size() == 6) { //刚搜完的一块内刚好有三个仅有两种可能的位置
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

	/*printf("test x的矩阵:\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			printf("%d ", x[i][j]);
		printf("\n");
	}*/
	/*printf("test 表示矩阵区块aaaaaaaaaaaaaaaa:\n");
	for (int i= 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
				printf("%d ", region_mat[i][j]);
		}
		printf("\n");
	}*/
	//printf("\n");
}

void block_output() {//输出设定的区块
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
		region_mat[x[i][j] - 1][y[i][j] - 1] = region;//用数字1-5表示矩阵中数字所属区域
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
	Posibility_ini();//初始化Posibility向量
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
