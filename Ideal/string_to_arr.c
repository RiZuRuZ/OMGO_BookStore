#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "aaa, bbb, ccc, ddd";  // string ต้นฉบับ
    char *arr[10];  // array ของ pointer เก็บคำสูงสุด 10 คำ
    int count = 0;

    // แยก string โดยใช้ comma และ space เป็นตัวแบ่ง
    char *token = strtok(str, ", "); // strtok คืน pointer ไปที่คำแรก
    while(token != NULL) {
        arr[count++] = token;       // เก็บ pointer ลง array
        token = strtok(NULL, ", "); // ดึงคำถัดไป
    }

    // แสดงผล
    for(int i = 0; i < count; i++) {
        printf("arr[%d] = %s\n", i, arr[i]);
    }

    return 0;
}
