/*********************************************************************************
 * � � � � � � � � � � � �   � � � � � �  �10  � �   5   � � � � � � �   �  +  + *
 *-------------------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                                     *
 * Project Name  : Teor_Grph_Lab10                                               *
 * File Name     : Lab10. CPP                                                    *
 * Programmer(s) : ������� �.�.                                                  *
 * Modifyed By   :                                                               *
 * Created       : 15/10/23                                                      *
 * Last Revision : 17/10/23                                                      *
 * Comment(s)    : ���������, �������������� ������������ ����� � ����. �����    *
 *                 ������������ ���������� ��������. ������ �����������          *
 *                 ���������� �����-����������. �������� � ���� ������������     *
 *                 �������������. ����������� ������ �������� ������ ���� �     *
 *                 ��������� �������� ������                                     *
 *********************************************************************************/


#include <iostream>              // ����������� ������ �����/������
#include <vector>                // ������ � ��������� ��� �������� �������� ���������� � �������� ���������
#include <fstream>               // ������ � �������� �����/������ ��� �����
#include <iomanip>               // ���������� � ������������� setw
#include <graphviz/gvc.h>        // ���������� Graphviz ��� ������������ ����������� ����� �� ������� ���������
#include <opencv2/opencv.hpp>    // ���������, ������������� ��� ������� OpenCv

using namespace std;             // ���������� ������������ ��� std


/*******************************************************************/
/*            � � � � � � � � � �    � � � � � � � � �             */
/*******************************************************************/

// ���� � ����� ����� ����������� ���������
// ������� �����
// ����� ��� ������� ���������
//const char* FNAMEIN = "matrix_t10_001.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_002.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_003.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_004.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_005.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_006.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_007.txt";                // ���� � �������� ���������
//const char* FNAMEIN = "matrix_t10_008.txt";                // ���� � �������� ���������


// ����� ��� ������ �����
//const char* FNAMEIN = "list_of_edges_t10_001.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_002.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_003.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_004.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_005.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_006.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_007.txt";         // ���� �� ������� ����
//const char* FNAMEIN = "list_of_edges_t10_008.txt";         // ���� �� ������� ����

// ����� ��� ������ ���������
// ������ � ������ �� ������������

// �������� �����
const char* FNAMEOUT = "Output_File.txt";

// ������������� ��� ������� ����������
const int INF = 10000;




/*******************************************************************/
/*      � � � � � � � � � �    � � � � � � � �    � � � � � �      */
/*******************************************************************/

 // ���������� ������� ��� ���������� ����� ������ �� �����
ifstream fin;
// ���������� ������� ��� ���������� ������ ������ � ����
ofstream fout;




/*******************************************************************/
/*                 � � � � � � � �   � � � � � � �                 */
/*******************************************************************/

/*------------------------------------------------------------------------*/
/*                 Graph                  */
/*----------------------------------------*/

class Graph
{
private:
	vector<vector<int>> m_matrix;                             // ���� � ��������� ����������� �������� ���������
	int m_size;                                               // ������ ������� ��������� (���������� ������ � �����)

public:
	// �����������
	Graph();
	// ����������
	~Graph();
	// ����������� ������ ��� ��������� �������� �������
	const int GetSize();
	// ������� ������������ True, ���� ���� ���������������, False, ���� ���� �������;
	bool is_directed();
	// �������, ������������ ������� ���������
	vector<vector<int>> adjacency_matrix();
	// ������� �������, ��������� ������ ������, ���������� ��� �����, ������������ ��;
	int Weight(int Vi, int Vj);
	// �������, ����������� ������ ������ � ���������� True, ���� � ����� ���� ��������������� ����� / ����, False, ���� ����� ���;
	bool is_edge(int Vi, int Vj);
	// �������, ������������ ������ ������, ������� ������� v;
	vector<int> adjacency_list(int v);
	// �������, ������������ ������ ���� ���� �����;
	vector<pair<int, int>> list_of_edges_pairs();
	// �������, ������������ ������ ���� ���� �����, ����������� ������� v / ��������� �� ������� v
	vector<pair<int, int>> list_of_edges(int v);
};




/*******************************************************************/
/*              � � � � � � � � �    � � � � � � �                 */
/*******************************************************************/

// ���������� ����� ��� ����������
string drawGraph(const vector<vector<int>>& adjacencyMatrix);     // ���������� ����������� ������ �� ��������� ������ adjacencyMatrix, ���������� ������������� �������� 

// ����� ����� �� ����� � ���� ��������
void OpenImage(const vector<vector<int>>& adjacencyMatrix);       // ���������� ����������� ������ �� ��������� ������ adjacencyMatrix, ���������� ������������� �������� 

// ����� ������� ��������� �� �����
void PrintMatrix(vector<vector<int>> matrix);                     // �������, ������� ���������� ������� �� �����. �������� �� ��������

// ������ ������� � ������� ������
void Usloviya();

// ���������� ���� � ����� - �� ������� �� ���� ����� �� ���� �������
int Sink(vector<vector<int>> matrix);                             // ������� ��������� �����

