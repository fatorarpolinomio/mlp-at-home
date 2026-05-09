// Faz com que esse header file seja incluido apenas uma vez (similar ao Header
// Guards)
#pragma once

enum ActivationFunction {
    ReLu,
    Sigmoid,
};

// MultiLayerPerceptronNetwork é uma implementação autoral de uma rede neural
// MLP
#include <vector>
class MultiLayerPerceptronNetwork {
  private:
    std::vector<std::vector<std::vector<float>>>
        weights;                            // matrix de pesos por camada
    std::vector<std::vector<float>> biases; // matriz de viéses

    // tamanho da entrada
    int input_size;
    // tamanho da saída
    int output_size;
    // tamanho da camada escondida
    int hidden_size;
    // quantidade de camadas escondidas
    int hidden_layers = 1;
    enum ActivationFunction activation_function = ActivationFunction::ReLu;

    std::vector<float> activationFunction(std::vector<float> &z);

  public:
    // construtor
    MultiLayerPerceptronNetwork(
        int input_size, int output_size, int hidden_size, int hidden_layers = 1,
        ActivationFunction activation_function = ActivationFunction::ReLu) {
        this->input_size = input_size;
        this->output_size = output_size;
        this->hidden_size = hidden_size;
        this->hidden_layers = hidden_layers;
        this->activation_function = activation_function;
    }

    void train();

    std::vector<float> predict(std::vector<float> &data);
};
