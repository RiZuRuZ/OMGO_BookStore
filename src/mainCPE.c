#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char ID[10];
    char name[50];
    int age;
    int gender; // 0: Female, 1: Male
    char email[50];
    char phone[20];
    float money;
    char rentBook[200];
    char rentDate[20];
    char returnDate[20];
    char history[1000];
} customer;

typedef struct {
    char ID[10];
    char title[50];
    char author[50];
    char type[20];
    char genre[20];
    float price;
    int stock;
    float rentPrice;
    int rentStock;
} libraryowner;

typedef struct {
    char arr[10][50];
    int count;
} split;


int splitString(char *str, char arr[10][50]) {
    int count = 0;
    char *token = strtok(str, "&");
    while (token != NULL && count < 10) {
        strcpy(arr[count++], token);
        token = strtok(NULL, "&");
    }
    return count;
}

char* search_bookname_by_id(libraryowner library[50], char book_id[10]) {
    for (int i = 0; i < 50; i++) {
        if (library[i].ID[0] == '\0') break; // ไม่มีข้อมูลแล้ว
        if (strcmp(library[i].ID, book_id) == 0) {
            return library[i].title;
        }
    }
    return NULL; // ไม่พบหนังสือ
}

//ยังไม่ได้ลองอาจจะ bug
char* search_user_by_id(customer Customers[50], char customer_id[10]) {
    for (int i = 0; i < 50; i++) {
        if (Customers[i].ID[0] == '\0') break; // ไม่มีข้อมูลแล้ว
        if (strcmp(Customers[i].ID, customer_id) == 0) {
            return Customers[i].name;
        }
    }
    return NULL; // ไม่พบuser
}

void show_book(libraryowner library[50], int k){ //k is range
    for(int i = 0; i < k; i++){
        printf("BOOK %s: %s, author %s, type %s, genre %s, price %.2f, stock %d, rentPrice %.2f, rentStock %d\n",
                library[i].ID, library[i].title, library[i].author, library[i].type,
                library[i].genre, library[i].price, library[i].stock,
                library[i].rentPrice, library[i].rentStock);
    }
}

void show_customers(customer Customers[50], int k, split splitrent[50], split splithistory[50], libraryowner library[50]){ //k is range
    int i,j;
    for(i = 0; i < k; i++){
        printf("Customer %s: %s, age %d, gender %d, email %s, phone %s, money %.2f\nRentBook: %s\nRentDate: %s, ReturnDate: %s\nHistory: %s\n",
            Customers[i].ID, Customers[i].name, Customers[i].age, Customers[i].gender,
            Customers[i].email, Customers[i].phone, Customers[i].money,
            Customers[i].rentBook, Customers[i].rentDate, Customers[i].returnDate, Customers[i].history);

        // แสดงผลลัพธ์
        for (j = 0; j < splitrent[i].count; j++) {
            printf("RentBook[%d] = %s = %s\n", j, splitrent[i].arr[j], search_bookname_by_id(library, splitrent[i].arr[j]));
        }
        for (j = 0; j < splithistory[i].count; j++) {
            printf("History[%d] = %s = %s\n", j, splithistory[i].arr[j], search_bookname_by_id(library, splithistory[i].arr[j]));
        }
        printf("\n");
    }
}
// อ่านข้อมูลจากไฟล์(OWNER) ***ห้ามยุ่ง***
int read_library_file(FILE *owner, libraryowner library[]) {
    int i = 0;
    while (fscanf(owner, "%s %s %s %s %s %f %d %f %d",
        library[i].ID,
        library[i].title,
        library[i].author,
        library[i].type,
        library[i].genre,
        &library[i].price,
        &library[i].stock,
        &library[i].rentPrice,
        &library[i].rentStock) != EOF) {
        i++;
    }
    return i; // คืนค่าจำนวนหนังสือที่อ่านได้
}

// อ่านข้อมูลจากไฟล์(USER) ***ห้ามยุ่ง***
int read_customer_file(FILE *user, customer Customers[], split splitrent[], split splithistory[]) {
    int i = 0;
    char tempRentBook[200];
    char tempHistory[1000];

    while (fscanf(user, "%s %s %d %d %s %s %f %s %s %s %s",
        Customers[i].ID,
        Customers[i].name,
        &Customers[i].age,
        &Customers[i].gender,
        Customers[i].email,
        Customers[i].phone,
        &Customers[i].money,
        Customers[i].rentBook,
        Customers[i].rentDate,
        Customers[i].returnDate,
        Customers[i].history) != EOF) {

        // แยก string ด้วย comma
        strcpy(tempRentBook, Customers[i].rentBook);
        splitrent[i].count = splitString(tempRentBook, splitrent[i].arr);

        strcpy(tempHistory, Customers[i].history);
        splithistory[i].count = splitString(tempHistory, splithistory[i].arr);

        i++;
    }
    return i; // คืนค่าจำนวนลูกค้าที่อ่านได้
}

int main() {
    FILE *owner = fopen("ownerCPE.txt", "r");
    FILE *user = fopen("userCPE.txt", "r");
    if (!owner || !user) {
        printf("Error opening file!\n");
        return 1;
    }

    libraryowner library[50];
    customer Customers[50];
    split splitrent[50], splithistory[50];

    //เรียกใช้ฟังก์ชันอ่านไฟล์
    int range_library = read_library_file(owner, library);
    int range_customers = read_customer_file(user, Customers, splitrent, splithistory);

    //printf("Read %d books and %d customers successfully.\n", range_library, range_customers);


    ///////////////////////main///////////////////////
    //login owner user 
    int login = -1;
    printf("Login as (0 = owner, 1 = user): ");
    scanf("%d", &login);

    //login
    //selection
    int selection = -1;
    while (selection != 0) {
        if (login == 0) {  // Owner menu
            printf("\n--- Owner Menu ---\n");
            printf("1. Show book\n");
            printf("2. Show customer\n");
            printf("3. System rent\n");
            printf("4. Change\n");
            printf("5. Income\n");
            printf("0. Exit\n");
        } else {  // User menu
            printf("\n--- User Menu ---\n");
            printf("1. History rent\n");
            printf("2. Money\n");
            printf("3. Show book\n");
            printf("4. Rent\n");
            printf("0. Exit\n");
        }

        printf("Selection: ");
        scanf("%d", &selection);

        if (login == 0) {
            switch (selection) {
                case 1: printf("Show book\n"); show_book(library,range_library); break;
                case 2: printf("Show customer\n"); show_customers(Customers, range_customers, splitrent, splithistory, library); break;
                case 3: printf("System rent\n"); break;
                case 4:
                    printf("Change Mode:\n");
                    printf("1. Add Book\n");
                    printf("2. Remove Book\n");
                    printf("3. Edit Book\n");
                    int sub;
                    scanf("%d", &sub);
                    if(sub == 1) { /* Add book function */ }
                    else if(sub == 2) { /* Remove book function */ }
                    else if(sub == 3) { /* Edit book function */ }
                    else printf("Invalid option.\n");
                    break;
                case 5: printf("Income\n"); break;
                case 0: printf("Exit owner mode.\n"); break;
                default: printf("Invalid option! Please enter 0–5.\n");
            }
        } else {
            switch (selection) {
                case 1: printf("History rent\n"); break;
                case 2: printf("Money\n"); break;
                case 3: printf("Show book\n"); show_book(library,range_library); break;
                case 4: printf("Rent\n"); break;
                case 0: printf("Exit user mode.\n"); break;
                default: printf("Invalid option! Please enter 0–4.\n");
            }
        }
    }

    printf("END of program");
    fclose(user);
    fclose(owner);
    return 0;
}
