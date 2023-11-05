#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para verificar se um número é primo
int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *serieFile, *parFile, *imparFile, *primosFile, *testeFile, *resultadosFile;

    // Abre o arquivo "serie.txt" para gravação dos primeiros 1000 valores
    serieFile = fopen("serie.txt", "w");
    if (serieFile == NULL) {
        perror("Erro ao abrir o arquivo serie.txt");
        exit(1);
    }

    int valor = 5;
    for (int i = 0; i < 1000; i++) {
        fprintf(serieFile, "%d\n", valor);
        valor += 3;
    }
    fclose(serieFile);

    // Abre o arquivo "serie.txt" para leitura dos valores
    serieFile = fopen("serie.txt", "r");
    if (serieFile == NULL) {
        perror("Erro ao abrir o arquivo serie.txt");
        exit(1);
    }

    // Abre os arquivos "par.txt" e "impar.txt" para gravação
    parFile = fopen("par.txt", "w");
    imparFile = fopen("impar.txt", "w");
    if (parFile == NULL || imparFile == NULL) {
        perror("Erro ao abrir arquivos par.txt ou impar.txt");
        exit(1);
    }

    // Separa os valores pares e ímpares
    int num;
    while (fscanf(serieFile, "%d", &num) != EOF) {
        if (num % 2 == 0) {
            fprintf(parFile, "%d\n", num);
        } else {
            fprintf(imparFile, "%d\n", num);
        }
    }
    fclose(parFile);
    fclose(imparFile);

    fclose(serieFile);

    // Abre o arquivo "serie.txt" novamente para leitura dos valores primos
    serieFile = fopen("serie.txt", "r");
    if (serieFile == NULL) {
        perror("Erro ao abrir o arquivo serie.txt");
        exit(1);
    }

    // Abre o arquivo "primos.txt" para gravação dos valores primos
    primosFile = fopen("primos.txt", "w");
    if (primosFile == NULL) {
        perror("Erro ao abrir o arquivo primos.txt");
        exit(1);
    }

    while (fscanf(serieFile, "%d", &num) != EOF) {
        if (isPrime(num)) {
            fprintf(primosFile, "%d\n", num);
        }
    }
    fclose(primosFile);
    fclose(serieFile);

    // Cria o arquivo "teste.txt" com os números de 1 a 5000 e -1 como flag
    testeFile = fopen("teste.txt", "w");
    if (testeFile == NULL) {
        perror("Erro ao criar o arquivo teste.txt");
        exit(1);
    }

    for (int i = 1; i <= 5000; i++) {
        fprintf(testeFile, "%d\n", i);
    }
    fprintf(testeFile, "-1\n");
    fclose(testeFile);

    // Abre o arquivo "teste.txt" para leitura e cria o arquivo "resultados.txt"
    testeFile = fopen("teste.txt", "r");
    resultadosFile = fopen("resultados.txt", "w");
    if (testeFile == NULL || resultadosFile == NULL) {
        perror("Erro ao abrir arquivos teste.txt ou resultados.txt");
        exit(1);
    }

    int encontrado;
    while (fscanf(testeFile, "%d", &num) != EOF) {
        encontrado = 0;
        rewind(serieFile);
        int posicao = 1;
        int valorAnterior, valorPosterior;

        while (fscanf(serieFile, "%d", &valor) != EOF) {
            if (valor == num) {
                encontrado = 1;
                fprintf(resultadosFile, "O valor %d está no arquivo na posição %d\n", num, posicao);
                break;
            } else if (valor > num) {
                valorPosterior = valor;
                if (posicao > 1) {
                    fseek(serieFile, -8, SEEK_CUR); // Volta 8 bytes (número de dígitos em 5000)
                    fscanf(serieFile, "%d", &valorAnterior);
                    fprintf(resultadosFile, "O valor %d não está no arquivo, valores mais próximos: %d e %d\n", num, valorAnterior, valorPosterior);
                } else {
                    fprintf(resultadosFile, "O valor %d não está no arquivo, valores mais próximos: -1 e %d\n", num, valorPosterior);
                }
                break;
            }
            posicao++;
        }

        if (!encontrado) {
            fseek(serieFile, -8, SEEK_END); // Volta 8 bytes (número de dígitos em 5000)
            fscanf(serieFile, "%d", &valorAnterior);
            fprintf(resultadosFile, "O valor %d não está no arquivo, valores mais próximos: %d e -1\n", num, valorAnterior);
        }
    }

    fclose(testeFile);
    fclose(resultadosFile);

    return 0;
}
