#include <iostream>
using namespace std;


struct dot {  // Структура точки
	double x;
	double y;
};

void read_dot(dot& p) {  // Функция считывания точки
	cin >> p.x >> p.y;
}

void write_dot(dot p) {  // Функция вывода точки
	cout << p.x << " " << p.y << endl;
}

struct segment {   // Структура отрезка
	dot a;
	dot b;
	// Параметры прямой, на которой лежит отрезок:
	// k = (b.y - a.y) / (b.x - a.x)
	// m = a.y - a.x * (b.y - a.y) / (b.x - a.x)
	double A, B, C;
};

void create_segment(segment& s, dot a, dot b) {  // Создание отрезка
	s.a = a;
	s.b = b;

	if (b.x == a.x) {
		s.A = 1;
		s.B = 0;
		s.C = b.x - 2 * b.x;
	}
	else {
		s.A = (-b.y + a.y) / (b.x - a.x);
		s.B = 1;
		s.C = a.y - a.x * (b.y - a.y) / (b.x - a.x);
	}
}

bool is_dot_in_segment(dot a, segment s) {
	double k = (s.b.y - s.a.y) / (s.b.x - s.a.x);
	double m = s.a.y - s.a.x * (s.b.y - s.a.y) / (s.b.x - s.a.x);
	if (a.y != a.x * k + m) {
		return false;
	}
	if (a.x < s.a.x and a.x < s.b.x or a.x > s.a.x and a.x > s.b.x or
		a.y < s.a.y and a.y < s.b.y or a.y > s.a.y and a.y > s.b.y) {
		return false;
	}
	return true;
}

bool is_lines_crossed(segment s1, segment s2) {   // TO DO: ..........
	if (s1.B == 0 or s2.B == 0) {
		if (s1.B == 0 and s2.B == 0) {
			if ((s1.C - 2 * s1.C) / s1.A == (s2.C - 2 * s2.C) / s2.A) {
				cout << "inf" << endl;
			}
			else {
				cout << "paralel" << endl;
			}
		}
		if (s1.B == 0 and s2.B != 0) {
			if (s2.A == 0) {
				cout << (s1.C - 2 * s1.C) / s1.A << " " << (s2.C - 2 * s2.C) / s2.B;
			}
			else {
				double k2 = s2.A / (s2.B - 2 * s2.B);
				double m2 = s2.C / (s2.B - 2 * s2.B);
				cout << (s1.C - 2 * s1.C) / s1.A << " " << k2 * (s1.C - 2 * s1.C) / s1.A + m2;
			}
		}
		if (s2.B == 0 and s1.B != 0) {
			if (s1.A == 0) {
				cout << (s2.C - 2 * s2.C) / s2.A << " " << (s1.C - 2 * s1.C) / s1.B;
			}
			else {
				double k1 = s1.A / (s1.B - 2 * s1.B);
				double m1 = s1.C / (s1.B - 2 * s1.B);
				cout << (s2.C - 2 * s2.C) / s2.A << " " << k1 * (s2.C - 2 * s2.C) / s2.A + m1;
			}
		}
	}
	else {
		double k1 = s1.A / (-s1.B);
		double m1 = s1.C / (-s1.B);
		double k2 = s2.A / (-s2.B);
		double m2 = s2.C / (-s2.B);
		if (k1 == k2) {
			if (m2 == m1) {
				cout << "inf" << endl;
			}
			else {
				cout << "paralel" << endl;
			}
		}
		else {
			cout << (m2 - m2) / (k1 - k2) << " " << k1 * (m2 - m2) / (k1 - k2) + m1 << endl;
		}
	}
}

int main() {
}