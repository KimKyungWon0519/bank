#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX_USER 100
#define MAX_LENGHT 20
#define MAX_NUMBER 15

int index = 0;

using namespace std;

enum {
	CREATE = 1, //계좌생성
	PLUS = 2, //계좌입금
	MINUS = 3, //계좌출금
	ALLINFOF = 4, //계좌조회
	EXIT = 5 //종료
};

class Bank
{
public:
	Bank(); //맴버변수 초기화
	Bank(int ID, int money, char* personalNumber, char* name); //맴버변수 재정의
	~Bank(); //맴버변수 소멸
	int getAccID(); //accID 가져오기
	int getBalance(); //balance 가져오기
	void plusMoney(int money); //입금
	void minusMoney(int money); //출금
	void printInformation(); //정보 출력
	char* getPersonalNumber(); //personalNumber 가져오기
	
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
	cout << "계좌 번호 : " << accID << endl;
	cout << "사용자 이름 : " << cusName << endl;
	cout << "사용자 주민등록 번호 : " << personalNumber << endl;
	cout << "계좌 금액 : " << balance << endl;
}

Bank* account = new Bank[MAX_USER];
  
void printMenu(); //메뉴 출력
void selectedInput(int& input); //번호 입력
void chosenMenu(int input); //메뉴 선택
void createAccount(); //계좌 생성
void inputInformation(int& id, int& money, char name[], char personalNumber[]); //개인정보 입력
int foundID(int id); //아이디 찾기
bool isOverlapUser(char personalNumber[]); //주민등록번호 중복 확인
void deposit(); //계좌 입금
bool isHadInformation(); //현재 계좌에 가입한 사람이 있는 지 확인
void inputInformation(int& id, int& money); //아이디 및 입출금 금액 확인
void noFound(); //해당되는 아이디를 찾을 수 없을 경우 호출
void withdrawal(); //계좌 출금
void ViewAllInformation(); //모든 정보 확인

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

void chosenMenu(int input) {
	switch (input)
	{
	case CREATE:
		cout << "\n[개좌개설]" << endl;
		createAccount();
		break;
	case PLUS:
		cout << "\n[입    금]" << endl;
		deposit();
		break;
	case MINUS:
		cout << "\n[출    금]" << endl;
		break;
	case ALLINFOF:
		cout << "\n[전체 출력]" << endl;
		ViewAllInformation();
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

void createAccount() {
	int id, money;
	char name[MAX_LENGHT], personalNumber[MAX_NUMBER];

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
				account[index++] = Bank(id, money, personalNumber, name);
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

void inputInformation(int& id, int& money, char name[], char personalNumber[]) {
	cout << "계좌 번호 : ";
	cin >> id;
	cout << "사용자 이름 : ";
	cin >> name;
	cout << "사용자 주민등록번호 입력(000000-0000000) : ";
	cin >> personalNumber;
	cout << "계좌 잔액 입력 : ";
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
		cout << "정보없음" << endl;
		printf("\n");
		return false;
	}
	else {
		return true;
	}
}

void inputInformation(int& id, int& money) {
	cout << "계좌번호를 입력해주세요 : ";
	cin >> id;
	cout << "입금 금액을 입력해주세요 : ";
	cin >> money;
}

void noFound() {
	cout << "유효하지 않은 ID 입니다." << endl;

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
				cout << "한도초과" << endl;
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
		cout << "존재하는 계좌가 없음 " << endl;
}