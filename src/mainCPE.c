#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

typedef struct {
    char ID[10];
    char pass[30];
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

typedef struct {
    int day;
    int month;
    int year;
} DateInfo;

// typedef struct {
//     int day;
//     int month;
//     int year;
//     float income;
//     float total;
// } IncomeData;

typedef struct{
    float income;
    float total;
    char date[11];
}storeIncome;

void date(DateInfo *today) {
    setlocale(LC_ALL, "th_TH.UTF-8");

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    today->day = tm_info->tm_mday;
    today->month = tm_info->tm_mon + 1;
    today->year = tm_info->tm_year + 1900;
}

int userSignUp(customer Customers[], int range_customers) {
    if (range_customers >= 50) {
        printf("User database is full!\n");
        return range_customers;
    }

    customer newUser;

    // สร้าง ID อัตโนมัติ
    sprintf(newUser.ID, "C%03d", range_customers + 1);
    printf("Your user ID: %s\n", newUser.ID);

    printf("Enter name: ");
    scanf(" %49[^\n]", newUser.name);

    printf("Enter age: ");
    scanf("%d", &newUser.age);

    printf("Enter gender (0=Female, 1=Male): ");
    scanf("%d", &newUser.gender);

    printf("Enter email: ");
    scanf("%s", newUser.email);

    printf("Enter phone: ");
    scanf("%s", newUser.phone);

    printf("Set your password: ");
    scanf("%s", newUser.pass);

    newUser.money = 0.0f;
    strcpy(newUser.rentBook, "");
    strcpy(newUser.rentDate, "");
    strcpy(newUser.returnDate, "");
    strcpy(newUser.history, "");

    // เพิ่ม user ลง array
    Customers[range_customers] = newUser;
    range_customers++;

    // บันทึกลงไฟล์
    FILE *file = fopen("userCPE.txt", "a");
    if (file) {
        fprintf(file, "%s %s %s %d %d %s %s %.2f %s %s %s %s\n",
            newUser.ID, newUser.pass ,newUser.name, newUser.age, newUser.gender,
            newUser.email, newUser.phone, newUser.money,
            newUser.rentBook, newUser.rentDate, newUser.returnDate, newUser.history
        );
        fclose(file);
    } else {
        printf("Error opening user file!\n");
    }

    printf("User account created successfully!\n");
    return range_customers;
}

int userLogin(customer Customers[50], int k, int *locate_user_index){//่ฟังก์ชั่นการ login user
    char userID[30],userPass[30];
    printf("------------------------------------------------\n");
    for(int i=0; i<3; i++){//่กรอกรหัสผ่านได้แค่ 3 ครั้ง
        printf("Enter your ID: ");
        scanf("%s",userID);
        printf("Enter your password: ");
        scanf("%s",userPass);
        printf("------------------------------------------------\n");
        for(int j=0; j<k; j++){
            if (strcmp(userID, Customers[j].ID) == 0 && strcmp(userPass, Customers[j].pass) == 0) {//รหัสผ่านตรงกับ ID ของใคร
                *locate_user_index = j;
                return 1;
            } 
        }
    }
    return 0;
}

int ownerLogin(){ //ฟังก์ชั่นการ login owner
    char ownerName[30],ownerPass[30];
    printf("------------------------------------------------\n");
    for(int i=0; i<3; i++){
        printf("Enter your name: ");
        scanf("%s",ownerName);
        printf("Enter your password: ");
        scanf("%s",ownerPass);
        printf("------------------------------------------------\n");
        if (strcmp(ownerName, "OMGO") == 0 && strcmp(ownerPass, "BookStore") == 0) {//เช็ครหัสผ่านของ owner
            return 1;
        } 
    }
    return 0;
}

//====================================================================================
int splitString(char *str, char arr[10][50]) {//แยก string ด้วย &
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


char* search_user_by_id(customer Customers[50], char customer_id[10]) {
    for (int i = 0; i < 50; i++) {
        if (Customers[i].ID[0] == '\0') break; // ไม่มีข้อมูลแล้ว
        if (strcmp(Customers[i].ID, customer_id) == 0) {
            return Customers[i].name;
        }
    }
    return NULL; // ไม่พบuser
}

void show_book(libraryowner library[50], int k) {//แสดงหนังสือทั้งหมด

    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-6s | %-50s | %-25s | %-20s | %-20s | %-10s | %-8s | %-12s | %-10s |\n",
           "ID", "Title", "Author", "Type", "Genre", "Price", "Stock", "RentPrice", "RentStock");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < k; i++) {
        printf("| %-6s | %-50s | %-25s | %-20s | %-20s | %10.2f | %8d | %12.2f | %10d |\n",
               library[i].ID,
               library[i].title,
               library[i].author,
               library[i].type,
               library[i].genre,
               library[i].price,
               library[i].stock,
               library[i].rentPrice,
               library[i].rentStock
        );
    }

    printf("---------------------------------------------------------------------------------------------------------------------------\n");
}


