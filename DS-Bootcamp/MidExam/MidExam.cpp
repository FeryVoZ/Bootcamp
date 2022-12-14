#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>

const int maxBuckets = 999;

void logoWarteg(){
    FILE *fpLW = fopen("WartegLogo.txt", "r");
    char logo;
    while(!feof(fpLW)){
        logo=getc(fpLW);
		printf("%c", logo);
    }
    fclose(fpLW);
}

void logoExit(){
    FILE *fpLE = fopen("ExitLogo.txt", "r");
    char logo;
    while(!feof(fpLE)){
        logo=getc(fpLE);
		printf("%c", logo);
    }
    fclose(fpLE);
}

struct Dish{
    char dish[255];
    long long int prc, quantity;
    Dish *next, *prev;
}*head=NULL, *tail=NULL;

Dish *createDish(char dish[], long long int prc, long long int quantity){
    Dish *newDish = (Dish*)malloc(sizeof(Dish));
    strcpy(newDish->dish,dish);
    newDish->prc=prc;
    newDish->quantity=quantity;
    newDish->next = NULL;
    newDish->prev = NULL;
    return newDish;
}


int menuCounter=0;

void insertLL(char dish[], long long int prc, long long int quantity){
    Dish *newDish = createDish(dish, prc, quantity);
    if(!head) head=tail=newDish;
    else if(head->quantity<=newDish->quantity){
        newDish->next=head;
        head->prev=newDish;
        head=newDish;
    }
    else if(tail->quantity>=newDish->quantity){
        tail->next=newDish;
        newDish->prev=tail;
        tail=newDish;
    }
    else{
        Dish *temp = head;
        while(temp->next->quantity>=newDish->quantity){
            temp=temp->next;
        }
        newDish->next=temp->next;
        newDish->prev=temp;
        temp->next->prev=newDish;
        temp->next=newDish;
    }
    menuCounter++;
}

void removeLL(char dish[]){
    bool  cek = true;
    if(!head){
        puts("There are no dishes!");
        return;
    }
    else if(strcmp(head->dish,dish)==0){
        Dish *newHead = head->next;
        head->next=NULL;
        free(head);
        head = newHead;
        puts("The dish has been removed!");
    }
    else if(strcmp(tail->dish, dish)==0){
        Dish *newTail = tail->prev;
        tail->prev=NULL;
        free(tail);
        tail = newTail;
        puts("The dish has been removed!");
    }
    else{
        Dish *temp = head;
        while(strcmp(temp->dish, dish)!=0){
            if(temp==tail && strcmp(temp->dish, dish)!=0){
                cek = false;
                break;
            }
            temp = temp->next;
        }
        if(cek==false){
            puts("The dish does not exist!");
        }
        else{
           temp->next->prev=temp->prev;
           temp->prev->next=temp->next;
           temp->next = temp->prev = NULL;
           free(temp); 
           puts("The dish has been removed!");
        }
    }
}

char foundDish[255];
long long int foundPrc=0, foundQty=0;

int searchMenu(char dish[]){
    if(!head){
        return -1;
    }
    else{
        Dish *curr = head;
        while(curr && strcmp(curr->dish,dish)!=0){
            if(curr==tail&&strcmp(curr->dish,dish)!=0){
                return -2;
            }
            curr=curr->next;
        }
        strcpy(foundDish,curr->dish);
        foundPrc = curr->prc;
        foundQty = curr->quantity;
        return 1;
    }
}

void printLL(){
    if(!head){
        puts("There are no dishes!");
        return;
    }
    else{
        int i=0;
        Dish *curr = head;
        puts(" =================================================");
        puts("|                   Bude's Menu                   |");
        puts(" =================================================");
        puts("| No. | Name           | Quantity     | Price     |");
        puts(" =================================================");
        while(curr){
            printf("| %d.  | %-13s  | %03lld          | Rp%-7lld |\n", i+1, curr->dish, curr->quantity, curr->prc);
            i++;
            curr=curr->next;
        }
        puts(" =================================================");
    }
}

struct Customers{
    char name[255];
    Dish *foodOrder;
}*table[maxBuckets];

Customers *createCust(char name[]){
    Customers *newCust = (Customers*)malloc(sizeof(Customers));
    strcpy(newCust->name, name);
    newCust->foodOrder=NULL;
    return newCust;
}

unsigned long djb2(char name[]){
    unsigned long key = 5381;
    for(int i=0; name[i]!='\0'; i++){
        int ascii = int(name[i]);
        key = (key << 5) + key + ascii;
    }
    return key%maxBuckets;
}

void linearProbing(int idx, char name[]){
    Customers *newCust = createCust(name);
    for(int i=(idx+1)%maxBuckets; i!=idx; i=(i+1)%maxBuckets){
        if(!table[i]){
            table[i]=newCust;
            return;
        }
    }
}

