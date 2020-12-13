#include <locale.h>
#include <ctime>
#include "windows.h"
#include <iostream>

using namespace std;

struct Node
{
	// указатель на следующий элемент в очереди
	Node* next;
	// значение элемента в очереди
	int value;
};

class Ochered
{
public:
	// Колличество элементов в списке
	int N;
	int i;
	int size = 0;
	int size_1 = NULL;
	// Счетчик колличества операций
	unsigned long long int N_op = 0;
	// указатель на первый элемент 
	Node* head;
	// указатель на хвост очереди
	Node* tail;

	// инициализация очереди
	void Init()								  //2
	{
		head = NULL;	N_op++;						  //1
		// При инициализации head и tail = NULL
		tail = head;	N_op++;						  //1
	}

	// добавление элемента в начало очереди, x - значение этого элемента
	void Add(int x)							  //(3+2+2)+(1+2+1)+2=13
	{
		// создание нового элемента
		Node* node = new Node;	N_op += 3;				  //3
		// в поле next данного элемента записывается NULL
		node->next = NULL;	N_op += 2;					  //2
		// в поле value записывается значение ячейки очереди int
		node->value = x;	N_op += 2;					  //2
		// после инициализации и при создании первого элемента мы проходим по ветке else
		if (tail != NULL)						  //1
		{
			N_op++;
			/* добавление элемента через хвост в очереди,
			tail указывает на первый элемент в очереди перед добавляемым
			в поле next первого элемента записывается адрес нового первого элемента*/
			tail->next = node; N_op += 2;					  //2
			// tail начинает указывать на новый элемент в очереди
			tail = node;	N_op++;					  //1
		}
		else
		{
			N_op++;
			// хвост указывает на первый элемент в очереди
			tail = node;	N_op++;					  //1 
			// голова указывает на первый элемент в очереди
			head = tail; 	N_op++;					  //1
		}
		size++;		N_op += 2;					  //2
	}

	// проверка очереди на пустоту
	bool Isempty()							  //1
	{
		N_op++;
		//true, если head = NULL; false, если head указывает на какой-либо элемент в очереди
		return head == NULL;						  //1
	}

	// удаление элемента из конца очереди
	int Del()								  //1+(2+2+2+1+2+2+2)=14
	{
		int val = NULL;	N_op++;					  //1
		// если очередь не пуста
		if (Isempty() != 1)						  //2
		{
			N_op++;
			// создаем указатель на структуру
			Node* tmp;
			//  в указателюь tmp кладем ссылку на next предпоследнего элемента в очереди 
			tmp = head->next; N_op += 2;					  //2
			// в val записываем значение последнего элемента в очереди
			val = head->value; N_op += 2;					  //2
			// удаляем объект по указателю head (последний элемент в очереди)
			delete head;
			// head начинает указывать на предпоcледний элемент в очереди (последний удален)
			head = tmp;		N_op++;				  //1

			// После удаления последнего элемента из очереди происходит повторная инициализация
			if (Isempty() == 1)					  //2
			{
				N_op++;
				Init();					  //2
			}
			size--;		N_op += 2;				  //2
			// возвращаем значение последнего элемента в очереди
			return val;
		}
		else { cout << "Очередь пуста!" << endl; }
		return 0;

	}

	// получение значения из конца очереди
	int Value()								  //3 
	{
		// если очередь не пуста
		if (Isempty() != 1)						  //2
		{
			N_op += 2;
			// через указатель head получить значение value последнего элемента в очереди
			return head->value; 					  //1
		}
		else { cout << "Очередь пуста!" << endl; }
		return 0;
	}

};

