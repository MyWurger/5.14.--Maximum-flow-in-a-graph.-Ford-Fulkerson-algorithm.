/*********************************************************************************
 * Л А Б О Р А Т О Р Н А Я   Р А Б О Т А  №10  З А   5   С Е М Е С Т Р   С  +  + *
 *-------------------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                                     *
 * Project Name  : Teor_Grph_Lab10                                               *
 * File Name     : Lab10. CPP                                                    *
 * Programmer(s) : Викулов Д.Г.                                                  *
 * Modifyed By   :                                                               *
 * Created       : 15/10/23                                                      *
 * Last Revision : 17/10/23                                                      *
 * Comment(s)    : Программа, рассчитывающая максимальный поток в сети. Поиск    *
 *                 производится алгоритмом Джонсона. Расчёт выполняется          *
 *                 алгоритмом Форда-Фалкерсона. Источник и сток определяются     *
 *                 автоматически. Результатом работы является список рёбер с     *
 *                 указанием величины потока                                     *
 *********************************************************************************/


#include <iostream>              // стандартные потоки ввода/вывода
#include <vector>                // работа с векторами для удобства быстрого извлечения и удаления элементов
#include <fstream>               // работа с потоками ввода/вывода для файла
#include <iomanip>               // библиотека с модификатором setw
#include <graphviz/gvc.h>        // библиотека Graphviz для графического изображения графа по матрице смежности
#include <opencv2/opencv.hpp>    // заголовок, подтягивающий все функции OpenCv

using namespace std;             // используем пространство имён std


/*******************************************************************/
/*            Г Л О Б А Л Ь Н Ы Е    К О Н С Т А Н Т Ы             */
/*******************************************************************/

// путь к файлу через константный указатель
// Входные файлы
// ТЕСТЫ ДЛЯ МАТРИЦЫ СМЕЖНОСТИ
//const char* FNAMEIN = "matrix_t10_001.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_002.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_003.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_004.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_005.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_006.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_007.txt";                // файл с матрицей смежности
//const char* FNAMEIN = "matrix_t10_008.txt";                // файл с матрицей смежности


// ТЕСТЫ ДЛЯ СПИСКА РЕБЕР
//const char* FNAMEIN = "list_of_edges_t10_001.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_002.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_003.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_004.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_005.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_006.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_007.txt";         // файл со списком рёбер
//const char* FNAMEIN = "list_of_edges_t10_008.txt";         // файл со списком рёбер

// ТЕСТЫ ДЛЯ СПИСКА СМЕЖНОСТИ
// ТЕСТОВ В АРХИВЕ НЕ ПРЕДСТАВЛЕНО

// ВЫХОДНЫЕ ФАЙЛЫ
const char* FNAMEOUT = "Output_File.txt";

// бесконечность для матрицы расстояний
const int INF = 10000;




/*******************************************************************/
/*      Г Л О Б А Л Ь Н Ы Е    Ф А Й Л О В Ы Е    П О Т О К И      */
/*******************************************************************/

 // объявление объекта для потокового ввода данных из файла
ifstream fin;
// объявление объекта для потокового вывода данных в файл
ofstream fout;




/*******************************************************************/
/*                 И Е Р А Р Х И Я   К Л А С С О В                 */
/*******************************************************************/

/*------------------------------------------------------------------------*/
/*                 Graph                  */
/*----------------------------------------*/

class Graph
{
private:
	vector<vector<int>> m_matrix;                             // граф в программе представлен матрицей смежности
	int m_size;                                               // размер матрицы смежности (количество вершин в графе)

public:
	// конструктор
	Graph();
	// деструктор
	~Graph();
	// константный геттер для получения значения размера
	const int GetSize();
	// функция возвращающая True, если граф ориентированный, False, если граф простой;
	bool is_directed();
	// функция, возвращающая матрицу смежности
	vector<vector<int>> adjacency_matrix();
	// весовая функция, принимает номера вершин, возвращает вес ребра, связывающего их;
	int Weight(int Vi, int Vj);
	// функция, принимающая номера вершин и возвращает True, если в графе есть соответствующее ребро / дуга, False, если ребра нет;
	bool is_edge(int Vi, int Vj);
	// функция, возвращающая список вершин, смежных вершине v;
	vector<int> adjacency_list(int v);
	// функция, возвращающая список всех рёбер графа;
	vector<pair<int, int>> list_of_edges_pairs();
	// функция, возвращающая список всех рёбер графа, инцидентных вершине v / исходящих из вершины v
	vector<pair<int, int>> list_of_edges(int v);
};




/*******************************************************************/
/*              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                 */
/*******************************************************************/

// сохранение графа как фотографии
string drawGraph(const vector<vector<int>>& adjacencyMatrix);     // объявление константной ссылки на двумерный вектор adjacencyMatrix, содержащий целочисленные значения 

// вывод графа на экран в виде картинки
void OpenImage(const vector<vector<int>>& adjacencyMatrix);       // объявление константной ссылки на двумерный вектор adjacencyMatrix, содержащий целочисленные значения 

