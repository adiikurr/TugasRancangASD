/*
    Kelompok Polkadot - Topik Sistem Informasi Apotek
    1. Adi Kurniawan            - 672021172
    2. Robertos Hartanto Wijaya - 672021146

    Username    : admin
    Password    : adiarta
*/
// Data Apotek (No pasien, Nama Pasien, Jenis Kelamin, Umur Pasien, Nama Obat)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <dos.h>
#include <conio.h>
#define ENTER 13
#define BKSP 8
#define TAB 9

//-riwayat
//tampilan sedang dalam pengerjaan
//kalo ada bug/error kasih tau yak

struct Apotek
{
    int umurPasien,noPasien;
    char namaPasien[20], namaObat[20], jenisKelamin[20];
    struct Apotek *next;
}*head,*current,*tail;
struct node
{
    struct Apotek apotek;
    struct node *next;
};

//struct node *head = NULL;
//struct node *tail = NULL;

int bdata=0;

void menu()
{
    struct Apotek apotek;

    int pilihan=0,a=50,b=50,c=50,d=50;
    system("cls");
    gotoxy(35,4);while(a--){printf("=");}//Sleep(5);}
    gotoxy(40,6);printf("SELAMAT DATANG DI DATABASE APOTEK\n");
    gotoxy(43,7);printf("\t  RAJANYA OBAT\n");
    gotoxy(35,9);while(b--){printf("-");}//Sleep(5);}
    gotoxy(40,11);printf("1. Mencetak Database ke File Text");
    gotoxy(40,12);printf("2. Menambahkan Data Baru ke Database");
    gotoxy(40,13);printf("3. Menampilkan Isi Database");
    gotoxy(40,14);printf("4. Mengupdate Data di Database");
    gotoxy(40,15);printf("5. Menghapus Data di Database");
    gotoxy(40,16);printf("6. Mencari Data di Database");
    gotoxy(40,17);printf("7. Mengurutkan Data di Database");
    gotoxy(40,18);printf("8. Melihat Riwayat Aktivitas di Database");
    gotoxy(40,19);printf("9. Keluar Dari Program");
    gotoxy(35,22);while(c--){printf("=");}//Sleep(5);
    gotoxy(40,24);printf("Masukkan Pilihan = ");
    gotoxy(35,26);while(d--){printf("-");}//Sleep(5);
    gotoxy(60,24);scanf("%d", &pilihan);
    chMenu(pilihan);

}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void back(){
    gotoxy(45,26);printf("Tekan enter untuk kembali");
    getch();
    menu();
}

bool isEmpty()
{
    return head == NULL;
}

void writeFile()
{
    FILE *fptr = fopen("Database Apotek.txt","w");
    struct Apotek *current = head;

    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");
    } else {
        while(current != NULL)
        {
            fprintf(fptr, "Nomor Pasien            : %d\n", current->noPasien);
            fprintf(fptr, "Nama Pasien             : %s\n", current->namaPasien);
            fprintf(fptr, "Jenis Kelamin Pasien    : %s\n", current->jenisKelamin);
            fprintf(fptr, "Umur Pasien             : %d\n", current->umurPasien);
            fprintf(fptr, "Nama Obat Pasien        : %s\n\n", current->namaObat);
            current = current->next;
        }
    }
    fclose(fptr);
    back();

}