// ����������� ��������� � ����� - � ������� �� ������ �� ���� ���� -> ������� � ��������������� ������� �������
int Source(vector<vector<int>> matrix);                           // ������� ��������� �����  

// ������� ��� ���������� ���� �� DFS
bool findPathDFS(vector<vector<int>> graph,                       // ������� ��������� �����
	             vector<vector<int>> residualGraph,               // ������� ���������� ����
	             int source,                                      // ��������      
	             int sink,                                        // ����
	             vector<bool>& visited,                           // ������ ���������� ������
	             vector<int>& path);                              // ���������� ����

// ������� ��� ���������� ������������� ������ �� ��������� �����-����������
void maxFlowFordFulkerson(vector<vector<int>> graph,              // ������� ��������� �����
	                      vector<vector<int>>& flowMatrix,        // ������� �������
	                      int source,                             // ��������
	                      int sink);                              // ����

// ����� �������  � ����
void PrintMatrToFile(vector<vector<int>> matrix);                 // �������, ������� ���������� ������� � ����. �������� �� ��������




// ����������� - ���������� ������� �� �����
Graph::Graph()
{
	fin.open(FNAMEIN);            // ��������� ������ � ������
	if (!fin.is_open())           // ���� �� ������
	{
		cout << "����� � ����� ������ ���. ���������� ����������� ������";
		fin.close();              // ������� ���� ��� ������
		system("pause");
		exit(0);                  // ���������� ��������, ��������������� ���� � caller
	}// if (!fin.is_open())

	int value;                    // ��������� ����������� ������
	char key;                     // ���� ��� �������� ������������� �������� ������� ����� � �����
	bool spravka = true;          // ���� ��� ������ ������� �� �����
	vector<int> row;              // ������ ��� ���������� ������������� �������� �� ����� ���������
	vector<vector<int>> matrix;   // ��������������� ������� ���������

	// ������ ����� ������� �����, ����� ������������ ������� ������� �� ����� �������
	while (spravka)
	{
		cout << "\x1b[30m � � � � � � �   � � � �   � � �   <h>   � � �   � � � � � �   � � � � � � � � � : \x1b[30m";
		// ������������ ��� ���� ��� ����, ����� ���� �������, ����� �������� �� ����� ����
		cin >> key;
		cout << "\n �� �����: " << key << endl;

		// � ����������� �� �������� �����
		switch (key)
		{
			// ������ � �������� ���������
		case('m'):
		case('M'):
		{
			cout << "\n\t\t\t\t\x1b[32m � �   � � � � � � �   � � �   � � � � � � �   -   � � � � � � �   � � � � � � � � �\n\n\x1b[30m\n";
			// ��������� ��������� ����� �� �����
			while (fin >> value)
			{
				// ����� ���������� ������ ������ ������� ������ ������
				row.clear();
				// �������� � ������ ������ ��������� ������� �� ������� while (fin >> value)
				row.push_back(value);
				// ��������� ��� ��������� �������� ������, ���� �� ����� ������ � ��������� - \n
				while (fin.peek() != '\n' && fin >> value)
				{
					row.push_back(value);
				}// while (fin.peek() != '\n' && fin >> value)

				// ������ � ������� ��������� ������. ��� ������ ����� ���������� ������, ��� ��� �������� � �������� ���������
				m_matrix.push_back(row);

			}// while (fin >> value)

			// ��������� ���� �� ����. ������� ���������
			spravka = false;
			break;
		}

		// ������ �� ������� ����
		case('e'):
		case('E'):
		{
			cout << "\n\t\t\t\t\x1b[32m � �   � � � � � � �   � � �   � � � � � � �   -   � � � � � �   � � � � �\n\n\x1b[30m\n";

			// ��������� �������� �� ����� � ������
			// � ������� ����� ���������� � ������������ ����� ��� ��������: ��������� �������, �������� ������� � ��� �����
			while (fin >> value)
			{
				// ����� ���������� ������ ������ ������� ������ ������
				row.clear();
				// �������� � ������ ������ ��������� ������� �� ������� while (fin >> value)
				row.push_back(value);
				// ��������� ��� ��������� �������� ������, ���� �� ����� ������ � ��������� - \n
				while (fin.peek() != '\n' && fin >> value)
				{
					row.push_back(value);
				}// while (fin.peek() != '\n' && fin >> value)

				// ������ � ������� ��������� ������. ��� ������ ����� ���������� ������, ��� ��� �������� � �������� ���������
				m_matrix.push_back(row);
			}// while (fin >> value)

			// ������� ���� ������
			fin.close();
			int size_m = m_matrix[m_matrix.size() - 1][0];    // ������ ������� ���������
			vector<vector<int>> vec_1(size_m);                // ������� ���������

			for (int i = 0; i < size_m; i++)                  // ����� ������ ������ ������ vec_1
			{
				vec_1[i].resize(size_m, 0);
			}// for i

			// ��������� ������� ���������
			for (int i = 0; i < m_matrix.size(); i++)
			{
				if (m_matrix[0].size() == 3)                  // 3 ������� - ��� ��� �����, ���� �� �� ������, �� ������ �� = 1
				{
					vec_1[m_matrix[i][0] - 1][m_matrix[i][1] - 1] = m_matrix[i][2];
				}
				else
				{
					vec_1[m_matrix[i][0] - 1][m_matrix[i][1] - 1] = 1;
				}// if (m_matrix[0].size() == 3)
			}// for i

			// ���������� ������� ���������
			m_matrix = vec_1;
			// ��������� ���� �� ����. ������� ���������
			spravka = false;
			break;
		}

		// �������� �� �������� ���������
		case('l'):
		case('L'):
		{
			cout << "\n\t\t\t\t\x1b[32m � �   � � � � � � �   � � �   � � � � � � �   -   � � � � � �   � � � � � � � � �\n\n\x1b[30m\n";

			// ������ �� ����� ���������
			string line;
			int rowNumber = 0;            // ����� ������� ������

			// ������ ����������
			while (getline(fin, line))
			{
				// ���� ������ ������, ��������� ������� ������ ������
				if (line.empty())
				{
					matrix.push_back(vector<int>(m_size, 0));
				}
				// ������ �� ������
				else
				{
					// ������ ������
					vector<int> row;
					// ������� ����� ��� ������ �������� �� ������ line. ����� �� ����� ������������ iss ������ � ���������� >> ��� ���������� �������� �� ������.
					istringstream iss(line);
					// ��������� �������� ��� ������
					int value;

					// ������ �������� �� ����� � �������� ��� � ������ ������
					while (iss >> value)
					{
						row.push_back(value);
					}// while

					// �������� ������ � �������
					matrix.push_back(row);
				}// if (line.empty()) 

				// ����������� ����� ������
				rowNumber++;
			}// while (getline(fin, line)) 

			// ���� �������� - ��������� ���
			fin.close();

			m_size = matrix.size();                         // ������ ������� ���������

			vector<vector<int>> vec_1(m_size);              // ��� ������� ��������� �������� m_size

			for (int i = 0; i < m_size; i++)                // ����� ������ ������ ������ ��� ������� ���������
			{
				// ��������� ��������������� ������� ������ �� ����� �������
				vec_1[i].resize(m_size, 0);
			}// for i

			for (int i = 0; i < m_size; i++)                 // ��������� ��� ������� ��������� 
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					// ������� � ��� ��������, ������� ����������� ��� ������ � �����
					vec_1[i][matrix[i][j] - 1] = 1;
				}// for j
			}// for i

			// �������� �������� � �������� ������� ���������
			for (int i = 0; i < m_size; i++)
			{
				row.clear();
				for (int j = 0; j < m_size; ++j)
				{
					row.push_back(vec_1[i][j]);
				}// fot j

				m_matrix.push_back(row);
			}// for i

			// ��������� ���� �� ����. ������� ���������
			spravka = false;
			break;
		}

		// ������������ ������ �������
		case('h'):
		case('H'):
		{
			// ��������� ���� ����� ��������� ������� �� ������
			spravka = true;
			// ������� �������
			Usloviya();
			break;
		}

		// ����� - ������������ ��� �� ��� ����. ����������� ��������� � �������
		default:
			cout << "\n\x1b[31m ������������� ��������� � ������� �������� �� ������ ������!!!\n\x1b[30m";
			// ��������� ���� ����������
			fin.close();
			exit(0);
		}
	}
	// ��������� ���� ����������
	fin.close();
	// ���������� ������ ���������/ ��������������� ������� ���������
	m_size = m_matrix.size();
}

