#include "pch.h"
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <cstdint>
#include <windows.h>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(720, 530), L"Парковка");

int t = -1;
Clock clc;

class DrawCar
{
private:
	float x, y, w, h, dt;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:

	DrawCar(String F, float X, float Y, float W, float H) {
		File = F;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(x = X, y = Y);
		sprite.setOrigin(w = W, h = H);
	}
	void draw() { window.draw(sprite); }
	void update(float X, float Y) { sprite.setPosition(X, Y); }
	void hide() { sprite.setColor(Color(255, 255, 255, 0)); }
	void show() { sprite.setColor(Color(255, 255, 255, 255)); }
};

class DrawBox
{
private:
	float x, y;
	RectangleShape bort;
public:
	DrawBox(float x, float y) : bort(Vector2f(60, 160)) {
		bort.setFillColor(Color::Transparent);
		bort.setOutlineColor(Color::White);
		bort.setOutlineThickness(1);
		bort.setPosition(x, y);
	}
	void draw() { window.draw(bort); }
};

class DrawLines
{
private:
	float x, y;
	VertexArray lines;
public:
	DrawLines(float x, float y) : lines(LineStrip, 2) {
		lines[0].position = Vector2f(x, y);
		lines[1].position = Vector2f(x + 60, y);
	}
	void draw() { window.draw(lines); }
};


class _DrawText
{
private:
	float x, y;
	string *a1;
	Text txt;
	Font font;

public:
	_DrawText(float x, float y, string *a1) : txt(*a1, font)
	{
		font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
		txt.setCharacterSize(14);
		txt.setFillColor(Color::White);
		txt.setPosition(x, y);
	}
	void draw() { window.draw(txt); }
	void update(float X, float Y) { txt.setPosition(X, Y); }
	void show() { txt.setFillColor(Color::White); }
	void hide() { txt.setFillColor(Color::Black); }
};


class Parking
{
private:
	string a[10];
	int k[10];
	int n;

public:
	Parking() { n = 0; }
	~Parking() {}
	void removecar(string);
	void addcar(string);
	void config(string);
	void drawPark();

	void menu();
};

void Parking::addcar(string num)
{
	if (n == 10) cout << "Стоянка заполнена, выберите другое действие!";
	else {
		a[n] = num;
		k[n] = 0;
		n++;
		cout << "Машина добавлена!" << endl;
	}
}

void Parking::removecar(string num)
{
	int i = 0;

	while (i < n) {
		if (num == a[i]) {
			t = i;
			break;
		}
		i++;
	}
	if (t == -1) cout << "Такой машины нет на стоянке!" << endl;
	else {
		for (i = n - 1; i > t; i--) 
			k[i]++;

		cout << "\nМашина: " << a[t] << " покидает стоянку\n\n";
		for (i = t; i < n - 1; i++) {
			a[i] = a[i + 1];
			k[i] = k[i + 1];
		}
		n--;
	}
}

void Parking::config(string num)
{
	cout << endl;
	if (num[0] == 'A' && num.size() == 8) {
		addcar(num.substr(2, 6));
	}
	else if (num[0] == 'D' && num.size() == 8) {
		removecar(num.substr(2, 6));
	}
	else cout << "Неверный шифр!" << endl;
	_getch();
}