void InsertData(struct Apotek apotek)
{

    struct Apotek *temp;
    int i;
    fflush(stdin);
    printf("MAKSIMAL DATA YANG DAPAT DIINPUT ADALAH 5\n");
    printf("Masukkan Jumlah Data yang Ingin Di Input : ");
    scanf("%d",&bdata);

    if(bdata>5){
        printf("DATA YANG DI INPUT MAKSIMAL 5!!!");
        InsertData(apotek);
    }else{
        for(i=0;i<bdata;i++){
        current = (struct Apotek*)malloc(sizeof(struct Apotek));
            printf("Masukan Nomor Pasien            : "); scanf("%d", &current->noPasien);
            printf("Masukan Nama Pasien             : "); scanf(" %[^\n]", current->namaPasien);
            printf("Masukan Jenis Kelamin Pasien    : "); scanf(" %[^\n]", current->jenisKelamin);
            printf("Masukan Umur Pasien             : "); scanf("%i", &current->umurPasien);
            printf("Masukan Nama Obat Pasien        : "); scanf(" %[^\n]", current->namaObat);
            printf("\n");

        if(isEmpty(head))
        {
            head = tail = current;
        }else {
            tail->next = current;//posisi ke (1) -> (2) = curent
            tail = current;//tail = 1 -> 2
        }tail->next = NULL;//2 -> 3 = NULL || 0 -> 1 = NULL
        }
    }
    back();
}

void DisplayData()
{
    int a,i=1;
    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");back();
    } else {
        current = head;
        while(current != NULL){
            printf("Data ke - %i\n", i);
            printf("Nomor Pasien            : %d\n", current->noPasien);
            printf("Nama Pasien             : %s\n", current->namaPasien);
            printf("Jenis Kelamin Pasien    : %s\n", current->jenisKelamin);
            printf("Umur Pasien             : %d\n", current->umurPasien);
            printf("Nama Obat Pasien        : %s\n\n",current->namaObat);
            current = current->next;
            printf("\n");i++;
        }
        i=0;
    }
    back();
}

void login(){
    char u[10];int a=45,b=45,c=5,d=5;
    char p[10];
    time_t tm;
    int i = 0;char ch;
    time(&tm);

    system("cls");
    gotoxy(35,8);printf("+");while(a--){printf("=");Sleep(7);}printf("+");
    gotoxy(81,14);printf("+");
    while(c--){gotoxy(81,13-c);printf("|");Sleep(7);}
    while(b--){gotoxy(36+b,14);printf("=");Sleep(7);}
    gotoxy(35,14);printf("+");
    while(d--){gotoxy(35,9+d);printf("|");Sleep(7);}
    gotoxy(47,10);printf("Username : ");
    gotoxy(47,12);printf("Password : ");
    gotoxy(35,7);printf("%s", ctime(&tm));
    gotoxy(58,10);scanf(" %s",&u);
    gotoxy(58,12);
    while(1){
        ch = getch();

        if(ch == ENTER || ch == TAB){
            p[i] = '\0';
            break;
        }else if (ch == BKSP){
            if(i > 0){
                i--;
                printf(" ");
            }
        }else{
            p[i++] = ch;
            printf("*");
        }
    }

    if(strcmp(u,"admin")==0 && strcmp(p,"adiarta")==0)
    {
        gotoxy(47,16);strupr(p);printf("SELAMAT DATANG %s\n", p);
        gotoxy(43,18);printf("TEKAN ENTER UNTUK MELANJUTKAN...");
        getch();
        menu();
    }
    else
    {
        gotoxy(40,16);printf("Username atau password mungkin salah\n");
        gotoxy(43,18);printf("TEKAN ENTER UNTUK MENGULANG...");
        getch();
        login();
    }
}

void loading(){
}

void author(){
    int a=45,b=45,c=9,d=9,x=0;
    gotoxy(35,8);printf("+");while(a--){printf("=");Sleep(7);}printf("+");
    gotoxy(81,18);printf("+");
    while(c--){gotoxy(81,17-c);printf("|");Sleep(7);}
    while(b--){gotoxy(36+b,18);printf("=");Sleep(7);}
    gotoxy(35,18);printf("+");
    while(d--){gotoxy(35,9+d);printf("|");Sleep(7);}
    gotoxy(52,10);printf("Adi Kurniawan");
    gotoxy(54,12);printf("672021172");
    gotoxy(47,14);printf("ROBERTOS HARTANTO WIJAYA");
    gotoxy(54,16);printf("672021172");


    Sleep(1000);
    for(int i=5; i>-1; i--){
        gotoxy(43, 20);printf("Program will end in %i seconds!", i); Sleep(1000);
    }
system("cls");
exit(0);
}

