#include <stdio.h>
#include <time.h>

int main() {
    time_t now;               // เก็บเวลาปัจจุบัน
    struct tm *local;         // เวลาแบบท้องถิ่น
    char dateTime[50];        // เก็บข้อความเวลา

    time(&now);               // ดึงเวลาปัจจุบันจากระบบ
    local = localtime(&now);  // แปลงเป็นเวลาท้องถิ่น

    // จัดรูปแบบเวลาเป็นข้อความ
    strftime(dateTime, sizeof(dateTime), "%d/%m/%Y %H:%M:%S", local);
    printf("📅 เวลาปัจจุบัน: %s\n", dateTime);

    // คำนวณอีก 4 วันข้างหน้า
    time_t t = now;  // ✅ เริ่มจากเวลาปัจจุบัน
    t += 4 * 24 * 60 * 60;  // บวก 4 วัน

    struct tm *tm_info = localtime(&t); // ✅ ประกาศตัวแปรก่อนใช้

    printf("📆 อีก 4 วันข้างหน้า: %02d/%02d/%d\n",
           tm_info->tm_mday,
           tm_info->tm_mon + 1,
           tm_info->tm_year + 1900);

    return 0;
}
/*

struct tm {
    int tm_sec;   // วินาที (0–59)
    int tm_min;   // นาที (0–59)
    int tm_hour;  // ชั่วโมง (0–23)
    int tm_mday;  // วันที่ในเดือน (1–31)
    int tm_mon;   // เดือน (0–11) → ต้อง +1
    int tm_year;  // ปีนับจาก 1900 → ต้อง +1900
    int tm_wday;  // วันในสัปดาห์ (0=อาทิตย์)
    int tm_yday;  // วันที่ในปี (0–365)
    int tm_isdst; // daylight saving flag
};

*/
