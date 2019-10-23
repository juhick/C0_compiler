#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include"Stack.cpp"

using namespace std;
//ָ��ṹ�壬��ָ�������
struct Instruction{
	string code;
	int t;
	int a;
};

int main() {
	//ָ�����ӳ��������
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
	//����ջ
	Stack<int>s(10000, 0);

	int p, b, a;
	//�ݴ�ÿһ��ָ��
	Instruction i;

	cout << "start" << endl;

	p = 0;
	b = 0;
	int key = 0;
	int top, top_low;//ջ������ջ��

	s.push(0);
	s.push(0);

	//ָ��ջ
	Stack<Instruction>is(1000);

	//�ļ�������
	ifstream f;

	string path;

	cout << "�������ļ���:" << endl;
	cin >> path;
	//���ļ�
	f.open(path);
	//���ļ��������ȡָ��
	while (f >> i.code) {
		f >> i.t;
		f >> i.a;
		is.push(i);
	}
	//�ر��ļ�
	f.close();
	//��ʼ���н���ָ��
	do {
		i = is.get(p);
		//����ǰָ�������Ӧ��ָ�������ʾ��������ԣ���ʽʹ��ʱ��Ҫȥ����
		cout << "p:" << p << ' ' << i.code << ' ' << i.t << ' ' << i.a << endl;
		//˳��ִ�У���û����ת�̶ȣ�
		p++;
		//�ж����ĸ�ָ��
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
			//������ʽ�ռ��ջ���õĵ�ַ��ָ����õĵ�ַ
			s.set(s.getTop(), b);
			s.set(s.getTop() + 1, p);
			//�ƶ���ǰ�����Ļ���ַ
			b = s.getTop();
			//�л�ָ��Ϊ�����ú����ĵ�ַ
			p = i.a;
			//�ƶ�ջ��������
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