void deleteData(){
    int a=0,nomor,b,ada=0;char del;
    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");back();
    }else{
        struct Apotek *temp = head;
        current=head;
        printf("Cari nomor pasien yang mau dihapus : ");scanf("%d", &nomor);

        for(a=0; a < bdata; a++)
        {
            if(temp->noPasien == nomor)
            {
                printf("Data yang dicari ditemukan! : \n\n");
                printf("Nomor Pasien            : %d\n", current->noPasien);
                printf("Nama Pasien             : %s\n", current->namaPasien);
                printf("Jenis Kelamin Pasien    : %s\n", current->jenisKelamin);
                printf("Umur Pasien             : %d\n", current->umurPasien);
                printf("Nama Obat Pasien        : %s\n\n", current->namaObat);
                printf("Apakah ada yakin ingin menghapus data? (Y/N) :          ");
                ada=1;
                break;
            }else if(ada==0){
                printf("\nData tidak ada");
                gotoxy(43,18);printf("TEKAN ENTER UNTUK MENGULANG...");
                getch();system("cls");
                deleteData();
            }
                temp=temp->next;
        }scanf(" %c",&del);


        //cari posisi index data yang mau dihapus
        int index = 0;
        while (current != NULL) {
            if (temp->noPasien == nomor){
                break;
            }
            index++;
            current = current->next;
        }


        if (index == 0){
            head = temp->next;
            free(temp);
            printf("\nData berhasil dihapus");back();
        }else{

            //nyari dan mindahin posisi temp ke data yang mau dicari
            for (int i=0; temp!=NULL && i<index-1; i++){
                temp = temp->next;
            }

            if (temp == NULL || temp->next == NULL){
                printf("\nData tidak ada");
                gotoxy(43,18);printf("TEKAN ENTER UNTUK MENGULANG...");
                getch();system("cls");
                deleteData();
            }else{
                struct Apotek *next = temp->next->next;
                free(temp->next);
                temp->next = next;
                printf("\nData berhasil dihapus");
                back();
            }
        }    }
}

void searchData(){
    int noP, found = 0,f,uP;
    char naP[30],jeK[30],naO[30];
    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");back();
    } else {
        current=head;
        gotoxy(43,6);printf("=== Mencari data pasien apotek ===");
        gotoxy(40,9);printf("Apa yang ingin Anda cari?");
        gotoxy(40,10);printf("1. Nomor Pasien \t\t3. Jenis Kelamin");
        gotoxy(40,11);printf("2. Nama Pasien\t\t\t4. Umur");
        gotoxy(40,12);printf("5. Nama Obat");
        gotoxy(40,13);printf("Masukan data yang ingin dicari : "); scanf("%d", &f);

        switch(f){
        case 1:
            gotoxy(40,15);printf("Masukan nomor pasien yang ingin dicari : "); scanf("%d", &noP);
            while(current != NULL){
                    if(current->noPasien == noP){
                        displaySearch();
                        found = 1;
                        break;
                    }
                current = current->next;
            }
            break;
        case 2:
            gotoxy(40,15);printf("Masukan nama pasien yang ingin dicari : "); scanf(" %[^\n]", &naP);
            while(current != NULL){
                    if(strcmp(current->namaPasien,naP)==0){
                        displaySearch();
                        found = 1;
                        break;
                    }
                current = current->next;
            }
            break;
        case 3:
            gotoxy(40,15);printf("Masukan jenis kelamin pasien yang ingin dicari : "); scanf(" %[^\n]", &jeK);
            while(current != NULL){
                    if(strcmp(current->jenisKelamin , jeK)==0){
                        displaySearch();
                        found = 1;
                        break;
                    }
                current = current->next;
            }
            break;
        case 4:
            gotoxy(40,15);printf("Masukan umur pasien yang ingin dicari : "); scanf("%d", &uP);
            while(current != NULL){
                    if(current->umurPasien == uP){
                        displaySearch();
                        found = 1;
                        break;
                    }
                    current = current->next;
            }
            break;
        case 5:
            gotoxy(40,15);printf("Masukan nama obat pasien yang ingin dicari : "); scanf(" %[^\n]", &naO);
            while(current != NULL){
            if(strcmp(current->namaObat,naO)==0){
                displaySearch(naO);
                found = 1;
                break;
                }
                current = current->next;
            }
            break;
        default:
            gotoxy(50,17);printf("Pilihan tidak ada");getch();searchData();
        }


        if(found == 0)
        {
            printf("Data yang dicari tidak ditemukan!");
        }

    }
}

