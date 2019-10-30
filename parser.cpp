#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<map>
#include"Stack.cpp"

using namespace std;
//ָ��ṹ�壬��ָ���������
struct Instruction{
	string code;
	int t = 0;
	int a = 0;
};

int main() {
	//ָ�����ӳ�����
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
	Stack<int>running(10000, 0);

	//ָ���ַ����ǰ��������ַ������
	int position, base, arg;

	//�ݴ�ÿһ��ָ��
	Instruction i;

	//cout << "start" << endl;
	//��ʼ��ָ���ַ�뺯����ַ
	position = 0;
	base = 0;
	int key = 0;
	int top, top_low;//ջ������ջ��

	//ȫ�ֵķ�����
	running.push(0);
	running.push(0);

	//ָ��ջ
	Stack<Instruction>ins(1000);

	//�ļ�������
	ifstream file;

	string path;

	cout << "�������ļ���:" << endl;

	cin >> path;

	//���ļ�
	file.open(path);

	//���ļ��������ȡָ��
	while (file >> i.code) {
		file >> i.t;
		file >> i.a;
		ins.push(i);
	}

	//�ر��ļ�
	file.close();

	//��ʼ���н���ָ��
	do {
		i = ins.get(position);

		//����ǰָ�������Ӧ��ָ�������ʾ��������ԣ���ʽʹ��ʱ��Ҫȥ����
		cout << "p:" << position << ' ' << i.code << ' ' << i.t << ' ' << i.a << endl;

		//˳��ִ�У���û����ת�̶ȣ�
		position++;

		//�ж����ĸ�ָ��
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
			//������ʽ�ռ��ջ���õĵ�ַ��ָ����õĵ�ַ
			running.set(running.getTop(), base);
			running.set(running.getTop() + 1, position);

			//�ƶ���ǰ�����Ļ���ַ
			base = running.getTop();

			//�л�ָ��Ϊ�����ú����ĵ�ַ
			position = i.a;

			//�ƶ�ջ�������ٺ��λ��
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