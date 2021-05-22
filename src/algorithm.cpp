#include "algorithm.hpp"
#include <iostream>

// файл с определениями

namespace itis {

  using namespace std;

  //Выделение памяти под матрицу смежности
  int** create_matrix(int n) {
    int** matrix = new int*[n];

    for (int i = 0; i < n; i++) {
      matrix[i] = new int[n];
    }

    return matrix;
  }

  //Очищение памяти
  void delete_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
      delete[] matrix[i];
    }

    delete[] matrix;
  }

  //Создание графа из набора сгенерированных данных
  int** create_graph(ifstream& file, int& n) {
    file >> n;

    int** matrix = create_matrix(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        file >> matrix[i][j];
      }
    }
    return matrix;
  }

  int* algorithm(int** matrix, int size, bool& has_negative_cycle) {
    const int INF = INT_MAX;
    int start = 0;

    int* label = new int[size];

    for (int i = 0; i < size; i++) {
      label[i] = INF;
    }

    label[start] = 0;

    for (int k = 1; k < size; k++)
      for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
          if (label[j] + matrix[j][i] < label[i])
            label[i] = label[j] + matrix[j][i];

    // Для определения отрицательных циклов
    int* array = new int[size];
    for (int i = 0; i < size; i++)
      array[i] = label[i];

    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        if (array[j] + matrix[j][i] < array[i])
          array[i] = array[j] + matrix[j][i];

    has_negative_cycle = false;
    for (int i = 0; i < size; i++)
      if (array[i] < label[i])
        has_negative_cycle = true;

    delete[] array;

    return label;
  }

}  // namespace itis