// ����������
Graph::~Graph()
{
	// ������ ���� - ������� ������������ �������������
}

// ������ ��� ��������� �������� �������
const int Graph::GetSize()
{
	// ���������� �������� ������� �������
	return(m_size);
}


// ������� ������������ True, ���� ���� ���������������, False, ���� ���� �������;
bool Graph::is_directed()
{
	// ��� �� �������
	for (int i = 0; i < m_size; i++)
	{
		// ��� �� ��������
		for (int j = 0; j < m_size; j++)
		{
			// ���� ���� �����������������, �� ������� �����������, ��� ��� �� ����� ����� ������ ������ ������������
			if (m_matrix[i][j] != m_matrix[j][i])
			{
				return true; // ������� ������������ ����� - ���� ���������������
			}// if (m_matrix[i][j] != m_matrix[j][i])

		}// for j

	}// for i

	return false; // �� ������� ������������ ����� - ���� �����������������
}


// �������, ������������ ������� ���������
vector<vector<int>> Graph::adjacency_matrix()
{
	return(m_matrix);
}


// ������� �������, ��������� ������ ������, ���������� ��� �����, ������������ ��;
int Graph::Weight(int Vi, int Vj)

{
	// ������ ������ ����� �� ��������� ���������� ��������
	if ((Vi >= m_size || Vi < 0) || (Vj >= m_size || Vj < 0))
	{
		cout << "������! ����� ������� �� ����������\n";
		// ������� ������
		return(-1);
	}// if

	// ���� ���� ����������(� ������� ��������� �� 0)
	if (m_matrix[Vi][Vj] != 0)
	{
		cout << "��� ����� ����� ��������� " << Vi << " � " << Vj << " �����" << m_matrix[Vi][Vj] << endl;
		cout << m_matrix[Vi][Vj] << endl;
		// ���������� ��� ����� ����� ���������
		return(m_matrix[Vi][Vj]);
	}// if

	// ���� ���������������. ������� ��� ����
	else if ((m_matrix[Vi][Vj] != m_matrix[Vj][Vi]) && (m_matrix[Vi][Vj] != 0 || m_matrix[Vj][Vi] != 0))
	{
		cout << "���� ���������������. ���� ����. ����������� �����������. ��� ���� ����� ��������� " << Vi << " � " << Vj << " �����" << m_matrix[Vi][Vj] << endl;
		// ���������� ��� ����
		return(m_matrix[Vi][Vj]);
	}// else if

	// ����� ����� ��������� ��� - ������� ������� ��������� ����� 0
	else if (m_matrix[Vi][Vj] == 0)
	{
		cout << "����� ����� ��������� " << Vi << " � " << Vj << "���\n";
		// ������� ������� ��������
		return(m_matrix[Vi][Vj]);
	}// else if

	return(0);
}


