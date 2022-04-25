bid/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * DATE: 25/02/22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


/* ******************* FUNCTION DECLARATION ********************* */

tProductCategory getCategory(char * category);
/*
 * Goal: Returns the category assigned to an item in the list
 * Input: category: Category of a product
 * Output: The correspondent category
 * Precondition: category has to be a valid category
 * */
char* printCategory(tProductCategory p);
/*
 * Goal: Displays the category of an item in the list
 * Input: p: The product category
 * Output: A string with the corresponding category
 * Precondition: p has to be a valid category
 * */
tItemL newProduct(char *product, char *seller, char *category, char *price);
/*
 * Goal: Returns a new product based on the parameters passed and its bid counter initialized to 0
 * Input: product: The id of the product
 *        seller: The product's user/seller
 *        category: The product's category
 *        price: The product's price
 * Output: A product with all the information
 * */
void new(char *product, char *seller, char *category, char *price, tList *list);
/*
 * Goal: Adds a new product to the specfied                   list
 * Input: product: The id of the product
 *        seller: The product's user/seller
 *        category: The product's category
 *        price: The product's price
 *        list: List to be modified
 * Output: The modified list with the new product inserted
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 * */
void delete(char *product, tList *list);
/*
 * Goal: Deletes an specified item from the list
 * Input: product: Product to be removed
 *        list: List to be modified
 * Output: The modified list without the product
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 * */
void bid(char *product, char *bidder, char *bid_price, tList *list);
/*
 * Goal: Increments the bids of a product of the list by 1
 * Input: product: Product's id
 *        bidder: User that bids on the product
 *        bid_price: Price user bids on the product
 *        list: List to be modified
 * Output: The modified list with the product's price changed and its bid counter incremented
 * Precondition: The list has to be initialized
 * */
void stats(tList *list);
/*
 * Goal: Displays the whole current list of products and statistics of those products.
 * Input: list: List to be handled
 * Precondition: The list has to be initialized
 * */


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {

    switch (command) {

        case 'N':
            //Input format: 01 N product1 user1  painting 150.00
            printf("********************\n");
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, list);
            break;

        case 'S':
            //Input format: 10 S
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(list);
            break;

        case 'B':
            //09 B: product product2 bidder user2 price 125.00
            printf("********************\n");
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(param1, param2, param3, list);
            break;

        case 'D':
            //09 D: product product2
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, list);
            break;
        default:
            break;
    }
}

char* printCategory(tProductCategory p){
    //Checks if the given category is book or painting
    if(p == book){
        return "book";
    } else if(p == painting){
        return "painting";
    } else{
        return "ERROR_PRINTING_CATEGORY";
    }
}

tProductCategory getCategory(char *category){

    if(!strcmp(category, "book")){
        return book;
    } else if(!strcmp(category, "painting")){
        return painting;
    } else{
        printf("ERROR_GETTING_CATEGORY");
    }
}

tItemL newProduct(char *product, char *seller, char *category, char *price){

    tItemL new_product;

    strcpy(new_product.productId, product);
    strcpy(new_product.seller, seller);
    new_product.productCategory = getCategory(category);
    new_product.productPrice = atof(price);

    //Initialized bid counter to 0
    new_product.bidCounter = 0;

    return new_product;
}

void new(char *product, char *seller, char *category, char *price, tList *list){

    tPosL p = LNULL;
    //Create a new product using an auxiliary function, that already initializes its bid counter to 0
    tItemL new_product = newProduct(product, seller, category, price);

    //Check if an element with the same productId exists in the list
    if( findItem(new_product.productId, *list) == LNULL){
        //No item with the introduced productId has been found, so we check if it can be inserted at the end -> POS = LNULL
        if(insertItem(new_product, p, list) == false){
            //An error occurred in the insertion of the element
            printf("+ Error: New not possible\n");
            } else {
            printf("* New: product %s seller %s category %s price %.2f\n",
                   new_product.productId, new_product.seller, printCategory(new_product.productCategory), new_product.productPrice);
        }
    } else {
        //An error occurred, there was already a element with that productId in the list
        printf("+ Error: New not possible\n");
    }
}


void delete(char *product, tList *list){

    tPosL p;
    tItemL user;

    p = findItem(product, *list);
    //Check if an element with the same productId exists in the list
    if( p != LNULL){
        user = getItem(p, *list);
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               user.productId, user.seller, printCategory(user.productCategory), user.productPrice, user.bidCounter );
        //An item with the introduced productId has been found
        deleteAtPosition(p, list);
    }
    else {
        //An error occurred, there was no element with that productId in the list
        printf("+ Error: Delete not possible\n");
    }
}

void bid(char *product, char *bidder, char *bid_price, tList *list){

    tPosL p;
    tItemL bid_product;

    //Locate the product
    p = findItem(product, *list);

    //There is a product with that product identifier
    if( p != LNULL) {
        //We save on bid_product the found item
        bid_product = getItem(p, *list);

        //We check that the bidder is not the same person as the seller and that the product price is smaller than the bid
        if( strcmp(bidder, bid_product.seller) != 0 && bid_product.productPrice < atof(bid_price)){

            //We update the product's price
            bid_product.productPrice = atof(bid_price);
            //We increment its bid counter by 1
            bid_product.bidCounter += 1;
            updateItem(bid_product, p, list);

            //* Bid: product product2 seller user1 category painting price 125.00 bids 1
            printf("* Bid: product %s seller %s category %s price %.2f bids %d\n", bid_product.productId, bid_product.seller, printCategory(bid_product.productCategory),bid_product.productPrice, bid_product.bidCounter);
        } else{
            printf("+ Error: Bid not possible\n");
        }
    }
    else {
        //An error occurred, there was already an element with that productId in the list
        printf("+ Error: Bid not possible\n");
    }
}



void stats(tList * list){
//Goal: Display de statistics of the products on the list
    tPosL pos;
    tItemL product;

    int booksProducts = 0, paintingProducts = 0;
    float booksSum = 0, paintingSum = 0;
    float avgPBooks, avgPPaintings;

    // When the List is empty, there is nothing to show.
    if(isEmptyList(*list) == true ){
        printf("+ Error: Stats not possible\n");
        return;

    //Otherwise we iterate through the list.
    } else if(!isEmptyList(*list)) {
        pos = first(*list);
        do {
            product = getItem(pos, *list);

            //When the product has books category, we add 1 to booksProducts, we add the price to booksSum.
            if (product.productCategory == 0) {
                booksProducts++;
                booksSum += product.productPrice;
                //And the same thing for the Painting Category
            } else if (product.productCategory == 1) {
                paintingProducts++;
                paintingSum += product.productPrice;
            } else {
                printf("+ Error: Stats not possible, it does not exist a category with that name\n");
            }

            //We print the Product's info
            printf("Product %s seller %s category %s price %.2f bids %d\n",
                   product.productId, product.seller, printCategory(product.productCategory), product.productPrice,
                   product.bidCounter);

            pos = next(pos, *list);
        } while (pos != LNULL);

        //Once we finished iterating through the list we calculate the average price of each category.
        if(booksSum == 0){
            avgPBooks = 0;
        } else {
            avgPBooks = (float)booksSum / (float)booksProducts;
        }
        if(paintingSum == 0){
            avgPPaintings = 0;
        } else {
            avgPPaintings = (float)paintingSum / (float)paintingProducts;
        }

        // We print the table
        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", booksProducts, booksSum, avgPBooks);
        printf("Painting  %8d %8.2f %8.2f\n", paintingProducts, paintingSum, avgPPaintings);

    }
}


void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    //Creates an empty list
    tList list;
    createEmptyList(&list);

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}






