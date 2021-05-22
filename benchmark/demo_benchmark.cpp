#include <iostream>
#include <fstream>
#include "Timer.hpp"
#include <filesystem>
#include <string>

// подключаем вашу структуру данных
#include "algorithm.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

int main(int argc, char **argv) {

    string path = ".\\dataset\\";
    const string test_data_name = "data";
    path += test_data_name;

    long int count_top[] = {500, 10000, 100000, 1000000, 5000000};
    const int SETS_NUMBER = 5;
    const int FILE_NUMBER = 10;
    for (int set_n = 0; set_n < SETS_NUMBER; set_n++) {
      cout << "---------SET NUMBER " << set_n << "---------" << endl;

      double middle_time = 0;
      for (int file_n = 1; file_n <= FILE_NUMBER; file_n++) {
        string file_path = path + "\\" + to_string(count_top[set_n]) + "\\" + to_string(file_n) + ".txt";
        ifstream file(file_path);

        int n = 0;
        int** matrix = create_graph(file, n);

        bool has_negative_cycle = false;
        Timer timer;
        int* array_top = algorithm(matrix, n, has_negative_cycle);
        double time = timer.elapsed();
        cout << "Time taken: " << time << '\n';
        cout << (has_negative_cycle ? "Graph has negative cycle" : "Graph hasn't negative cycle") << endl;
        middle_time += time;

        delete_matrix(matrix, n);
        delete[] array_top;
        file.close();
      }
      middle_time /= 10;
      cout << "Middle time = " << middle_time;
      cout << "--------------------------------" << endl;
    }
  }