// �������, ����������� ������ ������ � ���������� True, ���� � ����� ���� ��������������� ����� / ����, False, ���� ����� ���;
bool Graph::is_edge(int Vi, int Vj)
{
	// ������ ������ ����� �� ��������� ���������� �������� - ���� ���
	if ((Vi >= m_size || Vi < 0) || (Vj >= m_size || Vj < 0))
	{
		// �������, ��� ���� ���
		return(false);
	}// if

	// ������� ������� ��������� �� ����� 0 - ����� ����
	if (m_matrix[Vi][Vj] != 0)
	{
		// ������������, ��� ����� ����
		return(true);
	}// if

	// ������� ������� ��������� ������� - ����� ���
	if (m_matrix[Vi][Vj] == 0)
	{
		// ������������, ��� ����� ���
		return(false);
	}// if

}


// �������, ������������ ������ ������, ������� ������� v;
vector<int> Graph::adjacency_list(int v)
{
	// ������ ������
	vector<int> adjList;

	// �������� �� ���� �������� � ���������, ���� �� ����� ����� �������� v � ������� ��������
	for (int i = 0; i < m_size; i++)
	{
		// ���� ���� - ������� ������� �� �������
		if (m_matrix[v][i] != 0)
		{
			// �������� ������� � ������
			adjList.push_back(i);
		}// if (m_matrix[v][i] != 0)

	}// for i

	// ���������� ������ ������� ������
	return adjList;
}


// �������, ������������ ������ ���� ���� �����;
vector<pair<int, int>> Graph::list_of_edges_pairs()
{
	// ������ ���, ���������� ����� � ���� ���� ����������� ��� ������
	vector<pair<int, int>> edges_pairs;
	// ��� �� ���� ��������� ������
	for (int i = 0; i < m_size; i++)
	{
		// ��� �� ���� ��������� �������
		for (int j = 0; j < m_size; j++)
		{
			// ���� ������� �� �������
			if (m_matrix[i][j] != 0)
			{
				// ��������� ���� ������
				edges_pairs.push_back(make_pair(i, j));
			}// if (m_matrix[i][j] != 0)
		}// for j
	}// for i

	// ������� ������ ���� (��� ������)
	return(edges_pairs);
}


// �������, ������������ ������ ���� ���� �����, ����������� ������� v / ��������� �� ������� v
vector<pair<int, int>> Graph::list_of_edges(int v)
{
	int count = 0;
	vector<pair<int, int>> edges;         // ������ ��� ������(������ ����)
	vector<pair<int, int>> edges_inc;     // ������ ���� ����������� ������� v / ��������� �� ������� v
	edges = list_of_edges_pairs();        // �������� ��� ���� ������ �����

	// ������� ��� ����. ���� ���� �����������������, �� ��� ����� ���� (v,n) � (n, v) - ���������� ����������� ��� ������������� ������ �������. � ������� - ��������� ������� ������ ������
	for (int i = 0; i < edges.size(); i++)
	{
		// ������������� ������ ������� ����
		if (edges[i].first == v)
		{
			// �������� � ����� �����, ����������� ������� ������ �����
			edges_inc.push_back(edges[i]);
			// ����������� �������
			count = count + 1;
		}//if (edges[i].first == v)
	}//for i

	// ����������  ������ ���� ���� �����, ����������� ������� v / ��������� �� ������� v
	return(edges_inc);
}




/*------------------------------------------------------------------------*/
/*                �������               */
/*--------------------------------------*/

