#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include"Stack.cpp"

using namespace std;
//指令结构体，存指令的三部分
struct Instruction{
	string code;
	int t = 0;
	int a = 0;
};

int main() {
	//指令进行映射编码
	map<string, int> instruction;

	instruction["LIT"] = 0;
	instruction["LOD"] = 1;
	instruction["STO"] = 2;
	instruction["CAL"] = 3;
	instruction["INT"] = 4;
	instruction["JMP"] = 5;
	instruction["JPC"] = 6;
	instruction["ADD"] = 7;
	instruction["SUB"] = 8;
	instruction["MUL"] = 9;
	instruction["DIV"] = 10;
	instruction["RED"] = 11;
	instruction["WRT"] = 12;
	instruction["RET"] = 13;

	//运行栈
	Stack<int>running(10000, 0);

	//指令地址、当前函数基地址、参数
	int position, base, arg;

	//暂存每一条指令
	Instruction i;

	//cout << "start" << endl;
	//初始化指令地址与函数基址
	position = 0;
	base = 0;
	int key = 0;
	int top, top_low;//栈顶，次栈顶

	//全局的返回量
	running.push(0);
	running.push(0);

	//指令栈
	Stack<Instruction>ins(1000);

	//文件输入流
	ifstream file;

	string path;

	cout << "请输入文件名:" << endl;

	cin >> path;

	//打开文件
	file.open(path);

	//从文件中逐个读取指令
	while (file >> i.code) {
		file >> i.t;
		file >> i.a;
		ins.push(i);
	}

	//关闭文件
	file.close();

	//开始逐行解释指令
	do {
		i = ins.get(position);

		//将当前指令编号与对应的指令输出显示（便与调试，正式使用时需要去掉）
		cout << "p:" << position << ' ' << i.code << ' ' << i.t << ' ' << i.a << endl;

		//顺序执行（若没有跳转程度）
		position++;

		//判断是哪个指令
		switch (instruction[i.code]) {
		case 0://LIT
			running.push(i.a);
			break;
		case 1://LOD
			if (i.t == 0) {
				running.push(running.get(base + i.a + 2));
			}
			else if (i.t == 1) {
				running.push(running.get(2 + i.a));
			}
			break;
		case 2://STO
			if (i.t == 0) {
				running.set(base + i.a + 2, running.top());
			}
			else if (i.t == 1) {
				running.set(2 + i.a, running.top());
			}
			running.pop();
			break;
		case 3://CAL
			//两个隐式空间存栈调用的地址与指令调用的地址
			running.set(running.getTop(), base);
			running.set(running.getTop() + 1, position);

			//移动当前函数的基地址
			base = running.getTop();

			//切换指令为被调用函数的地址
			position = i.a;

			//移动栈顶至开辟后的位置
			running.setTop(running.getTop() + 2);
			break;
		case 4://INT
			running.setTop(running.getTop() + i.a);
			break;
		case 5://JMP
			position = i.a;
			break;
		case 6://JPC
			if (running.top() == 0)
			{
				position = i.a;
			}
			running.pop();
			break;
		case 7://ADD
			top = running.top();
			running.pop();
			top_low = running.top();
			running.pop();
			running.push(top + top_low);
			break;
		case 8://SUB
			top = running.top();
			running.pop();
			top_low = running.top();
			running.pop();
			running.push(top_low - top);
			break;
		case 9://MUL
			top = running.top();
			running.pop();
			top_low = running.top();
			running.pop();
			running.push(top_low * top);
			break;
		case 10://DIV
			top = running.top();
			running.pop();
			top_low = running.top();
			running.pop();
			running.push(top_low / top);
			break;
		case 11://RED
			cin >> arg;
			running.push(arg);
			break;
		case 12://WRT
			arg = running.top();
			running.pop();
			cout << arg << endl;
			break;
		case 13://RET
			running.setTop(base);
			cout << "s.Top " << running.getTop() << endl;
			base = running.get(running.getTop());
			position = running.get(running.getTop() + 1);
			break;
		}
	} while (position != 0);

	return 0;
}