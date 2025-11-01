void Add_Book() {
    libraryowner b[50];
    FILE *owner;
    owner = fopen("Owner.txt", "r"); 
    int i = 0;
    while (fscanf(owner, "%s %s %s %s %s %f %d %f %d",
        b[i].ID, b[i].title, b[i].author, b[i].type, b[i].genre,
        &b[i].price, &b[i].stock, &b[i].rentPrice, &b[i].rentStock) == 9){
            i++;
    }
    fclose(owner);

    printf("\n=== Add New Book ===\n");
    printf("Book ID: ");
    scanf("%9s", b[i].ID);
    getchar(); // clear newline
    printf("Name: ");
    fgets(b[i].title, sizeof(b[i].title), stdin);
    b[i].title[strcspn(b[i].title, "\n")] = '\0';
    printf("Author: ");
    fgets(b[i].author, sizeof(b[i].author), stdin);
    b[i].author[strcspn(b[i].author, "\n")] = '\0';
    printf("Type: ");
    fgets(b[i].type, sizeof(b[i].type), stdin);
    b[i].type[strcspn(b[i].type, "\n")] = '\0';
    printf("Genre: ");
    fgets(b[i].genre, sizeof(b[i].genre), stdin);
    b[i].genre[strcspn(b[i].genre, "\n")] = '\0';
    printf("Sale Price: ");
    scanf("%f", &b[i].price);
    printf("Stock (for sale): ");
    scanf("%d", &b[i].stock);
    printf("Rental Price: ");
    scanf("%f", &b[i].rentPrice);
    printf("Stock (for rent): ");
    scanf("%d", &b[i].rentStock);
    i++;

    for (int a = 0; a < i - 1; a++) {
        for (int j = 0; j < i - a - 1; j++) {
            if (strcmp(b[j].ID, b[j + 1].ID) > 0) {
                libraryowner temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    owner = fopen("Owner.txt", "w");
    if (owner == NULL) {
        printf("Cannot open file for writing!\n");
        return;
    }
    for (int j = 0; j < i; j++) {
        fprintf(owner, "%s %s %s %s %s %.2f %d %.2f %d\n",
            b[j].ID, b[j].title, b[j].author, b[j].type, b[j].genre,
            b[j].price, b[j].stock, b[j].rentPrice, b[j].rentStock);
    }
    fclose(owner);
    printf("Book added successfully!\n");
}

void Remove_Book() {
    FILE *owner = fopen("Owner.txt", "r");
    if (owner == NULL) {
        printf("Cannot open file!\n");
        return;
    }
    libraryowner b[50];
    char deleteID[10];
    int found = 0, i = 0;
    printf("\n=== Remove Book ===\n");
    printf("Enter Book ID to remove: ");
    scanf("%s", deleteID);

    while (fscanf(owner, "%s %s %s %s %s %f %d %f %d",
        b[i].ID, b[i].title, b[i].author, b[i].type, b[i].genre,
        &b[i].price, &b[i].stock, &b[i].rentPrice, &b[i].rentStock) == 9){
            i++;
    }
    fclose(owner);

    owner = fopen("Owner.txt", "w");
    if (owner == NULL) {
        printf("Cannot open file for writing!\n");
        return;
    }
    for (int j = 0; j < i; j++) {
        if (strcmp(b[j].ID, deleteID) == 0) {
            found = 1;
            continue;
        }
        fprintf(owner, "%s %s %s %s %s %.2f %d %.2f %d\n",
            b[j].ID, b[j].title, b[j].author, b[j].type, b[j].genre,
            b[j].price, b[j].stock, b[j].rentPrice, b[j].rentStock);
    }
    fclose(owner);
    if (found)
        printf("Book removed successfully!\n");
    else
        printf("Book ID not found!\n");
}

void Edit_Book() {
    FILE *owner = fopen("Owner.txt", "r");
    if (owner == NULL) {
        printf("Cannot open file!\n");
        return;
    }
    libraryowner b[50];
    char editID[10];
    int found = 0, i = 0;
    printf("\n=== Edit Book ===\n");
    printf("Enter Book ID to Edit: ");
    scanf("%s", editID); 
    while (fscanf(owner, "%s %s %s %s %s %f %d %f %d",
        b[i].ID, b[i].title, b[i].author, b[i].type, b[i].genre,
        &b[i].price, &b[i].stock, &b[i].rentPrice, &b[i].rentStock) == 9){
            i++;
    }
    fclose(owner);
    
    owner = fopen("Owner.txt", "w");
    if (owner == NULL) {
        printf("Cannot open file for writing!\n");
        return;
    }
    for (int j = 0; j < i; j++) {
        if (strcmp(b[j].ID, editID) == 0) {
            char chk;
            printf("Edit Name (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                getchar();
                fgets(b[j].title, sizeof(b[j].title), stdin);
                b[j].title[strcspn(b[j].title, "\n")] = '\0';
            }
            printf("Edit Author (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                getchar();
                fgets(b[j].author, sizeof(b[j].author), stdin);
                b[j].author[strcspn(b[j].author, "\n")] = '\0';
            }
            printf("Edit Type (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                getchar();
                fgets(b[j].type, sizeof(b[j].type), stdin);
                b[j].type[strcspn(b[j].type, "\n")] = '\0';
            }
            printf("Edit Genre (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                getchar();
                fgets(b[j].genre, sizeof(b[j].genre), stdin);
                b[j].genre[strcspn(b[j].genre, "\n")] = '\0';
            }
            printf("Edit Sale Price (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%f", &b[j].price);
            }
            printf("Edit Stock (for sale) (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%d", &b[j].stock);
            }
            printf("Edit Rental Price (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%f", &b[j].rentPrice);
            }
            printf("Edit Stock (for rent) (y/n): ");
            scanf(" %c", &chk);
            if (chk == 'y' || chk == 'Y') {
                printf("Edit to: ");
                scanf("%d", &b[j].rentStock);
            }
        }
        fprintf(owner, "%s %s %s %s %s %.2f %d %.2f %d\n",
            b[j].ID, b[j].title, b[j].author, b[j].type, b[j].genre,
            b[j].price, b[j].stock, b[j].rentPrice, b[j].rentStock);  
    }
    fclose(owner);
}
