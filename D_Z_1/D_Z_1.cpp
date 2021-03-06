#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <locale.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

class Vect
{
protected:
	int rv;
	float *v;
public:

	Vect()
	{
		rv = 0;
		v = NULL;
	}
	Vect(const Vect &r) :rv(r.rv) {
		v = new float[r.rv]; 	for (int i = 0; i < r.rv; i++)	v[i] = r.v[i];
	}

	Vect(int size, float z = 0) :rv(size) //конструктор, принимающий размерность массива и заполняющего его нулями
	{
		v = new float[rv];
		for (int i = 0; i < rv; i++)
			v[i] = z;
	}
	~Vect()//деструктор
	{
		delete v;
	}

	Vect operator =(const Vect op) //оператор присваивания
	{
		delete v;
		v = new float[op.rv];
		for (int i = 0; i < op.rv; i++)
			v[i] = op.v[i];
		rv = op.rv;
		return *this;
	}
	Vect operator +(Vect op)//оператор сложения векторов 
	{
		if (rv == op.sizevect())
		{
			Vect temp(op.sizevect());
			for (int i = 0; i < op.sizevect(); i++)
				temp.v[i] = op.v[i] + v[i];
			return temp;
		}
		else
		{
			puts("Размер первого вектора не соответствует размеру второго");
			return *this;
		}
	}
		void razmer(int n1, int a=0)
	{
		if (v != NULL)
		{
			delete[]v;
			rv = 0;
		}
		rv = n1;
		if (rv > 0)
			v = new float[rv];
		else
			v = NULL;
		for (int i = 0; i < rv;i++)
		{
			v[i] = a;
		}
		
	}
	float &operator[](int ind) const //оператор индексирования [] 
	{
		float k = 0;
		if (ind > rv) return k;
		return v[ind];
	}
	float &operator()(int ind) const //оператор индексирования () 
	{
		float k = 0;
		if (ind > rv) return k;
		return v[ind];
	}
	Vect operator *(float k) //умножение вектора на число
	{
		for (int i = 0; i < rv; i++)
			v[i] = v[i] * k;
		return *this;
	}
	float operator *(Vect op) //скалярное умножение векторов
	{
		float summa = 0;
		if (rv == op.rv)
			for (int i = 0; i < rv; i++)
				summa += v[i] * op.v[i];
		else
		{
			puts("Размер первого вектора не соответствует размеру второго вектора");
			return 0;
		}
		return summa;
	}
	Vect operator -()  //унарный минус
	{
		for (int i = 0; i < sizevect(); i++)
			v[i] = -v[i];
		return *this;
	}
	Vect operator -(Vect op)//оператор вычитания векторов (-бинарный минус)
	{
		if (rv == op.sizevect())
		{
			Vect temp(op.sizevect());
			for (int i = 0; i < op.sizevect(); i++)
				temp.v[i] = op.v[i] - v[i];
			return temp;
		}
		else
		{
			puts("Размер первого вектора не соответствует размеру второго");
			return *this;
		}
	}
	void print()
	{
		for (int i = 0; i < rv; i++)
			printf("%3.2f\t", v[i]);
		printf("\n");
	}
	int sizevect() //возвращает размер вектора
	{
		return rv;
	}
	friend ostream &operator<<(ostream &out, Vect el);
	friend Vect operator*(float a, Vect b);
};

