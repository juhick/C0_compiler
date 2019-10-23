#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include"Stack.cpp"

using namespace std;
//指令结构体，存指令的三项
struct Instruction{
	string code;
	int t;
	int a;
};

int main() {
	//指令进行映射编码编码
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
	//数据栈
	Stack<int>s(10000, 0);

	int p, b, a;
	//暂存每一条指令
	Instruction i;

	cout << "start" << endl;

	p = 0;
	b = 0;
	int key = 0;
	int top, top_low;//栈顶，次栈顶

	s.push(0);
	s.push(0);

	//指令栈
	Stack<Instruction>is(1000);

	//文件输入流
	ifstream f;

	string path;

	cout << "请输入文件名:" << endl;
	cin >> path;
	//打开文件
	f.open(path);
	//从文件中逐个读取指令
	while (f >> i.code) {
		f >> i.t;
		f >> i.a;
		is.push(i);
	}
	//关闭文件
	f.close();
	//开始逐行解释指令
	do {
		i = is.get(p);
		//将当前指令编号与对应的指令输出显示（便与调试，正式使用时需要去掉）
		cout << "p:" << p << ' ' << i.code << ' ' << i.t << ' ' << i.a << endl;
		//顺序执行（若没有跳转程度）
		p++;
		//判断是哪个指令
		switch (instruction[i.code]) {
		case 0://LIT
			s.push(i.a);
			break;
		case 1://LOD
			if (i.t == 0) {
				s.push(s.get(b + i.a));
			}
			else if (i.t == 1) {
				s.push(s.get(i.a));
			}
			break;
		case 2://STO
			if (i.t == 0) {
				s.set(b + i.a, s.top());
			}
			else if (i.t == 1) {
				s.set(i.a, s.top());
			}
			s.pop();
			break;
		case 3://CAL
			//两个隐式空间存栈调用的地址与指令调用的地址
			s.set(s.getTop(), b);
			s.set(s.getTop() + 1, p);
			//移动当前函数的基地址
			b = s.getTop();
			//切换指令为被调用函数的地址
			p = i.a;
			//移动栈顶至开辟
			s.setTop(s.getTop() + 2);
			break;
		case 4://INT
			s.setTop(s.getTop() + i.a);
			break;
		case 5://JMP
			p = i.a;
			break;
		case 6://JPC
			if (s.top() == 0)
			{
				p = i.a;
			}
			s.pop();
			break;
		case 7://ADD
			top = s.top();
			s.pop();
			top_low = s.top();
			s.pop();
			s.push(top + top_low);
			break;
		case 8://SUB
			top = s.top();
			s.pop();
			top_low = s.top();
			s.pop();
			s.push(top_low - top);
			break;
		case 9://MUL
			top = s.top();
			s.pop();
			top_low = s.top();
			s.pop();
			s.push(top_low * top);
			break;
		case 10://DIV
			top = s.top();
			s.pop();
			top_low = s.top();
			s.pop();
			s.push(top_low / top);
			break;
		case 11://RED
			cin >> a;
			s.push(a);
			break;
		case 12://WRT
			a = s.top();
			s.pop();
			cout << a << endl;
			break;
		case 13://RET
			s.setTop(b);
			cout << "s.Top " << s.getTop() << endl;
			b = s.get(s.getTop());
			p = s.get(s.getTop() + 1);
			break;
		}
	} while (p != 0);

	return 0;
}