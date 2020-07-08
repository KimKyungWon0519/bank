#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 200

enum {
	CREATE_NORMAL = 1, //���ݰ��� ����
	CREATE_DEPOSIT = 2, //������� ����
	PLUS = 3, //�����Ա�
	MINUS = 4, //�������
	ALLINFOF = 5, //������ȸ
	EXIT = 6 //����
};

using namespace std;

class NormalBank {
protected:
	const int accID; //���� ��ȣ
	int balance; //���� �ݾ�
	string const personalNumber; //�ֹε�Ϲ�ȣ
	string cusName; //����� �̸�
	bool hadDepositBank; // ���� ���°� �ִ��� Ȯ��

public:
	NormalBank();
	NormalBank(const NormalBank& ref);
	NormalBank(int id, int money, string number, string name); //�ɹ����� �ʱ�ȭ
	virtual ~NormalBank() {};
	int getAccID(); //Id ���� ����
	string getPersonalNumber(); //�ֹε�Ϲ�ȣ ��������
	virtual void plusMoney(int money); //�ݾ� ����
	int getBalance(); //�ݾ� ��������
	void minusMoney(int money); //�ݾ� ����
	virtual void printInformation(); //��� �ɹ� ���� ���
	bool getHadDepositBank(); //���� ���� ���� Ȯ�� ���� ��������
	void setHadDepositBank(bool value); //���� ���� ���� Ȯ�� ���� �� �ٲٱ�
	string getName(); // ����� �̸� ��������
};

class DepositBank : public NormalBank {
public:
	DepositBank(int newAccID, NormalBank newBank) : NormalBank(newAccID, 0, newBank.getPersonalNumber(), newBank.getName()) {} // ���� ���� ����
	~DepositBank() {}
	void plusMoney(int money); // �Ա�
	void printInformation(); //���
};

class AccountManager {
	NormalBank* account[MAX_USER]; //�迭 ����
	int index = 0; //�迭 �ε���

	void inputInformation(int& id, int& money, string& name, string& personalNumber); //���� ���� ���� ���� �Է�
	void inputInformation(int& id, string& personalNumber); //���� ���� ���� ���� �Է�
	int foundID(int id); //���°� ������ �ش� ���̵��� �ε��� ��ȯ, ������ -1 ��ȯ
	int isOverlapUser(string personalNumber); //����ڰ� �ߺ� Ȯ��
	bool isHadInformation(); //������ ���°� ������ false ��ȯ, ������ true
	void inputInformation(int& id, int& money); //���� ��ȣ�� �ݾ� �Է�
	void noFound(); //���°� �������� ������ ���
public:
	void createNomalBank(); //���� ���� ���� ����
	void createDepositBank(); //���� ���� ����
	void deposit(); //���� �Ա�
	void withdrawal(); //���� ���
	void viewAllInformation(); //���� ��ü ���
	~AccountManager();
};

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
	cout << "1. ������� ����" << endl;
	cout << "2. ���ݰ��� ����" << endl;
	cout << "3. ��    ��" << endl;
	cout << "4. ��    ��" << endl;
	cout << "5. �������� ��ü ���" << endl;
	cout << "6. ���α׷� ����" << endl;
}

void selectedInput(int& input) {
	cout << "�޴� ���� : ";
	cin >> input;
}

