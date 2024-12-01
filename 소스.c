#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DAYS 30  // 시뮬레이션할 날 수

// 주식 가격 데이터 생성
void generate_stock_prices(double prices[], int days, double initial_price) {
    double volatility = 0.02;  // 변동성 (2%)
    prices[0] = initial_price;

    for (int i = 1; i < days; i++) {
        double change = 1 + (rand() % 2001 - 1000) / 100000.0;  // -1% ~ +1% 랜덤
        prices[i] = prices[i - 1] * change;
    }
}

// 최대 이익 계산 (Greedy Algorithm)
double calculate_max_profit(double prices[], int days) {
    double max_profit = 0.0;
    double min_price = prices[0];

    for (int i = 1; i < days; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];  // 최저 가격 갱신
        }
        else {
            double profit = prices[i] - min_price;
            if (profit > max_profit) {
                max_profit = profit;  // 최대 이익 갱신
            }
        }
    }
    return max_profit;
}

// 데이터를 파일에 저장 (fopen_s 사용)
void save_prices_to_file(const char* filename, double prices[], int days) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");  // fopen_s 사용

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
    srand(time(NULL));  // 랜덤 시드 설정

    double prices[DAYS];
    double initial_price;

    // 사용자에게 초기 주식 가격 입력 받기
    printf("Enter the initial stock price: ");
    scanf_s("%lf", &initial_price);  // 초기 주식 가격 입력 받기

    // 주식 가격 데이터 생성
    generate_stock_prices(prices, DAYS, initial_price);

    // 최대 이익 계산
    double max_profit = calculate_max_profit(prices, DAYS);
    printf("\nMaximum Profit: $%.2f\n\n", max_profit);

    // 날짜별 주식 가격 변화 출력
    printf("Stock prices over %d days:\n", DAYS);
    for (int i = 0; i < DAYS; i++) {
        printf("Day %d: $%.2f\n", i + 1, prices[i]);
    }

    // 주식 가격 데이터를 파일에 저장
    save_prices_to_file("stock_prices.dat", prices, DAYS);

    printf("\nStock prices saved to 'stock_prices.dat'.\n");

    return 0;
}
