#include <stdio.h>
#include <time.h>

int main() {
    time_t now;               // ตัวแปรเก็บเวลา (ชนิดพิเศษ)
    struct tm *local;         // โครงสร้างเวลาท้องถิ่น
    char dateTime[50];        // buffer สำหรับเก็บข้อความเวลา

    time(&now);               // ดึงเวลาปัจจุบันจากระบบ
    local = localtime(&now);  // แปลงเป็นเวลาท้องถิ่น (ตาม timezone เครื่อง)

    // จัดรูปแบบเป็นข้อความ
    strftime(dateTime, sizeof(dateTime), "%d/%m/%Y %H:%M:%S", local);

    printf("📅 DATE: %s\n", dateTime);
    return 0;
}