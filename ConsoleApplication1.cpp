#include <iostream>
using namespace std;
#define M_PI 3.1415926535897932


struct dot {  // Структура точки
	double x;
	double y;

	dot operator + (const dot& d) {
		return dot{x + d.x, y + d.y};
	}

	dot operator - (const dot& d) {
		return dot{x - d.x, y - d.y};
	}
};

void read_dot(dot& p) {  // Функция считывания точки
	cin >> p.x >> p.y;
}

void write_dot(dot p) {  // Функция вывода точки
	cout << p.x << " " << p.y << endl;
}

void turn_dot(dot& a, double angle) {  // Функция поворота точки
	double x = a.x;                   // относительно начала координат
	double y = a.y;
	a.x = floor((x * cos(angle) - y * sin(angle)) * 1000000000000) / 1000000000000;
	a.y = floor((x * sin(angle) + y * cos(angle)) * 1000000000000) / 1000000000000;
	
	// Округление нужно, чтобы исправить небольшую неточность числа PI
	
	//Без округления:
	// a.x = x * cos(angle) - y * sin(angle);
	// a.y = x * sin(angle) + y * cos(angle);
}




struct segment {   // Структура отрезка
	dot a;
	dot b;
	// Параметры прямой, на которой лежит отрезок:
	// k = (b.y - a.y) / (b.x - a.x)
	// m = a.y - a.x * (b.y - a.y) / (b.x - a.x)
};

void create_segment(segment& s, dot a, dot b) {  // Создание отрезка
	s.a = a;
	s.b = b;
}

double segment_length(segment s) {   // Длина отрезка
	return sqrt((s.a.x - s.b.x) * (s.a.x - s.b.x) + (s.a.y - s.b.y) * (s.a.y - s.b.y));
}




struct square {    // Структура квадрата
	dot O;         // Координата центра квадрата
	double a;      // Длина стороны
	double angle;  // Угол поворота квадрата относительно т.O
		       //против часовой стрелки в радианах

	dot A, B, C, D; // вершины квадрата (см. функц. create_square(), там же на схематичном рисунке
	// можно посмотреть расположение вершин)

	dot OA, OB, OC, OD; // векторы (подробнее см. функц. create_square())
};

void create_square(square& s, dot O, double a, double angle) {   // Создание квадрата
	s.O = O;
	s.a = a;
	s.angle = angle;

	// Сейчас у нас есть вектор O
	// Получим векторы вершин квадрата до его поворота:
	s.A.x = O.x + a / 2;
	s.A.y = O.y + a / 2;	//         /\ Y
	s.B.x = O.x + a / 2;	//         |
	s.B.y = O.y - a / 2;	//         |          D---------A
	s.C.x = O.x - a / 2;	//         |          |         |
	s.C.y = O.y - a / 2;	//         |          |    o    |
	s.D.x = O.x - a / 2;	//         |          |         |
	s.D.y = O.y + a / 2;	//         |          |         |
				//         |          C---------B
				//         |    
				//         |    
				//         |    
				//         |-----------------------------------> X

	// Теперь получим координаты вершин "относительно центра квадрата"
	// Здесь-то нам и пригодится переопределение операторов "+" и "-" для точек:
	s.OA = s.A - s.O;
	s.OB = s.B - s.O;
	s.OC = s.C - s.O;
	s.OD = s.D - s.O;

	// Теперь повернём векторы OA, OB, OC, OD при помощи матрицы поворота,
	// Для этого нам и понадобится функция turn_dot():
	turn_dot(s.OA, s.angle);
	turn_dot(s.OB, s.angle);
	turn_dot(s.OC, s.angle);
	turn_dot(s.OD, s.angle);

	// Теперь посчитаем новые координаты вершин квадрата
	// После поворота:
	s.A = s.O + s.OA;
	s.B = s.O + s.OB;
	s.C = s.O + s.OC;
	s.D = s.O + s.OD;
}

double square_area(square s) {  // Площадь квадрата
	return s.a * s.a;
}

double square_perimetr(square s) {  // Периметр квадрата
	return 4 * s.a;
}




struct circle {  // Структура круга
	dot O;       // Центр
	double R;    // Радиус
};

void create_circle(circle& C, dot O, double R) {  // Создание окружности
	C.O = O;
	C.R = R;
}

