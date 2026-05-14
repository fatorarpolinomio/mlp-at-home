#pragma once

#include "../mlp/mlp.hpp"
#include <string>
#include <vector>

// Função para carregar os dados do CSV
std::vector<TrainingData> loadData(const std::string &filename, int input_size,
                                   int output_size);

// Função para separar os dados em Treino e Teste
void splitTrainTest(const std::vector<TrainingData> &full_data,
                    float train_ratio, std::vector<TrainingData> &train_data,
                    std::vector<TrainingData> &test_data);

// Função para carregar os dados do dataset de Caracteres
std::vector<TrainingData> loadCharacterData(const std::string &x_filename,
                                            const std::string &y_filename);
