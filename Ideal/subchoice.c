/*
else if (subChoice == 2) {
    // ✅ Remove book completely
    char targetID[10];
    printf("Enter book ID to remove completely: ");
    scanf("%s", targetID);

    int found = 0;
    for (int i = 0; i < range_library; i++) {
        if (strcmp(library[i].ID, targetID) == 0) {
            found = 1;

            // ขยับข้อมูลทับตำแหน่งนั้น
            for (int j = i; j < range_library - 1; j++) {
                library[j] = library[j + 1];
            }
            range_library--; // ลดจำนวนหนังสือลง 1
            printf("✅ Book %s removed from memory.\n", targetID);

            // เขียนไฟล์ใหม่ทั้งหมด
            FILE *f = fopen("ownerCPE.txt", "w");
            if (f == NULL) {
                printf("❌ Error: cannot open file to update.\n");
                break;
            }

            for (int k = 0; k < range_library; k++) {
                fprintf(f, "%s %s %s %s %s %.2f %d %.2f %d\n",
                        library[k].ID,
                        library[k].title,
                        library[k].author,
                        library[k].type,
                        library[k].genre,
                        library[k].price,
                        library[k].stock,
                        library[k].rentPrice,
                        library[k].rentStock);
            }
            fclose(f);

            printf("💾 Updated file 'ownerCPE.txt' successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("❌ Book ID '%s' not found.\n", targetID);
    }
}
*/