double circle_length(circle c) {  // Длина окружности
	return c.R * 2 * M_PI;
}

double circle_square(circle c) {  // Площадь круга
	return M_PI * c.R * c.R;
}




// Функция, проверяющая принадлежность точки отрезку:
bool is_dot_in_segment(dot a, segment s) {
	double e = 0.00000000000001;   // Погрешность нужна в случае точек с иррациональными координатами,
	double k, m;				  // которые из-за округления "не до конца ложатся" на прямую
	if (s.b.x != s.a.x) {
		k = (s.b.y - s.a.y) / (s.b.x - s.a.x);
		m = s.a.y - s.a.x * (s.b.y - s.a.y) / (s.b.x - s.a.x);
		if (not ((a.x * k + m) * (1 - e) <= a.y and a.y <= (a.x * k + m) * (1 + e))) {
			return false;
		}
		if (a.x < s.a.x and a.x < s.b.x or a.x > s.a.x and a.x > s.b.x or
			a.y < s.a.y and a.y < s.b.y or a.y > s.a.y and a.y > s.b.y) {
			return false;
		}
		return true;
	}
	else {
		if (a.x != s.a.x) {
			return false;
		}
		if (a.y >= s.a.y and a.y <= s.b.y or a.y <= s.a.y and a.y >= s.b.y) {
			return true;
		}
		return false;
	}
}

// Функция, проверяющая принадлежность точки кругу:
bool is_dot_in_circle(dot a, circle c) {
	segment S;
	create_segment(S, a, c.O);
	double l = segment_length(S);
	if (l <= c.R) {
		return true;
	}
	return false;
}

// Функция, проверяющая принадлежность точки квадрату:
bool is_dot_in_square(dot a, square s) {
	// Введем новую систему координат с началом в точке s.O
	// и осями, параллельными соответсвенно осям начальной системе координат.
	// В новой системе координат координаты s.A, s.B, s.C, s.D равны соответственно
	// s.OA, s.OB, s.OC, s.OD

	dot Oa;  // - Координата точки а в новой системе отсчета
	Oa = a - s.O;

	// Теперь в новой системе отсчета повернем квадрат на угол - angle,
	// чтобы его стороны стали параллельны осям координат,
	// ведь в этом случае вхождение точки в квадрат найти проще.
	// Вместе с квадратом конечно же поворачиваем и точку Oa.
	turn_dot(Oa, -s.angle);
	// dot A, B, C, D;
	// A = s.OA;
	// B = s.OB;
	// C = s.OC;
	// D = s.OD;                 --------- ЭТУ ЧАСТЬ КОДА ДАЖЕ ПИСАТЬ НЕ НУЖНО, 
	// turn_dot(A, -s.angle);              Т.К. МЫ МОЖЕМ ПОВЕРНУТЬ КВАДРАТ "МЫСЛЕННО"
	// turn_dot(B, -s.angle);
	// turn_dot(C, -s.angle);
	// turn_dot(D, -s.angle);

	// Схематично полученную на данном шаге ситуацию можно представить так:
	//
	//
	//						/\ Y'
	//						|
	//						|
	//						|
	//						|
	//			     D'_________________|___________________A'
	//	                     |			|		    |
	//	                     |		   	|		    |
	//	                     |			|	a.	    |
	//	                     |			|		    |
	//	                     |			|		    |
	//	                     |			|	 	    |
	//	   	  ------------------------------|------------------------------> X'
	//			     |			|O		    |
	//			     |			|		    |
	//			     |			|		    |
	//			     |			|		    |
	//			     |			|		    |
	//			     |			|		    |
	//			     C'_________________|___________________B'
	//					 	|
	//					     	|
	//						|
	//						|
	//						|
	//						|

	// Теперь просто по координатам проверим лежит ли эта точка в квадрате:
	if ((-s.a / 2 <= Oa.x and Oa.x <= s.a / 2) and (-s.a / 2 <= Oa.y and Oa.y <= s.a / 2)) {
		return true;
	}
	return false;
}




int main() {
	dot a, b;
	dot c;
	segment s;
	read_dot(a);
	read_dot(b);
	read_dot(c);
	create_segment(s, a, b);
	if (is_dot_in_segment(c, s)) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}
