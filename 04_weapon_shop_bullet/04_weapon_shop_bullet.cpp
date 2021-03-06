/*
Завдання 3.1. Можна використати у завданні  3.1 раніше побудований(класна робота) шаблон класу Стек.

Напишіть програму з трьома класами - автомат, магазин, набій.
Кожен набій пронумерований (нумерація послідовна і при запуску програми починається з випадкового числа) і вміє вистрілювати і влучати в мішень з імовірністю 70%. Кожен набій у програмі має унікальний номер.
Магазин реалізований у вигляді стеку, містить 30 набоїв і вміє:
o	заряджати набій (отримує його "готовим")
o	віддавати набій (верхній)

Автомат вміє:
o	прийняти магазин(тобто можна змінювати магазини у автоматі)
o	стріляти - попросити магазин дати 1 набій, і, якщо дав, попросити набій вистрелити (набій при цьому скаже, чи влучив, а автомат передасть результат "нагору" )

При пострілі в консоль має виводитись повідомлення такого типу:
Автомат вистрелив кулю 5, і промахнувся.
Автомат вистрелив кулю 6, і влучив.

*/


#include "stdafx.h"
#include <iostream> 
#include <string>
#include <ctime>

using namespace std;

class Bullet
{
private:

	string name = "bullet #";
	static int id;

public:

	Bullet()
	{
		++id;
		name = name + to_string(id);
	}

	~Bullet()
	{
	}

	string getName()const
	{
		return name;
	}

	void setId()
	{
		id = rand() % 69;
	}

	void show()const
	{
		cout << name << endl;
	}
};

class Shop
{
	enum size { MAXSIZE = 30, EMPTY = -1 };

private:

	Bullet shop[MAXSIZE];
	int top;

public:

	Shop()
	{
		top = -1;
	}

	~Shop()
	{
	}

	void clear()
	{
		top = EMPTY;
	}

	int getSize()const
	{
		return top + 1;
	}

	Bullet peek()const
	{
		if (top == EMPTY)
		{
			cerr << "Index -1";
			//return -1;
		}
		else
			return shop[top];
	}

	void push(Bullet elem)
	{
		if (isFull())
			cerr << "Shop iz Full!\n";
		else
		{
			++top;
			shop[top] = elem;
		}
	}

	Bullet pop()
	{
		if (isEmpty())
		{
			cerr << "Shop is empty!\n";
			//return;
		}
		else
		{
			Bullet tmp = peek();
			--top;
			return tmp;
		}
	}

	bool isEmpty()const
	{
		if (top == EMPTY)
			return 1;
		else
			return 0;
	}

	bool isFull()const
	{
		if (top == MAXSIZE - 1)
			return 1;
		else
			return 0;
	}

	void print()const
	{
		if (isEmpty())
			cout << "Empty\n";
		else
		{
			cout << endl << getSize() << " bullets in shop:\n";
			for (int i = 0; i <= top; i++)
				cout << shop[i].getName() << "  ";
			cout << endl;
		}
	}
};

class Weapon
{

private:

	Shop weapon;

public:

	Weapon(Shop & shop)
	{
		setShop(shop);
	}

	~Weapon()
	{
	}

	void setShop(Shop & shop)
	{
		weapon = shop;
		cout << "\nSet new shop with " << weapon.getSize() << " bullet(s)\n";
	}

	void shoot(Shop & shop)
	{
		if (weapon.isEmpty())
			cout << "Shop is empty. You don't shoot\n";
		else
		{
			int hit = rand() % 100;
			//Bullet bullet = weapon.pop();
			//cout << "Weapon shoot " << bullet.getName() << endl;
			cout << "Weapon shoot " << weapon.pop().getName() << " and ";
			if (hit < 70)
				cout << "hit\n";
			else
				cout << "missed\n";
			shop = weapon;
		}
	}


};

int Bullet::id = 0;

int main()
{
	srand(unsigned(time(0)));

	Shop shop;
	Bullet bullet;
	bullet.setId(); //присвоюємо рандомний номер початковій кулі

	//заповнюємо магазин кулями
	while (!shop.isFull()) 
	{ 
		Bullet bullet; 
		shop.push(bullet);
	}

	//черга 10 пострілів
	Weapon weapon(shop);
	for(int i = 1; i <= 10; ++i)
		weapon.shoot(shop);

	//вставка іншого порожнього магазину
	Shop emptyShop;
	weapon.setShop(emptyShop);
	weapon.shoot(emptyShop); // не стріляє

	//в ставляємо попередній в якому лишилось 20 куль
	weapon.setShop(shop); 
	weapon.shoot(shop); //стріляє

	shop.print(); //залишилось 19 куль
	


	cout << endl;
	system("pause");
	return 0;
}