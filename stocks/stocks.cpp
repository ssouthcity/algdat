#include <iostream>
#include <random>
#include <time.h>

int stocks(int flux[], int days, int *buy, int *sell)
{
    int prices[days];
    int cumprice = 0;
    for (int i = 0; i < days; ++i)
    {
        cumprice += flux[i];
        prices[i] = cumprice;
    }

    *buy = *sell = days - 1;

    for (int i = days - 2; i >= 0; --i)
    {
        if (prices[i] > prices[*sell])
            *sell = i;
        else if (prices[*sell] - prices[i] > prices[*sell] - prices[*buy])
            *buy = i;
    }

    return prices[*sell] - prices[*buy];
}

void benchmark()
{
    srand(time(NULL));

    int loads[] = {1000, 10000, 100000};
    int amount = 10000;

    for (int i = 0; i < 3; ++i)
    {
        int arr[loads[i]];
        for (int j = 0; j < loads[j]; ++j)
            arr[j] = rand();

        clock_t start = clock();
        for (int j = 0; j < amount; ++j)
        {
            int buy, sell;
            stocks(arr, loads[i], &buy, &sell);
        }
        clock_t end = clock();

        double elapsed = double(end - start) / CLOCKS_PER_SEC;

        std::cout << "Benchmark Load: " << loads[i] << std::endl;
        std::cout << "Time: " << elapsed << std::endl;
    }
}

int main(int argc, char const **argv)
{
    if (argc < 2)
    {
        std::cout << "Signature: stocks <starting price> <fluctuations...>" << std::endl;
        return 1;
    }

    int flux[argc - 1];
    for (int i = 1; i < argc; ++i)
        flux[i - 1] = atoi(argv[i]);

    int buy, sell;
    int profit = stocks(flux, argc - 1, &buy, &sell);

    std::cout << "Buy:    " << buy << std::endl;
    std::cout << "Sell:   " << sell << std::endl;
    std::cout << "Profit: " << profit << std::endl;

    benchmark();

    return 0;
}