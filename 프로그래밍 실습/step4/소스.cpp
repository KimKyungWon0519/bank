#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 200

enum {
	CREATE_NORMAL = 1, //예금계좌 생성
	CREATE_DEPOSIT = 2, //보통계좌 생성
	PLUS = 3, //계좌입금
	MINUS = 4, //계좌출금
	ALLINFOF = 5, //계좌조회
	EXIT = 6 //종료
};

using namespace std;

class NormalBank {
protected:
	const int accID; //계좌 번호
	int balance; //계좌 금액
	string const personalNumber; //주민등록번호
	string cusName; //사용자 이름
	bool hadDepositBank; // 예금 계좌가 있는지 확인

public:
	NormalBank();
	NormalBank(const NormalBank& ref);
	NormalBank(int id, int money, string number, string name); //맴버변수 초기화
	virtual ~NormalBank() {};
	int getAccID(); //Id 가져 오기
	string getPersonalNumber(); //주민등록번호 가져오기
	virtual void plusMoney(int money); //금액 증가
	int getBalance(); //금액 가져오기
	void minusMoney(int money); //금액 감소
	virtual void printInformation(); //모든 맴버 변수 출력
	bool getHadDepositBank(); //예금 계좌 존재 확인 변수 가져오기
	void setHadDepositBank(bool value); //예금 계좌 존재 확인 변수 값 바꾸기
	string getName(); // 사용자 이름 가져오기
};

class DepositBank : public NormalBank {
public:
	DepositBank(int newAccID, NormalBank newBank) : NormalBank(newAccID, 0, newBank.getPersonalNumber(), newBank.getName()) {} // 예금 계좌 생성
	~DepositBank() {}
	void plusMoney(int money); // 입금
	void printInformation(); //출력
};

class AccountManager {
	NormalBank* account[MAX_USER]; //배열 생성
	int index = 0; //배열 인덱스

	void inputInformation(int& id, int& money, string& name, string& personalNumber); //보통 계좌 생성 정보 입력
	void inputInformation(int& id, string& personalNumber); //예금 계좌 생성 정보 입력
	int foundID(int id); //계좌가 있으면 해당 아이디의 인덱스 반환, 없으면 -1 반환
	int isOverlapUser(string personalNumber); //사용자가 중복 확인
	bool isHadInformation(); //생성된 계좌가 없으면 false 반환, 있으면 true
	void inputInformation(int& id, int& money); //계좌 번호와 금액 입력
	void noFound(); //계좌가 존재하지 않음을 출력
public:
	void createNomalBank(); //보통 계좌 계좌 생성
	void createDepositBank(); //예금 계좌 생성
	void deposit(); //계좌 입금
	void withdrawal(); //계좌 출금
	void viewAllInformation(); //계좌 전체 출력
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
	cout << "1. 보통계좌 개설" << endl;
	cout << "2. 예금계좌 개설" << endl;
	cout << "3. 입    금" << endl;
	cout << "4. 출    금" << endl;
	cout << "5. 계좌정보 전체 출력" << endl;
	cout << "6. 프로그램 종료" << endl;
}

void selectedInput(int& input) {
	cout << "메뉴 선택 : ";
	cin >> input;
}

