/*
Pat McDonald G00281051
Course: 52960 -- MULTI-PARADIGM PROGRAMMING
Code is adapted from course materials and code examples
*/

//standard C licbrary header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Product entity
struct Product
{
	char *name;
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
	char *name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};
//Print product function(name,price)
void printProduct(struct Product pn)
{
	printf("-------------------\n");
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", pn.name, pn.price);
	printf("-------------------\n");
}

//Stock shop method: read in stock.csv
struct Shop createAndStockShop()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	//read the csv file
	fp = fopen("stock.csv", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	//read cash from csv
	getline(&line, &len, fp);
	double shopCash = atof(line);
	struct Shop shop = {shopCash};

	while ((read = getline(&line, &len, fp)) != -1)
	{
		char *pn = strtok(line, ","); //product name
		char *pr = strtok(NULL, ","); //price
		char *qy = strtok(NULL, ","); //quantity
		// datatype conversions
		int quantity = atoi(qy);
		double price = atof(pr);
		char *name = malloc(sizeof(char) * 50); //memory allocation - set to 50
		strcpy(name, pn); //string copy to dynamically allocated memory

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
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;

	fp = fopen("order.csv", "r");
	//exit program if file not present
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//read customer name and cbudget
	read = getline(&line, &len, fp);
	char *cn = strtok(line, ","); //customer name
	char *cb = strtok(NULL, ","); //customer budget
	char *custName = malloc(sizeof(char) * 50);
	double custBudget = atof(cb);
	strcpy(custName, cn);

	struct Customer c = {custName, custBudget};
	printf("CUSTOMER NAME: %s \nBUDGET: %.2f\n", custName, custBudget);
	while ((read = getline(&line, &len, fp)) != -1)
	{
		char *pn = strtok(line, ","); //product name
		char *qy = strtok(NULL, ","); //quantity
		int quantity = atoi(qy);
		char *productName = malloc(sizeof(char) * 50);
		strcpy(productName, pn);
		struct Product product = {productName};
		struct ProductStock orderItem = {product, quantity};
		c.shoppingList[c.index++] = orderItem;
	}
	return c;
}

//customer and order data
void printCustomer(struct Customer c)
{
	printf("-------------------\n");
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------------\n");
	for (int i = 0; i < c.index; i++)
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);

		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
		printf("The cost to %s will be €%.2f\n", c.name, cost);

		printf("-------------------\n");
	}
}

// TODO CHECK THIS CODE BEFORE FINAL SUBMISSION!!

// searching both and comparing and returning price
double findProductPrice(struct Shop s, struct Customer c)
{
	struct Product productcustomer;
	double amount = 0;
	double shortAmount;
	//loop products
	printf("\n--------Your Bill--------\n");
	for (int i = 0; i < s.index; i++)
	{
		//loop order
		for (int j = 0; j < c.index; j++)
		{
			struct Product product = s.stock[i].product;
			struct Product productcustomer = c.shoppingList[j].product;
			// compare product and order
			if (strcmp(product.name, productcustomer.name) == 0)
			{
				printf("%s, Price %.2f * Quantity %d\n", c.shoppingList[j].product.name, product.price, c.shoppingList[j].quantity);

				//check quantity
				if (s.stock[i].quantity < c.shoppingList[j].quantity)
				{
					//not in stock;
					printf("Sorry, We've only got %d \n \n", s.stock[i].quantity);
				}
				else
				{
					//calc bill
					amount = product.price * c.shoppingList[j].quantity + amount;
					s.stock[i].quantity = s.stock[i].quantity - c.shoppingList[j].quantity;
				}
			}
		}
	}
	if (c.budget < amount)
	{
		shortAmount = (amount - c.budget);
		printf("----------------------\n");
		printf("Payment amount is short, you need to pay: %.2f \n", shortAmount);
		printf("----------------------\n");
	}
else
	{
		printf("\n");
		printf("Total Bill: %.2f\n", amount);
		// new float in shop
		printf("\n");
		printf("--------Shop Float--------\n");
		// add to the shop float
		s.cash = s.cash + amount;
		printf("Shop float has been updated: %.2f\n", s.cash);
		
		for (int i = 0; i < s.index; i++)
		{
			printf("%s, in stock: %d \n", s.stock[i].product.name, s.stock[i].quantity);
			printf("----------------------\n");
		}
	}

return -1;
}

struct Customer live()
{

// what's your name?
printf("Hello! What's your name?\n");
char *name = malloc(sizeof(char) * 50);
scanf(" %s", name);

// budget
printf("What's your budget?\n");
double budget;
scanf("%lf", &budget);

printf("What would you like to buy?\n");
char *p = malloc(sizeof(char) * 50);
char temp;
scanf("%c", &temp);
scanf("%[^\n]s", p);

printf("How many would you like?\n");
int quantity;
scanf(" %d", &quantity);

struct Customer newc = {name, budget};
printf("\nName : %s, Budget: %.2f", newc.name, newc.budget);

struct Product product = {p};
struct ProductStock orderItem = {product, quantity};
newc.shoppingList[newc.index++] = orderItem;

printf("\nName : %s, Quantity: %d", newc.shoppingList[0].product.name, newc.shoppingList[0].quantity);

return newc;
}
int main(void)
{

struct Shop shop = createAndStockShop();
printShop(shop);

struct Customer c = custOrder();
printf("Name: %s,  Budget %f,  \n", c.name, c.budget);

printCustomer(c);

//search price
findProductPrice(shop, c);

struct Customer newCust = live();
findProductPrice(shop, newCust);

return 0;
}