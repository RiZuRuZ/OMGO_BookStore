#include <stdio.h>
#include <time.h>
#include <locale.h>

typedef struct {
    int day;
    int month;
    int year;
    char timeStr[20];  // "HH:MM:SS"
} DateInfo;

int main() {
    setlocale(LC_ALL, "th_TH.UTF-8");

    DateInfo today;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // บันทึกข้อมูลลงใน struct
    today.day = tm_info->tm_mday;
    today.month = tm_info->tm_mon + 1;
    today.year = tm_info->tm_year + 1900;
    strftime(today.timeStr, sizeof(today.timeStr), "%H:%M:%S", tm_info);

    // วันในภาษาไทย
    char *thaiDays[] = {"อาทิตย์","จันทร์","อังคาร","พุธ","พฤหัสบดี","ศุกร์","เสาร์"};

    // แสดงผลทั้งหมด
    printf("วัน: %s\n", thaiDays[tm_info->tm_wday]);
    printf("วันที่: %d\n", today.day);
    printf("เดือน: %d\n", today.month);
    printf("ปี: %d\n", today.year);
    printf("เวลา: %s\n", today.timeStr);

    return 0;
}
