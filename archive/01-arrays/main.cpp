#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;

struct Card
{
	string type;
	int number = 0;
	string owner;
	int daysLeft = 0;
	int balance = 0;
	int ridesAmount = 0;
};

const int MAX_CARD = 100;

int randNumber(int a = 10000, int b = 99999)
{
	return a + rand() % (b - a + 1);
}

int findByNumber(Card cards[], int cardCnt, int number)
{
	for (int i = 0; i < cardCnt; i++)
	{
		if (cards[i].number == number)
			return i;
	}
	return -1;
}

void addCard(Card cards[], int& cardCnt) {
	if (cardCnt == MAX_CARD)
	{
		cout << "Нет мест, добавление невозможно.\n";
		return;
	}
	Card temp; int num;

	bool unique;
	do {
		num = randNumber();
		unique = true;                    
		for (int i = 0; i < cardCnt; i++) {
			if (cards[i].number == num) {
				unique = false;
				break;                    
			}
		}
	} while (!unique);

	temp.number = num;


	cout << "Номер вашей карты: " << temp.number << "\n";
	cout << "ФИО владельца: "; 
	cin.ignore();
	getline(cin, temp.owner);
	cout << "Выберите тип карты: \n";
	cout << "1. Безлимитная\n";
	cout << "2. Карта-кошелек\n";
	cout << "3. Разовая\n";
	int x; cin >> x;
	switch (x) {
	case 1:
		temp.type = "Безлимитная";
		cout << "Дней действия: ";
		cin >> temp.daysLeft;
		break;
	case 2:
		temp.type = "Карта кошелек";
		cout << "Начальный баланс : ";
		cin >> temp.balance;
		break;
	case 3:
		temp.type = "Разовая";
		cout << "Количество поездок: ";
		cin >> temp.ridesAmount;
		break;
	default:
		cout << "Неверная команда. Создана карта на одну поездку.\n";
		temp.type = "Разовая";
		temp.ridesAmount = 1;
		break;
	}

	cout << "Элемент добавлен\n";
	cout << endl;
	cards[cardCnt] = temp;
	cardCnt++;

}



void availableCards(Card cards[], int cardCnt){
	if (cardCnt == 0)
	{
		cout << "Массив пустой.\n";
		return;
	}

	cout << " " << string(105, '-') << endl;
	cout << "  |" << "  |      Номер      |      Тип    |              ФИО               |           | Остаток | Количество |" << endl;
	cout << "  |" << "  |      карты      |     карты   |           владельца            |  Баланс   |   дней  |  поездок   |" << endl;
	cout << " " << string(105, '-') << endl;
	for (int i = 0; i < cardCnt; i++)
	{
		cout << left << "  |" << setw(2) << i + 1 << "|" << setw(17) << cards[i].number << '|' << setw(13) << cards[i].type << "|" << setw(32) << cards[i].owner << "|" << setw(11) << cards[i].balance << "|" << setw(9) << cards[i].daysLeft << "|" << setw(12) << cards[i].ridesAmount << "|" << right << endl;
	}
	cout << " " << string(105, '-') << endl;
}

void deleteCards(Card cards[], int& cardCnt) {
	if (cardCnt == 0)
	{
		cout << "Удаление невозможно. Массив пустой.\n";
		return;
	}

	cout << "Введите номер карты, которую нужно удалить: ";
	int ind = -1; char q; int num; cin >> num;

	ind = findByNumber(cards, cardCnt, num);
	if (ind == -1) 
	{
		cout << "Карты с данным номером не существует.\n";
		return;
	}
	cout << "Выбранная карта:\n";
	cout << cards[ind].number << " " << cards[ind].type << " " << cards[ind].owner << " " << cards[ind].balance << " " << cards[ind].daysLeft << " " << cards[ind].ridesAmount;
	cout << "\nУдалить карту? (Y/N): "; cin >> q;
	if (q == 'N') {
		cout << "Отмена удаления\n";
		return;
	}
	if (q != 'Y') {
		cout << "Неверный выбор\n";
		return;
	}
	for (int i = ind + 1; i < cardCnt; i++) 
		cards[i - 1] = cards[i];
	cardCnt--;
	cout << "Запись удалена\n";

}

