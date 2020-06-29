#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 100

enum {
	CREATE = 1, //계좌생성
	PLUS = 2, //계좌입금
	MINUS = 3, //계좌출금
	ALLINFOF = 4, //계좌조회
	EXIT = 5 //종료
};

using namespace std;

class Bank {
	const int accID; //계좌 번호
	int balance; //계좌 금액
	string const personalNumber; //주민등록번호
	string cusName; //사용자 이름

public:
	Bank();
	Bank(const Bank& ref);
	Bank(int id, int money, string number, string name); //맴버변수 초기화
	int getAccID(); //Id 가져 오기
	string getPersonalNumber(); //주민등록번호 가져오기
	void plusMoney(int money); //금액 증가
	int getBalance(); //금액 가져오기
	void minusMoney(int money); //금액 감소
	void printInformation(); //모든 맴버 변수 출력
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
	cout << "계좌 번호 : " << accID << endl;
	cout << "사용자 이름 : " << cusName << endl;
	cout << "사용자 주민등록 번호 : " << personalNumber << endl;
	cout << "계좌 금액 : " << balance << endl;
}

class AccountManager {
	Bank* account[MAX_USER]; //배열 생성
	int index = 0; //배열 인덱스

	void inputInformation(int& id, int& money, string& name, string& personalNumber); //계좌 생성 정보 입력
	int foundID(int id); //계좌가 있으면 해당 아이디의 인덱스 반환, 없으면 -1 반환
	bool isOverlapUser(string personalNumber); //사용자가 중복되면 true, 아니면 false
	bool isHadInformation(); //생성된 계좌가 없으면 false 반환, 있으면 true
	void inputInformation(int& id, int& money); //계좌 번호와 금액 입력
	void noFound(); //계좌가 존재하지 않음을 출력
public:
	void createAccount(); //계좌 생성
	void deposit(); //계좌 입금
	void withdrawal(); //계좌 출금
	void viewAllInformation(); //계좌 전체 출력
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
			cout << "ERROR : 계좌번호를 0보다 작은 값으로 입력을 하였습니다." << endl;
			return;
		}
		if (money < 10) {
			cout << "ERROR : 입금 금액을 10보다 작은 값으로 입력을 하였습니다." << endl;
			return;
		}

		if (foundID(id)) {
			if (!isOverlapUser(personalNumber)) {
				account[index++] = new Bank(id, money, personalNumber, name);
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
		cout << "100명 이하의 고객만 가입이 가능합니다. 현재 고객 : " << index + 1 << endl << endl;
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
		cout << "정보없음" << endl;
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
	cout << "입금 금액을 입력해주세요 : ";
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
		}
	else
		cout << "존재하는 계좌가 없음 " << endl;
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
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void selectedInput(int& input) {
	cout << "메뉴 선택 : ";
	cin >> input;
}

void chosenMenu(int input, AccountManager* accoutManger) {
	switch (input)
	{
	case CREATE:
		cout << "\n[개좌개설]" << endl;
		(*accoutManger).createAccount();
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
		cout << "\n[전체 출력]" << endl;
		(*accoutManger).viewAllInformation();
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