// вывод матрицы смежности на экран
void PrintMatrix(vector<vector<int>> matrix);                     // матрица, которую необходимо вывести на экран. Передача по значению

// печать справки и авторов работы
void Usloviya();

// определяем сток в графе - не исходит ни одно ребро из этой вершины
int Sink(vector<vector<int>> matrix);                             // матрица смежности графа

// определение источника в графе - в вершину не входит ни одна дуга -> столбец с соответствующим номером нулевой
int Source(vector<vector<int>> matrix);                           // матрица смежности графа  

// Функция для нахождения пути по DFS
bool findPathDFS(vector<vector<int>> graph,                       // матрица смежности графа
	             vector<vector<int>> residualGraph,               // матрица остаточной сети
	             int source,                                      // источник      
	             int sink,                                        // сток
	             vector<bool>& visited,                           // вектор посещённых вершин
	             vector<int>& path);                              // посещённый путь

// Функция для нахождения максимального потока по алгоритму Форда-Фалкерсона
void maxFlowFordFulkerson(vector<vector<int>> graph,              // матрица смежности графа
	                      vector<vector<int>>& flowMatrix,        // матрица потоков
	                      int source,                             // источник
	                      int sink);                              // сток

// вывод матрицы  в файл
void PrintMatrToFile(vector<vector<int>> matrix);                 // матрица, которую необходимо вывести в файл. Передача по значению




// конструктор - считывание матрицы из файла
Graph::Graph()
{
	fin.open(FNAMEIN);            // связываем объект с файлом
	if (!fin.is_open())           // файл не найден
	{
		cout << "Файла с таким именем нет. Невозможно осуществить чтение";
		fin.close();              // закрыть файл для чтения
		system("pause");
		exit(0);                  // возвращаем значение, соответствующее типу в caller
	}// if (!fin.is_open())

	int value;                    // очередной считываемый символ
	char key;                     // ключ для указания пользователем варианта задания графа в файле
	bool spravka = true;          // ключ для вывода справки на экран
	vector<int> row;              // вектор для считывания промежуточных значений из файла построчно
	vector<vector<int>> matrix;   // вспомогательная матрица смежности

	// повтор ввода задания графа, когда пользователь захотел вывести на экран справку
	while (spravka)
	{
		cout << "\x1b[30m В В Е Д И Т Е   К Л Ю Ч   И Л И   <h>   Д Л Я   В Ы З О В А   П О Д С К А З К И : \x1b[30m";
		// пользователь ввёл ключ для того, чтобы явно указать, каким способом он задал граф
		cin >> key;
		cout << "\n Вы ввели: " << key << endl;

		// в зависимости от значения ключа
		switch (key)
		{
			// работа с матрицей смежности
		case('m'):
		case('M'):
		{
			cout << "\n\t\t\t\t\x1b[32m В Ы   В Ы Б Р А Л И   Т И П   З А Д А Н И Я   -   М А Т Р И Ц А   С М Е Ж Н О С Т И\n\n\x1b[30m\n";
			// считываем очередное число из файла
			while (fin >> value)
			{
				// после считывания каждой строки очищаем вектор строки
				row.clear();
				// загоняем в вектор первый считанный элемент от первого while (fin >> value)
				row.push_back(value);
				// считываем все остальные элементы строки, пока не нашли символ её окончания - \n
				while (fin.peek() != '\n' && fin >> value)
				{
					row.push_back(value);
				}// while (fin.peek() != '\n' && fin >> value)

				// кладем в матрицу считанную строку. Все строки имеют одинаковый размер, так как работаем с матрицей смежности
				m_matrix.push_back(row);

			}// while (fin >> value)

			// повторять ввод не надо. Матрица заполнена
			spravka = false;
			break;
		}

		// работа со списком рёбер
		case('e'):
		case('E'):
		{
			cout << "\n\t\t\t\t\x1b[32m В Ы   В Ы Б Р А Л И   Т И П   З А Д А Н И Я   -   С П И С О К   Р Ё Б Е Р\n\n\x1b[30m\n";

			// считываем значения из файла в вектор
			// в векторе будут находиться с чередованием через три элементы: начальная вершина, конечная вершина и вес ребра
			while (fin >> value)
			{
				// после считывания каждой строки очищаем вектор строки
				row.clear();
				// загоняем в вектор первый считанный элемент от первого while (fin >> value)
				row.push_back(value);
				// считываем все остальные элементы строки, пока не нашли символ её окончания - \n
				while (fin.peek() != '\n' && fin >> value)
				{
					row.push_back(value);
				}// while (fin.peek() != '\n' && fin >> value)

				// кладем в матрицу считанную строку. Все строки имеют одинаковый размер, так как работаем с матрицей смежности
				m_matrix.push_back(row);
			}// while (fin >> value)

			// закрыть файл чтения
			fin.close();
			int size_m = m_matrix[m_matrix.size() - 1][0];    // размер матрицы смежности
			vector<vector<int>> vec_1(size_m);                // матрица смежности

			for (int i = 0; i < size_m; i++)                  // задаём размер каждой ячейки vec_1
			{
				vec_1[i].resize(size_m, 0);
			}// for i

			// заполняем матрицу смежности
			for (int i = 0; i < m_matrix.size(); i++)
			{
				if (m_matrix[0].size() == 3)                  // 3 элемент - это вес ребра, если он не указан, то значит он = 1
				{
					vec_1[m_matrix[i][0] - 1][m_matrix[i][1] - 1] = m_matrix[i][2];
				}
				else
				{
					vec_1[m_matrix[i][0] - 1][m_matrix[i][1] - 1] = 1;
				}// if (m_matrix[0].size() == 3)
			}// for i

			// запоминаем матрицу смежности
			m_matrix = vec_1;
			// повторять ввод не надо. Матрица заполнена
			spravka = false;
			break;
		}

		// работаем со списками смежности
		case('l'):
		case('L'):
		{
			cout << "\n\t\t\t\t\x1b[32m В Ы   В Ы Б Р А Л И   Т И П   З А Д А Н И Я   -   С П И С О К   С М Е Ж Н О С Т И\n\n\x1b[30m\n";

			// чтение из файла построчно
			string line;
			int rowNumber = 0;            // номер текущей строки

			// чтение построчное
			while (getline(fin, line))
			{
				// Если строка пустая, заполняем текущую строку нулями
				if (line.empty())
				{
					matrix.push_back(vector<int>(m_size, 0));
				}
				// строка не пустая
				else
				{
					// вектор строки
					vector<int> row;
					// создает поток для чтения значений из строки line. Затем мы можем использовать iss вместе с оператором >> для извлечения значений из строки.
					istringstream iss(line);
					// очередная величина для чтения
					int value;

					// читаем значение из файла и помещаем его в вектор строки
					while (iss >> value)
					{
						row.push_back(value);
					}// while

					// помещаем строку в матрицу
					matrix.push_back(row);
				}// if (line.empty()) 

				// увеличиваем номер строки
				rowNumber++;
			}// while (getline(fin, line)) 

			// файл прочитан - закрываем его
			fin.close();

			m_size = matrix.size();                         // размер матрицы смежности

			vector<vector<int>> vec_1(m_size);              // доп матрица смежности размером m_size

			for (int i = 0; i < m_size; i++)                // задаём размер каждой ячейки доп матрицы смежности
			{
				// заполняем вспомогательную матрицу нулями по всему размеру
				vec_1[i].resize(m_size, 0);
			}// for i

			for (int i = 0; i < m_size; i++)                 // заполняем доп матрицу смежности 
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					// единица в тех столбцах, которые перечислены для данной в файле
					vec_1[i][matrix[i][j] - 1] = 1;
				}// for j
			}// for i

			// загоняем значения в основную матрицу смежности
			for (int i = 0; i < m_size; i++)
			{
				row.clear();
				for (int j = 0; j < m_size; ++j)
				{
					row.push_back(vec_1[i][j]);
				}// fot j

				m_matrix.push_back(row);
			}// for i

			// повторять ввод не надо. Матрица заполнена
			spravka = false;
			break;
		}

		// пользователь выбрал справку
		case('h'):
		case('H'):
		{
			// повторить ввод после появления мправки на экране
			spravka = true;
			// выводим условия
			Usloviya();
			break;
		}

		// иначе - пользователь ввёл не тот ключ. Заканчиваем программу с ошибкой
		default:
			cout << "\n\x1b[31m ПЕРЕЗАПУСТИТЕ ПРОГРАММУ И ВВЕДИТЕ ЗНАЧЕНИЕ ИЗ СПИСКА КЛЮЧЕЙ!!!\n\x1b[30m";
			// закрываем файл считывания
			fin.close();
			exit(0);
		}
	}
	// закрываем файл считывания
	fin.close();
	// запоминаем размер считанной/ преобразованной матрицы смежности
	m_size = m_matrix.size();
}