// Класс наследник
class Numbers : public Ochered
{
public:
	// получение значения из списка, x - номер элемента в списке
	int get(int x)							  //2+1+1+(1+33n)=5+33n
	{
		// если очередь не пуста
		if (Isempty() != 1)						  //2
		{
			N_op++;
			size_1 = size;	N_op++;				  //1
			int val1 = NULL;	N_op++;				  //1
			N_op++;
			// Перебор всех значений в списке
			for (int i = 0; i < size_1 ; i++)	//1+∑_1^n▒〖(1+4+1+27)=1+∑_1^n▒〖(33)=1+33n〗〗
			{
				if (i == x)					  //1
				{
					N_op++;
					// Когда i доходит до номера получаемого элемента, то в val записывается значение данного элемента
					val1 = Value();	N_op++;		  //4	
				}

				// Перебор начинается только в случае если x не равен нулю
				if (x != 0)					  //1
				{
					N_op++;
					// Вначале элемент удаляется из конца очереди, и сразу же добавляется в начало очереди, и так в цикле пока не восстановится первоначальное состояние очереди
					Add(Del());					  //14+13=27
				}
				else
				{
					N_op++;
					// В противном случае сразу выходим из цикла for
					break;
				}
			}
			// Возвращается значение элемента под номером x из очереди
			return val1;
		}
		else { cout << "Очередь пуста!" << endl; }
		return 0;
	}