void show_customers(customer Customers[50], int k, split splitrent[50], split splithistory[50], libraryowner library[50]) {//แสดงข้อมูลลูกค้าทั้งหมด
    int i, j;

    for (i = 0; i < k; i++) {

        printf("==============================================================================================\n");
        printf("| %-92s |\n", "Customer Information");
        printf("==============================================================================================\n");

        printf("| %-12s | %-75s |\n", "ID", Customers[i].ID);
        printf("| %-12s | %-75s |\n", "Name", Customers[i].name);

        char agebuf[10];
        sprintf(agebuf, "%d", Customers[i].age);
        printf("| %-12s | %-75s |\n", "Age", agebuf);

        char genderbuf[10];
        sprintf(genderbuf, "%d", Customers[i].gender);
        printf("| %-12s | %-75s |\n", "Gender", genderbuf);

        printf("| %-12s | %-75s |\n", "Email", Customers[i].email);
        printf("| %-12s | %-75s |\n", "Phone", Customers[i].phone);

        char moneybuf[30];
        sprintf(moneybuf, "%.2f", Customers[i].money);
        printf("| %-12s | %-75s |\n", "Money", moneybuf);

        printf("==============================================================================================\n");

        // Rent table
        printf("| %-92s |\n", "Rent Books");
        printf("==============================================================================================\n");
        printf("| %-5s | %-15s | %-67s |\n", "No.", "BookID", "Book Title");
        printf("----------------------------------------------------------------------------------------------\n");

        for (j = 0; j < splitrent[i].count; j++) {
            printf("| %-5d | %-15s | %-67s |\n",
                   j,
                   splitrent[i].arr[j],
                   search_bookname_by_id(library, splitrent[i].arr[j]));
        }

        if (splitrent[i].count == 0) {
            printf("| %-92s |\n", "No rented books");
        }

        printf("==============================================================================================\n");

        // History table
        printf("| %-92s |\n", "History");
        printf("==============================================================================================\n");
        printf("| %-5s | %-15s | %-67s |\n", "No.", "BookID", "Book Title");
        printf("----------------------------------------------------------------------------------------------\n");

        for (j = 0; j < splithistory[i].count; j++) {
            printf("| %-5d | %-15s | %-67s |\n",
                   j,
                   splithistory[i].arr[j],
                   search_bookname_by_id(library, splithistory[i].arr[j]));
        }

        if (splithistory[i].count == 0) {
            printf("| %-92s |\n", "No history records");
        }

        printf("==============================================================================================\n\n");
    }
}


void show_HistoryRent(customer Customers[50], int *i){//แสดงประวัติการยืมของลูกค้าที่ login
    if(strlen(Customers[*i].rentBook) == 0){
        printf("There is no information in the system.\n");
    } else {
        printf("Customers ID %s: %s\nRentBook: %s\nRentDate: %s, ReturnDate: %s\nHistory: %s\n",
        Customers[*i].ID, Customers[*i].name,
        Customers[*i].rentBook, Customers[*i].rentDate, 
        Customers[*i].returnDate, Customers[*i].history);
    }
    
}

