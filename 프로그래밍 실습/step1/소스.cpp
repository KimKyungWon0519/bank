#include <iostream>

#define NAME_LEN 20

using namespace std;

typedef struct account {
	int accID; //계좌번호
	int balance; //잔액
	char cusNmae[NAME_LEN]; //고객이름
}Account;

enum {
	CREATE = 1, //계좌생성
	PLUS = 2, //계좌입금
	MINUS = 3, //계좌출금
	ALLINFOF = 4, //계좌조회
	EXIT = 5 //종료
};

Account* account = new Account[100];
int index = 0;

void printMenu(); // 메뉴 출력
void inputInformation(int& id, int& money); //입출 계좌번호, 금액 입력
void noFound(); //ID가 없을 때 오류 출력 
void selectNumber(int& input); //메뉴 번호 입력 
void chooseMenu(int input); //메뉴 선택
void createAccount(); //계좌 생성
void plusMoney(); //계좌 입금
void minusMoney(); //계좌 출금
void viewAllInfor(); //계좌 조회
bool isHadInformation(); //계좌가 있는지 없는지 판단
int foundID(int id); //계좌 번호 찾기

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
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void inputInformation(int& id, int& money) {
	cout << "계좌ID : ";
	cin >> id;

	while (true) {
		cout << "금  액 : ";
		cin >> money;

		if (money > 0)
			break;
		else
			cout << "0보다 더 큰 수를 입력해주세요." << endl;
	}
}

void noFound() {
	cout << "유효하지 않은 ID 입니다." << endl;

	printf("\n");
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

void selectNumber(int& input) {
	cout << "선택 : ";
	cin >> input;
}

void chooseMenu(int input) {
	switch (input)
	{
	case CREATE:
		cout << "\n[개좌개설]" << endl;
		createAccount();
		break;
	case PLUS:
		cout << "\n[입    금]" << endl;
		plusMoney();
		break;
	case MINUS:
		cout << "\n[출    금]" << endl;
		minusMoney();
		break;
	case ALLINFOF:
		cout << "\n[전체 출력]" << endl;
		viewAllInfor();
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
	char name[20];

	if (index < 100) {
		cout << "계좌ID : ";
		cin >> id;
		cout << "이  름 : ";
		cin >> name;
		cout << "입금액 : ";
		cin >> money;

		if (id <= 0) {
			cout << "계좌 생성 실패 : id값을 0보다 더 큰 수를 입력해주세요" << endl;
			return;
		}
		else if (money < 10) {
			cout << "계좌 생성 실패 : 금액을 10보다 더 큰 수를 입력해주세요" << endl;
			return;
		}


		if (foundID(id) == -1) {
			account[index].accID = id;
			strcpy_s(account[index].cusNmae, name);
			account[index].balance = money;

			index++;
		}
		else {
			cout << "계좌번호가 중복됩니다." << endl;
		}
	}
	else
		cout << "100명의 고객까지만 가입이 가능합니다." << endl;

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
				cout << "한도초과" << endl;
		}
		else
			noFound();
	}

	printf("\n");
}

void viewAllInfor() {
	if (index > 0) {
		for (int i = 0; i < index; i++) {
			cout << "계좌ID : " << account[i].accID << endl;
			cout << "이  름 : " << account[i].cusNmae << endl;
			cout << "잔  액 : " << account[i].balance << endl;
			printf("\n");
		}
	}
	else
		cout << "정보가 없음" << endl;

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