void insertCust(char name[]){
    Customers *newCust = createCust(name);
    int idx = djb2(name);
    if(!table[idx]){
        table[idx]=newCust;
    }
    else{
        linearProbing(idx, name);
    }
}

int searchCust(char name[]){
    int idx = djb2(name);
    
    if(!table[idx]){
        return -1;
    }
    else {
        for(int i=(idx+1)%maxBuckets; i!=idx; i=(i+1)%maxBuckets){
            if(strcmp(table[i]->name, name)==0){
                idx=i;
                break;
            }
        }
        return idx;
    }
}

void *insertOrder(int idx, char name[], long long int prc, long long int qty){
    Dish  *newOrder = createDish(name, prc, qty);
    if(!table[idx]->foodOrder){
        table[idx]->foodOrder=newOrder;
    }
    else{
        Dish *curr = table[idx]->foodOrder;
        while(curr->next){
            curr=curr->next;
        }
        curr->next=newOrder;
        newOrder->prev=curr;
    }
}

void removeCust(int idx){
    table[idx]->foodOrder=NULL;
    free(table[idx]);
}

void removeOrder(int idx){
    Dish *curr = table[idx]->foodOrder;
    while(curr->next){
        free(curr);
        curr = curr->next;
    }
}

void cls(){
    system("clear");
}

void showInfo() {
    struct utsname info; 
    time_t currentTime;
    struct tm *localTime;

    uname(&info); 
    time(&currentTime);

    localTime = localtime(&currentTime);

    char dateTimeString[100];
    strftime(dateTimeString, 100, "%A %B %d %I:%M:%S %Y", localTime);
    printf("System: %s\n", info.sysname);
    printf("The current date and time is: %s\n", dateTimeString);
}

void addDish(){
    cls();
    bool cek = true;
    char dish[255];
    long long int price, quantity, len=0;
    do{
        cek=true;
        int trueCounter=0, falseCounter=0;
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", dish);
        getchar();
        len=strlen(dish);
        for(int i=0; i<len; i++){
            if(dish[i]>='a'&&dish[i]<='z'){ 
                trueCounter++;
            }
            else if(dish[i]==' '){
                trueCounter++;
            }
            else{
                falseCounter++;
            }
        }
        if(falseCounter!=0) cek=false;
    }while(cek==false);
    
    do{
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%lld", &price);
        getchar();
    }while(price<1000||price>50000);

    do{
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%lld", &quantity);
        getchar();
    }while(quantity<1||quantity>999);

    insertLL(dish, price, quantity);
    puts("The dish has been added!");
    printf("Press enter to continue...");
    getchar();
}

void removeDish(){
    char rmDish[255];
    int len=0, trueCounter=0, falseCounter=0;
    bool cek=true;
    cls();
    printLL();
    puts("");
    do{
        cek = true;
        trueCounter=0;
        falseCounter=0;
        printf("Insert dish's name to be deleted [Lowercase letters]: ");
        scanf("%[^\n]", rmDish);
        getchar();
        len = strlen(rmDish);
        for(int i=0; i<len; i++){
            if(rmDish[i]>='a'&&rmDish[i]<='z'){ 
                trueCounter++;
            }
            else if(rmDish[i]==' '){
                trueCounter++;
            }
            else{
                falseCounter++;
            }
        }
        if(falseCounter>0) cek=false;
    }while(cek==false);
    removeLL(rmDish);
    printf("Press enter to continue...");
    getchar();
}

void addCustomers(){
    char name[255];
    int len=0;
    bool cek=true;
    do{
        int trueCounter=0, falseCounter=0;
        cls();
        cek=true;
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", name);
        getchar();
        len=strlen(name);
        for(int i=0; i<len; i++){
            if(name[i]>='a'&&name[i]<='z'){
                trueCounter++;
            }
            else if(name[i]>='A'&&name[i]<='Z'){
                trueCounter++;
            }
            else{
                falseCounter++;
            }
        }
        if(falseCounter>0) cek=false;
    }while(cek==false);
    insertCust(name);
    puts("Customer has been added!");
    printf("Press enter to continue...");
    getchar();
}

void searchCostumer(){
    char srcName[255];
    bool cek=true;
    int len=0;
    do{
        cls();
        int trueCounter=0, falseCounter=0;
        cek=true;
        printf("Insert the customer's name to be searched [Without space]: ");
        scanf("%s", srcName);
        getchar();
        len=strlen(srcName);
        for(int i=0; i<len; i++){
            if(srcName[i]>='a'&&srcName[i]<='z'){
                trueCounter++;
            }
            else if(srcName[i]>='A'&&srcName[i]<='Z'){
                trueCounter++;
            }
            else{
                falseCounter++;
            }
        }
        if(falseCounter>0) cek=false;
    }while(cek==false);
    int srcResult = searchCust(srcName);
    if(srcResult==-1) printf("%s is not present.\n", srcName);
    else printf("%s's customer number is %d\n", srcName, srcResult+1); 
    printf("Press enter to continue...");
    getchar();
}