void show_AllHistoryRent(customer Customers[50], int k) {//แสดงข้อมูลการยืมของลูกค้าทุกคน
    printf("------------------------------------------------------------------------------------------------------------\n");
    printf("| %-6s | %-15s | %-20s | %-12s | %-12s | %-30s |\n",
           "ID", "Name", "Current Rent", "Rent Date", "Return Date", "History");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < k; i++) {
        char TempAns[200] = "";
        char Temprentdate[20] = "";
        char Tempreturndate[20] = "";
        char Temphistory[1000] = "";

        // --- ข้อมูลการยืมปัจจุบัน ---
        if (strlen(Customers[i].rentBook) == 0) {
            strcpy(TempAns, "-");
            strcpy(Temprentdate, "-");
            strcpy(Tempreturndate, "-");
        } else {
            strcpy(TempAns, Customers[i].rentBook);
            strcpy(Temprentdate, Customers[i].rentDate);
            strcpy(Tempreturndate, Customers[i].returnDate);
        }

        // --- ประวัติการยืมทั้งหมด ---
        if (strlen(Customers[i].history) == 0)
            strcpy(Temphistory, "-");
        else
            strcpy(Temphistory, Customers[i].history);

        // --- แสดงผลในรูปตาราง ---
        printf("| %-6s | %-15s | %-20s | %-12s | %-12s | %-30s |\n",
               Customers[i].ID,
               Customers[i].name,
               TempAns,
               Temprentdate,
               Tempreturndate,
               Temphistory);
    }

    printf("------------------------------------------------------------------------------------------------------------\n");
}


void show_income(storeIncome Income[], int count) {
    if (count == 0) {
        printf("No income records found.\n");
        return;
    }

    printf("\n========== STORE INCOME RECORDS ==========\n");
    printf("%-12s %-10s %-10s\n", "Date", "Income", "Total");
    printf("------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-12s %10.2f %10.2f\n",
               Income[i].date,
               Income[i].income,
               Income[i].total);
    }
    printf("------------------------------------------\n\n");
}

void save_library_to_file(libraryowner library[], int range_library) {
    FILE *file = fopen("ownerCPE.txt", "w");
    if (!file) {
        printf("Error saving file!\n");
        return;
    }
    for (int i = 0; i < range_library; i++) {
        fprintf(file, "%s %s %s %s %s %.2f %d %.2f %d\n",
            library[i].ID,
            library[i].title,
            library[i].author,
            library[i].type,
            library[i].genre,
            library[i].price,
            library[i].stock,
            library[i].rentPrice,
            library[i].rentStock
        );
    }
    fclose(file);
}

void save_customer_to_file(customer Customers[], int range_customers) {
    FILE *file = fopen("userCPE.txt", "w");
    if (!file) {
        printf("Error saving customer file!\n");
        return;
    }

    for (int i = 0; i < range_customers; i++) {
        fprintf(file, "%s|%s|%s|%d|%d|%s|%s|%.2f|%s|%s|%s|%s\n",
            Customers[i].ID,
            Customers[i].pass,
            Customers[i].name,
            Customers[i].age,
            Customers[i].gender,
            Customers[i].email,
            Customers[i].phone,
            Customers[i].money,
            Customers[i].rentBook,
            Customers[i].rentDate,
            Customers[i].returnDate,
            Customers[i].history
        );
    }

    fclose(file);
}

void revenue(storeIncome Income[], int count) {
    printf("\n-------------------- Store Revenue --------------------\n");
    printf("%-12s %-10s %-12s\n", "Date", "Income", "Total Income");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-12s %-10.2f %-12.2f\n",
               Income[i].date, Income[i].income, Income[i].total);
    }

    printf("--------------------------------------------------------\n");
    printf("📄 Total records: %d | Final total: %.2f\n",
           count, Income[count - 1].total);
}

void money(customer Customers[], int range_customer, int *locate_user_index){//Mick
    float top_up;
    printf("To go back: Enter -1\n");
    printf("How much do you want to top up? ");
    scanf("%f", &top_up);

    if(top_up == -1) return; // ออกถ้าไม่ต้องการเติม

    Customers[*locate_user_index].money += top_up;
    save_customer_to_file(Customers, range_customer);
    printf("Top-up successful! Your new balance: %.2f\n", Customers[*locate_user_index].money);
}

void save_income(float today_income) {
    FILE *r = fopen("income.txt", "r");
    float last_total = 0.0f;
    if (r != NULL) {
        char date[11];
        float inc, tot;
        while (fscanf(r, "%s %f %f", date, &inc, &tot) == 3) {
            last_total = tot;
        }
        fclose(r);
    }

    float new_total = last_total + today_income;

    DateInfo today;
    date(&today);

    FILE *a = fopen("income.txt", "a");
    if (a == NULL) {
        printf("Cannot open income.txt for writing!\n");
        return;
    }

    fprintf(a, "%02d/%02d/%04d %.2f %.2f\n",
            today.day, today.month, today.year,
            today_income, new_total);
    fclose(a);

    printf("Income saved for %02d/%02d/%04d | +%.2f (Total: %.2f)\n",
           today.day, today.month, today.year,
           today_income, new_total);
}

