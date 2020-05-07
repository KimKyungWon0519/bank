#include <iostream>

#define NAME_LEN 20

using namespace std;

typedef struct account {
	int accID; //���¹�ȣ
	int balance; //�ܾ�
	char cusNmae[NAME_LEN]; //���̸�
}Account;

enum {
	CREATE = 1, //���»���
	PLUS = 2, //�����Ա�
	MINUS = 3, //�������
	ALLINFOF = 4, //������ȸ
	EXIT = 5 //����
};

Account* account = new Account[100];
int index = 0;

void printMenu(); // �޴� ���
void inputInformation(int& id, int& money); //���� ���¹�ȣ, �ݾ� �Է�
void noFound(); //ID�� ���� �� ���� ��� 
void selectNumber(int& input); //�޴� ��ȣ �Է� 
void chooseMenu(int input); //�޴� ����
void createAccount(); //���� ����
void plusMoney(); //���� �Ա�
void minusMoney(); //���� ���
void viewAllInfor(); //���� ��ȸ
bool isHadInformation(); //���°� �ִ��� ������ �Ǵ�
int foundID(int id); //���� ��ȣ ã��

int main() {

	int input = 0;

	while (true)
	{
		printMenu();
		selectNumber(input);
		chooseMenu(input);
	}

	delete[] account;
}

void printMenu() {
	cout << "----Menu----" << endl;
	cout << "1. ���°���" << endl;
	cout << "2. ��    ��" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. �������� ��ü ���" << endl;
	cout << "5. ���α׷� ����" << endl;
}

void inputInformation(int& id, int& money) {
	cout << "����ID : ";
	cin >> id;

	while (true) {
		cout << "��  �� : ";
		cin >> money;

		if (money > 0)
			break;
		else
			cout << "0���� �� ū ���� �Է����ּ���." << endl;
	}
}

void noFound() {
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;

	printf("\n");
}

bool isHadInformation() {
	if (index == 0) {
		cout << "��������" << endl;
		printf("\n");
		return false;
	}
	else {
		return true;
	}
}

void selectNumber(int& input) {
	cout << "���� : ";
	cin >> input;
}

void chooseMenu(int input) {
	switch (input)
	{
	case CREATE:
		cout << "\n[���°���]" << endl;
		createAccount();
		break;
	case PLUS:
		cout << "\n[��    ��]" << endl;
		plusMoney();
		break;
	case MINUS:
		cout << "\n[��    ��]" << endl;
		minusMoney();
		break;
	case ALLINFOF:
		cout << "\n[��ü ���]" << endl;
		viewAllInfor();
		break;
	case EXIT:
		cout << "���α׷��� �����մϴ�." << endl;
		exit(0);
		break;
	default:
		cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�." << endl;
		printf("\n");
		break;
	}
}

void createAccount() {
	int id, money;
	char name[20];

	if (index < 100) {
		cout << "����ID : ";
		cin >> id;
		cout << "��  �� : ";
		cin >> name;
		cout << "�Աݾ� : ";
		cin >> money;

		if (id <= 0) {
			cout << "���� ���� ���� : id���� 0���� �� ū ���� �Է����ּ���" << endl;
			return;
		}
		else if (money < 10) {
			cout << "���� ���� ���� : �ݾ��� 10���� �� ū ���� �Է����ּ���" << endl;
			return;
		}


		if (foundID(id) == -1) {
			account[index].accID = id;
			strcpy_s(account[index].cusNmae, name);
			account[index].balance = money;

			index++;
		}
		else {
			cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
		}
	}
	else
		cout << "100���� �������� ������ �����մϴ�." << endl;

	printf("\n");

}

void plusMoney() {
	int id, money, idx;

	if (isHadInformation()) {

		inputInformation(id, money);

		if ((idx = foundID(id)) != -1)
			account[idx].balance += money;
		else
			noFound();
	}

	printf("\n");
}

void minusMoney() {
	if (isHadInformation()) {
		int id, money, idx;

		inputInformation(id, money);

		if ((idx = foundID(id)) != -1) {
			if (money < account[idx].balance)
				account[idx].balance -= money;
			else
				cout << "�ѵ��ʰ�" << endl;
		}
		else
			noFound();
	}

	printf("\n");
}

void viewAllInfor() {
	if (index > 0) {
		for (int i = 0; i < index; i++) {
			cout << "����ID : " << account[i].accID << endl;
			cout << "��  �� : " << account[i].cusNmae << endl;
			cout << "��  �� : " << account[i].balance << endl;
			printf("\n");
		}
	}
	else
		cout << "������ ����" << endl;

	printf("\n");
}

int foundID(int id) {
	int i = 0;

	for (i = 0; i < index; i++) {
		if (account[i].accID == id) {
			return i;
		}
	}

	return -1;
}