ostream &operator<<(ostream &out, Vect el) //операция печати вектора 
{
	for (int i = 0; i < el.rv; i++)
		out << el.v[i] << "     ";
	return out;
}
Vect operator *(float a, Vect b) //бинарная операция умножения числа на вектор
{
	Vect temp(b.rv);
	for (int i = 0; i < b.rv; i++)
	{
		temp.v[i] = b.v[i] * a;
	}
	return temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
class Array
{
protected:
	Vect * arr; //агрегация
	int n;//строчки
	int m;//столбцы
public:
	Array() // конструктор по умолчанию
	{
		n = m = 0;
		arr = NULL;
	}
	Array(const Array &r) :n(r.n), m(r.m)   //конструктор копирования
	{
		arr = new Vect[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = r.arr[i];
			for (int j = 0; j < m; j++)
				arr[i][j] = r.arr[i][j];
		}
	}
	Array(int n1, int m1, float t = 0) //конструктор принимающий размерность
	{ 
		n = n1; //строчки
		m = m1; //столбцы
		//выделяем память для матрицы (arr) под n векторов Vector размерности m
		arr = new Vect[n];
		for (int i = 0; i < n; i++)
		{
			Vect temp(m, t);
			arr[i] = temp;
		}
	}
	~Array() //деструктор
	{
		if (arr != NULL) delete[] arr;
	}

	Array &operator=(const Array &obj) //оператор присваивания =
	{
		n = obj.n;
		m = obj.m;
		arr = new Vect[m];
		for (int i = 0; i < m; i++)
			arr[i] = obj.arr[i];
		return *this;
	}
	Vect &operator[](int ind) const //оператор индексирования [] 
	{
		return arr[ind];
	}

	Vect &operator()(int ind) const //оператор индексирования () 
	{
		return arr[ind];
	}
	Array operator+(Array &obj) //сумма матриц + 
	{
		if ((m == obj.getM())&(n == obj.getN()))
		{
			int n1, m1;
			n1 = n;
			m1 = m;
			Array temp(n1, m1);
			for (int i = 0; i < n; i++)
				temp[i] = arr[i];
			for (int i = 0; i < obj.getN(); i++)
				temp[i] = temp[i] + obj[i];
			return temp;
		}
		else cout << "\nРазмеры матрицы не совпадают!!!\n";
	}
	Array operator -()  //унарный минус
	{
		for (int i = 0; i < getN(); i++)
			arr[i] = -arr[i];
		return *this;
	}
	Array operator -(Array &obj) //разность матриц - 
	{
		if ((m == obj.getM())&(n == obj.getN()))
		{
			Array temp(n, m);
			for (int i = 0; i < n; i++)
				temp[i] = arr[i];
			for (int i = 0; i < obj.getN(); i++)
				temp[i] = obj[i] - temp[i];
			return temp;
		}
		else cout << "\nРазмеры матрицы не совпадают!!!\n";
	}
	Array operator*(Array &obj) //произведение двух матриц
	{
		if (m == obj.getN())
		{
			int n1, m1;
			n1 = n;
			m1 = obj.getM();
			Array temp(n1, m1);
			for (int i(0); i < n1; i++)
				for (int j(0); j < m1; j++)
				{
					temp[i][j] = 0;
					for (int k = 0; k < m1; k++)
						temp[i][j] = temp[i][j] + arr[i][k] * obj[k][j];
				}
			return temp;
		}
		else cout << "\nОперация невозможна! Размеры матрицы не совпадают\n";
	}

	Array operator *(Vect &obj) //умножение матрицы на вектор
	{
		int n1, m1;
		n1 = n; //количество строк (=количество векторов)
		m1 = obj.sizevect();//количество столбцов (=размер вектора)
		Array temp(n1, 1);
		for (int i=0; i < n1; i++)
		{
			temp[i][0] = 0;
			for (int j=0; j < m1; j++)
			{
				//cout <<i+1<<". " << temp[i][0] << "+" << arr[i][j] << "*" << obj[j] << endl;
				temp[i][0] = temp[i][0] + arr[i][j] * obj[j];

			}
			//cout<<temp[i][0]<<"\n";
		}
		return temp;
	}
	Array operator*(float b) //умножение матрицы на число
	{
		Array temp(n, m);
		for (int i=0; i < n; i++)
			for (int j=0; j < m; j++)
				temp[i][j] = arr[i][j] * b;
		return temp;
	}
	
	Array Tran()  //транспонирование матрицы
	{
		Array temp(m, n);
		for (int i=0; i < m; i++)
		{
			for (int j=0; j < n; j++)
				temp[i][j] = arr[j][i];
		}
		return temp;
	}
	int getN() const { return n; } //возвращает количество строк
	int getM() const { return m; } //возвращает количество столбцов 
	friend ostream& operator<<(ostream &out, const Array &mv);
	friend Array operator*(float a, Array &b); //умножение числа на матрицу
};
ostream& operator<<(ostream &out, const Array &mv)
{
	for (int i = 0; i < mv.n; i++)
	{
		for (int j = 0; j < mv.m; j++)
			printf("%5.1f   ", mv[i][j]);
		out << endl;
	}
	return out;
}
Array operator*(float a, Array &b) //бинарная операция умножения числа на матрицу
{
	Array temp(b.getN(), b.getM());
	for (int i(0); i < b.getN(); i++)
		for (int j(0); j < b.getM(); j++)
			temp[i][j] = b[i][j] * a;
	return temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Slau : public Array
{
public:
	Slau() : Array() {} //конструктор по умолчанию

	Slau(int n1, int m1) : Array(n1, m1) {} //конструктор, принимающий размеры 

	Slau(const Slau &r)   //конструктор копирования
	{
		n = r.getN();
		m = r.getM();
		arr = new Vect[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = r.arr[i];
			for (int j = 0; j < m; j++)
				arr[i][j] = r.arr[i][j];
		}
	}
	Vect Gauss(float **A, float *B, int n)
	{
		float *X = new float[n], max;
		int k = 0, m;
		while (k < n)
		{
			//Поиск строки с максимальным a[i][k]
			max = abs(A[k][k]);
			m = k;
			for (int i(k + 1); i < n; i++)
			{
				if (abs(A[i][k]) > max)
				{
					max = abs(A[i][k]);
					m = i;
				}
			}
			//Перестановка строк
			if (max == 0)
			{
				cout << "\nНулевой столбец матрицы А! Решения нет!!!";
				_getch();
				return 0;
			}
			for (int j(0); j < n; j++)
			{
				float temp = A[k][j];
				A[k][j] = A[m][j];
				A[m][j] = temp;
			}
			float temp = B[k];
			B[k] = B[m];
			B[m] = temp;
			//Нормализация уравнений
			for (int i(k); i < n; i++)
			{
				float temp = A[i][k];
				if (temp != 0)
				{
					for (int j(0); j < n; j++)
						A[i][j] = A[i][j] / temp;
					B[i] = B[i] / temp;
				}
				if ((i != k) && (temp != 0))
				{
					for (int j(0); j < n; j++)
						A[i][j] = A[i][j] - A[k][j];
					B[i] = B[i] - B[k];
				}
			}
			k++;
		}

		//!Обратная подстановка
		for (k = n - 1; k >= 0; k--)
		{
			X[k] = B[k];
			for (int i(0); i < k; i++)
				B[i] = B[i] - A[i][k] * X[k];
		}
		Vect P(n);
		for (int i(0); i < n; i++)
			P[i] = X[i];
		return P;
	}
	~Slau() {} //деструктор
};



int main()
{
	setlocale(0, "rus");
	srand((unsigned)time(NULL));
	float umn, chislo = 3; 
	float a = 2, b = 0.5;
	Vect V1(4);
	Vect V2(V1);//копирующий конструктор 
	Vect V3(3);
	////////////////////////////////////////
	////////////////////////////////К  Л  А  С  С    В  Е  К  Т  О  Р  О  В\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	    \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
	cout << "_/* _/* _/* _/* _/* _/* _/* _/* _КЛАСС ВЕКТОРОВ_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_\n\n";
	cout << "\n\n6.Проверка операторов индексирования [] и ():\n";
	for (int i = 0; i < 4; i++)
	{
		V1[i] = (rand() % 100) * 0.1 - 5; 
		V2(i) = (rand() % 100) * 0.1 - 5; 
	}
	cout << "Вектор(текущее значение) V1:   " << V1 << endl;
	cout << "Вектор(текущее значение) V2:   " << V2 << "\n\n";
	umn = V1 * V2;
	cout << "9a).Cкалярное произведение векторов   umn = V1 * V2:\numn = " << umn << "\n\n";
	V2 = V1;
	cout << "5.Проверка оператора присваивания = (V2=V1):\nV2 = (" << V2 << ")" << "\n\n";
	V1 = V1 + V2;
	cout << "7.Сумма векторов (V1=V1+V2):\n" << V1 << "\n\n";
	cout << "\n!!!Промежуточный вывод векторов:\nВектор V1:   " << V1 << "\nВектор V2:   " << V2 << "\n\n";
	cout << "9б).Умножение вектора V1 = ( " << V1 << ") на число " << chislo << ":" << endl;
	V1 = V1 * chislo;
	cout << "Вектор(текущее значение) V1:   " << V1 << "\n\n";
	V2 = -V2;
	cout << "8а).Унарный минус-(V2 = -V2):" << endl;
	cout << "Вектор(текущее значение) V2:   " << V2 << "\n\n";
	cout << "\n!!!Промежуточный вывод векторов:\nВектор V1:   " << V1 << "\nВектор V2:   " << V2 << "\n\n";
	V2 = V2 - V1;
	cout << "8б).Бинарный минус-(V1 = V1-V2):" << endl;
	cout << "Вектор(текущее значение) V2:   " << V2 << "\n\n";
	V1 = b * V1;
	cout << "9в).Умножение числа на вектор   V1 = 0.5 * V1\nОбъект V1:   " << V1 << "\n\n";
	cout << "\n!!!Промежуточный вывод векторов:\nВектор V1:   " << V1 << "\nВектор V2:   " << V2 << "\n\n";
	cout << "\n11)Размеры векторов:\nРазмер V1 = " << V1.sizevect() << "\nРазмер V2 = " << V2.sizevect();
	cout << "\n\nНажмите любую кнопку для продолжения...  ";
	_getch();
	system("cls");
	////////////////////////////////К  Л  А  С  С    М  А  Т  Р  И  Ц\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
	cout << "_/* _/* _/* _/* _/* _/* _/* _/* _КЛАСС МАТРИЦ_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_\n\n";
	Array M1(3, 3); //создание объекта-матрицы с заданными размерами. Срабатывает констуктор, принимающий размеры матрицы
	Array M2(M1);   //работа копирующего констуктора (создается такой же объект b, что и объект a)
	cout << "\n\nИнициализация с помощью [] и ():\n";
	for (int i(0); i < 3; i++)
		for (int j(0); j < 3; j++)
		{
			M1[i][j] = (rand() % 100)*0.1 - 2; //6.проверка оператора индексирования []
			M2(i)(j) = (rand() % 100)*0.1 - 2; //6.проверка оператора индексирования ()
		}
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	cout << "Размеры матрицы M1: N(количество строк)=" << M1.getN() << "  M(количество столбцов)= " << M1.getM() << "\n\n";
	M2 = M2 * a;
	cout << "9б)Умножение матрицы на число (M2 = M2*2):\nОбъект M2:\n" << M2 << endl;
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	M1 = M2;
	cout << "5.Равенство двух матриц  M1 = M2:\nМатрица М1:\n" << M1 << endl;
	M1 = M1 * M2;
	cout << "9а) Произведение двух матриц (M1=M1*M2): " << endl << M1 << endl;
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	M1 = -M1;
	cout << "8а)Унарный минус -(M1=-M1): " << endl << M1 << "\n\n";
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	M1 = M1 + M2;
	cout << "7. Сумма матриц + (M1=M1+M2): " << endl << M1 << "\n\n";
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	M2 = M2 - M1;
	cout << "8б) Разность матриц (M2=M2-M1): " << endl << M2;
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	M1 = a * M1;
	cout << "9в)Умножение числа на матрицу  M1 = 2 * M1\nОбъект M1:\n" << M1 << endl;
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1 << "\nМатрица M2:\n" << M2 << "\n\n";
	cout << "!!!Промежуточный вывод матриц:\nМатрица M1:\n" << M1;
	for (int i = 0; i < 3; i++)
		V3(i) = (rand() % 100) * 0.1 - 5;
	cout << "Вектор(текущее значение) V3:   " << V3 << "\n\n";
	Array M4=M1 * V3;
	cout << "9г)Умножение матрицы на вектор m   M4 = M1 * V3:\nОбъект М4:\n" << M4 << endl;
	_getch();
	system("cls");
	cout << "_/* _/* _/* _/* _/* _/* _/* _/* _КЛАСС СЛАУ_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_ *\\_\n\n";
	int kol;
	cout << "Введите количество уравнений: ";
	cin >> kol;
	float **A = new float*[kol];
	float *B = new float[kol];
	cout << "\nВведите коэффициенты:\n\n";
	for (int i=0; i < kol; i++)
	{
		*(A + i) = new float[kol];
		for (int j=0; j < kol; j++)
		{
			cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
			cin >> A[i][j];
		}
	}
	cout << "\nВведите правые части уравнений:\n\n";
	for (int i=0; i < kol; i++)
	{
		cout << "B[" << i + 1 << "] = ";
		cin >> B[i];
	}
	Slau systema(kol, kol);
	cout << "\nОтвет:\n\n" << systema.Gauss(A, B, kol) << endl;
	_getch();
	return 0;
}

