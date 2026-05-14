#include "dataIO.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

std::vector<TrainingData> loadData(const std::string &filename, int input_size,
                                   int output_size) {
    std::vector<TrainingData> dataset;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return dataset;
    }

    bool first_line = true;
    while (std::getline(file, line)) {
        // Tratando um bugzinho com o BOM (Byte Order Mark)
        if (first_line) {
            if (line.size() >= 3 && line.substr(0, 3) == "\xEF\xBB\xBF") {
                line.erase(0, 3);
            }
            first_line = false;
        }
        if (line.empty() ||
            line.find_first_not_of(" \r\n\t") == std::string::npos) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;
        TrainingData data;

        // Lê os atributos de entrada (X)
        for (int i = 0; i < input_size && std::getline(ss, value, ','); i++) {
            float val;
            try {
                val = std::stof(value);
            } catch (std::invalid_argument) {
                std::cout << "Erro na formatação do CSV" << '\n';
            }
            data.input.push_back(val);
        }

        // Lê os rótulos/saída (Y)
        for (int i = 0; i < output_size && std::getline(ss, value, ','); i++) {
            float val;
            try {
                val = std::stof(value);

            } catch (std::invalid_argument) {
                std::cout << "Erro na formatação do CSV" << '\n';
            }
            data.output.push_back(val);
        }

        dataset.push_back(data);
    }
    return dataset;
}

void splitTrainTest(const std::vector<TrainingData> &full_data,
                    float train_ratio, std::vector<TrainingData> &train_data,
                    std::vector<TrainingData> &test_data) {

    std::vector<TrainingData> shuffled_data = full_data;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled_data.begin(), shuffled_data.end(), g);

    size_t train_size = static_cast<size_t>(shuffled_data.size() * train_ratio);

    train_data.assign(shuffled_data.begin(),
                      shuffled_data.begin() + train_size);
    test_data.assign(shuffled_data.begin() + train_size, shuffled_data.end());

    std::cout << "Treino: " << train_data.size() << " dados\n"
              << "Teste: " << test_data.size() << " dados" << std::endl;
}

std::vector<TrainingData> loadCharacterData(const std::string &x_filename,
                                            const std::string &y_filename) {
    std::vector<TrainingData> dataset;
    std::ifstream x_file(x_filename);
    std::ifstream y_file(y_filename);
    std::string x_line, y_line;

    if (!x_file.is_open() || !y_file.is_open()) {
        std::cerr << "Erro ao abrir os arquivos de caracteres!" << std::endl;
        return dataset;
    }

    bool is_first_line = true;

    // Lê as linhas dos dois arquivos simultaneamente
    while (std::getline(x_file, x_line) && std::getline(y_file, y_line)) {

        // Limpa o BOM (Byte Order Mark)
        if (is_first_line) {
            if (x_line.size() >= 3 && x_line.substr(0, 3) == "\xEF\xBB\xBF")
                x_line.erase(0, 3);
            if (y_line.size() >= 3 && y_line.substr(0, 3) == "\xEF\xBB\xBF")
                y_line.erase(0, 3);
            is_first_line = false;
        }

        if (x_line.empty() || y_line.empty() ||
            y_line.find_first_not_of(" \r\n\t") == std::string::npos) {
            continue;
        }

        std::stringstream ss(x_line);
        std::string value;
        TrainingData data;

        try {
            for (int i = 0; i < 120 && std::getline(ss, value, ','); i++) {
                data.input.push_back(std::stof(value));
            }

            // Converte a letra para um vetor One-Hot Encoding (-1 em todas as
            // posições menos a correta)
            data.output = std::vector<float>(26, -1.0f);

            // Remove espaços e quebras de linha que possam ter vindo junto com
            // a letra
            y_line.erase(
                std::remove_if(y_line.begin(), y_line.end(), ::isspace),
                y_line.end());
            char letra = y_line[0];

            if (letra >= 'A' && letra <= 'Z') {
                int index = letra - 'A';
                data.output[index] =
                    1.0f; // Coloca 1 apenas na posição da letra correta
            }

            dataset.push_back(data);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Erro ao converter valor na linha X: " << x_line
                      << std::endl;
            exit(1);
        }
    }
    return dataset;
}