void displaySearch(){
    printf("Data yang dicari ditemukan! : \n\n");
    printf("Nomor Pasien            : %d\n", current->noPasien);
    printf("Nama Pasien             : %s\n", current->namaPasien);
    printf("Jenis Kelamin Pasien    : %s\n", current->jenisKelamin);
    printf("Umur Pasien             : %d\n", current->umurPasien);
    printf("Nama Obat Pasien        : %s\n\n", current->namaObat);
    back();
}

void historyData(){
}

void sortData(){
    noData();

    int ad=0;

    gotoxy(40,9);printf("Sorting Data Berdasarkan");
    gotoxy(40,10); printf("1. Ascending");
    gotoxy(40,11);printf("2. Descending");
    gotoxy(40,12);printf("Masukkan pilihan : ");scanf("%d",&ad);

    switch(ad){
        case 1:system("cls");sortDataAscend();break;
        case 2:system("cls");sortDataDescend();break;
        default:printf("Pilihan tidak tersedia");gotoxy(45,26);printf("Tekan enter untuk kembali");getch();sortData();break;
    }


}

void sortDataAscend(){
    noData();
    struct Apotek *i, *j;
    int tempInt,pilih;
    char tempChar[20];

    gotoxy(43,6);printf("=== Menyortir data pasien apotek ===");
    gotoxy(40,9);printf("Apa yang ingin anda sortir?");
    gotoxy(40,10);printf("1. Nomor Pasien \t\t3. Jenis Kelamin");
    gotoxy(40,11);printf("2. Nama Pasien\t\t\t4. Umur");
    gotoxy(40,12);printf("5. Nama Obat");
    gotoxy(40,13);printf("Masukan data yang ingin sortir : "); scanf("%d", &pilih);

    switch(pilih){
        case 1:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if((i->noPasien) > (j->noPasien))
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 2:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(i->namaPasien, j->namaPasien)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 3:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(i->jenisKelamin, j ->  jenisKelamin)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 4:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if((i->umurPasien) > (j->umurPasien))
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 5:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(i->namaObat, j->namaObat)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        default:
            printf("inputan salah");gotoxy(45,26);printf("Tekan enter untuk mengulang");getch();sortDataAscend();break;
    }
    system("cls");DisplayData();
}

void sortDataDescend(){
    noData();
    struct Apotek *i, *j;
    int tempInt,pilih;
    char tempChar[20];

    gotoxy(43,6);printf("=== Mencari data pasien apotek ===");
    gotoxy(40,9);printf("Apa yang ingin Anda cari?");
    gotoxy(40,10);printf("1. Nomor Pasien \t\t3. Jenis Kelamin");
    gotoxy(40,11);printf("2. Nama Pasien\t\t\t4. Umur");
    gotoxy(40,12);printf("5. Nama Obat");
    gotoxy(40,13);printf("Masukan data yang ingin dicari : "); scanf("%d", &pilih);

    switch(pilih){
        case 1:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if((i->noPasien) < (j->noPasien))
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 2:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(j->namaPasien, i->namaPasien)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 3:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(j->jenisKelamin, i->jenisKelamin)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 4:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if((i->umurPasien) < (j->umurPasien))
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        case 5:
            for(i = head; i != NULL; i = i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                    {
                        if(strcmp(j->namaObat, i->namaObat)>0)
                        {
                            tempInt = i->noPasien;
                            i->noPasien = j->noPasien;
                            j->noPasien = tempInt;

                            tempInt = i->umurPasien;
                            i->umurPasien = j->umurPasien;
                            j->umurPasien = tempInt;

                            strcpy(tempChar, i->namaPasien);
                            strcpy(i->namaPasien, j->namaPasien);
                            strcpy(j->namaPasien, tempChar);

                            strcpy(tempChar, i->jenisKelamin);
                            strcpy(i->jenisKelamin, j->jenisKelamin);
                            strcpy(j->jenisKelamin, tempChar);

                            strcpy(tempChar, i->namaObat);
                            strcpy(i->namaObat, j->namaObat);
                            strcpy(j->namaObat, tempChar);
                        }
                    }
            }
            break;
        default:
            printf("inputan salah");gotoxy(45,26);printf("Tekan enter untuk mengulang");getch();sortDataDescend();break;
    }
    system("cls");DisplayData();
}