// деструктор
Graph::~Graph()
{
	// пустое тело - векторы уничтожаются автоматически
}

// геттер для получения значения размера
const int Graph::GetSize()
{
	// возвращаем значение размера матрицы
	return(m_size);
}


// функция возвращающая True, если граф ориентированный, False, если граф простой;
bool Graph::is_directed()
{
	// идём по строкам
	for (int i = 0; i < m_size; i++)
	{
		// идём по столбцам
		for (int j = 0; j < m_size; j++)
		{
			// если граф неориентированный, то матрица симметрична, так как по ребру можно пройти подвум направлениям
			if (m_matrix[i][j] != m_matrix[j][i])
			{
				return true; // Найдено направленное ребро - граф ориентированный
			}// if (m_matrix[i][j] != m_matrix[j][i])

		}// for j

	}// for i

	return false; // Не найдено направленных ребер - граф неориентированный
}


// функция, возвращающая матрицу смежности
vector<vector<int>> Graph::adjacency_matrix()
{
	return(m_matrix);
}


// весовая функция, принимает номера вершин, возвращает вес ребра, связывающего их;
int Graph::Weight(int Vi, int Vj)

{
	// номера вершин вышли за диапазоны допустимых значений
	if ((Vi >= m_size || Vi < 0) || (Vj >= m_size || Vj < 0))
	{
		cout << "Ошибка! Такой вершины не существует\n";
		// вернули ошибку
		return(-1);
	}// if

	// если путь существует(в матрице смежности не 0)
	if (m_matrix[Vi][Vj] != 0)
	{
		cout << "Вес ребра между вершинами " << Vi << " и " << Vj << " равен" << m_matrix[Vi][Vj] << endl;
		cout << m_matrix[Vi][Vj] << endl;
		// возвращаем вес ребра между вершинами
		return(m_matrix[Vi][Vj]);
	}// if

	// граф ориентированный. Выводим вес дуги
	else if ((m_matrix[Vi][Vj] != m_matrix[Vj][Vi]) && (m_matrix[Vi][Vj] != 0 || m_matrix[Vj][Vi] != 0))
	{
		cout << "Граф ориентированный. Дуга есть. Направление учитывается. Вес дуги между вершинами " << Vi << " и " << Vj << " равен" << m_matrix[Vi][Vj] << endl;
		// возвращаем вес дуги
		return(m_matrix[Vi][Vj]);
	}// else if

	// ребра между вершинами нет - элемент матрицы смежности равен 0
	else if (m_matrix[Vi][Vj] == 0)
	{
		cout << "Ребра между вершинами " << Vi << " и " << Vj << "нет\n";
		// Вернули нулевое значение
		return(m_matrix[Vi][Vj]);
	}// else if

	return(0);
}