void chosenMenu(int input, AccountManager* accoutManger) {
	switch (input)
	{
	case CREATE_NORMAL:
		cout << "\n[보통 개좌 개설]" << endl;
		(*accoutManger).createNomalBank();
		break;
	case CREATE_DEPOSIT:
		cout << "\n[예금 계좌 개설]" << endl;
		(*accoutManger).createDepositBank();
		break;
	case PLUS:
		cout << "\n[입    금]" << endl;
		(*accoutManger).deposit();
		break;
	case MINUS:
		cout << "\n[출    금]" << endl;
		(*accoutManger).withdrawal();
		break;
	case ALLINFOF:
		cout << "\n[전체 출력]" << endl << endl;;
		(*accoutManger).viewAllInformation();
		cout << "-------------------------------------------------\n" << endl;
		break;
	case EXIT:
		cout << "프로그램을 종료합니다." << endl;
		exit(0);
		break;
	default:
		cout << "잘못된 번호를 입력하셨습니다." << endl;
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
			cout << "ERROR : 계좌번호를 0보다 작은 값으로 입력을 하였습니다." << endl << endl;;
			return;
		}
		if (money < 10) {
			cout << "ERROR : 입금 금액을 10보다 작은 값으로 입력을 하였습니다." << endl << endl;
			return;
		}

		if (foundID(id) == -1) {
			if (isOverlapUser(personalNumber) == -1) {
				account[index++] = new NormalBank(id, money, personalNumber, name);
				cout << endl;
			}
			else {
				cout << "ERROR : 사용자 중복" << endl << endl;;
				return;
			}
		}
		else {
			cout << "ERROR : 계좌번호 중복" << endl << endl;;
			return;
		}
	}
	else
		cout << "ERROR : 100명 이하의 고객만 가입이 가능합니다. 현재 고객 : " << index + 1 << endl << endl;
}

void AccountManager::createDepositBank() {
	string personalNumber = "";
	int accID, idx;

	if (isHadInformation()) {
		inputInformation(accID, personalNumber);

		if (accID <= 0) {
			cout << "ERROR : 계좌번호를 0보다 작은 값으로 입력을 하였습니다." << endl << endl;;
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
					cout << "ERROR : 계좌번호가 중복 되었습니다." << endl << endl;
				}
			}
			else {
				cout << "ERROR : 이미 예금계좌가 존재합니다." << endl << endl;
			}
		}
		else {
			cout << "ERROR : 사용자가 존재하지 않습니다." << endl << endl;
		}
	}
}

void AccountManager::inputInformation(int& id, int& money, string& name, string& personalNumber) {
	cout << "계좌 번호 : ";
	cin >> id;
	cout << "사용자 이름 : ";
	cin >> name;
	cout << "사용자 주민등록번호 입력(000000-0000000) : ";
	cin >> personalNumber;
	cout << "계좌 잔액 입력 : ";
	cin >> money;
}

void AccountManager::inputInformation(int& id, string& personalNumber) {
	cout << "사용자 주민등록번호 입력(000000-0000000) : ";
	cin >> personalNumber;
	cout << "계좌 번호 : ";
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
			cout << "ERROR : 금액은 1원보다 더 작은 액수로 넣을 수 없습니다." << endl << endl;;
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
		cout << "ERROR : 사용자가 존재하지 않음" << endl;
		printf("\n");
		return false;
	}
	else {
		return true;
	}
}

void AccountManager::inputInformation(int& id, int& money) {
	cout << "계좌번호를 입력해주세요 : ";
	cin >> id;
	cout << "금액을 입력해주세요 : ";
	cin >> money;
}

void AccountManager::noFound() {
	cout << "유효하지 않은 ID 입니다." << endl;

	printf("\n");
}

void AccountManager::withdrawal() {
	int id, money, idx;

	if (isHadInformation()) {
		inputInformation(id, money);

		if (money < 1) {
			cout << "ERROR : 금액은 1원보다 더 작은 액수로 넣을 수 없습니다." << endl << endl;;
			return;
		}
		if ((idx = foundID(id)) != -1) {
			if (money < account[idx]->getBalance())
				account[idx]->minusMoney(money);
			else
				cout << "한도초과" << endl;
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
		cout << "존재하는 계좌가 없음 " << endl;
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
	cout << "이자액 : " << interest << endl << endl;
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
	cout << "사용자 주민등록 번호 : " << personalNumber << endl;
	cout << "사용자 이름 : " << cusName << endl << endl;
	cout << "[보통 계좌]" << endl;
	cout << "계좌 번호 : " << accID << endl;
	cout << "계좌 금액 : " << balance << endl << endl << endl;;
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
	cout << "이자액 : " << interest << endl << endl;;
	balance += interest;
}

void DepositBank::printInformation() {
	cout << "[에금 계좌]" << endl;
	cout << "계좌 번호 : " << accID << endl;
	cout << "계좌 금액 : " << balance << endl << endl;
}