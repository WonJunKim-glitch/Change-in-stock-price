#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DAYS 30  // �ùķ��̼��� �� ��

// �ֽ� ���� ������ ����
void generate_stock_prices(double prices[], int days, double initial_price) {
    double volatility = 0.02;  // ������ (2%)
    prices[0] = initial_price;

    for (int i = 1; i < days; i++) {
        double change = 1 + (rand() % 2001 - 1000) / 100000.0;  // -1% ~ +1% ����
        prices[i] = prices[i - 1] * change;
    }
}

// �ִ� ���� ��� (Greedy Algorithm)
double calculate_max_profit(double prices[], int days) {
    double max_profit = 0.0;
    double min_price = prices[0];

    for (int i = 1; i < days; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];  // ���� ���� ����
        }
        else {
            double profit = prices[i] - min_price;
            if (profit > max_profit) {
                max_profit = profit;  // �ִ� ���� ����
            }
        }
    }
    return max_profit;
}

// �����͸� ���Ͽ� ���� (fopen_s ���)
void save_prices_to_file(const char* filename, double prices[], int days) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");  // fopen_s ���

    if (err != 0 || file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (int i = 0; i < days; i++) {
        fprintf(file, "%d %.2f\n", i + 1, prices[i]);
    }

    fclose(file);
}

int main() {
    srand(time(NULL));  // ���� �õ� ����

    double prices[DAYS];
    double initial_price;

    // ����ڿ��� �ʱ� �ֽ� ���� �Է� �ޱ�
    printf("Enter the initial stock price: ");
    scanf_s("%lf", &initial_price);  // �ʱ� �ֽ� ���� �Է� �ޱ�

    // �ֽ� ���� ������ ����
    generate_stock_prices(prices, DAYS, initial_price);

    // �ִ� ���� ���
    double max_profit = calculate_max_profit(prices, DAYS);
    printf("\nMaximum Profit: $%.2f\n\n", max_profit);

    // ��¥�� �ֽ� ���� ��ȭ ���
    printf("Stock prices over %d days:\n", DAYS);
    for (int i = 0; i < DAYS; i++) {
        printf("Day %d: $%.2f\n", i + 1, prices[i]);
    }

    // �ֽ� ���� �����͸� ���Ͽ� ����
    save_prices_to_file("stock_prices.dat", prices, DAYS);

    printf("\nStock prices saved to 'stock_prices.dat'.\n");

    return 0;
}