void updateData(){

    if(isEmpty(head)){
        printf("Belum ada Data, silahkan input dulu!\n");
        back();
    }else{
        struct Apotek *current;
        char namabaru[30],kelaminbaru[30],obatbaru[30],ch;
        int edit=0,umurbaru,i=0,j,found=0,nop,nobaru,pil,a;
        current=head;

        printf("1. Nomor Pasien\n");
        printf("2. Nama Pasien\n");
        printf("3. Jenis Kelamin Pasien\n");
        printf("4. Umur Pasien\n");
        printf("5. Nama Obat Pasien\n");
        printf("Masukkan Pilihan data yang mau diedit : ");
        scanf("%d", &pil);
        printf("\nMasukkan No Pasien: ");
        scanf("%d", &nop);

            switch(pil){
            case 1://nopasien
               printf("Data saat ini : %d ",current->noPasien);
               printf("Data baru : ");scanf("%d",&nobaru);
               current->noPasien = nobaru;
               printf("\nData berhasil diedit");
               found=1;
               break;
            case 2://namapasien
               printf("Data saat ini : %s ",current->namaPasien);
               printf("Data baru : ");
               scanf(" %[^\n]",&namabaru);
               strcpy(current->namaPasien, namabaru);
               found=1;
            break;
            case 3://kelaminpasien
                printf("Data saat ini : %s ",current->jenisKelamin);
                printf("Data baru : ");
                scanf(" %[^\n]",&kelaminbaru);
                strcpy(current->jenisKelamin, kelaminbaru);
                found=1;
            break;
            case 4://umurpasien
                printf("Data saat ini : %d ",current->umurPasien);
                printf("Data baru : ");
                scanf("%d",&umurbaru);
                current->umurPasien = umurbaru;
                found=1;
            break;
            case 5://obatpasien
                printf("Data saat ini : %s ",current->namaObat);
                printf("Data baru : ");
                scanf(" %[^\n]",&obatbaru);
                strcpy(current->namaObat, obatbaru);
                        found=1;
            break;
            default:
                printf("inputan salah");gotoxy(45,26);printf("Tekan enter untuk mengulang");getch();break;
            }

          if(found==0){
            printf("data tidak tersedia");
            gotoxy(45,26);printf("Tekan enter untuk kembali");
            getch();system("cls");
            updateData();
          }
    }

back();

}

void chMenu(int pilihan){
    struct Apotek apotek;
    switch(pilihan){
        case 1:system("cls");writeFile();break;
        case 2:system("cls");InsertData(apotek);break;
        case 3:system("cls");DisplayData();break;
        case 4:system("cls");updateData();break;
        case 5:system("cls");deleteData();break;
        case 6:system("cls");searchData();break;
        case 7:system("cls");sortData();break;
        case 8:system("cls");historyData();break;
        case 9:system("cls");author();break;
        default:gotoxy(43,27);printf("Masukan pilihan dari 1 sampai 8 saja");
        gotoxy(45,28);printf("Tekan enter untuk kembali");
        getch();system("cls");
        menu();
    }
}

int main(){
    //loading();
    //login();
    menu();
}