int dateDifference(char *actualDate, char *expectedDate) {
    struct tm actual_tm = {0}, expected_tm = {0};

    // แปลงสตริงวันที่เป็น struct tm
    sscanf(actualDate, "%d/%d/%d",
           &actual_tm.tm_mday, &actual_tm.tm_mon, &actual_tm.tm_year);
    sscanf(expectedDate, "%d/%d/%d",
           &expected_tm.tm_mday, &expected_tm.tm_mon, &expected_tm.tm_year);

    // ปรับค่าให้เข้ากับรูปแบบ struct tm (เดือนนับจาก 0, ปีนับจาก 1900)
    actual_tm.tm_mon -= 1;
    expected_tm.tm_mon -= 1;
    actual_tm.tm_year -= 1900;
    expected_tm.tm_year -= 1900;

    // แปลงเป็น time_t
    time_t t_actual = mktime(&actual_tm);
    time_t t_expected = mktime(&expected_tm);

    // หาผลต่าง (เป็นวินาที)
    double diff_seconds = difftime(t_actual, t_expected);

    // แปลงเป็นวัน
    int diff_days = (int)(diff_seconds / (60 * 60 * 24));

    return diff_days; // อาจเป็นบวก (คืนช้า) หรือศูนย์ หรือลบ (คืนก่อนกำหนด)
}