// функция, принимающая номера вершин и возвращает True, если в графе есть соответствующее ребро / дуга, False, если ребра нет;
bool Graph::is_edge(int Vi, int Vj)
{
	// номера вершин вышли за диапазоны допустимых значений - дуги нет
	if ((Vi >= m_size || Vi < 0) || (Vj >= m_size || Vj < 0))
	{
		// вернули, что дуги нет
		return(false);
	}// if

	// элемент матрицы смежности не равен 0 - ребро есть
	if (m_matrix[Vi][Vj] != 0)
	{
		// подтверждаем, что ребро есть
		return(true);
	}// if

	// элемент матрицы смежности нулевой - ребра нет
	if (m_matrix[Vi][Vj] == 0)
	{
		// подтверждаем, что ребра нет
		return(false);
	}// if

}


// функция, возвращающая список вершин, смежных вершине v;
vector<int> Graph::adjacency_list(int v)
{
	// список вершин
	vector<int> adjList;

	// Проходим по всем вершинам и проверяем, есть ли ребро между вершиной v и текущей вершиной
	for (int i = 0; i < m_size; i++)
	{
		// путь есть - элемент матрицы не нулевой
		if (m_matrix[v][i] != 0)
		{
			// помещаем вершину в список
			adjList.push_back(i);
		}// if (m_matrix[v][i] != 0)

	}// for i

	// Возвращаем список смежных вершин
	return adjList;
}


// функция, возвращающая список всех рёбер графа;
vector<pair<int, int>> Graph::list_of_edges_pairs()
{
	// вектор пар, содержащий ребро в виде двух инцидентных ему вершин
	vector<pair<int, int>> edges_pairs;
	// идём по всем элементам строки
	for (int i = 0; i < m_size; i++)
	{
		// идём по всем элементам столбца
		for (int j = 0; j < m_size; j++)
		{
			// если элемент не нулевой
			if (m_matrix[i][j] != 0)
			{
				// загрузили пару вершин
				edges_pairs.push_back(make_pair(i, j));
			}// if (m_matrix[i][j] != 0)
		}// for j
	}// for i

	// вернули вектор рёбер (пар вершин)
	return(edges_pairs);
}


// функция, возвращающая список всех рёбер графа, инцидентных вершине v / исходящих из вершины v
vector<pair<int, int>> Graph::list_of_edges(int v)
{
	int count = 0;
	vector<pair<int, int>> edges;         // вектор пар вершин(вектор рёбер)
	vector<pair<int, int>> edges_inc;     // вектор рёбер инцидентных вершине v / исходящих из вершины v
	edges = list_of_edges_pairs();        // получаем все пары вершин графа

	// обходим эти пары. Если граф неориентированный, то там будет пара (v,n) и (n, v) - достаточно рассмотреть для инцидентности первый элемент. В орграфе - исходящий элемент всегда первый
	for (int i = 0; i < edges.size(); i++)
	{
		// рассматриваем первый элемент пары
		if (edges[i].first == v)
		{
			// помещаем в списо ребер, инцидентных вершине данное ребро
			edges_inc.push_back(edges[i]);
			// увеличиваем счётчик
			count = count + 1;
		}//if (edges[i].first == v)
	}//for i

	// возвращаем  список всех рёбер графа, инцидентных вершине v / исходящих из вершины v
	return(edges_inc);
}




/*------------------------------------------------------------------------*/
/*                Функции               */
/*--------------------------------------*/