// ���������� ����� ��� ����������
string drawGraph(const vector<vector<int>>& adjacencyMatrix)
{
	// ��������� ������ ������� ���������. ���� ������ 19, �� ������� �� ������� �������
	if (adjacencyMatrix.size() <= 25)
	{
		bool key = false;
		// ��������� ������� ����� �� ������, ����� ������, ����� �� ��������� �� ��� ������
		for (int i = 0; i < adjacencyMatrix.size(); i++)
		{
			for (int j = 0; j < adjacencyMatrix.size(); j++)
			{
				// ���� ��� ����� ������ 1 ��� �������������, ������, ����� ��������� ��� � ������
				if (adjacencyMatrix[i][j] > 1 || adjacencyMatrix[i][j] < 0)
					key = true;
			}
		}

		// ��������� ���� ��� ������ ����� � ������� DOT
		std::ofstream file;
		file.open("graph.dot");
		file << "digraph G {" << endl;

		if (key)
		{
			// ������� ���� � ��������� ����� �����
			for (int i = 0; i < adjacencyMatrix.size(); i++)
			{
				for (int j = 0; j < adjacencyMatrix[i].size(); j++)
				{
					// ���������, ��� ��� ����� �� ����� 0, ����� �� �������� �������� �����
					if (adjacencyMatrix[i][j] != 0)
					{
						// ������� ����� � ��������� ���� � ������� DOT
						file << i << " -> " << j << " [label=\"" << adjacencyMatrix[i][j] << "\"];" << endl;
					}// if (adjacencyMatrix[i][j] != 0) 
				}// for j
			}// for i
		}

		else
		{
			// ������� ���� ��� �������� ����� �����
			for (int i = 0; i < adjacencyMatrix.size(); i++)
			{
				for (int j = 0; j < adjacencyMatrix[i].size(); j++)
				{
					// ���������, ��� ��� ����� ����� 1, ����� �� �������� �������� �����
					if (adjacencyMatrix[i][j] == 1)
					{
						// ������� ����� ��� �������� ���� � ������� DOT
						file << i << " -> " << j << ";" << endl;
					}//if (adjacencyMatrix[i][j] == 1) 
				}// for j
			}// for i
		}// if key

		// ��������� ���� � ��������� ����������
		file << "}" << std::endl;
		file.close();

		// ���������� ����������� ����� � ������� PNG � ������� ������� DOT
		system("dot -Tpng graph.dot -o graph.png");
		cout << "\n\nGraph image saved as graph.png" << endl;
	}

	// �������, ��� ���� ������� ��� ���������
	else
	{
		cout << "\n\nGraph image is not saved as graph.png. It is too big" << endl;
	}// if

	// ���������� �������� ��� �������� ������ OpenCV
	return "graph.png";
}


// ����� ����� �� �����
void OpenImage(const std::vector<std::vector<int>>& adjacencyMatrix)
{
	// ��������� ����������� ������� ���������
	if (adjacencyMatrix.size() <= 25)
	{
		// �������� ���� � �����������, ���������� � ������� ������� drawGraph
		std::string imagePath = drawGraph(adjacencyMatrix);
		// ��������� ����������� � ������� OpenCV
		cv::Mat img = cv::imread(imagePath, -1);

		// ���������, ������� �� ��������� �����������
		if (img.empty())
		{
			cout << "Could not open or find the image" << endl;
			return;
		}// if

		// ������� ���� � ��������� "Graph"
		cv::namedWindow("Graph", cv::WINDOW_NORMAL);
		// ���������� ����������� � ����
		cv::imshow("Graph", img);
		// ����, ���� ������������ ������ ����� �������
		cv::waitKey(0);
		// ��������� ����
		cv::destroyWindow("Graph");
		return;
	}// if (adjacencyMatrix.size() <= 19)
}


// ����� ������� ��������� �� �����
void PrintMatrix(vector<vector<int>> matrix)
{
	// ��������� ������� ����
	setlocale(0, "C");            // ������� ������ � �������� �������
	cout << setw(2) << setfill(' ') << (char)218 << (char)196 << (char)196 << setw(matrix.size() * 2 + 7) << setfill(' ') << (char)196 << (char)196 << (char)191 << endl;          // ����� ������� ���������� ������

	// ��� �� �������
	for (int i = 0; i < matrix.size(); i++)
	{
		cout << setw(5) << setfill(' ');
		// ��� �� ��������
		for (int j = 0; j < matrix.size(); j++)
		{
			// ������� ������� �������
			cout << matrix[i][j] << " ";
		}// for j

		cout << endl;
	}// for i
	cout << setw(2) << setfill(' ') << (char)192 << (char)196 << (char)196 << setw(matrix.size() * 2 + 7) << setfill(' ') << (char)196 << (char)196 << (char)217 << endl;          // ����� ������� �������
	// ���������� ������� ����
	setlocale(LC_ALL, "Russian");

	// ���������� ��������� ��������
	return;
}