void Parking::drawPark()
{
	int j = 70, x1 = 15, y1 = 250;

	Font fnt1;
	fnt1.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	Text text(L"Эмулятор стоянки автомобилей\n\nшифр должен иметь вид Х_YYYYYY\nгде X - (А-машина вьезжает, D-машина выезжает)\nYYYYYY - номер машины\n\nСостояние основной стоянки:\n", fnt1);
	text.setCharacterSize(14);
	text.setFillColor(Color::White);
	text.setPosition(15, 10);

	Text txt0(L"cтоянка пуста!", fnt1);
	txt0.setCharacterSize(14);
	txt0.setFillColor(Color::White);
	txt0.setPosition(230, 106);

	Text txt1(L"cтоянка заполнена!", fnt1);
	txt1.setCharacterSize(14);
	txt1.setFillColor(Color::White);
	txt1.setPosition(230, 106);

	Text txt2(L"Временная стоянка:", fnt1);
	txt2.setCharacterSize(14);
	txt2.setFillColor(Color::White);
	txt2.setPosition(15, 320);

	vector<DrawLines*> dl;
	x1 = 15, y1 = 250;
	for (int i = 0; i < 10; i++) {
		dl.push_back(new DrawLines(x1, y1));
		x1 += j;
	}

	vector<DrawLines*> dl1;
	x1 = 15, y1 = 275;
	for (int i = 0; i < 10; i++) {
		dl1.push_back(new DrawLines(x1, y1));
		x1 += j;
	}

	vector<DrawLines*> dl2;
	x1 = 15, y1 = 460;
	for (int i = 0; i < 10; i++) {
		dl2.push_back(new DrawLines(x1, y1));
		x1 += j;
	}

	vector<DrawLines*> dl21;
	x1 = 15, y1 = 485;
	for (int i = 0; i < 10; i++) {
		dl21.push_back(new DrawLines(x1, y1));
		x1 += j;
	}

	vector<DrawBox*> bx;
	x1 = 15; y1 = 140;
	for (int i = 0; i < 10; i++) {
		bx.push_back(new DrawBox(x1, y1));
		x1 += j;
	}

	vector<DrawBox*> bx1;
	x1 = 15; y1 = 350;
	for (int i = 0; i < 10; i++) {
		bx1.push_back(new DrawBox(x1, y1));
		x1 += j;
	}

	vector<DrawCar*> cr;
	x1 = 155; y1 = 240;
	for (int i = 0; i < 10; i++) {
		cr.push_back(new DrawCar("E:\\Car.png", x1, y1, 130, 90));
		x1 += j;
	}

	while (window.isOpen()) {
		Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			}
		}

		window.setFramerateLimit(70);
		window.setPosition(Vector2i(600, 70));

		vector<DrawCar*> cr1;
		x1 = 715; y1 = 450;
		for (int i = 0; i < 9; i++) {
			cr1.push_back(new DrawCar("E:\\Car.png", x1, y1, 130, 90));
			x1 -= j;
		}

		vector<_DrawText*> tx;
		x1 = 20, y1 = 253;
		for (int i = 0; i < 10; i++) {
			tx.push_back(new _DrawText(x1, y1, &a[i]));
			x1 += j;
		}

		vector<_DrawText*> tx1;
		x1 = 40, y1 = 278;
		for (int i = 0; i < 10; i++) {
			tx1.push_back(new _DrawText(x1, y1, &std::to_string(k[i])));
			x1 += j;
		}

		window.clear();

		for (int i = 0; i < 10; i++) {
			bx[i]->draw();
			dl[i]->draw();
			dl1[i]->draw();
		}

		for (int i = 0; i < 9; i++) {
			bx1[i]->draw();
			dl2[i]->draw();
			dl21[i]->draw();
		}

		Time elapsed;

		for (int i = 0; i < n; i++) {
			cr[i]->draw();
			tx[i]->draw();
			tx1[i]->draw();

		}

		if (n == 0)
			window.draw(txt0);
		if (n == 10)
			window.draw(txt1);

		window.draw(txt2);
		window.draw(text);
		window.display();

		menu();

		for (int i = 0; i <= 10000000; i++)
			elapsed = clc.getElapsedTime();

		clc.restart();

		if (t != -1) {
			window.clear();

			vector<_DrawText*> tx;
			x1 = 20, y1 = 253;
			for (int i = 0; i < 10; i++) {
				tx.push_back(new _DrawText(x1, y1, &a[i]));
				x1 += j;
			}

			vector<_DrawText*> tx1;
			x1 = 40, y1 = 278;
			for (int i = 0; i < 10; i++) {
				tx1.push_back(new _DrawText(x1, y1, &std::to_string(k[i])));
				x1 += j;
			}

			vector<_DrawText*> _tx;
			x1 = 580, y1 = 463;
			for (int i = 0; i < 9; i++) {
				_tx.push_back(new _DrawText(x1, y1, &a[i]));
				x1 -= j;
			}

			vector<_DrawText*> _tx1;
			x1 = 600, y1 = 488;
			for (int i = 0; i < 9; i++) {
				_tx1.push_back(new _DrawText(x1, y1, &std::to_string(k[i] - 1)));
				x1 -= j;
			}

			window.clear();

			for (int i = 0; i < 10; i++) {
				bx[i]->draw();
				dl[i]->draw();
				dl1[i]->draw();
			}

			for (int i = 0; i < 9; i++) {
				bx1[i]->draw();
				dl2[i]->draw();
				dl21[i]->draw();
			}

			// перемещение на временную стоянку
			for (int i = n - 1; i >= t; i--) {
				cr[i]->hide();
				tx[i]->hide();
				tx1[i]->hide();
				cout << "Временная стоянка: " << a[i] << endl;
			}

			cout << endl;

			x1 = 715; y1 = 450;
			for (int i = n - 1; i >= t; i--) {
				cr1[i]->update(x1, y1);
				cr1[i]->draw();
				x1 -= j;
			}

			x1 = 580, y1 = 463;
			for (int i = n - 1; i >= t; i--) {
				_tx[i]->update(x1, y1);
				_tx[i]->draw();
				x1 -= j;
			}

			x1 = 600, y1 = 488;
			for (int i = n - 1; i >= t; i--) {
				_tx1[i]->update(x1, y1);
				_tx1[i]->draw();
				x1 -= j;
			}

			for (int i = 0; i < n; i++) {
				cr[i]->draw();
				tx[i]->draw();
				tx1[i]->draw();
			}

			window.draw(txt2);
			window.draw(text);
			window.display();

			for (int i = 0; i <= 50000000; i++)
				elapsed = clc.getElapsedTime();

			clc.restart();

			window.clear();

			for (int i = 0; i < 10; i++) {
				bx[i]->draw();
				dl[i]->draw();
				dl1[i]->draw();
			}

			for (int i = 0; i < 9; i++) {
				bx1[i]->draw();
				dl2[i]->draw();
				dl21[i]->draw();
			}

			for (int i = t; i < n; i++)
				cout << "Машина: " << a[i] << " возвращается основную на стоянку" << endl;

			cout << endl;

			// перемещение на основную стоянку
			for (int i = n - 1; i >= t; i--) {
				cr[i]->show();
				tx[i]->show();
				tx1[i]->show();	
			}

			for (int i = n - 1; i >= t; i--) {
				delete(cr1[i]);
				delete(_tx[i]);
				delete(_tx1[i]);
			}

			for (int i = 0; i < n; i++) {
				cr[i]->draw();
				tx[i]->draw();
				tx1[i]->draw();
			}

			window.draw(txt2);
			window.draw(text);
			window.display();

			for (int i = 0; i <= 10000000; i++)
				elapsed = clc.getElapsedTime();
			clc.restart();
		}
		t = -1;
	}
}

void Parking::menu()
{
	int t;
	string tmp;
	system("cls");
	cout << "1. Ввод шифра\n0. Выход\n>> ";
	cin >> t;
	if (t == 1) {
		cin >> tmp;
		config(tmp);
	}
	else exit(-1);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Parking p1;

	p1.addcar("yo123k");
	p1.addcar("aa565b");
	p1.addcar("aa482k");
	p1.addcar("op230b");
   	p1.addcar("tt231a");
	p1.addcar("op230a");
	p1.addcar("op230h");
	p1.addcar("op230e");
	p1.addcar("op230y");
	p1.addcar("op230i");

	p1.drawPark();
}

