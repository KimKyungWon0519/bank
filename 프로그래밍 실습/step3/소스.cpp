#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 100

enum {
	CREATE = 1, //���»���
	PLUS = 2, //�����Ա�
	MINUS = 3, //�������
	ALLINFOF = 4, //������ȸ
	EXIT = 5 //����
};

using namespace std;

class Bank {
	const int accID; //���� ��ȣ
	int balance; //���� �ݾ�
	string const personalNumber; //�ֹε�Ϲ�ȣ
	string cusName; //����� �̸�

public:
	Bank();
	Bank(const Bank& ref);
	Bank(int id, int money, string number, string name); //�ɹ����� �ʱ�ȭ
	int getAccID(); //Id ���� ����
	string getPersonalNumber(); //�ֹε�Ϲ�ȣ ��������
	void plusMoney(int money); //�ݾ� ����
	int getBalance(); //�ݾ� ��������
	void minusMoney(int money); //�ݾ� ����
	void printInformation(); //��� �ɹ� ���� ���
};

Bank::Bank()
	:accID(-1), personalNumber("")
{
	cout << "Bank::Bank()" << endl;
	balance = -1;
	cusName = "";
}

Bank::Bank(int id, int money, string number, string name)
	: accID(id), personalNumber(number)
{
	balance = money;
	cusName = name;
}

Bank::Bank(const Bank& ref)
	:accID(ref.accID), personalNumber(ref.personalNumber)
{
	cout << "copy construct" << endl;
}

int Bank::getAccID() {
	return accID;
}

string Bank::getPersonalNumber() {
	return personalNumber;
}

void Bank::plusMoney(int money) {
	balance += money;
}

int Bank::getBalance() {
	return balance;
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

class AccountManager {
	Bank* account[MAX_USER]; //�迭 ����
	int index = 0; //�迭 �ε���

	void inputInformation(int& id, int& money, string& name, string& personalNumber); //���� ���� ���� �Է�
	int foundID(int id); //���°� ������ �ش� ���̵��� �ε��� ��ȯ, ������ -1 ��ȯ
	bool isOverlapUser(string personalNumber); //����ڰ� �ߺ��Ǹ� true, �ƴϸ� false
	bool isHadInformation(); //������ ���°� ������ false ��ȯ, ������ true
	void inputInformation(int& id, int& money); //���� ��ȣ�� �ݾ� �Է�
	void noFound(); //���°� �������� ������ ���
public:
	void createAccount(); //���� ����
	void deposit(); //���� �Ա�
	void withdrawal(); //���� ���
	void viewAllInformation(); //���� ��ü ���
	~AccountManager();
};

AccountManager::~AccountManager() {
	for (int i = 0; i < MAX_USER; i++)
		delete account[i];
}

void AccountManager::createAccount() {
	int id, money;
	string name, personalNumber;

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
				account[index++] = new Bank(id, money, personalNumber, name);
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

void AccountManager::inputInformation(int& id, int& money, string& name, string& personalNumber) {
	cout << "���� ��ȣ : ";
	cin >> id;
	cout << "����� �̸� : ";
	cin >> name;
	cout << "����� �ֹε�Ϲ�ȣ �Է�(000000-0000000) : ";
	cin >> personalNumber;
	cout << "���� �ܾ� �Է� : ";
	cin >> money;
}

int AccountManager::foundID(int id) {
	for (int i = 0; i < index; i++) {
		int getID = account[i]->getAccID();
		if (getID == id) {
			return i;
		}
	}

	return -1;
}

bool AccountManager::isOverlapUser(string personalNumber) {
	for (int i = 0; i < index; i++) {
		if (personalNumber == account[i]->getPersonalNumber()) {
			return true;
		}
	}

	return false;
}

void AccountManager::deposit() {
	int id, money, idx;

	if (isHadInformation()) {
		inputInformation(id, money);

		if ((idx = foundID(id)) != -1)
			account[idx]->plusMoney(money);
		else
			noFound();
	}
}

bool AccountManager::isHadInformation() {
	if (index == 0) {
		cout << "��������" << endl;
		printf("\n");
		return false;
	}
	else {
		return true;
	}
}

void AccountManager::inputInformation(int& id, int& money) {
	cout << "���¹�ȣ�� �Է����ּ��� : ";
	cin >> id;
	cout << "�Ա� �ݾ��� �Է����ּ��� : ";
	cin >> money;
}

void AccountManager::noFound() {
	cout << "��ȿ���� ���� ID �Դϴ�." << endl;

	printf("\n");
}

void AccountManager::withdrawal() {
	int id, money, idx;

	if (isHadInformation()) {
		inputInformation(id, money);

		if ((idx = foundID(id)) != -1) {
			if (money < account[idx]->getBalance())
				account[idx]->minusMoney(money);
			else
				cout << "�ѵ��ʰ�" << endl;
		}
		else
			noFound();
	}

	printf("\n");
}

void AccountManager::viewAllInformation() {
	if (index > 0)
		for (int i = 0; i < index; i++) {
			account[i]->printInformation();
		}
	else
		cout << "�����ϴ� ���°� ���� " << endl;
}

void printMenu();
void selectedInput(int& input);
void chosenMenu(int input, AccountManager* accoutManger);

int main() {
	AccountManager accoutManger;
	int input = 0;

	while (true)
	{
		printMenu();
		selectedInput(input);
		chosenMenu(input, &accoutManger);
	}
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

void chosenMenu(int input, AccountManager* accoutManger) {
	switch (input)
	{
	case CREATE:
		cout << "\n[���°���]" << endl;
		(*accoutManger).createAccount();
		break;
	case PLUS:
		cout << "\n[��    ��]" << endl;
		(*accoutManger).deposit();
		break;
	case MINUS:
		cout << "\n[��    ��]" << endl;
		(*accoutManger).withdrawal();
		break;
	case ALLINFOF:
		cout << "\n[��ü ���]" << endl;
		(*accoutManger).viewAllInformation();
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