// ������ ������� � ������� ������
void Usloviya()
{
	cout << "\n\t\t\t\t/********************************************************************************\n";
	cout << "\t\t\t\t* � � � � � � � � � � � �   � � � � � �  �10  � �   5   � � � � � � �   �  +  +   *\n";
	cout << "\t\t\t\t*---------------------------------------------------------------------------------*\n";
	cout << "\t\t\t\t* Project Type  : Win64 Console Application                                       *\n";
	cout << "\t\t\t\t* Project Name  : Teor_Grph_Lab10                                                 *\n";
	cout << "\t\t\t\t* File Name     : Lab10. CPP                                                      *\n";
	cout << "\t\t\t\t* Programmer(s) : ������� �.�.                                                    *\n";
	cout << "\t\t\t\t* Modifyed By   :                                                                 *\n";
	cout << "\t\t\t\t* Created       : 15/10/23                                                        *\n";
	cout << "\t\t\t\t* Last Revision : 17/10/23                                                        *\n";
	cout << "\t\t\t\t***********************************************************************************/\n";

	cout << "\n\t\t\t\t\t\t\t\x1b[31m   � � � � � � � : \n\n\x1b[30m";
	// ������� ������� � �������
	setlocale(0, "C");                       // ��������� ������� ����
	cout << char(218) << setw(40) << setfill((char)196) << (char)191 << endl << (char)179;  // ������� ������� ������ �����
	setlocale(LC_ALL, "Rus");                // ���������� ������� ����
	cout << " �������� ���� ������� �� ������:      ";
	setlocale(0, "C");                       // ��������� ������� ����
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)194 << setw(35) << setfill((char)196) << (char)180 << setfill(' ') << endl << (char)179;    // ������� ������ ������ ����� � ������������ ����� ������� � ��������� ���������
	cout << "  e " << (char)179 << "  Edges_list_file_path            ";                                                                                                         // ������� ������� ������ � ������ � �������� ��������� �������
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  m " << (char)179 << "  Adjacency_matrix_file_path      ";
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  l " << (char)179 << "  Adjacency_list_file_path        ";
	cout << (char)179 << endl << (char)195 << setw(5) << setfill((char)196) << (char)197 << setw(35) << setfill((char)196) << (char)180 << endl << (char)179;
	cout << "  o " << (char)179 << "  Output_file_path                ";
	cout << (char)179 << endl << (char)192 << setw(5) << setfill((char)196) << (char)193 << setw(35) << setfill((char)196) << (char)217 << endl;
	cout << endl;
	setlocale(LC_ALL, "Rus");               // ���������� ������� ����

	return;                                 // ���������� ��������� ��������
}


// ���������� ���� � ����� - �� ������� �� ���� ����� �� ���� �������
int Sink(vector<vector<int>> matrix)        // ������� ��������� �����
{
	// ���������� ������ � ������� ���������
	int V = matrix.size();
	// ����� ������� - �����
	int sink = -1;
	// ����
	bool zero = true;
	// ������� - ����, ���� � ������ ������� ��������� � ��������������� ������� ��������� ���� ����
	// ���������� �� ���� �������
	for (int i = 0; i < V; i++)
	{
		zero = true;
		// ��� �� ��������
		for (int j = 0; j < V; j++)
		{
			// ���� ����� ��������� ������� � ������ ������� ���������
			// ��������� � ������ ������, ��������� ���������� �������
			if (matrix[i][j] != 0)
			{
				zero = false;
				continue;
			}// if

		}// for j

		// ���� �������� �� ���� ������ � ��� ��� ����
		if (zero == true)
		{
			// ���������� ��� ������
			sink = i;
			// ���������� � �����
			return(sink);
		}// if

	}// for i

	// ���� �� ����� ������ - ������� �������������� ��������
	return(-1);
}


// ����������� ��������� � ����� - � ������� �� ������ �� ���� ���� -> ������� � ��������������� ������� �������
int Source(vector<vector<int>> matrix)      // ������� ��������� �����
{
	// ���������� ������ � ������� ���������
	int V = matrix.size();
	// ����� ������� - ���������
	int source = -1;
	// ����
	bool zero = true;

	// ������� - ����, ���� � ������� ������� ��������� � ��������������� ������� ��������� ���� ����
	// ���������� �� ���� ��������
	for (int j = 0; j < V; j++)
	{
		zero = true;
		// ��� �� �������
		for (int i = 0; i < V; i++)
		{
			// ���� ����� ��������� ������� � ������� ������� ���������
			// ��������� � ������� �������, ��������� ���������� �������
			if (matrix[i][j] != 0)
			{
				zero = false;
				continue;
			}// if

		}// for i

		// ���� �������� �� ����� ������� � ��� ��� ����
		if (zero == true)
		{
			// ���������� ���� �������
			source = j;
			// ���������� ��� �����
			return(source);
		}// if

	}// for i

	// ���� �� ����� ������ - ������� �������������� ��������
	return(-1);
}


// ������� ��� ���������� ���� �� DFS
bool findPathDFS(vector<vector<int>> graph,                   // ������� ��������� �����
	             vector<vector<int>> residualGraph,           // ������� ���������� ����
	             int source,                                  // ��������      
	             int sink,                                    // ����
	             vector<bool>& visited,                       // ������ ���������� ������
	             vector<int>& path)                           // ���������� ����
{
	// ��������� ������� ���������� ��� ����������
	visited[source] = true;
	// ��������� ��� ������� � ������ ����
	path.push_back(source);

	// ���� ������� ������� ���� ������� � �������� - ������
	if (source == sink)
	{
		// ���������� ���� � ���� ������
		return true;
	}// if

	// �������� �� ���� �������� �����
	for (int v = 0; v < graph.size(); v++) 
	{
		// ���� ������� �� ���� �������� � ���������� � ���������� ���� ���� �� ������ ������� �� �����-���� ������,
		// �������� ���������� ������� ��� ��������� ������� (������ v)
		// ���� ������� �� ���� ��������, � ���������� ���� �� ������ ������� �� ������ (����� ���������� ����), ���������� ���������� findPathDFS ��� ��������� �������.
		if (!visited[v] && residualGraph[source][v] > 0 && findPathDFS(graph, residualGraph, v, sink, visited, path))
		{
			// ���� ���� ������ � ����������� ������, �� ������������ true.
			return true;
		}// if
	}// for v

	// ���� �� ���� ���� �� ������, ��������� ������� ��������� �� ���� � ������������ false.
	path.pop_back();
	return false;
}