void chosenMenu(int input, AccountManager* accoutManger) {
	switch (input)
	{
	case CREATE_NORMAL:
		cout << "\n[���� ���� ����]" << endl;
		(*accoutManger).createNomalBank();
		break;
	case CREATE_DEPOSIT:
		cout << "\n[���� ���� ����]" << endl;
		(*accoutManger).createDepositBank();
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
		cout << "\n[��ü ���]" << endl << endl;;
		(*accoutManger).viewAllInformation();
		cout << "-------------------------------------------------\n" << endl;
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

AccountManager::~AccountManager() {
	for (int i = 0; i < MAX_USER; i++)
		delete account[i];
}

void AccountManager::createNomalBank() {
	int id, money;
	string name, personalNumber;

	if (index < MAX_USER) {
		inputInformation(id, money, name, personalNumber);

		if (id <= 0) {
			cout << "ERROR : ���¹�ȣ�� 0���� ���� ������ �Է��� �Ͽ����ϴ�." << endl << endl;;
			return;
		}
		if (money < 10) {
			cout << "ERROR : �Ա� �ݾ��� 10���� ���� ������ �Է��� �Ͽ����ϴ�." << endl << endl;
			return;
		}

		if (foundID(id) == -1) {
			if (isOverlapUser(personalNumber) == -1) {
				account[index++] = new NormalBank(id, money, personalNumber, name);
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
		cout << "ERROR : 100�� ������ ���� ������ �����մϴ�. ���� �� : " << index + 1 << endl << endl;
}

void AccountManager::createDepositBank() {
	string personalNumber = "";
	int accID, idx;

	if (isHadInformation()) {
		inputInformation(accID, personalNumber);

		if (accID <= 0) {
			cout << "ERROR : ���¹�ȣ�� 0���� ���� ������ �Է��� �Ͽ����ϴ�." << endl << endl;;
			return;
		}

		if ((idx = isOverlapUser(personalNumber)) != -1) {
			if (account[idx]->getHadDepositBank() == false) {


				if (foundID(accID) == -1) {
					account[idx + 100] = new DepositBank(accID, *account[idx]);
					account[idx]->setHadDepositBank(true);
					cout << endl;
				}
				else {
					cout << "ERROR : ���¹�ȣ�� �ߺ� �Ǿ����ϴ�." << endl << endl;
				}
			}
			else {
				cout << "ERROR : �̹� ���ݰ��°� �����մϴ�." << endl << endl;
			}
		}
		else {
			cout << "ERROR : ����ڰ� �������� �ʽ��ϴ�." << endl << endl;
		}
	}
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

void AccountManager::inputInformation(int& id, string& personalNumber) {
	cout << "����� �ֹε�Ϲ�ȣ �Է�(000000-0000000) : ";
	cin >> personalNumber;
	cout << "���� ��ȣ : ";
	cin >> id;

}

int AccountManager::foundID(int id) {
	for (int i = 0; i < index; i++) {
		int getID = account[i]->getAccID();
		if (getID == id) {
			return i;
		}
		if (account[i]->getHadDepositBank()) {
			getID = account[i + 100]->getAccID();
			if (getID == id) {
				return i;
			}
		}
	}

	return -1;
}

int AccountManager::isOverlapUser(string personalNumber) {
	for (int i = 0; i < index; i++) {
		if (personalNumber == account[i]->getPersonalNumber()) {
			return i;
		}
	}

	return -1;
}

void AccountManager::deposit() {
	int id, money, idx;

	if (isHadInformation()) {
		inputInformation(id, money);

		if (money < 1) {
			cout << "ERROR : �ݾ��� 1������ �� ���� �׼��� ���� �� �����ϴ�." << endl << endl;;
			return;
		}
		if ((idx = foundID(id)) != -1)
			account[idx]->plusMoney(money);
		else
			noFound();
	}
}

bool AccountManager::isHadInformation() {
	if (index == 0) {
		cout << "ERROR : ����ڰ� �������� ����" << endl;
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
	cout << "�ݾ��� �Է����ּ��� : ";
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

		if (money < 1) {
			cout << "ERROR : �ݾ��� 1������ �� ���� �׼��� ���� �� �����ϴ�." << endl << endl;;
			return;
		}
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
			if (account[i]->getHadDepositBank()) {
				account[i + 100]->printInformation();
			}
		}
	else
		cout << "�����ϴ� ���°� ���� " << endl;
}


NormalBank::NormalBank()
	:accID(-1), personalNumber("")
{
	balance = -1;
	cusName = "";
	hadDepositBank = false;
}

NormalBank::NormalBank(int id, int money, string number, string name)
	: accID(id), personalNumber(number)
{
	balance = money;
	cusName = name;
	hadDepositBank = false;
}

NormalBank::NormalBank(const NormalBank& ref)
	:accID(ref.accID), personalNumber(ref.personalNumber)
{
	balance = ref.balance;
	cusName = ref.cusName;
	hadDepositBank = ref.hadDepositBank;
}

int NormalBank::getAccID() {
	return accID;
}

string NormalBank::getPersonalNumber() {
	return personalNumber;
}

void NormalBank::plusMoney(int money) {
	int interest = 0;

	balance += money;
	interest = (double)(balance) * 0.01;
	cout << "���ھ� : " << interest << endl << endl;
	balance += interest;
}

int NormalBank::getBalance() {
	return balance;
}

void NormalBank::minusMoney(int money) {
	balance -= money;
}

void NormalBank::printInformation() {
	cout << "-------------------------------------------------" << endl << endl;
	cout << "����� �ֹε�� ��ȣ : " << personalNumber << endl;
	cout << "����� �̸� : " << cusName << endl << endl;
	cout << "[���� ����]" << endl;
	cout << "���� ��ȣ : " << accID << endl;
	cout << "���� �ݾ� : " << balance << endl << endl << endl;;
}

bool NormalBank::getHadDepositBank() {
	return hadDepositBank;
}

void NormalBank::setHadDepositBank(bool value) {
	hadDepositBank = value;
}

string NormalBank::getName() {
	return cusName;
}

void DepositBank::plusMoney(int money) {
	int interest = 0;

	balance += money;
	interest = (double)(balance) * 0.01;
	cout << "���ھ� : " << interest << endl << endl;;
	balance += interest;
}

void DepositBank::printInformation() {
	cout << "[���� ����]" << endl;
	cout << "���� ��ȣ : " << accID << endl;
	cout << "���� �ݾ� : " << balance << endl << endl;
}