void Rent_Book(libraryowner library[], customer Customers[], int range_library, int *locate_user_index, int range_customer, split splitrent[]) {
    int Amount;
    char Temp_Book_ID[10];
    char sure;
    DateInfo today;
    time_t now = time(NULL);
    struct tm *local;
    char Temp_Date[20];
    char Temp_Return[20];
    int i, j, ii;
    int returnDays;
    int realprice;
    int fine;
    int found[5];
    char ANavailable[50][20];


    for (int x = 0; x < 5; x++)
    found[x] = -1;
    // ถ้ายังไม่ได้ยืม → เข้าหน้ายืม
    ii = 0;
    if (strlen(Customers[*locate_user_index].rentBook) == 0) {
        printf("------------------ Rent Menu ------------------\n");
        printf("You are in borrow menu\n");
        // ก่อนลูปแสดงหนังสือ
        for (ii = 0; ii < range_library; ii++) {
            if (library[ii].stock > library[ii].rentStock)
                strcpy(ANavailable[ii], "Available");
            else
                strcpy(ANavailable[ii], "Not_Available");
        }

        // แสดงหนังสือ
        printf("------------------ Book List ------------------\n");
        printf("%-10s %-40s %-10s %-10s\n", "ID", "Title", "Price", "Stock");
        printf("--------------------------------------------------------------------------\n");
        for (ii = 0; ii < range_library; ii++) {
            printf("%-10s %-40s %-10.2f %-20s\n",
                library[ii].ID,
                library[ii].title,
                library[ii].rentPrice,
                ANavailable[ii]);
        }
        printf("--------------------------------------------------------------------------\n");

        printf("How many books do you want to borrow? (1-5): ");
        scanf("%d", &Amount);

        if (Amount <= 0 || Amount > 5) {
            printf("Invalid amount.\n");
            return;
        }

        i = 0;
        printf("How many days you want to borrow?(3-9 [3 is minimum]): ");
        scanf("%d", &returnDays);
        if (returnDays < 3 || returnDays > 9){
            printf("Fail.\n");
            return;
        }
        while (i < Amount) {  
            // ก่อนลูปแสดงหนังสือ
            for (ii = 0; ii < range_library; ii++) {
                if (library[ii].stock > library[ii].rentStock)
                    strcpy(ANavailable[ii], "Available");
                else
                    strcpy(ANavailable[ii], "Not_Available");
            }

            // แสดงหนังสือ
            printf("------------------ Book List ------------------\n");
            printf("%-10s %-40s %-10s %-10s\n", "ID", "Title", "Price", "Stock");
            printf("--------------------------------------------------------------------------\n");
            for (ii = 0; ii < range_library; ii++) {
                printf("%-10s %-40s %-10.2f %-20s\n",
                    library[ii].ID,
                    library[ii].title,
                    library[ii].rentPrice,
                    ANavailable[ii]);
            }
            printf("--------------------------------------------------------------------------\n");     
            
            printf("Please input your %d book ID: ", i + 1);
            scanf("%s", Temp_Book_ID);

            for (int j = 0; j < range_library; j++) {
                if (strcmp(library[j].ID, Temp_Book_ID) == 0) {
                    found[i] = j;
                    break;
                }
            }

            if (found[i] == -1) {
                printf("Book ID %s not found.\n", Temp_Book_ID);
                continue;
            }

            if (library[found[i]].rentStock >= library[found[i]].stock) {
                printf("Sorry, %s is out of stock.\n", library[found[i]].title);
                continue;
            }

            printf("You want '%s' (y/n): ", library[found[i]].title);
            scanf(" %c", &sure);

            if (sure == 'n' || sure == 'N') {
                printf("Please enter book ID again.\n");
                continue;
            } else if (sure == 'y' || sure == 'Y') {
                realprice = library[found[i]].rentPrice + (returnDays-3)*(library[found[i]].price)*5/100;
                if (Customers[*locate_user_index].money < realprice) {
                    printf("Not enough balance! Please top up first.\n");
                    break;
                }

                date(&today);
                sprintf(Temp_Date, "%02d/%02d/%04d", today.day, today.month, today.year);

                time_t t = now + (returnDays * 24 * 60 * 60);
                local = localtime(&t);
                sprintf(Temp_Return, "%02d/%02d/%04d", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);

                strcpy(Customers[*locate_user_index].rentDate, Temp_Date);
                strcpy(Customers[*locate_user_index].returnDate, Temp_Return);

                if (strlen(Customers[*locate_user_index].rentBook) > 0)
                    strcat(Customers[*locate_user_index].rentBook, "&");
                strcat(Customers[*locate_user_index].rentBook, Temp_Book_ID);

                if (strlen(Customers[*locate_user_index].history) > 0)
                    strcat(Customers[*locate_user_index].history, "&");
                strcat(Customers[*locate_user_index].history, Temp_Book_ID);

                printf("Book '%s' borrowed successfully!\n", library[found[i]].title);
                i++;
            } else {
                printf("Invalid! Please enter book ID again.\n");
                continue;
            }
        }
        for (int k = 0; k < i; k++) {
            save_income(library[found[k]].rentPrice + (returnDays-3)*(library[found[k]].price)*5/100);
            library[found[k]].rentStock += 1;
            Customers[*locate_user_index].money -= (library[found[k]].rentPrice + (returnDays-3)*(library[found[k]].price)*5/100);
        }
    }
    // ถ้ามีหนังสือที่ยืมอยู่ → เข้าหน้าคืน
    else {
        printf("------------------ Return Menu ------------------\n");
        printf("You are in return menu\n");
        printf("------------------------------------------------\n");

        // ✅ แสดงหนังสือที่ยืมอยู่
        printf("You are currently borrowing:\n");
        printf("%-10s %-25s %-10s\n", "ID", "Title", "Price");
        printf("------------------------------------------------\n");
        for (i = 0; i < range_library; i++) {
            if (strstr(Customers[*locate_user_index].rentBook, library[i].ID) != NULL) {
                printf("%-10s %-25s %-10.2f\n",
                       library[i].ID, library[i].title, library[i].rentPrice);
            }
        }
        printf("------------------------------------------------\n");

        date(&today);
        sprintf(Temp_Date, "%02d/%02d/%04d", today.day, today.month, today.year);

        int daysLate = dateDifference(Temp_Date, Customers[*locate_user_index].returnDate);
        if (daysLate < 0) daysLate = 0;

        if (daysLate > 0) {
            for (i = 0; i < splitrent[*locate_user_index].count; i++) {
                for (j = 0; j < range_library; j++) {
                    // ✅ ต้องใช้ == 0
                    if (strcmp(library[j].ID, splitrent[*locate_user_index].arr[i]) == 0) {
                        fine = (int)(library[j].rentPrice * 0.75 * daysLate);
                        printf("You returned '%s' %d day(s) late. Fine: %d\n",
                               library[j].title, daysLate, fine);

                        if (Customers[*locate_user_index].money >= fine) {
                            Customers[*locate_user_index].money -= fine;
                            printf("Fine paid successfully.\n");
                            save_income(fine);
                        } else {
                            printf("Not enough balance to pay fine! Please top up first.\n");
                            printf("Your balance: %.2f, Need: %d\n", Customers[*locate_user_index].money, fine);
                            return;
                        }
                    }
                }
            }
        } else {
            printf("Returned on time. Thank you!\n");
        }

        // ✅ คืนหนังสือทั้งหมด
        for (i = 0; i < range_library; i++) {
            if (strstr(Customers[*locate_user_index].rentBook, library[i].ID) != NULL &&
                library[i].rentStock > 0) {
                library[i].rentStock -= 1;
            }
        }

        // ✅ เคลียร์ข้อมูลยืม
        strcpy(Customers[*locate_user_index].rentBook, "");
        strcpy(Customers[*locate_user_index].rentDate, "");
        strcpy(Customers[*locate_user_index].returnDate, "");
    }

    save_customer_to_file(Customers, range_customer);
    save_library_to_file(library, range_library);
}