// сохранение графа как фотографии
string drawGraph(const vector<vector<int>>& adjacencyMatrix)
{
	// Проверяем размер матрицы смежности. Если больше 19, то считаем ее слишком большой
	if (adjacencyMatrix.size() <= 25)
	{
		bool key = false;
		// Проверяем наличие весов на ребрах, чтобы понять, нужно ли указывать их при выводе
		for (int i = 0; i < adjacencyMatrix.size(); i++)
		{
			for (int j = 0; j < adjacencyMatrix.size(); j++)
			{
				// Если вес ребра больше 1 или отрицательный, значит, нужно указывать вес в выводе
				if (adjacencyMatrix[i][j] > 1 || adjacencyMatrix[i][j] < 0)
					key = true;
			}
		}

		// Открываем файл для записи графа в формате DOT
		std::ofstream file;
		file.open("graph.dot");
		file << "digraph G {" << endl;

		if (key)
		{
			// Выводим граф с указанием весов ребер
			for (int i = 0; i < adjacencyMatrix.size(); i++)
			{
				for (int j = 0; j < adjacencyMatrix[i].size(); j++)
				{
					// Проверяем, что вес ребра не равен 0, чтобы не выводить ненужные ребра
					if (adjacencyMatrix[i][j] != 0)
					{
						// Выводим ребро с указанием веса в формате DOT
						file << i << " -> " << j << " [label=\"" << adjacencyMatrix[i][j] << "\"];" << endl;
					}// if (adjacencyMatrix[i][j] != 0) 
				}// for j
			}// for i
		}

		else
		{
			// Выводим граф без указания весов ребер
			for (int i = 0; i < adjacencyMatrix.size(); i++)
			{
				for (int j = 0; j < adjacencyMatrix[i].size(); j++)
				{
					// Проверяем, что вес ребра равен 1, чтобы не выводить ненужные ребра
					if (adjacencyMatrix[i][j] == 1)
					{
						// Выводим ребро без указания веса в формате DOT
						file << i << " -> " << j << ";" << endl;
					}//if (adjacencyMatrix[i][j] == 1) 
				}// for j
			}// for i
		}// if key

		// Закрываем файл и сохраняем результаты
		file << "}" << std::endl;
		file.close();

		// Генерируем изображение графа в формате PNG с помощью утилиты DOT
		system("dot -Tpng graph.dot -o graph.png");
		cout << "\n\nGraph image saved as graph.png" << endl;
	}

	// Выводим, что граф большой для рисования
	else
	{
		cout << "\n\nGraph image is not saved as graph.png. It is too big" << endl;
	}// if

	// возвращаем картинку для открытия силами OpenCV
	return "graph.png";
}


// вывод графа на экран
void OpenImage(const std::vector<std::vector<int>>& adjacencyMatrix)
{
	// Проверяем размерность матрицы смежности
	if (adjacencyMatrix.size() <= 25)
	{
		// Получаем путь к изображению, созданному с помощью функции drawGraph
		std::string imagePath = drawGraph(adjacencyMatrix);
		// Загружаем изображение с помощью OpenCV
		cv::Mat img = cv::imread(imagePath, -1);

		// Проверяем, удалось ли загрузить изображение
		if (img.empty())
		{
			cout << "Could not open or find the image" << endl;
			return;
		}// if

		// Создаем окно с названием "Graph"
		cv::namedWindow("Graph", cv::WINDOW_NORMAL);
		// Показываем изображение в окне
		cv::imshow("Graph", img);
		// Ждем, пока пользователь нажмет любую клавишу
		cv::waitKey(0);
		// Закрываем окно
		cv::destroyWindow("Graph");
		return;
	}// if (adjacencyMatrix.size() <= 19)
}


// вывод матрицы смежности на экран
void PrintMatrix(vector<vector<int>> matrix)
{
	// отключаем русский язык
	setlocale(0, "C");            // выводим массив в красивых скобках
	cout << setw(2) << setfill(' ') << (char)218 << (char)196 << (char)196 << setw(matrix.size() * 2 + 7) << setfill(' ') << (char)196 << (char)196 << (char)191 << endl;          // вывод верхних квадратных скобок

	// идём по строкам
	for (int i = 0; i < matrix.size(); i++)
	{
		cout << setw(5) << setfill(' ');
		// идём по столбцам
		for (int j = 0; j < matrix.size(); j++)
		{
			// выводим элемент матрицы
			cout << matrix[i][j] << " ";
		}// for j

		cout << endl;
	}// for i
	cout << setw(2) << setfill(' ') << (char)192 << (char)196 << (char)196 << setw(matrix.size() * 2 + 7) << setfill(' ') << (char)196 << (char)196 << (char)217 << endl;          // вывод верхних квадрат
	// подключаем русский язык
	setlocale(LC_ALL, "Russian");

	// возвращаем обещанное значение
	return;
}


