#include <stdio.h>
#include <string.h>

struct Customer {
  char* name;
  double budget;
};

struct Product {
  char* name;
  double price;
};


int main(void)
{
  struct Customer pat = {"Pat", 100.0};
  printf("Customer name is  %s\n", pat.name); 
  
  struct Product coke = {"Can Coke", 1.10};
  printf("The %s costs %2f\n", coke.name, coke.price);
  
  return 0;
};