int add_book(libraryowner library[], int range_library) {
    if (range_library >= 50) {
        printf("Library is full!\n");
        return range_library;
    }

    libraryowner newBook;
    printf("Enter new book ID: ");
    scanf("%s", newBook.ID);
    printf("Enter title: ");
    scanf("%s", newBook.title);
    printf("Enter author: ");
    scanf("%s", newBook.author);
    printf("Enter type: ");
    scanf("%s", newBook.type);
    printf("Enter genre: ");
    scanf("%s", newBook.genre);
    printf("Enter price: ");
    scanf("%f", &newBook.price);
    printf("Enter stock: ");
    scanf("%d", &newBook.stock);
    printf("Enter rentPrice: ");
    scanf("%f", &newBook.rentPrice);
    printf("Enter rentStock: ");
    scanf("%d", &newBook.rentStock);

    library[range_library] = newBook;
    range_library++;

    // เรียงลำดับหนังสือตาม ID (Bubble sort)
    for (int i = 0; i < range_library - 1; i++) {
        for (int j = 0; j < range_library - i - 1; j++) {
            if (strcmp(library[j].ID, library[j + 1].ID) > 0) {
                libraryowner temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    save_library_to_file(library, range_library);
    printf("Book added successfully!\n");

    return range_library;
}
//นำหนังสือออกจากระบบด้วยไอดี
int remove_book(libraryowner library[], int range_library) {
    char targetID[10];
    printf("Enter book ID to remove: ");
    scanf("%s", targetID);

    int found = 0;
    for (int i = 0; i < range_library; i++) {
        if (strcmp(library[i].ID, targetID) == 0) {
            found = 1;
            for (int j = i; j < range_library - 1; j++) {
                library[j] = library[j + 1];
            }
            range_library--;
            break;
        }
    }

    if (found) {
        save_library_to_file(library, range_library);
        printf("Book with ID %s removed successfully.\n", targetID);
    } else {
        printf("Book ID not found.\n");
    }

    return range_library;
}

//แก้ไขนำหนังสือด้วยไอดี
void edit_book(libraryowner library[], int range_library) {
    char editID[10];
    printf("Enter book ID to edit: ");
    scanf("%s", editID);

    int found = 0;
    for (int i = 0; i < range_library; i++) {
        if (strcmp(library[i].ID, editID) == 0) {
            found = 1;
            char chk;

            printf("Edit Title (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%s", library[i].title);
            }

            printf("Edit Author (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%s", library[i].author);
            }

            printf("Edit Type (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%s", library[i].type);
            }

            printf("Edit Genre (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%s", library[i].genre);
            }

            printf("Edit Sale Price (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%f", &library[i].price);
            }

            printf("Edit Stock (for sale) (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%d", &library[i].stock);
            }

            printf("Edit Rental Price (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%f", &library[i].rentPrice);
            }

            printf("Edit Stock (for rent) (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%d", &library[i].rentStock);
            }

            save_library_to_file(library, range_library);
            printf("Book ID %s updated successfully!\n", editID);
            break;
        }
    }

    if (!found) {
        printf("Book ID not found.\n");
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
    char line[1500];
    char *token;
    char tempRentBook[200];
    char tempHistory[1000];

    while (fgets(line, sizeof(line), user) != NULL) {
        // ตัด \n ทิ้งก่อน
        line[strcspn(line, "\n")] = '\0';

        // เคลียร์ค่า
        strcpy(Customers[i].rentBook, "");
        strcpy(Customers[i].rentDate, "");
        strcpy(Customers[i].returnDate, "");
        strcpy(Customers[i].history, "");

        // ใช้ strtok แยกตาม "|"
        token = strtok(line, "|");
        if (!token) continue; strcpy(Customers[i].ID, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(Customers[i].pass, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(Customers[i].name, token);

        token = strtok(NULL, "|");
        if (!token) continue; Customers[i].age = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue; Customers[i].gender = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(Customers[i].email, token);

        token = strtok(NULL, "|");
        if (!token) continue; strcpy(Customers[i].phone, token);

        token = strtok(NULL, "|");
        if (!token) continue; Customers[i].money = atof(token);

        token = strtok(NULL, "|");
        if (token) strcpy(Customers[i].rentBook, token);

        token = strtok(NULL, "|");
        if (token) strcpy(Customers[i].rentDate, token);

        token = strtok(NULL, "|");
        if (token) strcpy(Customers[i].returnDate, token);

        token = strtok(NULL, "|");
        if (token) strcpy(Customers[i].history, token);

        // ---- แยก Rent Book ----
        if (strlen(Customers[i].rentBook) > 0) {
            strcpy(tempRentBook, Customers[i].rentBook);
            splitrent[i].count = splitString(tempRentBook, splitrent[i].arr);
        } else {
            splitrent[i].count = 0;
        }

        // ---- แยก History ----
        if (strlen(Customers[i].history) > 0) {
            strcpy(tempHistory, Customers[i].history);
            splithistory[i].count = splitString(tempHistory, splithistory[i].arr);
        } else {
            splithistory[i].count = 0;
        }

        i++;
    }

    return i; // จำนวนลูกค้าที่อ่านได้
}
// int read_customer_file(FILE *user, customer Customers[], split splitrent[], split splithistory[]) {
//     int i = 0;
//     char tempRentBook[200];
//     char tempHistory[1000];

//     while (fscanf(user, "%s %s %s %d %d %s %s %f %s %s %s %s",
//         Customers[i].ID,
//         Customers[i].pass,
//         Customers[i].name,
//         &Customers[i].age,
//         &Customers[i].gender,
//         Customers[i].email,
//         Customers[i].phone,
//         &Customers[i].money,
//         Customers[i].rentBook,
//         Customers[i].rentDate,
//         Customers[i].returnDate,
//         Customers[i].history) != EOF) {

//         // แยก string ด้วย comma
//         strcpy(tempRentBook, Customers[i].rentBook);
//         splitrent[i].count = splitString(tempRentBook, splitrent[i].arr);

//         strcpy(tempHistory, Customers[i].history);
//         splithistory[i].count = splitString(tempHistory, splithistory[i].arr);

//         i++;
//     }
//     return i; // คืนค่าจำนวนลูกค้าที่อ่านได้
// }

int read_income_file(FILE *income, storeIncome Income[], int maxCount) {
    int i = 0;

    if (income == NULL) {
        printf("Error: file pointer is NULL.\n");
        return 0;
    }

    while (i < maxCount && fscanf(income, "%s %f %f",
           Income[i].date,
           &Income[i].income,
           &Income[i].total) == 3) {
        i++;
    }

    return i; // คืนค่าจำนวนข้อมูลที่อ่านได้
}

int main() {
    FILE *owner = fopen("ownerCPE.txt", "r");
    FILE *user = fopen("userCPE.txt", "r");
    FILE *income = fopen("income.txt", "r");
    if (!owner || !user || !income) {
        printf("Error opening file!\n");
        return 1;
    }
    storeIncome Income[100];
    libraryowner library[50];
    customer Customers[50];
    split splitrent[50], splithistory[50];

    //เรียกใช้ฟังก์ชันอ่านไฟล์
    int range_library = read_library_file(owner, library);
    int range_customers = read_customer_file(user, Customers, splitrent, splithistory);
    int range_income = read_income_file(income, Income, 100);; //File, struct, maxcount of income history

    //printf("Read %d books and %d customers successfully.\n", range_library, range_customers);


    ///////////////////////main///////////////////////
    

    //login 
    int login_state; // 0 not pass, 1 pass
    int user_index;
    int *locate_user_index = &user_index;
    while (1){
        int login = -1;
        printf("Login as (0 = owner, 1 = user): ");
        scanf("%d", &login);
        
        if (login == 0){
            login_state = ownerLogin();
            if (login_state == 0){
                    printf("ID or password is incorrect. Please enter again.\n");
                    printf("------------------------------------------------\n");
                    continue;
            }
        }
        else if (login == 1){
            int pick;
            printf("1. Sign up\n");
            printf("2. Sign in\n");
            printf("------------------------------------------------\n");
            printf("Selection: ");
            scanf("%d", &pick);

            if (pick == 1){
                range_customers = userSignUp(Customers, range_customers);
                continue;
            }
            else if (pick == 2){
                login_state = userLogin(Customers, range_customers, locate_user_index);
                if (login_state == 0){
                    printf("ID or password is incorrect. Please enter again.\n");
                    printf("------------------------------------------------\n");
                    continue;
                }
            }
            else {
                printf("Wrong option entered. Please enter again.\n");
                printf("------------------------------------------------\n");
                continue;
            }
        }
        else{
            printf("Wrong option entered. Please enter again.\n");
            printf("------------------------------------------------\n");
            continue;
        }
        //selection
        int selection = -1;
        while (selection != 0 && login_state == 1) {
            if (login == 0) {  // Owner menu
                printf("------------------ Owner Menu ------------------\n");
                printf("1. Show book\n");
                printf("2. Show customer\n");
                printf("3. System rent\n");
                printf("4. Change\n");
                printf("5. Income\n");
                printf("0. Exit\n");
                printf("------------------------------------------------\n");
            } else {  // User menu
                printf("------------------ User Menu -------------------\n");
                printf("Profile\n Customer ID %s: %s, money %.2f\n",
                Customers[*locate_user_index].ID, 
                Customers[*locate_user_index].name, 
                Customers[*locate_user_index].money);
                printf("------------------------------------------------\n");
                printf("1. History rent\n");
                printf("2. Money\n");
                printf("3. Show book\n");
                printf("4. Rent\n");
                printf("0. Exit\n");
                printf("------------------------------------------------\n");
            }

            printf("Selection: ");
            scanf("%d", &selection);
            printf("------------------------------------------------\n");

            if (login == 0) {
                switch (selection) {
                    case 1: printf("Show book\n"); show_book(library,range_library); break;
                    case 2: printf("Show customer\n"); show_customers(Customers, range_customers, splitrent, splithistory, library); break;
                    case 3: printf("System rent\n"); show_AllHistoryRent(Customers, range_customers); break;
                    case 4:
                        printf("Change Mode:\n");
                        printf("1. Add Book\n");
                        printf("2. Remove Book\n");
                        printf("3. Edit Book\n");
                        int sub;
                        scanf("%d", &sub);
                        if (sub == 1) range_library = add_book(library, range_library);
                        else if (sub == 2) range_library = remove_book(library, range_library);
                        else if (sub == 3) edit_book(library, range_library);
                        else printf("Invalid option.\n");
                        break;
                    case 5: printf("Income\n"); revenue(Income, range_income); break;
                    case 0: printf("Exit owner mode.\n"); break;
                    default: printf("Invalid option! Please enter 0-5.\n");
                }
            } else {
                switch (selection) {
                    case 1: printf("History rent\n"); show_HistoryRent(Customers, locate_user_index); break;
                    case 2: printf("Money\n"); money(Customers, range_customers, locate_user_index); break;
                    case 3: printf("Show book\n"); show_book(library,range_library); break;
                    case 4: printf("Rent\n"); Rent_Book(library, Customers, range_library, locate_user_index, range_customers, splitrent); break;
                    case 0: printf("Exit user mode.\n"); break;
                    default: printf("Invalid option! Please enter 0-4.\n");
                }
            }
        }
        printf("END of program");
        fclose(user);
        fclose(owner);
        fclose(income);
        break;
    }
    return 0;
}
