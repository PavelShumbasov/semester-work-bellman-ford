#pragma once

#include <iostream>
#include <fstream>

// Заголовочный файл с объявлением структуры данных

namespace itis {
	int** create_matrix(int n);
	void delete_matrix(int** matrix, int size);
	int** create_graph(std::ifstream& file, int& n);
	int* algorithm(int** matrix, int size, bool& has_negative_cycle);
}  
// namespace itis