// печать справки и авторов работы
void Usloviya()
{
	cout << "\n\t\t\t\t/********************************************************************************\n";
	cout << "\t\t\t\t* Л А Б О Р А Т О Р Н А Я   Р А Б О Т А  №10  З А   5   С Е М Е С Т Р   С  +  +   *\n";
	cout << "\t\t\t\t*---------------------------------------------------------------------------------*\n";
	cout << "\t\t\t\t* Project Type  : Win64 Console Application                                       *\n";
	cout << "\t\t\t\t* Project Name  : Teor_Grph_Lab10                                                 *\n";
	cout << "\t\t\t\t* File Name     : Lab10. CPP                                                      *\n";
	cout << "\t\t\t\t* Programmer(s) : Викулов Д.Г.                                                    *\n";
	cout << "\t\t\t\t* Modifyed By   :                                                                 *\n";
	cout << "\t\t\t\t* Created       : 15/10/23                                                        *\n";
	cout << "\t\t\t\t* Last Revision : 17/10/23                                                        *\n";
	cout << "\t\t\t\t***********************************************************************************/\n";

	cout << "\n\t\t\t\t\t\t\t\x1b[31m   С П Р А В К А : \n\n\x1b[30m";
	// Выводим условия в таблице
	setlocale(0, "C");                       // отключаем русский язык
	cout << char(218) << setw(40) << setfill((char)196) << (char)191 << endl << (char)179;  // выводим верхнюю строку шапки
	setlocale(LC_ALL, "Rus");                // подключаем русский язык
	cout << " Выберите одно значние из списка:      ";
	setlocale(0, "C");                       // отключаем русский язык
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)194 << setw(35) << setfill((char)196) << (char)180 << setfill(' ') << endl << (char)179;    // выводим нижнюю строку шапки с разделителем между номером и названием алгоритма
	cout << "  e " << (char)179 << "  Edges_list_file_path            ";                                                                                                         // выводим условия выбора и нижнюю с боковыми строчками таблицы
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  m " << (char)179 << "  Adjacency_matrix_file_path      ";
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  l " << (char)179 << "  Adjacency_list_file_path        ";
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  o " << (char)179 << "  Output_file_path                ";
	cout << (char)179 << endl << (char)192 << setw(5) << setfill((char)196) << (char)193 << setw(35) << setfill((char)196) << (char)217 << endl;
	cout << endl;
	setlocale(LC_ALL, "Rus");               // подключаем русский язык

	return;                                 // возвращаем обещанное значение
}


// определяем сток в графе - не исходит ни одно ребро из этой вершины
int Sink(vector<vector<int>> matrix)        // матрица смежности графа
{
	// количество вершин в матрице смежности
	int V = matrix.size();
	// номер вершины - стока
	int sink = -1;
	// флаг
	bool zero = true;
	// Вершина - сток, если в строке матрицы смежности с соответствующим номером находятся одни нули
	// проходимся по всем строкам
	for (int i = 0; i < V; i++)
	{
		zero = true;
		// идём по столбцам
		for (int j = 0; j < V; j++)
		{
			// если нашли ненулевой элемент в строке матрицы смежности
			// переходим к другой строке, игнорируя дальнейшие условия
			if (matrix[i][j] != 0)
			{
				zero = false;
				continue;
			}// if

		}// for j

		// если прошлись по всей строке и там все нули
		if (zero == true)
		{
			// запоминаем эту строку
			sink = i;
			// возвращаем её номер
			return(sink);
		}// if

	}// for i

	// если не нашли ничего - вернули несуществующее значение
	return(-1);
}


// определение источника в графе - в вершину не входит ни одна дуга -> столбец с соответствующим номером нулевой
int Source(vector<vector<int>> matrix)      // матрица смежности графа
{
	// количество вершин в матрице смежности
	int V = matrix.size();
	// номер выршины - источника
	int source = -1;
	// флаг
	bool zero = true;

	// Вершина - сток, если в столбце матрицы смежности с соответствующим номером находятся одни нули
	// проходимся по всем столбцам
	for (int j = 0; j < V; j++)
	{
		zero = true;
		// идём по строкам
		for (int i = 0; i < V; i++)
		{
			// если нашли ненулевой элемент в столбце матрицы смежности
			// переходим к другому столбцу, игнорируя дальнейшие условия
			if (matrix[i][j] != 0)
			{
				zero = false;
				continue;
			}// if

		}// for i

		// если прошлись по всему столбцу и там все нули
		if (zero == true)
		{
			// запоминаем этот столбец
			source = j;
			// возвращаем его номер
			return(source);
		}// if

	}// for i

	// если не нашли ничего - вернули несуществующее значение
	return(-1);
}


// Функция для нахождения пути по DFS
bool findPathDFS(vector<vector<int>> graph,                   // матрица смежности графа
	             vector<vector<int>> residualGraph,           // матрица остаточной сети
	             int source,                                  // источник      
	             int sink,                                    // сток
	             vector<bool>& visited,                       // вектор посещённых вершин
	             vector<int>& path)                           // посещённый путь
{
	// Очередная вершина помечается как посещённая
	visited[source] = true;
	// добавляем эту вершину в вектор пути
	path.push_back(source);

	// если текущая вершина пути совпала с конечной - стоком
	if (source == sink)
	{
		// возвращаем путь и флаг успеха
		return true;
	}// if

	// проходим по всем вершинам графа
	for (int v = 0; v < graph.size(); v++) 
	{
		// если вершина не была посещена и существует в остаточной сети путь от данной вершины до какой-либо другой,
		// вызываем рекурсивно функцию для следующей вершины (соседа v)
		// Если вершина не была посещена, и существует путь от данной вершины до другой (через остаточную сеть), рекурсивно вызывается findPathDFS для следующей вершины.
		if (!visited[v] && residualGraph[source][v] > 0 && findPathDFS(graph, residualGraph, v, sink, visited, path))
		{
			// Если путь найден в рекурсивном вызове, то возвращается true.
			return true;
		}// if
	}// for v

	// Если ни один путь не найден, последняя вершина удаляется из пути и возвращается false.
	path.pop_back();
	return false;
}


