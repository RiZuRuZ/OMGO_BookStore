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
    char *arr[10];
    int count;
} splitrent;

typedef struct {
    char *arr[10];
    int count;
} splithistory;

int splitString(char *str, char *arr[]) {
    int count = 0;
    char *token = strtok(str, "&");
    while (token != NULL) {
        arr[count++] = token;
        token = strtok(NULL, "&");
    }
    return count;
}

int main() {
    SetConsoleOutputCP(65001); // ให้ console แสดง UTF-8
    SetConsoleCP(65001);       // ให้ scanf / fgets อ่าน UTF-8 ได้
    FILE *df1;
    df1 = fopen("c60txt1.txt", "r");
    if (df1 == NULL) {
        printf("ไม่พบไฟล์ข้อมูล!\n");
        return 1;
    }

    customer Customers[50];
    splitrent splitrents[50];
    splithistory splithistories[50];
    int i = 0;
    int j = 0;

    while(fscanf(df1, "%s %s %d %d %s %s %f %s %s %s %s", 
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
        Customers[i].history) != EOF){

        printf("Customer %s: %s, age %d, gender %d, email %s, phone %s, money %.2f\nRentBook: %s\nRentDate: %s, ReturnDate: %s\nHistory: %s\n",
            Customers[i].ID, Customers[i].name, Customers[i].age, Customers[i].gender,
            Customers[i].email, Customers[i].phone, Customers[i].money,
            Customers[i].rentBook, Customers[i].rentDate, Customers[i].returnDate, Customers[i].history);


        // เรียกใช้ฟังก์ชัน
        splitrents[i].count = splitString(Customers[i].rentBook, splitrents[i].arr);
        splithistories[i].count = splitString(Customers[i].history, splithistories[i].arr);
        // แสดงผลลัพธ์
        for (j = 0; j < splitrents[i].count; j++) {
            printf("RentBook[%d] = %s\n", j, splitrents[i].arr[j]);
        }
        for (j = 0; j < splithistories[i].count; j++) {
            printf("History[%d] = %s\n", j, splithistories[i].arr[j]);
        }
        printf("\n");
        i++;
    }

    i = 0;
    j = 0;

    fclose(df1);
    return 0;
}
