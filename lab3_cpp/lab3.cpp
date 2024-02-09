// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;
enum name {
	gosha, kesha
};

class Complex         // класс "Комплексное число"
{
private:
	double re, im;      // действительная и мнимая части

public:
	// конструкторы 

	Complex()
	{
	};

	Complex(double r)
	{
		re = r;
		im = 0;
	}

	Complex(double r, double i)
	{
		re = r;
		im = i;
	}

	Complex(const Complex &c)   // конструктор копирования
	{
		re = c.re;
		im = c.im;
	}

	// деструктор
	~Complex()
	{
	}

	// остальные функции

	// Модуль комплексного числа
	double abs()
	{
		return sqrt(re * re + im * im);
	}

	// оператор присваивания
	Complex& operator = (Complex &c)
	{
		re = c.re;
		im = c.im;

		return (*this);
	}


	// оператор +=
	Complex& operator += (Complex &c)
	{
		re += c.re;
		im += c.im;
		return *this;
	}

	// оператор сложения
	Complex operator + (const Complex &c)
	{
		return Complex(re + c.re, im + c.im);
	}

	// оператор вычитания
	Complex operator - (const Complex &c)
	{
		return Complex(re - c.re, im - c.im);
	}

	// оператор умножения
	Complex operator * (const Complex &c)
	{
		return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
	}

	// оператор деления
	Complex operator / (const Complex &c)
	{
		Complex temp;

		double r = c.re * c.re + c.im * c.im;
		temp.re = (re * c.re + im * c.im) / r;
		temp.im = (im * c.re - re * c.im) / r;

		return temp;
	}

	// укажем дружественные операторы, которым мы разрешаем доступ
	// к личным (private) данным
	friend ostream & operator<< (ostream &, const Complex &);
	friend istream & operator>> (istream &, Complex &);

};

// перегрузка оператора <<
ostream& operator<< (ostream &out, const Complex &c)
{
	out << "(" << c.re << ", " << c.im << ")";
	return out;
}

// перегрузка оператора >>
istream& operator>> (istream &in, Complex &c)
{
	in >> c.re >> c.im;
	return in;
}
////////////////////////////////////////////////////////////////////////////////////////////////
struct Node: public Complex                             //Структура, являющаяся звеном списка
{
	Complex x;                             //Значение x будет передаваться в список
	Node *Next, *Prev;                 //Указатели на адреса следующего и предыдущего элементов списка
};

class List                              //Создаем тип данных Список
{
	Node *Head, *Tail;                 //Указатели на адреса начала списка и его конца
public:
	List() :Head(NULL), Tail(NULL) {};    //Инициализируем адреса как пустые
	~List();                           //Прототип деструктора
	void Show();                       //Прототип функции отображения списка на экране
	void Add(Complex x);                   //Прототип функции добавления элементов в список

	Complex &operator[](int num)// перегрузка для создания или переназначения элемента
	{
		Node *temp = Head;
		//Node *temp = Tail;

		for (int i = 0; temp!=NULL; i++)
		{
				if(i==num)
					return temp->x;
				temp = Head->Next;

		}
	};
	/*Complex &operator[](int num)// перегрузка для создания или переназначения элемента
	{
		Node *temp = Head;
		//Node *temp = Tail;

		for (int i = 0; i <= num; i++)
		{
			if ((i != num) && (Head != NULL))
				temp = Head->Next;
			else
			{
				//cout << current->x << endl;
				return temp->x;
			}

		}
	};*/

};

List::~List()                           //Деструктор
{
	while (Head)                       //Пока по адресу на начало списка что-то есть
	{
		Tail = Head->Next;             //Резервная копия адреса следующего звена списка
		delete Head;                   //Очистка памяти от первого звена
		Head = Tail;                   //Смена адреса начала на адрес следующего элемента
	}
}

void List::Add(Complex x)
{
	Node *temp = new Node;               //Выделение памяти под новый элемент структуры
	temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
	temp->x = x;                         //Записываем значение в структуру

	if (Head != NULL)                    //Если список не пуст
	{
		temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
		Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
		Tail = temp;                     //Меняем адрес хвоста
	}
	else //Если список пустой
	{
		temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
		Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
	}
}

void List::Show()
{
	//ВЫВОДИМ СПИСОК С КОНЦА
	Node *temp = Tail;                   //Временный указатель на адрес последнего элемента
	
	while (temp != NULL)               //Пока не встретится пустое значение
	{
		cout << temp->x << " ";        //Выводить значение на экран
		temp = temp->Prev;             //Указываем, что нужен адрес предыдущего элемента
	}
	cout << "\n";
	
	//ВЫВОДИМ СПИСОК С НАЧАЛА
	temp = Head;                       //Временно указываем на адрес первого элемента
	while (temp != NULL)              //Пока не встретим пустое значение
	{
		cout << temp->x << " ";        //Выводим каждое считанное значение на экран
		temp = temp->Next;             //Смена адреса на адрес следующего элемента
	}
	cout << "\n";
}
/*
class MassComp : public List
{
	void operator[](int num)
	{
		Node *current = Head;
		Node *temp = Tail;

		for (int i = 0; i <= num; i++)
		{
			if (i != num)
				Tail = Head->Next;
			else
				cout << temp->x << endl;
		}
	};
};*/


int main()
{
	system("CLS");

	Complex a(5, 2);
	Complex b(3, -3), d(0,0);
	cout << "a = " << a << "; b =" << b << endl;
	a += b;
	cout << "a = " << a << "; b =" << b << endl;
	Complex c = a + b;
	cout << c << endl;
	cout << a + b << endl;
	cout << a * b << endl;

	List lst; //Объявляем переменную, тип которой есть список
	lst.Add(a); //Добавляем в список элементы
	lst.Add(b);
	lst.Add(2);
	lst.Add(3);
	//lst.Show(); //Отображаем список на экране
	cout << "out from index\n" << endl;
	for (int i = 0;i < 4;i++)
		cout << lst[i] << "\n" << endl;
	//lst[1] = c;
	//lst[4] = d;
	lst.Show(); //Отображаем список на экране
	system("PAUSE");
	return 0;
}
/*
int main()
{
	Complex a(5, 2);
	Complex b(3, -3);
	cout << "a = " << a << "; b =" << b << endl;
	a += b;
	cout << "a = " << a << "; b =" << b << endl;
	Complex c = a + b;
	cout << c << endl;
	cout << a + b << endl;
	cout << a * b << endl;
	system("PAUSE");
	return 0;

}*/