// Функция для нахождения максимального потока по алгоритму Форда-Фалкерсона
void maxFlowFordFulkerson(vector<vector<int>> graph,              // матрица смежности графа
	                      vector<vector<int>>& flowMatrix,        // матрица потоков
	                      int source,                             // источник
	                      int sink)                               // сток
{
	// количество вершин в графе - размер матрицы смежности
	int V = graph.size();
	// матрица остаточной сети
	vector<vector<int>> residualGraph(V, vector<int>(V, 0));

	// Строим остаточную сеть. Изначально она совпадает с исходным графом
	// идём по всем строкам
	for (int i = 0; i < V; i++) 
	{
		// идём по всем столбцам
		for (int j = 0; j < V; j++) 
		{
			// приравниваем матрицы
			residualGraph[i][j] = graph[i][j];
		}// for j
	}// for i

	// вектор посещённых вершин для DFS
	vector<bool> visited(V, false);
	// вектор пути для DFS
	vector<int> path;

	cout << "\n\x1b[31m В О З М О Ж Н Ы Е   П У Т И   И З   И С Т О Ч Н И К А   К   С Т О К У: \x1b[30m";
	cout << endl;
	
	// пока существует путь из источника к стоку в матрице остаточной сети
	while (findPathDFS(graph, residualGraph, source, sink, visited, path)) 
	{
		cout << " ";
		// выводим рассматриваемые пути, участвующие в алгоритме
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] + 1 << " ";
		}// for i
		cout << endl;

		// Находим минимальную пропускную способность на пути
		int Cmin = INF;
		// идём по всем рёбрам пути
		for (int i = 0; i < path.size() - 1; i++) 
		{
			// начальная вершина ребра пути
			int u = path[i];
			// конечная вершина ребра пути
			int v = path[i + 1];

			// Cmin - минимальное значение ребра в пути
			Cmin = min(Cmin, residualGraph[u][v]);
		}// for i

		// Обновляем остаточную сеть и максимальный поток
		for (int i = 0; i < path.size() - 1; i++) 
		{
			// вычитание из исходной матрицы матрицы исходного потока равносильно вычитанию Cmin из тех элементов остаточной сети, для номеров которых добавляли этот Cmin в матрице потоков
			residualGraph[path[i]][path[i + 1]] = residualGraph[path[i]][path[i + 1]] - Cmin;
			// и наоборот
			residualGraph[path[i + 1]][path[i]] = residualGraph[path[i + 1]][path[i]] + Cmin;

			// для элемента Sa в матрице потоков добавляем Cmin
			flowMatrix[path[i]][path[i + 1]] += Cmin;

			// для элементов aS в матрице потоков вычитаем Cmin
			flowMatrix[path[i + 1]][path[i]] -= Cmin;
		}// for i

		// Сброс состояния visited и path для следующего поиска
		visited.assign(V, false);
		path.clear();
	}// while
}


// вывод матрицы  в файл
void PrintMatrToFile(vector<vector<int>> matrix)                 // матрица, которую необходимо вывести в файл. Передача по значению
{
	// идём по строкам матрицы
	for (int i = 0; i < matrix.size(); i++)
	{
		// идём по столбцам матрицы
		for (int j = 0; j < matrix.size(); j++)
		{
			// выводим очередной элемент матрицы в файл
			fout << matrix[i][j] << " ";
		}// for j
		fout << endl;
	}// for i

	// возвращаем обещанное значение
	return;
}