// ������� ��� ���������� ������������� ������ �� ��������� �����-����������
void maxFlowFordFulkerson(vector<vector<int>> graph,              // ������� ��������� �����
	                      vector<vector<int>>& flowMatrix,        // ������� �������
	                      int source,                             // ��������
	                      int sink)                               // ����
{
	// ���������� ������ � ����� - ������ ������� ���������
	int V = graph.size();
	// ������� ���������� ����
	vector<vector<int>> residualGraph(V, vector<int>(V, 0));

	// ������ ���������� ����. ���������� ��� ��������� � �������� ������
	// ��� �� ���� �������
	for (int i = 0; i < V; i++) 
	{
		// ��� �� ���� ��������
		for (int j = 0; j < V; j++) 
		{
			// ������������ �������
			residualGraph[i][j] = graph[i][j];
		}// for j
	}// for i

	// ������ ���������� ������ ��� DFS
	vector<bool> visited(V, false);
	// ������ ���� ��� DFS
	vector<int> path;

	cout << "\n\x1b[31m � � � � � � � � �   � � � �   � �   � � � � � � � � �   �   � � � � �: \x1b[30m";
	cout << endl;
	
	// ���� ���������� ���� �� ��������� � ����� � ������� ���������� ����
	while (findPathDFS(graph, residualGraph, source, sink, visited, path)) 
	{
		cout << " ";
		// ������� ��������������� ����, ����������� � ���������
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] + 1 << " ";
		}// for i
		cout << endl;

		// ������� ����������� ���������� ����������� �� ����
		int Cmin = INF;
		// ��� �� ���� ����� ����
		for (int i = 0; i < path.size() - 1; i++) 
		{
			// ��������� ������� ����� ����
			int u = path[i];
			// �������� ������� ����� ����
			int v = path[i + 1];

			// Cmin - ����������� �������� ����� � ����
			Cmin = min(Cmin, residualGraph[u][v]);
		}// for i

		// ��������� ���������� ���� � ������������ �����
		for (int i = 0; i < path.size() - 1; i++) 
		{
			// ��������� �� �������� ������� ������� ��������� ������ ����������� ��������� Cmin �� ��� ��������� ���������� ����, ��� ������� ������� ��������� ���� Cmin � ������� �������
			residualGraph[path[i]][path[i + 1]] = residualGraph[path[i]][path[i + 1]] - Cmin;
			// � ��������
			residualGraph[path[i + 1]][path[i]] = residualGraph[path[i + 1]][path[i]] + Cmin;

			// ��� �������� Sa � ������� ������� ��������� Cmin
			flowMatrix[path[i]][path[i + 1]] += Cmin;

			// ��� ��������� aS � ������� ������� �������� Cmin
			flowMatrix[path[i + 1]][path[i]] -= Cmin;
		}// for i

		// ����� ��������� visited � path ��� ���������� ������
		visited.assign(V, false);
		path.clear();
	}// while
}


// ����� �������  � ����
void PrintMatrToFile(vector<vector<int>> matrix)                 // �������, ������� ���������� ������� � ����. �������� �� ��������
{
	// ��� �� ������� �������
	for (int i = 0; i < matrix.size(); i++)
	{
		// ��� �� �������� �������
		for (int j = 0; j < matrix.size(); j++)
		{
			// ������� ��������� ������� ������� � ����
			fout << matrix[i][j] << " ";
		}// for j
		fout << endl;
	}// for i

	// ���������� ��������� ��������
	return;
}


