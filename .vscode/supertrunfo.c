#include <stdio.h>
#include <string.h>

// Estrutura da carta
typedef struct {
    char estado[50];
    char codigo[10];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica;
    float pibPerCapita;
} Carta;

// Função para calcular densidade e PIB per capita
void calcularIndicadores(Carta *carta) {
    carta->densidadeDemografica = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib / carta->populacao;
}

// Função para exibir menu de atributos
int exibirMenu(int usado) {
    printf("\nEscolha um atributo para comparar:\n");
    if (usado != 1) printf("1 - População\n");
    if (usado != 2) printf("2 - Área\n");
    if (usado != 3) printf("3 - PIB\n");
    if (usado != 4) printf("4 - Pontos Turísticos\n");
    if (usado != 5) printf("5 - Densidade Populacional\n");
    if (usado != 6) printf("6 - PIB per capita\n");
    printf("Opção: ");
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

// Obter valor do atributo
float obterValorAtributo(Carta carta, int atributo) {
    switch (atributo) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontosTuristicos;
        case 5: return carta.densidadeDemografica;
        case 6: return carta.pibPerCapita;
        default: return 0;
    }
}

// Comparar dois valores de um atributo
int compararAtributo(float v1, float v2, int atributo) {
    return (atributo == 5) ? (v1 < v2 ? 1 : (v1 > v2 ? 2 : 0)) : (v1 > v2 ? 1 : (v1 < v2 ? 2 : 0));
}

// Resultado final
void mostrarResultado(Carta c1, Carta c2, int att1, int att2) {
    float valor1A = obterValorAtributo(c1, att1);
    float valor2A = obterValorAtributo(c2, att1);
    float valor1B = obterValorAtributo(c1, att2);
    float valor2B = obterValorAtributo(c2, att2);

    printf("\n--- Comparação ---\n");
    printf("Atributo 1:\n%s: %.2f\n%s: %.2f\n", c1.nomeCidade, valor1A, c2.nomeCidade, valor2A);
    int vencedor1 = compararAtributo(valor1A, valor2A, att1);
    vencedor1 == 0 ? printf("-> Empate nesse atributo\n") :
    printf("-> %s venceu no primeiro atributo\n", vencedor1 == 1 ? c1.nomeCidade : c2.nomeCidade);

    printf("\nAtributo 2:\n%s: %.2f\n%s: %.2f\n", c1.nomeCidade, valor1B, c2.nomeCidade, valor2B);
    int vencedor2 = compararAtributo(valor1B, valor2B, att2);
    vencedor2 == 0 ? printf("-> Empate nesse atributo\n") :
    printf("-> %s venceu no segundo atributo\n", vencedor2 == 1 ? c1.nomeCidade : c2.nomeCidade);

    float soma1 = valor1A + valor1B;
    float soma2 = valor2A + valor2B;

    printf("\nSoma dos atributos:\n%s: %.2f\n%s: %.2f\n", c1.nomeCidade, soma1, c2.nomeCidade, soma2);

    if (soma1 > soma2) {
        printf("\n>>> %s venceu a rodada!\n", c1.nomeCidade);
    } else if (soma2 > soma1) {
        printf("\n>>> %s venceu a rodada!\n", c2.nomeCidade);
    } else {
        printf("\n>>> Empate!\n");
    }
}

// Seleciona carta com base no nome digitado
Carta selecionarCarta(char escolha[]) {
    Carta c;

    if (strcmp(escolha, "sp") == 0) {
        c = (Carta){"SP", "C001", "São Paulo", 12300000, 1521.11, 800000.0, 15};
    } else if (strcmp(escolha, "rio") == 0) {
        c = (Carta){"RJ", "C002", "Rio de Janeiro", 6710000, 1182.30, 410000.0, 12};
    } else if (strcmp(escolha, "bh") == 0) {
        c = (Carta){"MG", "C003", "Belo Horizonte", 2523000, 331.40, 130000.0, 8};
    } else if (strcmp(escolha, "bsb") == 0) {
        c = (Carta){"DF", "C004", "Brasília", 3050000, 5802.00, 210000.0, 10};
    } else {
        c = (Carta){"INV", "XXX", "Cidade Inválida", 0, 0.0, 0.0, 0};
    }

    calcularIndicadores(&c);
    return c;
}

int main() {
    char entrada1[10], entrada2[10];
    Carta carta1, carta2;

    printf("Super Trunfo - Escolha suas cidades!\n\n");
    printf("Opções: sp, rio, bh, bsb\n");

    // Entrada da primeira cidade
    do {
        printf("\nDigite a primeira cidade: ");
        scanf("%s", entrada1);
        carta1 = selecionarCarta(entrada1);
        if (strcmp(carta1.estado, "INV") == 0) {
            printf("Cidade inválida. Tente novamente.\n");
        }
    } while (strcmp(carta1.estado, "INV") == 0);

    // Entrada da segunda cidade
    do {
        printf("Digite a segunda cidade : ");
        scanf("%s", entrada2);
        carta2 = selecionarCarta(entrada2);
        if (strcmp(carta2.estado, "INV") == 0 || strcmp(entrada1, entrada2) == 0) {
            printf("Cidade inválida ou repetida. Tente novamente.\n");
        }
    } while (strcmp(carta2.estado, "INV") == 0 || strcmp(entrada1, entrada2) == 0);

    int atributo1 = 0, atributo2 = 0;

    // Escolha dos atributos
    do {
        atributo1 = exibirMenu(0);
    } while (atributo1 < 1 || atributo1 > 6);

    do {
        atributo2 = exibirMenu(atributo1);
    } while (atributo2 < 1 || atributo2 > 6 || atributo2 == atributo1);

    // Comparação
    mostrarResultado(carta1, carta2, atributo1, atributo2);

    return 0;
}