	// установка значения элемента в списке, x - номер элемента в списке, y - значение элемента в списке
	void set(int x, int y) 						  //2+3+31n=5+31n
	{
		// если очередь не пуста
		if (Isempty() != 1)						  //2
		{
			N_op++;
			if (x <= size)					  //1+1+1+31n=3+31n
			{
				N_op++;
				size_1 = size;	N_op++;			  //1
				N_op++;
				for (int i = 0; i < size_1 ; i++)	  //1+∑_1^n▒〖(1+2+1+27)〗=1+31n
				{
					if (i == x)				  //1
					{
						N_op++;
						// Запись значения y в список
						head->value = y; N_op += 2;		  //2
					}

					if (x != 0)				  //1
					{
						N_op++;
						Add(Del());			  //14+13=27
					}
					else
					{
						N_op++;
						break;
					}
				}
			}
			// Если элемент устанавливается за пределы изначального списка
			else					//1+2+1+∑_(n+1)^x▒〖(13)+13〗=17+ ∑_(n+1)^x▒〖(13)〗
			{
				N_op++;
				if (x == size)				  //2
				{
					N_op += 2;
					//Если номер элемента в списке на 1 больше размера очереди, значит элемент добавляется в начало очереди
					Add(y);
				}
				else
				{
					N_op += 2; N_op++;
					for (i = size ; i < x; i++)	  //1+∑_(n+1)^x▒〖(13)〗
					{
						// В противном случае очередь заполняется нулями
						Add(0);			  //13
					}
					Add(y);				  //13
				}

			}

		}
		else { cout << "Очередь пуста!" << endl; }
	}
	void Print()
	{
		unsigned long long int Bufer = N_op;
		if (Isempty())
		{
			return;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				cout << get(i) << " ";

			}
			cout << endl;
		}
		N_op= Bufer;
	}
		void sort()
		{
			int i;//	1
			int j ;// указатели, участвующие в разделении	1

			int lb, ub;  		// границы сортируемого в цикле фрагмента	2
			auto lbstack = new int[size]; N_op+=size; // стек запросов	n+1
			auto ubstack = new int[size]; N_op += size;;//	n+1
								  // каждый запрос задается парой значений,
								  // а именно: левой(lbstack) и правой(ubstack) 
								  // границами промежутка
	
			int stackpos = 1;   N_op++;	// текущая позиция стека	2
			int ppos;            // середина массива	 1
			int pivot;              // опорный элемент	1
			int temp;//1
			lbstack[1] = 0; N_op += 2;//2
			ubstack[1] = size - 1; N_op += 3;//3
	
			do {
	
				// Взять границы lb и ub текущего массива из стека.
	
				lb = lbstack[stackpos]; N_op += 2;//2*n
					ub = ubstack[stackpos]; N_op += 2;//2*n
				stackpos--; N_op += 2;//2*n
	
				do {
					// Шаг 1. Разделение по элементу pivot
	
					ppos = (lb + ub) >> 1; N_op += 2;//3*2n^2
					i = lb; N_op++;//1*2n^2
						j = ub; N_op++;//1*2n^2
						pivot = get(ppos); N_op++;//(5+33n+1)*2n^2
	
					do {
						while (get(i) < pivot)
						{//(5+33n+1)*2n^3
							N_op++;
							i++; N_op += 2;//2*2n^3
						}
						while (pivot < get(j))//(5+33n+1)*2n^3
						{
							N_op++;
							j--; N_op += 2;//2*2n^3
						}
						N_op++;
						if (i <= j) //1*2n^3
						{
							temp = get(i);//(5+33n+1)*2n^3
							N_op++;
							int buf = get(j);// (5+33n+1)*2n^3
							N_op++;
							set(i,buf); //(5+31n)*2n^3
							set(j,temp);//(5+31n)*2n^3
							N_op += 2;
							i++; //2*2n^3
							N_op += 2;
							j--;//2*2n^3
						}
						N_op++;
					} while (i <= j);//1*2n^3
	
					// Сейчас указатель i указывает на начало правого подмассива,
					// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
					// Возможен случай, когда указатель i или j выходит за границу массива
	
					// Шаги 2, 3. Отправляем большую часть в стек  и двигаем lb,ub
					N_op++;
					if (i < ppos) //1*2n^2
					{     // правая часть больше	
						N_op++;
						if (i < ub) //1*2n^2
						{
							N_op+=2;  //  если в ней больше 1 элемента - нужно 
							stackpos++;       //  сортировать, запрос в стек	//1*2n^2
							lbstack[stackpos] = i; N_op += 2;	//2*2n^2
							ubstack[stackpos] = ub; N_op += 2;	//2*2n^2
						}
						N_op++;
						ub = j; //1*2n^2            //  следующая итерация разделения
											//  будет работать с левой частью
	
					}
					else 
					{       	    // левая часть больше
						N_op++;
						if (j > lb)		//1*2n^2
						{
							N_op += 2;
							stackpos++;		//2*2n^2
							lbstack[stackpos] = lb;	N_op += 2;	//2*2n^2
							ubstack[stackpos] = j;	N_op += 2;	//2*2n^2
						}
						N_op++;
						lb = i;		//1*2n^2
					}
					N_op++;
				} while (lb < ub);    //1*2n^2    // пока в меньшей части более 1 элемента
				N_op++;
			} while (stackpos != 0);//1*n    // пока есть запросы в стеке
			delete[] lbstack;
			delete[] ubstack;
		}
	};

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	// Схема эксперимента
	// Инициализация очереди и заполнение хранилища ключей
	int i, t_s, t_f,kol,bolkol;
	cout << "Введите количество сортировок: ";
	cin >> bolkol;
	auto Nstor = new int[bolkol+1];//хранилище количества элементов в каждой очереди
	auto Timestor = new int[bolkol+1];//хранилище данных о времени выполнения каждой сортировки 
	auto N_opstor = new unsigned long long int[bolkol+1];//хранилище количества операций в каждой сортировке
	if (bolkol < 0)
	{
		cout << "Вы ввели неверное значение";
		return 0;
	}
	cout << endl << endl;
	for (int j = 1; j <= bolkol; j++)
	{
		cout << "Введите количество элементов "<<j<<"-й очереди: ";
		cin >> kol;
		if (kol < 0)
		{
			cout << "Вы ввели неверное значение";
			return 0;
		}
		auto Key = new int[kol];
		int N = kol;
		Numbers list;
		list.Init();
		for (i = 0; i < kol; i++)
		{
			// Заполнение хранилища ключей случайными числами до 1000
			Key[i] = rand() / 100 - 200;
		}

		for (int z = 0; z < kol; z++)
		{
			list.Add(Key[z]);
		}
		cout << "Изначальная очередь: " << endl;
		if (kol <= 299)
			list.Print();
		else
			cout << "Очередь слишком большая, вывод бесполезен"<<endl;
		t_s = GetTickCount();
		list.N_op = 0;
		list.sort();
		cout << "Отсортированная очередь: " << endl;
		if (kol <= 299)
			list.Print();
		else
			cout << "Очередь слишком большая, вывод бесполезен";
		t_f = GetTickCount();
		Nstor[j] = N;
		Timestor[j] = t_f - t_s;
		N_opstor[j] = list.N_op;
		delete[] Key;
		cout << endl << endl;
	}
	for (int j = 1; j <= bolkol; j++)
	{
		cout << "Сортировка номер " << j << ":  " << "Колличество отсортированных элементов: " << Nstor[j] << " Время сортировки (ms): " << Timestor[j] << " Колличество операций (N_op): " << N_opstor[j] << endl;
	}
	delete[] Nstor;
	delete[] Timestor;
	delete[] N_opstor;
	return 0;
}

