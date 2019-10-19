//standard C packages
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
  }
}

//Main method
int main(void)
{
  struct Customer pat = {"Pat", 100.0};
  
  
  struct Product coke = {"Can Coke", 1.10};
  // printProduct(coke);
  
  struct ProductStock cokeStock = {coke, 20 };
  pat.shoppingList[pat.index++] = cokeStock;
  printCustomer(pat);
  // printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
  // return 0;
};
