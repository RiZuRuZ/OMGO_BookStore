#include <stdio.h>
#include <time.h>
#include <locale.h>

typedef struct {
    int day;
    int month;
    int year;
} DateInfo;

// ✅ ใช้ pointer เพื่อให้แก้ค่าจริงใน main ได้
void date(DateInfo *today) {
    setlocale(LC_ALL, "th_TH.UTF-8");

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    today->day = tm_info->tm_mday;
    today->month = tm_info->tm_mon + 1;
    today->year = tm_info->tm_year + 1900;
}

int main() {
    DateInfo today;
    date(&today);  // ✅ ส่งที่อยู่ของ struct
    printf("%d/%d/%d\n", today.day, today.month, today.year);
}