void addBalance(Card cards[], int cardCnt) {
	if (cardCnt == 0)
	{
		cout << "Массив пустой.\n";
		return;
	}
	int num;
	cout << "Введите номер карты, которую нужно пополнить: ";
	cin >> num;
	char q; int addB; int ind;
	ind = findByNumber(cards, cardCnt, num);
	if (ind == -1)
	{
		cout << "Карта не найдена\n";
		return;
	}

	if (cards[ind].type == "Безлимитная") {
		cout << "Тип карты : " << cards[ind].type << "\n";
		cout << "Осталось дней: " << cards[ind].daysLeft << "\n";
		cout << "Хотите пополнить ? (Y/N)\n";
		cin >> q;
		if (q == 'N') {
			cout << "Пополнение отменено\n";
			return;
		}
		if (q != 'Y') {
			cout << "Неверный выбор\n";
			return;
		}
		cout << "Введите количество дней: ";
		cin >> addB;
		cards[ind].daysLeft += addB;
		cout << "Осталось дней: " << cards[ind].daysLeft << "\n";
		return;
	}
	else if (cards[ind].type == "Карта кошелек")
	{
		cout << "Тип карты : " << cards[ind].type << "\n";
		cout << "Ваш баланс: " << cards[ind].balance << " рублей \n";
		cout << "Хотите пополнить ? (Y/N)\n";
		cin >> q;
		if (q == 'N') {
			cout << "Пополнение отменено\n";
			return;
		}
		if (q != 'Y') {
			cout << "Неверный выбор\n";
			return;
		}
		cout << "Введите значение для увеличения баланса: ";
		cin >> addB;
		cards[ind].balance += addB;
		cout << "Ваш баланс: " << cards[ind].balance << endl;
		return;
	}
	else
	{
		cout << "Тип карты : " << cards[ind].type << "\n";
		cout << "Количество доступных поездок: " << cards[ind].ridesAmount << "\n";
		cout << "Хотите пополнить ? (Y/N)\n";
		cin >> q;
		if (q == 'N') {
			cout << "Пополнение отменено\n";
			return;
		}
		if (q != 'Y') {
			cout << "Неверный выбор\n";
			return;
		}
		cout << "Введите количество поездок: ";
		cin >> addB;
		cards[ind].ridesAmount += addB;
		cout << "Количество доступных поездок: " << cards[ind].ridesAmount << "\n";
		return;
	}
}

void checkBalance(Card cards[], int cardCnt) {
	if (cardCnt == 0)
	{
		cout << "Массив пустой.\n";
		return;
	}

	int num; int ind;
	cout << "Введите номер карты: ";
	cin >> num;
	ind = findByNumber(cards, cardCnt, num);
	if (ind == -1)
	{
		cout << "Карта не найдена\n";
		return;
	}
	if (cards[ind].type == "Безлимитная")
	{
		cout << "Осталось дней: " << cards[ind].daysLeft << "\n";
		return;
	}
	else if (cards[ind].type == "Карта кошелек")
	{
		cout << "Осталось рублей: " << cards[ind].balance << "\n";
		return;
	}
	else
	{
		cout << "Осталось поездок: " << cards[ind].ridesAmount << "\n";
		return;
	}
}

void findCard(Card cards[], int cardCnt) {
	if (cardCnt == 0)
	{
		cout << "Массив пустой.\n";
		return;
	}

	int ind; int num;
	cout << "Введите номер карты, которую ищите: ";
	cin >> num;
	ind = findByNumber(cards, cardCnt, num);
	if (ind == -1){
		cout << "Карта не найдена\n";
		return;
	}
	cout << "===== Информация о карте =====\n";
	cout << "Номер: " << cards[ind].number << "\n";
	cout << "Тип: " << cards[ind].type << "\n";
	cout << "Владелец: " << cards[ind].owner << "\n";

	if (cards[ind].type == "Безлимитная") {
		cout << "Дней осталось: " << cards[ind].daysLeft << "\n";
		return;
	}
	else if (cards[ind].type == "Карта кошелек")
	{
		cout << "Баланс: " << cards[ind].balance << " руб.\n";
		return;
	}
	else
	{
		cout << "Поездок осталось: " << cards[ind].ridesAmount << "\n";
		return;
	}
}