/*------------------------------------------------------------------------*/
/*            Главная функция           */
/*--------------------------------------*/
int main()
{
	// подключаем русский язык
	setlocale(LC_ALL, "Russian");
	// цвет консоли - белый
	system("color F0");
	// флаг печати в файл. Изначально - печати нет
	bool print = false;
	// ключ, введённый пользователем для печати
	char letter;
	// номер вершины - стока
	int sink = -1;
	// номер вершины - источника
	int source = -1;

	cout << "\t\t\t\t\t\t\x1b[34m    Р А Б О Т А   С   Г Р А Ф А М И\x1b[30m\n\n\n";
	// создали объект графа. Конструктор применился по-умолчанию
	Graph NewGraph;

	// Выбор, хочет ли пользователь выводить в файл вычесленную информацию
	cout << " Хотите ли Вы выводить данные в файл? Введите <o>, если хотите, или любой другой символ - если нет. Введите: ";
	cin >> letter;                             // ввод пользователем
	cout << "\n Вы ввели: " << letter;         // эхо-печать

	// Если пользователь хочет печатать. Устанавливаем флаг
	if (letter == 'o' || letter == 'O')
	{
		print = true;

	}// if (letter == 'o' || letter == 'O')


	// Выводим матрицу смежности по данным из файла на экран
	cout << "\n\n\t\t\t\t\x1b[35m    М А Т Р И Ц А   С М Е Ж Н О С Т И   П О   И С Х О Д Н Ы М   Д А Н Н Ы М :\x1b[30m\n\n";
	PrintMatrix(NewGraph.adjacency_matrix());

	cout << "\n\x1b[33m И С Т О Ч Н И К   И   С Т О К: \x1b[30m";
	// выводим источник
	source = Source(NewGraph.adjacency_matrix());
	cout << "\n Source: " << source +1;

	// выводим сток
	sink = Sink(NewGraph.adjacency_matrix());
	cout << "\n Sink: " << sink +1 << endl;

	// Матрица потоков, заполненная нулями
	vector<vector<int>> flowMatrix(NewGraph.GetSize(), vector<int>(NewGraph.GetSize()));

	// Вызываем алгоритм поиска максимального потока
	maxFlowFordFulkerson(NewGraph.adjacency_matrix(), flowMatrix, source, sink);
	
	// матрица потоков после окончания алгоритма
	cout << "\n\x1b[34m М А Т Р И Ц А   П О Т О К О В   П О С Л Е   В Ы П О Л Н Е Н И Я   А Л Г О Р И Т М А: \x1b[30m\n";
	PrintMatrix(flowMatrix);

	// вспомогательная переменная, которая будет получать максимальный поток по столбцу
	int MaxFlow = 0;

	// идём по всем строкам в столбце стока
	for (int i = 0; i < NewGraph.GetSize(); i++)
	{
		// суммируем столбцы - получится максимальный поток
		MaxFlow = MaxFlow + flowMatrix[i][sink];
	}// for i

	cout << "\n\x1b[35m М А К С И М А Л Ь Н Ы Й   П О Т О К   И   С П И С О К   Р Ё Б Е Р: \x1b[30m\n";
	cout << " " << MaxFlow << " - maximum flow from " << source + 1 << " to " << sink + 1 << endl;

	// выводим все потоки
	// идём по строкам
	for (int i = 0; i < NewGraph.GetSize(); i++)
	{
		// идём по столбцам
		for (int j = 0; j < NewGraph.GetSize(); j++)
		{
			// если в исходной матрице смежности существует путь между вершинами и в матрице потоков - значение положительное
			if (NewGraph.adjacency_matrix()[i][j] != 0 && flowMatrix[i][j] >=0)
			{
				// выводим пары вершин, поток между ними и пропускную способность ребра - элемент матрицы смежности
				cout << " " << i + 1 << " " << j + 1 << " " << flowMatrix[i][j] << "/" << NewGraph.adjacency_matrix()[i][j] << endl;
			}// if

		}// for j

	}// for i

	// вывод в файл
	if (print)
	{
		fout.open(FNAMEOUT);           // связываем объект с файлом
		if (!fout.is_open())           // файл не найден
		{
			cout << "Файла с таким именем нет. Невозможно осуществить чтение";
			fin.close();               // закрыть файл для чтения
			system("pause");
			exit(0);                   // возвращаем значение, соответствующее типу в caller
		}// if (!fout.is_open())

		fout << "\t\t\t\t\t\t    Р А Б О Т А   С   Г Р А Ф А М И";
		fout << "\n\n М А Т Р И Ц А   С М Е Ж Н О С Т И   П О   И С Х О Д Н Ы М   Д А Н Н Ы М :\n\n";
		// выводим матрицу смежности в файл
		PrintMatrToFile(NewGraph.adjacency_matrix());

		// матрица потоков после окончания алгоритма
		fout << "\n М А Т Р И Ц А   П О Т О К О В   П О С Л Е   В Ы П О Л Н Е Н И Я   А Л Г О Р И Т М А: \n";
		PrintMatrToFile(flowMatrix);

		fout << "\n М А К С И М А Л Ь Н Ы Й   П О Т О К   И   С П И С О К   Р Ё Б Е Р: \n";
		fout << " " << MaxFlow << " - maximum flow from " << source + 1 << " to " << sink + 1 << endl;

		// выводим все потоки
	// идём по строкам
		for (int i = 0; i < NewGraph.GetSize(); i++)
		{
			// идём по столбцам
			for (int j = 0; j < NewGraph.GetSize(); j++)
			{
				// если в исходной матрице смежности существует путь между вершинами и в матрице потоков - значение положительное
				if (NewGraph.adjacency_matrix()[i][j] != 0 && flowMatrix[i][j] >= 0)
				{
					// выводим пары вершин, поток между ними и пропускную способность ребра - элемент матрицы смежности
					fout << " " << i + 1 << " " << j + 1 << " " << flowMatrix[i][j] << "/" << NewGraph.adjacency_matrix()[i][j] << endl;
				}// if

			}// for j

		}// for i

	}// if

	// Выводим картинку с графом на экран
	OpenImage(NewGraph.adjacency_matrix());

	// закрываем файл для записи
	fin.close();
	// возвращаем обещанное значение в функцию
	return 0;
}