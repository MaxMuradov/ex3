/******************
Name: Maxim Muradov
ID: 346975386
Assignment: ex3
*******************/

/*
time spent on full logic: 4h
time spent on coding style and adjusting to your prohibitions: 5h
*/

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

void printBrand(int brand)
{
    //func that printing Brands
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
    //func to print types
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

int check_input(int input, int leftborder, int rightborder)
{
    //func to check if input is in borders(Valid)
    if (input > rightborder || input < leftborder)
        return 1;
    else
        return 0;
}

void Add_One(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //func that initialize row of brand by type sales
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

int not_enought_data_for(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //func that checks if cube have lack of info 
    //(not all brand have been initialized)
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (Cube[day][i][0] == -1)
            return 1;
    }
    return 0;
}

void check_brands(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //func that prints which brand are not initialized
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        if (Cube[day][i][0] == -1)
        {
            printBrand(i);
            printf(" ");
        }
}

int Add_All(int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    //func that insert info for all brand in one day
    while (not_enought_data_for(Cube, day) == 1) {
        printf("No data for brands ");
        check_brands(Cube, day);
        printf("\nPlease complete the data\n");
        Add_One(Cube, day);
    }

    //returning number of "next day"
    return ++day;
}

int Total_Sales_Per_Day(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //summarizing total sales for a day
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

int OverallTotal(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int opt)
{
    //func looking for max sales in some day
    //returning total sales for day n if opt = 1
    //returning maxday day n if opt = 0
    int t, max_total = -1;
    int maxday = 0;
    for (int i = day; i >= 0; i--)
    {
        t = Total_Sales_Per_Day(Cube, i);
        if (t >= max_total)
        {
            max_total = t;
            maxday = i;
        }
    }
    
    if (opt == 1)
        return max_total;
    else if (opt == 0)
        return maxday;
}

int Best_Sold_Brand(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int opt)
{
    //func looking for max sales for some brand in some day
    //returning best sold brand for a day if opt =1
    //returning max sales for that brand if opt = 0
    int maxbrand;
    int max = -1;
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
    if (opt == 1)
        return maxbrand;
    else if (opt == 0)
        return max;
}

int Overall_Best_Sold_Brand(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int opt)
{
    //func looking for max sales overall for brands
    //returning best sold brand overall
    //returning thru int* maxsales total sales for that brand
    int best_sold_brand = -1;
    int maxsales = -1;
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

        if (summ_sales >= maxsales)
        {
            maxsales = summ_sales;
            best_sold_brand = i;
        }
    }

    if (opt == 1)
        return best_sold_brand;
    else if (opt == 0)
        return maxsales;

}

int Best_Sold_Type(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int opt)
{
    //func looking for max sales for some type in some day
    //returning best sold type for a day if opt = 1
    //returning max sales for that type if opt = 0
    int maxtype;
    int max = -1;
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
    if (opt == 1)
        return maxtype;
    else if (opt == 0)
        return max;
}

int Overall_Best_Sold_Type(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, int opt)
{
    //func looking for max sales overall for types
    //returning best sold type overall if opt = 1
    //returning maxsales total sales for that type if opt = 0
    int best_sold_type = -1;
    int maxsales = -1;
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

        if (summ_sales >= maxsales)
        {
            maxsales = summ_sales;
            best_sold_type = j;
        }
    }

    if (opt == 1)
        return best_sold_type;
    else if (opt == 0)
        return maxsales;
}

void Stats(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //func that prints stats for a day by calling other func
    int analday;// :)
    int sales = -1;
    int tmp = 0;
    
    printf("What day would you like to analyze?\n");
    scanf(" %d", &analday);
    while (check_input(analday, 0, day) == 1)
    {
        printf("Please enter a valid day.\n");
        printf("What day would you like to analyze?\n");
        scanf(" %d", &analday);
    }


    sales = Total_Sales_Per_Day(Cube, analday);
    printf("In day number %d:\nThe sales total was %d \n", analday--, sales);
    
    tmp = Best_Sold_Brand(Cube, analday, 1);
    sales = Best_Sold_Brand(Cube, analday, 0);
    printf("The best sold brand with %d sales was ", sales);
    printBrand(tmp);
    
    tmp = Best_Sold_Type(Cube, analday, 1);
    sales = Best_Sold_Type(Cube, analday, 0);
    printf("\nThe best sold type with %d sales was ", sales);
    printType(tmp);
    printf("\n");
}

void PrintBrandDay(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day, const int brand)
{
    //func that prints cube data for one day
    int suv = Cube[day][brand][0];
    int sedan = Cube[day][brand][1];
    int coup = Cube[day][brand][2];
    int gt = Cube[day][brand][3];

    printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d \n", day + 1, suv, sedan, coup, gt);
}

void PrintAll(const int Cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], const int day)
{
    //func that prints cube data for all days by calling other func
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
    //func that prints overall data by calling other func
    int max_sales_day = OverallTotal(Cube, day, 0);
    int max_total_sales = OverallTotal(Cube, day, 1);

    int best_sold_brand_sales = Overall_Best_Sold_Brand(Cube, day, 0);
    int best_sold_brand = Overall_Best_Sold_Brand(Cube, day, 1);

    int best_sold_type_sales =  Overall_Best_Sold_Type(Cube, day, 0);
    int best_sold_type = Overall_Best_Sold_Type(Cube, day, 1);

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
    //func that printing deltas for all brands
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
    //func that initialize cube to -1
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
            //days++ (new day)
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

