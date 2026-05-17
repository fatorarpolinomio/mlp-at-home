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


// Exporta os hiperparâmetros de inicialização e finais
void exportHyperparameters(const std::string &filename,
                           int input_size, int output_size,
                           const std::vector<int> &hidden_sizes,
                           int epocas, float threshold, float learning_rate,
                           int epocas_executadas, float erro_final);

// Exporta os pesos e biases
void exportWeights(const std::string &filename, const WeightSnapshot &snap,
                   const std::string &label);

// Exporta o erro médio
void exportEpochErrors(const std::string &filename,
                       const std::vector<float> &epoch_losses);

// Exporta as previsões do conjunto de teste
void exportTestPredictions(const std::string &filename,
                           const std::vector<TrainingData> &test_data,
                           const std::vector<std::vector<float>> &predictions);