#include <iostream>
#include <stack>
using namespace std;

const double Pi = acos(-1);

double Sin(double x) {
	return(round(sin(x) * 1000000) / 1000000);
}
double Cos(double x) {
	return(round(cos(x) * 1000000) / 1000000);
}
double ctg(double x) {
	double a = Cos(x);
	double b = Sin(x);
	return(a / b);
}

struct Leksema
{
	char type;
	double value;
};

bool Maths(stack <Leksema> & Stack_n, stack <Leksema> & Stack_o, Leksema & item)
{
	double a,b,c;
	a = Stack_n.top().value;//берется верхнее число из стека с числами
	Stack_n.pop();//удаляется верхнее число из стека с числами
	switch (Stack_o.top().type) {//проверка типа верхней операции из стека с операциями
		case '+'://если тип из верхней операции из стека с операциями сложение
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item); //результат операции кладется обратно в стек с числами
		Stack_o.pop();
		break;

		case '-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

		case '*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

		case '/':
		b = Stack_n.top().value;
		if (a == 0) {
			cerr << "\nНа ноль делить нельзя!\n";
			return false;
		}
		else {
			Stack_n.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		}
		case '^':
			b = Stack_n.top().value;
			Stack_n.pop();
			c = pow(b,a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		case 's':
			c = Sin(a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		case 'c':
			c = Cos(a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		case 't':
			if (Cos(a) == 0) {
				cerr << "\nНевереный аругмент для тангенса\n";
				return false;
			}
			else{
				c = tan(a);
				item.type = '0';
				item.value = c;
				Stack_n.push(item);
				Stack_o.pop();
				break;
			}
		case 'g':
			if (Sin(a) == 0) {
				cerr << "\nНевереный аругмент для котангенса\n";
				return false;
			}
			else {
				c = ctg(a);
				item.type = '0';
				item.value = c;
				Stack_n.push(item);
				Stack_o.pop();
				break;
			}
		case 'e':
			c = exp(a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;

		default:
			cerr << "\nОшибка!\n";
			return false;

	}
	return true;
}

int getRang(char Ch) {//Приоритеты: 1 для сложения и вычитания, 2 для деления умножения возведения в степень
	if (Ch == '+' || Ch == '-') return 1;
	if (Ch == '/' || Ch == '*') return 2;
	if (Ch == '^') return 3;
	if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') return 4;
	return 0;
}

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Калькулятор\n";
	cout << "Для возведения в степерь     |'^'  | Пример:5^2\n";
	cout << "Для использования числа Пи   |'p'  | Пример:p/2\n";
	cout << "Для использования синуса     |'sin'| Пример:sin(p/2)\n";
	cout << "Для использования косинуса   |'cos'| Пример:cos(p*2)\n";
	cout << "Для использования тангенса   |'tan'| Пример:tan(p/4)\n";
	cout << "Для использования котангенса |'ctg'| Пример:ctg(p/4)\n";
	cout << "Для использования экспоненты |'exp'| Пример:sin(exp(6)/3-5)^2+cos(exp(6)/3-5)^2\n";
	cout << "Введите выражение: ";
	char Ch; // переменная в которую записывается текущий обрабатываемый символ
	double value;
	bool flag = 1;// ралзичие унарного минуса от вычитания
	stack <Leksema> Stack_n;//стек с числами
	stack <Leksema> Stack_o;//стек с операциями
	Leksema item;
	while (true) {
		Ch = cin.peek();//смотрим на первый символ
		cout << Ch << endl;
		if (Ch == '\n') break;//если достигнут конец строки, выходим из цикла
		if (Ch == ' ') {//игнорируем пробелы
			cin.ignore();
			continue;
		}
		if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e') {
			char foo[3];
			for (int i = 0;i < 3;i++) {
				Ch = cin.peek();
				foo[i] = Ch;
				cin.ignore();
			}
			if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') {
					item.type = 's';
					item.value = 0;
					Stack_o.push(item);	//операция кладётся в стек с операциями
					continue;
			}
			if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') {
				item.type = 'c';
				item.value = 0;
				Stack_o.push(item);	//операция кладётся в стек с операциями
				continue;
			}
			if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') {
				item.type = 't';
				item.value = 0;
				Stack_o.push(item);	//операция кладётся в стек с операциями
				continue;
			}
			if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') {
				item.type = 'g';
				item.value = 0;
				Stack_o.push(item);	//операция кладётся в стек с операциями
				continue;
			}
			if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
				item.type = 'e';
				item.value = 0;
				Stack_o.push(item);	//операция кладётся в стек с операциями
				continue;
			}

		}
		if (Ch == 'p') { //если прочитано число
			item.type = '0';
			item.value = Pi;
			Stack_n.push(item);	//число кладётся в стек с числами
			flag = 0;
			cin.ignore();
			continue;
		}
		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //если прочитано число
			cin >> value;
			item.type = '0';
			item.value = value;
			Stack_n.push(item);	//число кладётся в стек с числами
			flag = 0;
			continue;
		}
		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') {//если прочитана операция
			if (Stack_o.size() == 0) {//если стек с операциями пуст
				item.type = Ch;
				item.value = '0';
				Stack_o.push(item); //операция кладётся в стек с операциями
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) > getRang(Stack_o.top().type)) {//если стек с операциями не пуст, но приоритет текущей операции больше
				item.type = Ch;
				item.value = '0';
				Stack_o.push(item); //операция кладётся в стек с операциями
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) <= getRang(Stack_o.top().type)) {//если стек с операциями не пуст, но приоритет текущей операции  меньше
				if (Maths(Stack_n, Stack_o, item) == false) {
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (Ch == '(') {
			item.type = Ch;
			item.value = '0';
			Stack_o.push(item); //операция кладётся в стек с операциями
			cin.ignore();
			continue;
		}
		if (Ch == ')') {
			while (Stack_o.top().type != '(') {
				if (Maths(Stack_n, Stack_o, item) == false) {//если функций вернет false, прекращаем работу
					system("pause");
					return 0;
				}
				else continue; // если все хорошо
			}
			Stack_o.pop();
			cin.ignore();
			continue;
		}
		else {
			cout << "\nНеверная запись!\n";
			system("pause");
			return 0;
		}
	}
		while (Stack_o.size() != 0) {
			if (Maths(Stack_n, Stack_o, item) == false) {//если функций вернет false, прекращаем работу
				system("pause");
				return 0;
			}
			else continue; // если все хорошо
		}
		std::cout << "   Ответ: " << Stack_n.top().value << endl;
		return 0;
}