/*------------------------------------------------------------------------*/
/*            ������� �������           */
/*--------------------------------------*/
int main()
{
	// ���������� ������� ����
	setlocale(LC_ALL, "Russian");
	// ���� ������� - �����
	system("color F0");
	// ���� ������ � ����. ���������� - ������ ���
	bool print = false;
	// ����, �������� ������������� ��� ������
	char letter;
	// ����� ������� - �����
	int sink = -1;
	// ����� ������� - ���������
	int source = -1;

	cout << "\t\t\t\t\t\t\x1b[34m    � � � � � �   �   � � � � � � �\x1b[30m\n\n\n";
	// ������� ������ �����. ����������� ���������� ��-���������
	Graph NewGraph;

	// �����, ����� �� ������������ �������� � ���� ����������� ����������
	cout << " ������ �� �� �������� ������ � ����? ������� <o>, ���� ������, ��� ����� ������ ������ - ���� ���. �������: ";
	cin >> letter;                             // ���� �������������
	cout << "\n �� �����: " << letter;         // ���-������

	// ���� ������������ ����� ��������. ������������� ����
	if (letter == 'o' || letter == 'O')
	{
		print = true;

	}// if (letter == 'o' || letter == 'O')


	// ������� ������� ��������� �� ������ �� ����� �� �����
	cout << "\n\n\t\t\t\t\x1b[35m    � � � � � � �   � � � � � � � � �   � �   � � � � � � � �   � � � � � � :\x1b[30m\n\n";
	PrintMatrix(NewGraph.adjacency_matrix());

	cout << "\n\x1b[33m � � � � � � � �   �   � � � �: \x1b[30m";
	// ������� ��������
	source = Source(NewGraph.adjacency_matrix());
	cout << "\n Source: " << source +1;

	// ������� ����
	sink = Sink(NewGraph.adjacency_matrix());
	cout << "\n Sink: " << sink +1 << endl;

	// ������� �������, ����������� ������
	vector<vector<int>> flowMatrix(NewGraph.GetSize(), vector<int>(NewGraph.GetSize()));

	// �������� �������� ������ ������������� ������
	maxFlowFordFulkerson(NewGraph.adjacency_matrix(), flowMatrix, source, sink);
	
	// ������� ������� ����� ��������� ���������
	cout << "\n\x1b[34m � � � � � � �   � � � � � � �   � � � � �   � � � � � � � � � �   � � � � � � � � �: \x1b[30m\n";
	PrintMatrix(flowMatrix);

	// ��������������� ����������, ������� ����� �������� ������������ ����� �� �������
	int MaxFlow = 0;

	// ��� �� ���� ������� � ������� �����
	for (int i = 0; i < NewGraph.GetSize(); i++)
	{
		// ��������� ������� - ��������� ������������ �����
		MaxFlow = MaxFlow + flowMatrix[i][sink];
	}// for i

	cout << "\n\x1b[35m � � � � � � � � � � � �   � � � � �   �   � � � � � �   � � � � �: \x1b[30m\n";
	cout << " " << MaxFlow << " - maximum flow from " << source + 1 << " to " << sink + 1 << endl;

	// ������� ��� ������
	// ��� �� �������
	for (int i = 0; i < NewGraph.GetSize(); i++)
	{
		// ��� �� ��������
		for (int j = 0; j < NewGraph.GetSize(); j++)
		{
			// ���� � �������� ������� ��������� ���������� ���� ����� ��������� � � ������� ������� - �������� �������������
			if (NewGraph.adjacency_matrix()[i][j] != 0 && flowMatrix[i][j] >=0)
			{
				// ������� ���� ������, ����� ����� ���� � ���������� ����������� ����� - ������� ������� ���������
				cout << " " << i + 1 << " " << j + 1 << " " << flowMatrix[i][j] << "/" << NewGraph.adjacency_matrix()[i][j] << endl;
			}// if

		}// for j

	}// for i

	// ����� � ����
	if (print)
	{
		fout.open(FNAMEOUT);           // ��������� ������ � ������
		if (!fout.is_open())           // ���� �� ������
		{
			cout << "����� � ����� ������ ���. ���������� ����������� ������";
			fin.close();               // ������� ���� ��� ������
			system("pause");
			exit(0);                   // ���������� ��������, ��������������� ���� � caller
		}// if (!fout.is_open())

		fout << "\t\t\t\t\t\t    � � � � � �   �   � � � � � � �";
		fout << "\n\n � � � � � � �   � � � � � � � � �   � �   � � � � � � � �   � � � � � � :\n\n";
		// ������� ������� ��������� � ����
		PrintMatrToFile(NewGraph.adjacency_matrix());

		// ������� ������� ����� ��������� ���������
		fout << "\n � � � � � � �   � � � � � � �   � � � � �   � � � � � � � � � �   � � � � � � � � �: \n";
		PrintMatrToFile(flowMatrix);

		fout << "\n � � � � � � � � � � � �   � � � � �   �   � � � � � �   � � � � �: \n";
		fout << " " << MaxFlow << " - maximum flow from " << source + 1 << " to " << sink + 1 << endl;

		// ������� ��� ������
	// ��� �� �������
		for (int i = 0; i < NewGraph.GetSize(); i++)
		{
			// ��� �� ��������
			for (int j = 0; j < NewGraph.GetSize(); j++)
			{
				// ���� � �������� ������� ��������� ���������� ���� ����� ��������� � � ������� ������� - �������� �������������
				if (NewGraph.adjacency_matrix()[i][j] != 0 && flowMatrix[i][j] >= 0)
				{
					// ������� ���� ������, ����� ����� ���� � ���������� ����������� ����� - ������� ������� ���������
					fout << " " << i + 1 << " " << j + 1 << " " << flowMatrix[i][j] << "/" << NewGraph.adjacency_matrix()[i][j] << endl;
				}// if

			}// for j

		}// for i

	}// if

	// ������� �������� � ������ �� �����
	OpenImage(NewGraph.adjacency_matrix());

	// ��������� ���� ��� ������
	fin.close();
	// ���������� ��������� �������� � �������
	return 0;
}