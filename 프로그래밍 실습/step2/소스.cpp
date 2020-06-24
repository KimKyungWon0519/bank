#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 100
#define MAX_LENGHT 20
#define MAX_NUMBER 15

int index = 0;

using namespace std;

enum {
	CREATE = 1, //���»���
	PLUS = 2, //�����Ա�
	MINUS = 3, //�������
	ALLINFOF = 4, //������ȸ
	EXIT = 5 //����
};

class Bank
{
public:
	Bank(); //�ɹ����� �ʱ�ȭ
	Bank(int ID, int money, char* personalNumber, char* name); //�ɹ����� ������
	~Bank(); //�ɹ����� �Ҹ�
	int getAccID(); //accID ��������
	int getBalance(); //balance ��������
	void plusMoney(int money); //�Ա�
	void minusMoney(int money); //���
	void printInformation(); //���� ���
	char* getPersonalNumber(); //personalNumber ��������
	
private:
	int accID; 
	int balance;
	char* personalNumber;
	char* cusName;
};

Bank::Bank()
{
	accID = -1;
	balance = -1;
	personalNumber = NULL;
	cusName = NULL;
}

Bank::Bank(int ID, int money, char* personalNumber, char* name) {
	Bank::personalNumber = new char[MAX_NUMBER];
	cusName = new char[MAX_LENGHT];
	accID = ID;
	balance = money;
	strcpy(Bank::personalNumber, personalNumber);
	strcpy(cusName, name);
}

Bank::~Bank()
{
	delete[] cusName;
	delete[] personalNumber;
}

int Bank::getAccID() {
	return accID;
}

int Bank::getBalance() {
	return balance;
}

char* Bank::getPersonalNumber() {
	return personalNumber;
}

void Bank::plusMoney(int money) {
	balance += money;
}

void Bank::minusMoney(int money) {
	balance -= money;
}

void Bank::printInformation() {
	cout << "���� ��ȣ : " << accID << endl;
	cout << "����� �̸� : " << cusName << endl;
	cout << "����� �ֹε�� ��ȣ : " << personalNumber << endl;
	cout << "���� �ݾ� : " << balance << endl;
}

Bank* account = new Bank[MAX_USER];
  
void printMenu(); //�޴� ���
void selectedInput(int& input); //��ȣ �Է�
void chosenMenu(int input); //�޴� ����
void createAccount(); //���� ����
void inputInformation(int& id, int& money, char name[], char personalNumber[]); //�������� �Է�
int foundID(int id); //���̵� ã��
bool isOverlapUser(char personalNumber[]); //�ֹε�Ϲ�ȣ �ߺ� Ȯ��
void deposit(); //���� �Ա�
bool isHadInformation(); //���� ���¿� ������ ����� �ִ� �� Ȯ��
void inputInformation(int& id, int& money); //���̵� �� ����� �ݾ� Ȯ��
void noFound(); //�ش�Ǵ� ���̵� ã�� �� ���� ��� ȣ��
void withdrawal(); //���� ���
void ViewAllInformation(); //��� ���� Ȯ��

int main() {
	int input = 0;
	while (true)
	{
		printMenu();
		selectedInput(input);
		chosenMenu(input);
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

void selectedInput(int& input) {
	cout << "�޴� ���� : ";
	cin >> input;
}

void chosenMenu(int input) {
	switch (input)
	{
	case CREATE:
		cout << "\n[���°���]" << endl;
		createAccount();
		break;
	case PLUS:
		cout << "\n[��    ��]" << endl;
		deposit();
		break;
	case MINUS:
		cout << "\n[��    ��]" << endl;
		break;
	case ALLINFOF:
		cout << "\n[��ü ���]" << endl;
		ViewAllInformation();
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
	char name[MAX_LENGHT], personalNumber[MAX_NUMBER];

	if (index < MAX_USER) {
		inputInformation(id, money, name, personalNumber);

		if (id <= 0) {
			cout << "ERROR : ���¹�ȣ�� 0���� ���� ������ �Է��� �Ͽ����ϴ�." << endl;
			return;
		}
		if (money < 10) {
			cout << "ERROR : �Ա� �ݾ��� 10���� ���� ������ �Է��� �Ͽ����ϴ�." << endl;
			return;
		}

		if (foundID(id)) {
			if (!isOverlapUser(personalNumber)) {
				account[index++] = Bank(id, money, personalNumber, name);
				cout << endl;
			}
			else {
				cout << "ERROR : ����� �ߺ�" << endl << endl;;
				return;
			}
		}
		else {
			cout << "ERROR : ���¹�ȣ �ߺ�" << endl << endl;;
			return;
		}
	}
	else
		cout << "100�� ������ ���� ������ �����մϴ�. ���� �� : " << index + 1 << endl << endl;
}

void inputInformation(int& id, int& money, char name[], char personalNumber[]) {
	cout << "���� ��ȣ : ";
	cin >> id;
	cout << "����� �̸� : ";
	cin >> name;
	cout << "����� �ֹε�Ϲ�ȣ �Է�(000000-0000000) : ";
	cin >> personalNumber;
	cout << "���� �ܾ� �Է� : ";
	cin >> money;
}

int foundID(int id) {
	for (int i = 0; i < index; i++) {
		int getID = account[i].getAccID();
		if (getID == id) {
			return i;
		}
	}

	return -1;
}

bool isOverlapUser(char personalNumber[]) {
	for (int i = 0; i < index; i++) {
		if (!strcmp(personalNumber, account[i].getPersonalNumber())) {
			return true;
		}
	}

	return false;
}

void deposit() {
	int id, money, idx;

	if (isHadInformation) {
		inputInformation(id, money);

		if ((idx = foundID(id)) != -1)
			account[idx].plusMoney(money);
		else
			noFound();
	}
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

void inputInformation(int& id, int& money) {
	cout << "���¹�ȣ�� �Է����ּ��� : ";
	cin >> id;
	cout << "�Ա� �ݾ��� �Է����ּ��� : ";
	cin >> money;
}

void noFound() {
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;

	printf("\n");
}

void withdrawal() {
	int id, money, idx;

	if (isHadInformation()) {
		inputInformation(id, money);

		if ((idx = foundID(id)) != -1) {
			if (money < account[idx].getBalance())
				account[idx].minusMoney(money);
			else
				cout << "�ѵ��ʰ�" << endl;
		}
		else
			noFound();
	}

	printf("\n");
}

void ViewAllInformation() {
	if (index > 0)
		for (int i = 0; i < index; i++) {
			account[i].printInformation();
		}
	else
		cout << "�����ϴ� ���°� ���� " << endl;
}