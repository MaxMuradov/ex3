/******************
Name: Maxim Muradov
ID: 346975386
Assignment: ex3
*******************/

/*
im sorry thats some func are too complicated in print and also about using pointers i just wanted to return some var thru parametrs of func 
but it was much more complicated than in c++ where i can just give int& so yea, aaahh and forgive me please -til of bool, i know 
i could actually make this code better for ex requirements but im working and dont have much time
*/

#include <stdio.h>
#include<stdbool.h>

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

void printBrand(int brand)
{
    switch (brand)
    {
    case 0:
        printf("Toyoga");
        break;
    case 1:
        printf("HyunNight");
        break;
    case 2:
        printf("Mazduh");
        break;
    case 3:
        printf("FolksVegan");
        break;
    case 4:
        printf("Key-Yuh");
        break;

    default:
        break;
    }
}

void printType(int type)
{
    switch (type)
    {
    case 0:
        printf("SUV");
        break;
    case 1:
        printf("Sedan");
        break;
    case 2:
        printf("Coupe");
        break;
    case 3:
        printf("GT");
        break;

    default:
        break;
    }
}

bool check_input(int input, int leftborder, int rightborder)
{
    if (input > rightborder || input < leftborder)
        return 1;
    else
        return 0;
}

void Add_One(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int brand, amount;
    scanf("%d", &brand);
    if (check_input(brand, 0, 4))
    {
        printf("this brand dont exist\n");
    }
    else
    {
        for (int i = 0; i < NUM_OF_TYPES; i++)
        {
            scanf(" %d", &amount);
            Cube[day][brand][i] = amount;
        }
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

void check_brands(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        if (Cube[day][i][0] == -1)
        {
            printBrand(i);
            printf(" ");
        }
}
// do it

int Add_All(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    while (not_enought_data_for(Cube, day)) {
        printf("No data for brands ");
        check_brands(Cube, day);
        printf("\nPlease complete the data\n");
        Add_One(Cube, day);
    }

    return ++day;
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

int OverallTotal(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int* maxday)
{
    int t, max_total = -1;
    *maxday = 0;
    for (int i = day; i > 0; i--)
    {
        t = Total_Sales_Per_Day(Cube, i);
        if (t >= max_total)
        {
            max_total = t;
            *maxday = i;
        }
    }
    return max_total;
}

int Best_Sold_Brand(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int* max)
{
    int maxbrand;
    *max = -1;
    int brand_sale = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++, brand_sale = 0)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            brand_sale += Cube[day][i][j];
        }
        if (brand_sale >= *max)
        {
            *max = brand_sale;
            maxbrand = i;
        }
    }

    return maxbrand;
}

int Overall_Best_Sold_Brand(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int* maxsales)
{
    int best_sold_brand = -1;
    *maxsales = -1;
    int summ_sales = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++, summ_sales = 0)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for (int k = 0; k < day; k++)
            {
                summ_sales += Cube[k][i][j];
            }
        }

        if (summ_sales >= *maxsales)
        {
            *maxsales = summ_sales;
            best_sold_brand = i;
        }
    }

    return best_sold_brand;

}

int Best_Sold_Type(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int* max)
{
    int maxtype;
    *max = -1;
    int type_sale = 0;
    for (int j = 0; j < NUM_OF_TYPES; j++, type_sale = 0)
    {
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            type_sale += Cube[day][i][j];
        }
        if (type_sale >= *max)
        {
            *max = type_sale;
            maxtype = j;
        }
    }

    return maxtype;
}

int Overall_Best_Sold_Type(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int* maxsales)
{
    int best_sold_type = -1;
    *maxsales = -1;
    int summ_sales = 0;
    for (int j = 0; j < NUM_OF_TYPES; j++, summ_sales = 0)
    {
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            for (int k = 0; k < day; k++)
            {
                summ_sales += Cube[k][i][j];
            }
        }

        if (summ_sales >= *maxsales)
        {
            *maxsales = summ_sales;
            best_sold_type = j;
        }
    }

    return best_sold_type;

}

void Stats(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int analday;// :)
    int sales = -1;
    int tmp;
    printf("What day would you like to analyze?\n");
    scanf(" %d", &analday);
    while (check_input(analday, 0, day))
    {
        printf("Please enter valid day.\n");
        printf("What day would you like to analyze?\n");
        scanf(" %d", &analday);
    }
    
    printf("In day number %d:\n", analday--);
    printf("The sales total was %d \n", Total_Sales_Per_Day(Cube, analday));
    tmp = Best_Sold_Brand(Cube, analday, &sales);
    printf("The best sold brand with %d sales was ", sales);
    printBrand(tmp);
    tmp = Best_Sold_Type(Cube, analday, &sales);
    printf("\nThe best sold type with %d sales was ", sales);
    printType(tmp);
    printf("\n");
}

void PrintBrandDay(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, const int brand)
{
    int suv = Cube[day][brand][0];
    int sedan = Cube[day][brand][1];
    int coup = Cube[day][brand][2];
    int gt = Cube[day][brand][3];

    printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d \n", day + 1, suv, sedan, coup, gt);
}

void PrintAll(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    printf("*****************************************\n");
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        printf("Sales for ");
        printBrand(i);
        printf(":\n");
        for (int j = 0; j < day; j++)
            PrintBrandDay(Cube, j, i);
    }
    printf("*****************************************\n");
}

void OverallStats(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    int max_sales_day = 0;
    int max_total_sales = OverallTotal(Cube, day, &max_sales_day);

    int best_sold_brand_sales = 0;
    int best_sold_brand = Overall_Best_Sold_Brand(Cube, day, &best_sold_brand_sales);

    int best_sold_type_sales = 0;
    int best_sold_type = Overall_Best_Sold_Type(Cube, day, &best_sold_type_sales);

    printf("The best-selling brand overall is ");
    printBrand(best_sold_brand);
    printf(": %d$\n", best_sold_brand_sales);

    printf("The best-selling type of car is ");
    printType(best_sold_type);
    printf(": %d$\n", best_sold_type_sales);

    printf("The most profitable day was day number %d: %d$ \n", max_sales_day + 1, max_total_sales);
}


void Deltas(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    float delta = 0;
    int yesterday = 0;
    int daily_summ = 0;
    int summ = 0;

    for (int i = 0; i < NUM_OF_BRANDS; i++, summ = 0)
    {
        for (int d = 0; d < day; d++, daily_summ = 0)
        {
            for (int j = 0; j < NUM_OF_TYPES; j++)
            {
                daily_summ += Cube[d][i][j];
            }
            if (d != 0)
            {
                summ += daily_summ - yesterday;
            }
            yesterday = daily_summ;

        }

        delta = (float)summ / (day - 1);

        printf("Brand: ");
        printBrand(i);
        printf(", Average Delta: %f \n", delta);
    }
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
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
        case addOne:
            Add_One(cube, days);
            break;
        case addAll:
            days = Add_All(cube, days);
            break;
        case stats:
            Stats(cube, days);
            break;
        case print:
            PrintAll(cube, days);
            break;
        case insights:
            OverallStats(cube, days);
            break;
        case deltas:
            Deltas(cube, days);
            break;
        default:
            printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}

