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
    char rentBook[500];
} customer;

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
    int i = 0;
    char line[1024];

    while (fgets(line, sizeof(line), df1)) {
        // ใช้ sscanf ดึงเฉพาะส่วนก่อนรายการหนังสือ
        sscanf(line, "%s %s %d %d %[^,],%[^ ] %f %[^\n]",
            Customers[i].ID,
            Customers[i].name,
            &Customers[i].age,
            &Customers[i].gender,
            Customers[i].email,
            Customers[i].phone,
            &Customers[i].money,
            Customers[i].rentBook
        );

        printf("Customer %s: %s, age %d, gender %d, email %s, phone %s, money %.2f, rentBook %s\n",
               Customers[i].ID,
               Customers[i].name,
               Customers[i].age,
               Customers[i].gender,
               Customers[i].email,
               Customers[i].phone,
               Customers[i].money,
               Customers[i].rentBook);
        i++;
    }

    fclose(df1);
    return 0;
}
