#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de uma carta de cidade
typedef struct {
    char estado[30];
    char codigo[10];
    char nome[50];
    int populacao;
    float area;
    double pib;
    int pontosTuristicos;
} CartaCidade;

// Função para cadastrar uma carta
void cadastrarCarta(CartaCidade *carta, int numero) {
    printf("\n--- Cadastro da Carta %d ---\n", numero);
    printf("Estado: ");
    scanf(" %[^\n]", carta->estado);
    printf("Código: ");
    scanf(" %[^\n]", carta->codigo);
    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta->nome);
    printf("População: ");
    scanf("%d", &carta->populacao);
    printf("Área (km2): ");
    scanf("%f", &carta->area);
    printf("PIB (em milhões): ");
    scanf("%lf", &carta->pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
}

// Função para exibir uma carta
void exibirCarta(CartaCidade carta, int numero) {
    printf("\n--- Carta %d ---\n", numero);
    printf("Estado: %s\n", carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("Nome: %s\n", carta.nome);
    printf("População: %d\n", carta.populacao);
    printf("Área: %.2f km2\n", carta.area);
    printf("PIB: %.2lf milhões\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontosTuristicos);
}

// Função para calcular a densidade populacional
float densidadePopulacional(CartaCidade carta) {
    return carta.populacao / carta.area;
}

// Função para exibir o menu dinâmico de atributos
void exibirMenuAtributos() {
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População (maior vence)\n");
    printf("2 - Área (maior vence)\n");
    printf("3 - PIB (maior vence)\n");
    printf("4 - Pontos Turísticos (maior vence)\n");
    printf("5 - Densidade Populacional (menor vence)\n");
}

// Função para obter o nome do atributo
const char* nomeAtributo(int op) {
    switch(op) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        default: return "Desconhecido";
    }
}

// Função para comparar dois atributos e retornar o resultado
// Retorna 1 se carta1 vence, 2 se carta2 vence, 0 se empate
int compararAtributo(CartaCidade c1, CartaCidade c2, int atributo) {
    switch(atributo) {
        case 1: // População
            return (c1.populacao > c2.populacao) ? 1 : (c1.populacao < c2.populacao) ? 2 : 0;
        case 2: // Área
            return (c1.area > c2.area) ? 1 : (c1.area < c2.area) ? 2 : 0;
        case 3: // PIB
            return (c1.pib > c2.pib) ? 1 : (c1.pib < c2.pib) ? 2 : 0;
        case 4: // Pontos Turísticos
            return (c1.pontosTuristicos > c2.pontosTuristicos) ? 1 : (c1.pontosTuristicos < c2.pontosTuristicos) ? 2 : 0;
        case 5: { // Densidade Populacional (menor vence)
            float d1 = densidadePopulacional(c1);
            float d2 = densidadePopulacional(c2);
            return (d1 < d2) ? 1 : (d1 > d2) ? 2 : 0;
        }
        default:
            return 0;
    }
}

int main() {
    CartaCidade carta1, carta2;
    int op1, op2, resultado1, resultado2;

    // Cadastro das cartas
    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    // Exibição das cartas cadastradas
    exibirCarta(carta1, 1);
    exibirCarta(carta2, 2);

    // Menu dinâmico para escolha dos atributos
    printf("\n--- Comparação de Cartas ---\n");
    exibirMenuAtributos();
    printf("Escolha o primeiro atributo para comparar (1-5): ");
    scanf("%d", &op1);

    printf("Deseja comparar um segundo atributo? (1-Sim, 0-Não): ");
    int compararDois;
    scanf("%d", &compararDois);

    if (compararDois) {
        exibirMenuAtributos();
        printf("Escolha o segundo atributo para comparar (1-5, diferente do primeiro): ");
        do {
            scanf("%d", &op2);
            if(op2 == op1) printf("Escolha um atributo diferente do primeiro!\n");
        } while(op2 == op1);
    } else {
        op2 = 0;
    }

    // Lógica de comparação avançada (nível mestre)
    resultado1 = compararAtributo(carta1, carta2, op1);

    if (op2) {
        resultado2 = compararAtributo(carta1, carta2, op2);

        // Decisão aninhada: só compara o segundo atributo se houver empate no primeiro
        if (resultado1 == 0) {
            printf("\nEmpate no atributo %s! Comparando pelo segundo atributo...\n", nomeAtributo(op1));
            if (resultado2 == 1) {
                printf("Carta 1 venceu pelo atributo %s!\n", nomeAtributo(op2));
                printf("Cidade vencedora: %s\n", carta1.nome);
            } else if (resultado2 == 2) {
                printf("Carta 2 venceu pelo atributo %s!\n", nomeAtributo(op2));
                printf("Cidade vencedora: %s\n", carta2.nome);
            } else {
                printf("Empate também no segundo atributo (%s)!\n", nomeAtributo(op2));
                printf("Resultado: EMPATE entre %s e %s\n", carta1.nome, carta2.nome);
            }
        } else if (resultado1 == 1) {
            printf("\nCarta 1 venceu pelo atributo %s!\n", nomeAtributo(op1));
            printf("Cidade vencedora: %s\n", carta1.nome);
        } else {
            printf("\nCarta 2 venceu pelo atributo %s!\n", nomeAtributo(op1));
            printf("Cidade vencedora: %s\n", carta2.nome);
        }
    } else {
        // Apenas um atributo escolhido
        if (resultado1 == 1) {
            printf("\nCarta 1 venceu pelo atributo %s!\n", nomeAtributo(op1));
            printf("Cidade vencedora: %s\n", carta1.nome);
        } else if (resultado1 == 2) {
            printf("\nCarta 2 venceu pelo atributo %s!\n", nomeAtributo(op1));
            printf("Cidade vencedora: %s\n", carta2.nome);
        } else {
            printf("\nEmpate no atributo %s!\n", nomeAtributo(op1));
            printf("Resultado: EMPATE entre %s e %s\n", carta1.nome, carta2.nome);
        }
    }

    return 0;
}
