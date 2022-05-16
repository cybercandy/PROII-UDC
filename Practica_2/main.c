/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * DATE: 01 / 04 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"

#define MAX_BUFFER 255

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
 * Goal: Returns a new product based on the parameters passed, its bid counter initialized to 0 and creating an empty bid stack
 * Input: product: The id of the product
 *        seller: The product's user/seller
 *        category: The product's category
 *        price: The product's price
 * Output: A new product with all the information given
 * */
void new(char *product, char *seller, char *category, char *price, tList *list);
/*
 * Goal: Adds a new product to the specified list
 * Input: product: The id of the product
 *        seller: The product's user/seller
 *        category: The product's category
 *        price: The product's price
 *        list: List to be modified
 * Output: The modified list with the new product inserted
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 * */

void delete_bid_stack(tStack *stack);
/*
 * Goal: Removes all the elements of a given stack
 * Input: stack: Stack to be modified
 * Output: An empty stack
 * Precondition: The stack has to be initialised
 * */

void delete(char* product, tList * list);
/*
 * Goal: Removes the given product from the list and its associated bids
 * Input: product: The id of the product ot be removed
 *        list: List to be modified
 * Output: The modified list without the product if it existed
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 */

void stats(tList list);
/*
 * Goal: Displays the whole current list of products and statistics of those products, showing for each category the number of products in it,
 * the sum of their prices and their average price. It also shows the product for which its current highest bid has the largest increase.
 * Input: list: List to be handled
 * Precondition: The list has to be initialized
 * */

void bid(char*product, char*seller, char*bid_price, tList *list);
/*
 * Goal: Adds the new bid to the stack, only if it exceeds its current highest bid, or the original price in case that there are no bids.
 * Input: product: Product's id
 *        seller: User that bids on the product
 *        bid_price: Price user bids on the product
 *        list: List to be modified
 * Output: The modified list with the product's price changed if it fulfilled the specifications and its bid counter incremented.
 * Precondition: The list has to be initialized
 * */

void award(char*product, tList*list);
/*
 * Goal: It removes the sold product from the list, only if it has at least one element in its stack, and empties its bid stack
 * Input: product: Product's id that is going to be removed
 *        list: List to be modified
 * Output: The modified list without the product
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 */

void withdraw(char* product, char*user,tList * list);
/*
 * Goal: Deletes the current highest bid from the specified product only if the current highest bidder is the given user, decreasing its bid counter
 * Input: product: Product's id to be checked
 *        user: User that wants to withdraw its bid
 *        list: List to be handled
 * Output: The bid stack without the previous top bid
 * Precondition: The list has to be initialized
 * Postcondition: The top position of the bid stack may have varied
 */

void removeItem(tList * list);
/*
 * Goal: Removes all the products from the list that have no bids
 * Input: list: List to be modified
 * Output: The list without the elements that fulfilled the specification
 * Precondition: The list has to be initialized
 * Postcondition: The positions of the elements in the subsequent list may have varied
 */

void readTasks(char *filename);
/*
 * Goal: It process the input text file and initialises the product's list
 * Input: filename: Text file to be handled
 * Output: An empty product's list
 */

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list);
/*
 * Goal: Process the given information and decides which action to take bassed on it
 * Input: commandNumber: Number of the operation
 *        command: Operation to be made
 *        param1: Product's id
 *        param2: Bidder or seller
 *        param3: Product's price or product's category
 *        param4: Product's price
 *        list: List to be handled
 * Precondition: The list has to be initialized
 */

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {

    switch (command) {
        case 'N':
            //01 N product3 user1  painting 150.00
            printf("********************\n");
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, list);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(*list);
            break;
        case 'B':
            printf("********************\n");
            //06 B: product product2 bidder user2 price 125.00
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(param1, param2, param3, list);
            break;
        case 'D':
            //08 D: product product2
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, list);
            break;
        case 'A':
            //08 A product2
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            award(param1, list);
            break;
        case 'W':
            //08 W product2 user2
            printf("********************\n");
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            withdraw(param1, param2,list);
            break;
        case 'R':
            //12 R
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            removeItem(list);
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

    //Product that is going to be returned with all the information passed as parameters.
    tItemL new_product;

    strcpy(new_product.productId, product);
    strcpy(new_product.seller, seller);
    new_product.productCategory = getCategory(category);
    new_product.productPrice = atof(price);

    //Initialized bid counter to 0
    new_product.bidCounter = 0;

    //Creates an empty bid stack
    tStack stack;
    new_product.bidStack = createEmptyStack(&stack);

    return new_product;
}

