/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = { "Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh" };
char types[NUM_OF_TYPES][TYPES_NAMES] = { "SUV", "Sedan", "Coupe", "GT" };


void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
        "1.Enter Daily Data For A Brand\n"
        "2.Populate A Day Of Sales For All Brands\n"
        "3.Provide Daily Stats\n"
        "4.Print All Data\n"
        "5.Provide Overall (simple) Insights\n"
        "6.Provide Average Delta Metrics\n"
        "7.exit\n");
}

void Add_One(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int brand, amount;
    scanf_s("%d", &brand);
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        scanf_s(" %d", &amount);
        Cube[day][brand][i] = amount;
    }
}

bool not_enought_data_for(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (Cube[day][i][0] == -1)
            return 1;
    }
    return 0;
}

void check_brands() {}
// do it

void Add_All(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int& day)
{
    while (not_enought_data_for(Cube, day)) {
        printf("No data for brands: ");
        check_brands();
        printf("Please complete the data");
        Add_One(Cube, day);
    }

}

int Total_Sales_Per_Day(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int total = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            total += Cube[day][i][j];
        }
    }
    return total;
}

int Best_Sold_Brand(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int maxbrand, max = -1;
    int brand_sale = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++, brand_sale = 0)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            brand_sale += Cube[day][i][j];
        }
        if (brand_sale >= max)
        {
            max = brand_sale;
            maxbrand = i;
        }
    }

    return maxbrand;
}

int Best_Sold_Type(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int maxtype, max = -1;
    int type_sale = 0;
    for (int j = 0; j < NUM_OF_TYPES; j++, type_sale = 0)
    {
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            type_sale += Cube[day][i][j];
        }
        if (type_sale >= max)
        {
            max = type_sale;
            maxtype = j;
        }
    }

    return maxtype;
}

void Stats(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int analday; // :)
    printf("What day would you like to analyze?");
    scanf_s(" %d", &analday);
    printf("Total sales: %d \n", Total_Sales_Per_Day(Cube, analday));
    printf("Best sold brand: %d \n", Best_Sold_Brand(Cube, analday));
    printf("Best sold type %d \n", Best_Sold_Type(Cube, analday));
}

void init_array(int array[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
        for (int j = 0; j < NUM_OF_BRANDS; j++)
            for (int k = 0; k < NUM_OF_TYPES; k++)
                array[i][j][k] = -1;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    init_array(cube);
    int days = 0;
    int choice;
    printMenu();
    scanf_s("%d", &choice);
    while (choice != done) {
        switch (choice) {
        case addOne:
            Add_One(cube, days);
            break;
        case addAll:
            Add_All(cube, days);
            break;
        case stats:
            Stats(cube);
            break;
        case print:
            break;
        case insights:
            break;
        case deltas:
            break;
            //default:
            //    printf("Invalid input\n");
        }
        printMenu();
        scanf_s("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


