//standard C library packages import
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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
int index;
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

//Stock shop method: read in stock.csv
struct Shop createAndStockShop()
{
  FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

        //read cash from csv
        getline(&line, &len, fp);
        double shopCash = atof(line);
        struct Shop shop = {shopCash};
        

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        char *n = strtok(line, ",");
        char *p = strtok(NULL, ",");
        char *q = strtok(NULL, ",");
        // datatype conversions
        int quantity = atoi(q);
        double price = atof(p);
        char *name = malloc(sizeof(char) * 50);//memory allocation - set to 50
        strcpy(name, n);//string copy to dynamically allocated memory
        
        struct Product product = {name, price};
        struct ProductStock stockItem = {product, quantity};
        shop.stock[shop.index++] = stockItem;
    }
        return shop;
}
//printing shop data
void printShop(struct Shop s)
    {
      printf("Shop has %.2f in cash\n", s.cash);
        for (int i = 0; i < s.index; i++)
        {
          printProduct(s.stock[i].product);
          printf("The shop has %d of the above\n", s.stock[i].quantity);
        }
    }

//read customer order from order.csv
struct Customer custOrder()
{
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    fp = fopen("order.csv", "r");
    //exit program if file not present
    if (fp == NULL)
        exit(EXIT_FAILURE);
	
  //read customer name and budget
	read = getline(&line, &len, fp);
    char *a = strtok(line, ",");
    char *b = strtok(NULL, ",");
    char *custName = malloc(sizeof(char) * 50);
    double custBudget = atof(b);
    strcpy(custName, a); 
	struct Customer customer = { custName, custBudget};
    printf("CUSTOMER NAME: %s \nBUDGET: %.2f\n", custName, custBudget);
    while ((read = getline(&line, &len, fp)) != -1) {
		// TODO process remaining lines
    char *p = strtok(line, ",");
			char *q = strtok(NULL, ",");
			int quantity = atoi(q);
			char *productname = malloc(sizeof(char)*50);
			strcpy(productname, p);
			struct Product product = {productname};
			struct ProductStock orderItem = {product, quantity};
			customer.shoppingList[customer.index++]=orderItem;

	}        
	return customer;
}   

//customer and order data
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

struct Shop shop = createAndStockShop();
printShop(shop);
//printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
 return 0;

}