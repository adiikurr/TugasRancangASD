/*
    Kelompok Polkadot - Topik Sistem Informasi Apotek
    1. Adi Kurniawan            - 672021172
    2. Robertos Hartanto Wijaya - 672021146

    Username    : admin
    Password    : adiarta
*/
// Data Apotek (No pasien, Nama Pasien, Jenis Kelamin, Umur Pasien, Nama Obat)

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Apotek
{
    int noPasien, umurPasien;
    char namaPasien[20], namaObat[20], jenisKelamin[20];
};
struct node
{
    struct Apotek apotek;
    struct node *next;
};
struct node *head = NULL;
struct node *tail = NULL;

bool isEmpty();
void toMenu();
void WriteFile();
void InsertData(struct Apotek apotek);
void DisplayData();
void SearchData();
void SortData();

void main()
{
    struct Apotek apotek;
    int pilihan;
    char username[9], password[9];
    system("cls");
    printf("=====Login Page=====\n");
    printf("\nMasukan Username    : "); scanf("%s", username);

    if(strcmp(username, "admin") == 0)
    {
        printf("\nMasukan Password    : "); scanf("%s", password);
        if(strcmp(password, "adiarta") == 0)
        {
            printf("\nLogin Sukses!\n");
            printf("Tekan apa saja untuk masuk kedalam menu"); getch();
            do{
                system("cls");
                printf("Menu Apotek\n");
                printf("1. Mencetak Database ke File Text\n");
                printf("2. Menambahkan Data Baru ke Database\n");
                printf("3. Menampilkan Isi Database\n");
                printf("4. Mengupdate Data di Database\n");
                printf("5. Menghapus Data di Database\n");
                printf("6. Mencari Data di Database\n");
                printf("7. Mengurutkan Data di Database\n");
                printf("8. Keluar dari Program\n");
                printf("Masukan pilihanmu : "); scanf("%d", &pilihan);

                switch (pilihan)
                {
                case 1:
                    WriteFile();
                    toMenu();
                    break;
                case 2:
                    printf("Masukan Nomor Pasien            : "); scanf("%d", &apotek.noPasien);
                    printf("Masukan Nama Pasien             : "); scanf("%s", apotek.namaPasien);
                    printf("Masukan Jenis Kelamin Pasien    : "); scanf("%s", apotek.jenisKelamin);
                    printf("Masukan Umur Pasien             : "); scanf("%d", &apotek.umurPasien);
                    printf("Masukan Nama Obat Pasien        : "); scanf("%s", apotek.namaObat);
                    fflush(stdin);
                    InsertData(apotek);
                    toMenu();
                    break;
                case 3:
                    DisplayData(head);
                    toMenu();
                    break;
/*
                case 4:
                    break;
                case 5:
                    break;
*/
                case 6:
                    SearchData();
                    toMenu();
                    break;
                case 7:
                    SortData();
                    toMenu();
                    break;
                default:
                    if(pilihan != 8)
                    {
                        printf("Masukan pilihan dari 1 sampai 7 saja");
                    }
                }
            } while(pilihan != 8);
        } else {
        printf("Password salah, mohon coba lagi..");
        }

    } else {
        printf("Username salah, mohon coba lagi..");
        }
}

bool isEmpty()
{
    return head == NULL;
}

void toMenu()
{
    printf("\n\nTekan apa saja untuk kembali ke menu utama ");
    getch();
}

void WriteFile()
{
    FILE *fptr = fopen("Database Apotek.txt","w");
    struct node *current = head;

    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");
    } else {
        while(current != NULL)
        {
            fprintf(fptr, "Nomor Pasien            : %d\n", current->apotek.noPasien);
            fprintf(fptr, "Nama Pasien             : %s\n", current->apotek.namaPasien);
            fprintf(fptr, "Jenis Kelamin Pasien    : %s\n", current->apotek.jenisKelamin);
            fprintf(fptr, "Umur Pasien             : %d\n", current->apotek.umurPasien);
            fprintf(fptr, "Nama Obat Pasien        : %s\n\n", current->apotek.namaObat);
            current = current->next;
        }
    }
    fclose(fptr);
}

void InsertData(struct Apotek apotek)
{
    if(isEmpty(head))
    {
        struct node *temp = (struct node*) malloc(sizeof(struct node));
        temp->apotek = apotek;
        temp->next = NULL;
        head = temp;
        tail = temp;
    } else {
        struct node *temp = (struct node*) malloc(sizeof(struct node));
        temp->apotek = apotek;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }
}

void DisplayData()
{
    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");
    } else {
        struct node *current = head;
        while(current != NULL)
        {
            printf("Nomor Pasien            : %d\n", current->apotek.noPasien);
            printf("Nama Pasien             : %s\n", current->apotek.namaPasien);
            printf("Jenis Kelamin Pasien    : %s\n", current->apotek.jenisKelamin);
            printf("Umur Pasien             : %d\n", current->apotek.umurPasien);
            printf("Nama Obat Pasien        : %s\n\n", current->apotek.namaObat);
            current = current->next;
        }
    }
}

void SearchData()
{
    int noP, found = 0;
    struct node *current = head;
    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");
    } else {
        printf("Masukan nomor pasien yang ingin dicari : "); scanf("%d", &noP);
        while(current != NULL)
        {
            if(current->apotek.noPasien == noP)
            {
                printf("Data yang dicari ditemukan! : \n\n");
                printf("Nomor Pasien            : %d\n", current->apotek.noPasien);
                printf("Nama Pasien             : %s\n", current->apotek.namaPasien);
                printf("Jenis Kelamin Pasien    : %s\n", current->apotek.jenisKelamin);
                printf("Umur Pasien             : %d\n", current->apotek.umurPasien);
                printf("Nama Obat Pasien        : %s\n\n", current->apotek.namaObat);
                found = 1;
                break;
            }
            current = current->next;
        }
        if(found == 0)
        {
            printf("Data yang dicari tidak ditemukan!");
        }
    }
}

void SortData()
{
    struct node *i, *j;
    int tempInt;
    char tempChar[20];

    if(isEmpty(head))
    {
        printf("Data dalam Database Kosong");
    } else {
        for(i = head; i != NULL; i = i->next)
        {
            for(j = i->next; j != NULL; j = j->next)
            {
                if((i->apotek.noPasien) > (j->apotek.noPasien))
                {
                    tempInt = i->apotek.noPasien;
                    i->apotek.noPasien = j->apotek.noPasien;
                    j->apotek.noPasien = tempInt;

                    tempInt = i->apotek.umurPasien;
                    i->apotek.umurPasien = j->apotek.umurPasien;
                    j->apotek.umurPasien = tempInt;

                    strcpy(tempChar, i->apotek.namaPasien);
                    strcpy(i->apotek.namaPasien, j->apotek.namaPasien);
                    strcpy(j->apotek.namaPasien, tempChar);

                    strcpy(tempChar, i->apotek.jenisKelamin);
                    strcpy(i->apotek.jenisKelamin, j->apotek.jenisKelamin);
                    strcpy(j->apotek.jenisKelamin, tempChar);

                    strcpy(tempChar, i->apotek.namaObat);
                    strcpy(i->apotek.namaObat, j->apotek.namaObat);
                    strcpy(j->apotek.namaObat, tempChar);
                }
            }
        }
        printf("Data sudah berhasil disorting secara Ascending");
    }
}