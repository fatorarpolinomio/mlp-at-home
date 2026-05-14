#include "io/dataIO.hpp"
#include "mlp/mlp.hpp"
#include <iostream>

// Função auxiliar para achar qual posição do vetor tem o maior valor
char getPredictedLetter(const std::vector<float> &output) {
    int max_index = 0;
    float max_val = output[0];
    for (int i = 1; i < 26; i++) {
        if (output[i] > max_val) {
            max_val = output[i];
            max_index = i;
        }
    }
    return 'A' + max_index;
}

int main() {
    int input_size = 120;
    int output_size = 26;

    std::cout << "Carregando o dataset de caracteres..." << std::endl;
    auto full_dataset = loadCharacterData("datasets/caracteres/X.txt",
                                          "datasets/caracteres/Y.txt");

    if (full_dataset.empty()) {
        std::cerr << "Dataset vazio. Encerrando." << std::endl;
        return 1;
    }

    // 80% treino, 20% teste
    std::vector<TrainingData> train_data, test_data;
    splitTrainTest(full_dataset, 0.8f, train_data, test_data);

    // 120 entradas, 1 camada escondida com 60 neurônios
    auto mlp = MLPNetwork(input_size, output_size, std::vector<int>(1, 60),
                          ActivationFunctionType::Sigmoid);

    std::cout << "\nFazendo o treinamento..." << std::endl;
    int epocas = 100;
    float threshold = 0.05f;
    float learning_rate = 0.005f;

    mlp.train(train_data, epocas, threshold, learning_rate);

    std::cout << "\nResultados das previsões (10 primeiras):" << std::endl;
    int acertos = 0;

    for (size_t i = 0; i < test_data.size(); i++) {
        auto response = mlp.predict(test_data[i].input);

        char letra_esperada = getPredictedLetter(test_data[i].output);
        char letra_predita = getPredictedLetter(response);

        if (letra_esperada == letra_predita)
            acertos++;

        // Imprime apenas algumas para não poluir o terminal
        if (i < 10) {
            std::cout << "Esperado: " << letra_esperada
                      << " | Predicao: " << letra_predita << std::endl;
        }
    }

    float acuracia = (float)acertos / test_data.size() * 100.0f;
    std::cout << "\nRESUMO:" << std::endl;
    std::cout << "Acertos: " << acertos << " de " << test_data.size()
              << std::endl;
    std::cout << "Acuracia: " << acuracia << "%" << std::endl;

    // TODO: exportar dados do trabalho:
    // 1. hiperparametros finais e de inicialização
    // 2. pesos iniciais e finais
    // 3. erro cometido em cada interação
    // 4. saída produzida em cada dado de teste
    return 0;
}