void new(char *product, char *seller, char *category, char *price, tList *list){

    //Product to be added to the list if possible
    tItemL new_product = newProduct(product, seller, category, price);

    //We check the product is not already in the list
    if(findItem(new_product.productId, *list) == LNULL){
        //We check if it can be inserted
        if(insertItem(new_product, list) == false){
            printf("+ Error: New not possible\n");
        } else {
            printf("* New: product %s seller %s category %s price %.2f\n",
                   new_product.productId, new_product.seller, printCategory(new_product.productCategory), new_product.productPrice);
        }
    } else {
        printf("+ Error: New not possible\n");
    }
}

void bid(char*product, char*seller, char*bid_price, tList *list) {

    tPosL pos; //Auxiliary position variable
    tItemL bid_product; //Auxiliary product variable to check if the product fulfills the conditions
    tItemS added_bid; // Bid product that is going to be added to the stack

    //Product is located
    pos = findItem(product, *list);

    //If it exists we check the other conditions
    if (pos != LNULL) {
        //We save on bid_product the found item
        bid_product = getItem(pos, *list);

        //We check if the bidder is a different user than the seller and
        //if the stack is not empty, the bid price has to be higher than the top bid of the stack's price
        //if it is empty the bid price has to be higher than the original price
        if(strcmp(bid_product.seller, seller) != 0 && ((!isEmptyStack(bid_product.bidStack) &&
            peek(bid_product.bidStack).productPrice < atof(bid_price)) ||
            (isEmptyStack(bid_product.bidStack) && bid_product.productPrice < atof(bid_price))) ){

            //We save the bidder and the bid price
            strcpy(added_bid.bidder, seller);
            added_bid.productPrice = atof(bid_price);

            //We add the bid to the stack, only if push returns true
            if(push(added_bid, &bid_product.bidStack) == true){
                //We update its bid counter
                bid_product.bidCounter += 1;
                updateItem(bid_product, pos, list);

                printf("* Bid: product %s bidder %s category %s price %s bids %d\n",
                       bid_product.productId, seller, printCategory(bid_product.productCategory),
                       bid_price, bid_product.bidCounter);
            } else{
                //We could add to the stack
                printf("+ Error: Bid not possible\n");}
        }else {
            //Some condition was not fulfill
            printf("+ Error: Bid not possible\n");}
    } else {
        //The product does not exist
        printf("+ Error: Bid not possible\n");}
}


void delete_bid_stack(tStack *stack){

    while(isEmptyStack(*stack)){
        pop(stack);
    }
}

void delete(char* product, tList * list){
    tPosL pos; //Stores the position of the element to be deleted
    tItemL item; //Stores the product's info

    pos = findItem(product, *list);
    //Check if an element with the same productId exists in the list
    if( pos != LNULL){
        item = getItem(pos, *list);
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, printCategory(item.productCategory), item.productPrice, item.bidCounter);

        //Checks if the bid stack is empty, and if its not it deletes all of its elements
        delete_bid_stack(&item.bidStack);
        //An item with the introduced productId has been found
        deleteAtPosition(pos, list);

    } else{
        //An error occurred, there was no element with that productId in the list
        printf("+ Error: Delete not possible\n");
    }
}

void award(char*product, tList*list){
    tPosL pos; //Auxiliary position variable
    tItemL item; //Auxiliary item variable
    tItemS current_top; //Stores the current top

    pos = findItem(product, *list);
    if(pos != LNULL){
        item = getItem(pos, *list);
        //We check its bid stack
        if(!isEmptyStack(item.bidStack)){
            //Store the contents of the element in the top of the stack, to access its price later
            current_top = peek(item.bidStack);

             printf("* Award: product %s bidder %s category %s price %.2f\n", item.productId, current_top.bidder,
                    printCategory(item.productCategory), current_top.productPrice);

             //We delete its bid stack
             delete_bid_stack(&item.bidStack);

             //We remove the product from the list
             deleteAtPosition(pos, list);
        }else{
            //The bid stack of the product is empty
            printf("+ Error: Award not possible\n");
        }
    }else{
        //There was not an element with that productId on the list
        printf("+ Error: Award not possible\n");
    }
}

