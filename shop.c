//standard C library packages import
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Product entity
struct Product 
{
  char* name;
  double price;
};
//Stock entity
struct ProductStock 
{
  struct Product product;
  int quantity;
};
//Shop entity
struct Shop
{
double cash;
  struct ProductStock stock[20];
};
//Customer entity
struct Customer 
{
  char* name;
  double budget;
  struct ProductStock shoppingList[10];
  int index;
};

void printProduct(struct Product p) 
{
  printf("-------------------\n");
  printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
  printf("-------------------\n");
}

void printCustomer(struct Customer c)
{
   printf("-------------------\n");
  printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
  printf("-------------------\n");
  for(int i = 0; i < c.index; i++)
  {
    printProduct(c.shoppingList[i].product);
    printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
    
    double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
    printf("The cost to %s will be €%.2f\n", c.name, cost);
  }
}

//Stock method
void  createAndStockShop()
{
  struct Shop shop = { 200 };
  FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        printf("%s IS A LINE", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
  
}

//Main method
int main(void)
{
//   struct Customer pat = {"Pat", 100.0};
  
//   struct Product coke = {"Can Coke", 1.10};
//   struct Product bread = {"Bread", 0.70};
  
  
//   // printProduct(coke);
//   struct ProductStock cokeStock = {coke, 20 };
//   struct ProductStock breadStock = {bread, 2 };
  
//   pat.shoppingList[pat.index++] = cokeStock;
//   pat.shoppingList[pat.index++] = breadStock;

//   printCustomer(pat);

  createAndStockShop();
  // printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
 return 0;


};