void personalCard(Card cards[], int cardCnt, Card personalCards[], int& persCnt)
{
	if (cardCnt == 0)
	{
		cout << "Массив пустой.\n";
		return;
	}
	cout << "Поиск всех карт, конкретного человека\n";
	string name; persCnt = 0;
	cout << "Введите ФИО: ";
	cin.ignore();
	getline(cin, name);
	for (int i = 0; i < cardCnt; i++)
	{
		if (name == cards[i].owner)
		{
			personalCards[persCnt] = cards[i];
			persCnt++;
		}
	}

	availableCards(personalCards, persCnt);

}


void saveIntoFile(Card cards[], int cardCnt) {
	string fileName;
	cout << "Имя файла для сохранения: ";
	cin >> fileName;

	ofstream fout(fileName);
	if (fout.fail()) {
		cout << "Не удалось открыть файл " << fileName << "\n";
		return;
	}

	fout << cardCnt << "\n";

	for (int i = 0; i < cardCnt; i++) 
	{
		fout << cards[i].number << "\n";
		fout << cards[i].type << "\n";
		fout << cards[i].owner << "\n";
		fout << cards[i].daysLeft << " "
			<< cards[i].balance << " "
			<< cards[i].ridesAmount << "\n";
	}
	fout.close();
	cout << "Сохранено " << cardCnt << " карт в " << fileName << "\n";
}


void loadFromFile(Card cards[], int& cardCnt) {
	string fileName;
	cout << "Введите имя файла для загрузки массива: ";
	cin >> fileName;

	ifstream fin(fileName);
	if (fin.fail()) {
		cout << "Не удалось открыть файл " << fileName << "\n";
		return;
	}

	int n;
	fin >> n;

	if (n <= 0 || n > MAX_CARD) {
		cout << "Некорректное количество карт " << n << "\n";
		return;
	}

	for (int i = 0; i < n; i++) 
	{

		fin >> cards[i].number;
		fin.ignore(10000, '\n');
		getline(fin, cards[i].type);
		getline(fin, cards[i].owner);
		fin >> cards[i].daysLeft
			>> cards[i].balance
			>> cards[i].ridesAmount;
		fin.ignore(10000, '\n');
	}

	cardCnt = n;
	fin.close();
	cout << "Загружено " << n << " карт из " << fileName << "\n";

}


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	Card cards[MAX_CARD]; int cardCnt = 0; int choice;
	Card persCards[MAX_CARD]; int persCnt = 0;
	while (true) {
		cout << "===== ТРАНСПОРТНЫЕ КАРТЫ =====\n";
		cout << "1. Добавить карту\n";
		cout << "2. Доступные карты\n";
		cout << "3. Удалить карту\n";
		cout << "4. Пополнить баланс\n";
		cout << "5. Узнать баланс\n";
		cout << "6. Поиск карты по номеру\n";
		cout << "7. Поиск всех карт, конкретного человека\n";
		cout << "8. Сохранить в файл\n";
		cout << "9. Загрузить из файла\n";
		cout << "10. Выйти\n";
		cout << "Выберите действие: ";
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			string s;

			cin >> s;
			cout << "\nЭто не пункт меню\n";
			continue;
		}

		switch (choice) {
		case 1:
			addCard(cards, cardCnt);
			system("pause");
			break;
		case 2:
			availableCards(cards, cardCnt);
			system("pause");
			break;
		case 3:
			deleteCards(cards, cardCnt);
			system("pause");
			break;
		case 4:
			addBalance(cards, cardCnt);
			system("pause");
			break;
		case 5:
			checkBalance(cards, cardCnt);
			system("pause");
			break;
		case 6:
			findCard(cards, cardCnt);
			system("pause");
			break;
		case 7:
			personalCard(cards, cardCnt, persCards, persCnt);
			system("pause");
			break;
		case 8:
			saveIntoFile(cards, cardCnt);
			system("pause");
			break;
		case 9:
			loadFromFile(cards, cardCnt);
			system("pause");
			break;
		case 10:
			cout << "До свидания.\n";
			return 0;
		default: 
			cout << "Неверная команда\n";
			system("pause");
			break;
		}
	}
}