void stats(tList list){

    tPosL pos; //Auxiliary position to traverse the list
    tItemL product, top_highest_product; //Product -> Stores the current product and top_highest_product -> stores the product with the largest increase
    tItemS topBidder, top_highest_bid; //topBidder -> Stores the top bidder of each product and top_highest_bid -> stores the bid with the largest increase
    float current_increase, increase = 0; //current_increase -> Stores the current increase between the product and its top bidder and increase -> the current maximum increase

    int booksProducts = 0, paintingProducts = 0; //Store the number of products for each category
    float booksSum = 0, paintingSum = 0;  //Store the sum of the prices of products for each category
    float avgPBooks, avgPPaintings; //Store the average price of products for each category

    //When the list is empty no statistics are shown
    if(isEmptyList(list) == true) {
        printf("+ Error: Stats not possible\n");
        return;

    //Otherwise we traverse the list
    } else if(!isEmptyList(list)) {

        pos = first(list);
        do{
            //We store the current item in product
            product = getItem(pos, list);
            //We check to which category it belongs to, 0 for books and 1 for paintings
            if(product.productCategory == 0){
                booksProducts++; //Increase the number of books
                booksSum += product.productPrice; //Sum its price
            } else if(product.productCategory == 1){
                paintingProducts++; //Increase the number of paintings
                paintingSum += product.productPrice; //Sum its price
            } else{
                //There was a product on the list that had a non valid category
                printf("+ Error: Stats not possible\n");
                continue;
            }

            if(isEmptyStack(product.bidStack)){
                printf("Product %s seller %s category %s price %.2f. No bids\n",
                       product.productId, product.seller, printCategory(product.productCategory), product.productPrice);
            } else{
                //We take the top bidder of each product and store it in the topBidder
                topBidder = peek(product.bidStack);
                //We print the Product's info
                printf("Product %s seller %s category %s price %.2f bids %d top bidder %s\n",
                       product.productId, product.seller, printCategory(product.productCategory), product.productPrice,
                       product.bidCounter, topBidder.bidder);

                //We check the increase between the topBidder and the product
                current_increase = (topBidder.productPrice/product.productPrice)-1;
                //If the current increase is bigger than the maximum increase, current increase becomes the new max
                if(current_increase > increase){
                    increase = current_increase;
                    //We store the values of the product and the top bidder
                    top_highest_product = product;
                    top_highest_bid = topBidder;
                }

            }
            pos = next(pos, list);
        } while( pos != LNULL);

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

        //We check if the increase variable has changed, meaning that there are bids
        if(increase != 0){
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%s\n",
                   top_highest_product.productId, top_highest_product.seller, printCategory(top_highest_product.productCategory),
                   top_highest_product.productPrice, top_highest_bid.bidder, top_highest_bid.productPrice, increase*100, "%");
        } else{
            printf("Top bid not possible\n");
        }

    }
}

void withdraw(char* product, char*user,tList * list){
    tPosL pos; //Stores the position of the product
    tItemL item; //Stores the information of the product
    tItemS top; //Stores the item that is at the top of the bid stack

    pos = findItem(product, *list);
    if(pos!= LNULL){
        item = getItem(pos, *list);
        if(!isEmptyStack(item.bidStack)){
            top = peek(item.bidStack);
            if( strcmp(top.bidder, user) == 0){
                printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n",
                       item.productId, top.bidder, printCategory(item.productCategory), top.productPrice, item.bidCounter);
                //Decrease its bid counter
                item.bidCounter--;
                //We delete the highest bid
                pop(&item.bidStack);
                updateItem(item, pos, list);
            }else{
                //The top bidder is not the same as the input user
                printf("+ Error: Withdraw not possible\n");}
        }else{
            //The bid stack is empty
            printf("+ Error: Withdraw not possible\n");}
    }else{
        //There is no product with such identifier
        printf("+ Error: Withdraw not possible\n");
    }
}

void removeItem(tList*list){

    tPosL pos, aux_pos = LNULL; //Auxiliary positions to traverse the list, aux_pos is initialized to NULL, and pos to the first element of the list
    tItemL product; //Stores the current product
    int no_bids=0; //Stores the number of products that have no bids

    //We start in the first element of the list
    pos = first(*list);
    do{
        //We return the current product
        product = getItem(pos, *list);

        if(product.bidCounter==0 && isEmptyStack(product.bidStack)){
            printf("Removing product %s seller %s category %s price %.2f bids %d\n", product.productId, product.seller,
               printCategory(product.productCategory), product.productPrice, product.bidCounter);

            //We don't delete its bid stack, because if there are no bids, there is no bid stack
            deleteAtPosition(pos, list);
            no_bids++; //We increase the value of the products that have no bids

            //In case there are no more elements in the list, we exit the loop
            if(isEmptyList(*list)){
                break;}
        }else{
            aux_pos = pos;
        }
        //When aux_pos is NULL, pos will also point to NULL
        if(aux_pos==LNULL){
            //We make it point to the first element of the list again
            pos =first(*list);
        }else{
            //When pos still has a valid position, because no product was deleted, we continue to the next element of the list
            pos = next(aux_pos, *list);
        }

    } while(pos!=LNULL);

    //If after checking the whole list, there were no elements without bids, we give an error
    if(no_bids == 0){
        printf("+ Error: Remove not possible\n");
    }
}


void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    //Initialize the Product List
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