void viewWarteg(){
    puts("Customer's List");
    for(int i=0; i<999; i++){
        if(table[i]){
            printf("%d. %s\n", i+1, table[i]->name);
        }
    }
    printf("Press enter to continue...");
    getchar();
}

void order(){
    char name[255], dish[255];
    int manyOrder, qty;
    bool cek=true;
    int srcCustResult = 0;
    if(!head) {
        puts("The customer can't order because the menu is empty!");
        puts("Please add the dish first");
        printf("Press enter to continue...");
        getchar();
    }
    do{
        int trueCounter=0, falseCounter=0, len=0;
        cek=true;
        printf("Insert the customer's name: ");
        scanf("%[^\n]", name);
        getchar();
        len=strlen(name);
        for(int i=0; i<len; i++){
            if(name[i]>='a'&&name[i]<='z'){
                trueCounter++;
            }
            else if(name[i]>='A'&&name[i]<='Z'){
                trueCounter++;
            }
            else{
                falseCounter++;
            }
        }
        if(falseCounter>0){
            printf("Name only consist of lower and uppercase letters");
            getchar();
            cek=false;
        }
        srcCustResult = searchCust(name);
        if(srcCustResult==-1){
            printf("Customer is not present");
            getchar();
            cek=false;
        }
    }while(cek==false);

    do{
        printf("Insert the amount of dish: ");
        scanf("%d", &manyOrder);
        getchar();
        if(manyOrder>menuCounter){
            printf("Menu available only %d types\n", menuCounter);
            puts("Please input below or equal to the number of the menu");
            printf("Press enter to continue..."); getchar();
        }
    }while(manyOrder>menuCounter);

    for(int i=1; i<=manyOrder; i++){
        do{
            cek=true;
            printf("[%d] ", i);
            scanf("%[^\n] x%d", &dish, &qty);
            getchar();
            int srcResult = searchMenu(dish);
            if(srcResult==-2){
                puts("This menu is not exist!");
                cek=false;
                printf("Press enter to continue...");
                getchar();
            }
            if(qty>foundQty){
                puts("Sorry, our quantity of this food is not enough for your order");
                printf("Press enter to continue...");
                getchar();
            }
        }while(cek==false||qty>foundQty);
        insertOrder(srcCustResult, dish, foundPrc*qty, qty);
    }
    
    puts("Order success!");
    printf("Press enter to continue...");
    getchar();
}

void payment(){
    int idx;
    printf("Insert the customer's index: ");
    scanf("%d", &idx);
    if(!table[idx-1]){
        printf("The %d customer's index is not exist!\n");
        printf("Press enter to continue...");
        getchar();
    }
    else{
        long long int sumPrc=0;
        int i=1;
        printf("%s\n", table[idx-1]->name);
        Dish *curr = table[idx-1]->foodOrder;
        while(curr->next){
            printf("[%d] %s x%d\n", i, curr->dish, curr->quantity);
            sumPrc+=curr->prc;
            curr=curr->next;
            i++;
        }
        printf("Total: Rp%lld\n", sumPrc);
        printf("Press enter to continue...");
        removeOrder(idx-1);
        removeCust(idx-1);
        getchar();
    }
}

void Exit(){
    cls();
    logoExit();
    getchar();
    exit(0);
}

void mainMenu(){
    int inputMainMenu;
    while(true){
        cls();
        logoWarteg();
        puts("");
        showInfo();
        puts("1. Add Dish");
        puts("2. Remove Dish");
        puts("3. Add Customer");
        puts("4. Search Customer");
        puts("5. View Warteg");
        puts("6. Order");
        puts("7. Payment");
        puts("8. Exit Warteg");
        do{
            printf(">> ");
            scanf("%d", &inputMainMenu);
            getchar();
        }while(inputMainMenu<1||inputMainMenu>8);
        switch(inputMainMenu){
            case 1:
                addDish();
                break;
            case 2:
                removeDish();
                break;
            case 3:
                addCustomers();
                break;
            case 4:
                searchCostumer();
                break;
            case 5:
                viewWarteg();
                break;
            case 6:
                order();
                break;
            case 7:
            payment();
                break;
            case 8:
                Exit();
                break;
        }
    };
}

int main(){
    mainMenu();
    return 0;
}