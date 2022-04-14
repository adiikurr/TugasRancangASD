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
#include <string.h>
#include <windows.h>
#include <conio.h>
#define ENTER 13
#define BKSP 8
#define TAB 9

struct Apotek
{
    int umurPasien,noPasien;
    char namaPasien[100], namaObat[100], jenisKelamin[100];
    struct Apotek *next;
}*head,*current,*tail;

struct History{
    char Hist[100];
    struct History *nextt;
}*hhead, *hcurrent, *htail;

int bdata=0,max=0;

void menu()
{
    struct Apotek apotek;

    int pilihan=0,a=70,b=70,c=70,d=70;
    system("cls"); system("color B0");
    gotoxy(25,2);while(a--){printf("=");Sleep(5);}
    gotoxy(40,4);printf("SELAMAT DATANG DI DATABASE APOTEK\n");
    gotoxy(43,5);printf("\t  APOTEK FTI\n");
    gotoxy(25,7);while(b--){printf("-");Sleep(5);}
    gotoxy(40,9);printf("Tekan 1. Mencetak Database ke File Text");
    gotoxy(40,10);printf("Tekan 2. Membuat Data Baru ke Database");
    gotoxy(40,11);printf("Tekan 3. Menambah Data ke Database");
    gotoxy(40,12);printf("Tekan 4. Menampilkan Isi Database");
    gotoxy(40,13);printf("Tekan 5. Mengupdate Data di Database");
    gotoxy(40,14);printf("Tekan 6. Menghapus Data di Database");
    gotoxy(40,15);printf("Tekan 7. Mencari Data di Database");
    gotoxy(40,16);printf("Tekan 8. Mengurutkan Data di Database");
    gotoxy(40,17);printf("Tekan 9. Melihat Riwayat Aktivitas di Database");
    gotoxy(40,18);printf("Tekan 10. Keluar Dari Program");
    gotoxy(25,20);while(c--){printf("=");Sleep(5);}
    gotoxy(40,22);printf("Masukkan Pilihan = ");
    gotoxy(25,24);while(d--){printf("-");Sleep(5);}
    gotoxy(60,22);scanf("%d", &pilihan);

    do{
        switch(pilihan){
            case 1:system("cls"); system("color A0"); writeFile();break;
            case 2:system("cls"); system("color A0"); InsertData(apotek);break;
            case 3:system("cls"); system("color A0"); addData();break;
            case 4:system("cls"); system("color A0"); DisplayData();break;
            case 5:system("cls"); system("color A0"); updateData();break;
            case 6:system("cls"); system("color A0"); deleteData();break;
            case 7:system("cls"); system("color A0"); searchData();break;
            case 8:system("cls"); system("color A0"); sortData();break;
            case 9:system("cls"); system("color A0"); displayHistory();break;
            case 10:system("cls"); system("color A0"); author();break;
            default:gotoxy(43,27);printf("Masukan pilihan dari 1 sampai 9 saja");
                gotoxy(45,28);printf("Tekan enter untuk kembali");
                getch();system("cls");
                menu();
        }
    }while(pilihan != 10);
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

void noData(){
    int a=45,b=45,c=9,d=9,x=0;

    if(isEmpty(head))
    {
        gotoxy(52,11);printf("TIDAK ADA ADATA");
        gotoxy(51,13);printf("SILAKAN ISI DAHULU");
        back();
    }
}

int isEmpty()
{
    return head == NULL;
}

void writeFile()
{
    noData();
    FILE *fptr = fopen("Database Apotek.txt","w");
    struct Apotek *current = head;

    gotoxy(52,11);printf("DATA SUDAH DICETAK");
    gotoxy(51,13);printf("SILAHKAN LIAT DATABASE");
    fprintf(fptr, "----------------------------------------------------------------------------------------\n");
    fprintf(fptr, "| %-12s | %-25s | %-15s | %-5s | %-15s |\n","NO.PASIEN","NAMA PASIEN","JENIS KELAMIN","UMUR","NAMA OBAT");
    fprintf(fptr, "----------------------------------------------------------------------------------------\n");
    while(current != NULL)
        {
            fprintf(fptr, "| %-12d | %-25s | %-15s | %-5d | %-15s |\n", current->noPasien,current->namaPasien ,current->jenisKelamin,current->umurPasien,current->namaObat);
            current = current->next;
        }
    fprintf(fptr, "----------------------------------------------------------------------------------------\n");
    fclose(fptr);
    back();

}

void resetData(){
    struct Apotek *temp = head, *next;
    while(temp != NULL){
        temp = temp->next;
        free(head);
        head = temp;
    }
}

void insertHistory(char isi[100]){
    hcurrent = (struct History*)malloc(sizeof(struct History));
    strcpy(hcurrent->Hist,isi);
    if(hhead == NULL){
		hhead = htail = hcurrent;
	}
	else{
		htail->nextt = hcurrent;
		htail = hcurrent;
	}
	htail->nextt = NULL;
	htail=hcurrent;
}

void InsertData(struct Apotek apotek)
{
    struct Apotek *temp;
    int i,a=12,b=70,c=70,d=70;
    char isi[100];

    if(bdata>0){
        resetData();
    }
    fflush(stdin);
    gotoxy(25,2);while(b--){printf("=");Sleep(2);}
    gotoxy(45,4);printf("MENU MEMBUAT DATABASE BARU \n");
    gotoxy(52,5);printf("\tAPOTEK\n");
    gotoxy(25,7);while(c--){printf("-");Sleep(2);}
    gotoxy(25,10);while(d--){printf("-");Sleep(2);}
    gotoxy(35,8);printf("MAKSIMAL DATA YANG DAPAT DIINPUT ADALAH 5\n");
    gotoxy(35,9);printf("Masukkan Jumlah Data yang Ingin Di Input : ");scanf("%d",&bdata);

    if(bdata>5){
        gotoxy(40,12);printf("DATA YANG DI INPUT MAKSIMAL 5!!!");
        gotoxy(43,14);printf("Tekan enter untuk kembali");getch();
        system("cls");InsertData(apotek);
    }
    else{
        for(i=0;i<bdata;i++){
            current = (struct Apotek*)malloc(sizeof(struct Apotek));
            gotoxy(35,12+(i*6));printf("Masukan Nomor Pasien            : "); scanf("%d", &current->noPasien);
            gotoxy(35,13+(i*6));printf("Masukan Nama Pasien             : "); scanf(" %[^\n]", current->namaPasien);strupr(current->namaPasien);
            gotoxy(35,14+(i*6));printf("Masukan Jenis Kelamin Pasien    : "); scanf(" %[^\n]", current->jenisKelamin);strupr(current->jenisKelamin);
            gotoxy(35,15+(i*6));printf("Masukan Umur Pasien             : "); scanf("%i", &current->umurPasien);
            gotoxy(35,16+(i*6));printf("Masukan Nama Obat Pasien        : "); scanf(" %[^\n]", current->namaObat);strupr(current->namaObat);
            printf("\n");
        if(isEmpty(head))
        {
            head = tail = current;
        }else {
            tail->next = current;
            tail = current;
        }tail->next = NULL;
        }sprintf(isi,"Admin membuat %i data baru",bdata);
        insertHistory(isi);
    }
    gotoxy(35,14+(i*6));printf("Kata Berhasil Dibuat dan Ditambahkan");
    gotoxy(35,15+(i*6));printf("Tekan enter untuk kembali");
    getch();
    menu();
}

void addData(){
    int i,s,a=70,b=70,c=70;
    max = 5-bdata;
    char isi[100];

    gotoxy(25,2);while(a--){printf("=");Sleep(5);}
    gotoxy(45,4);printf("MENU MENAMBAH DATA DI DATABASE \n");
    gotoxy(52,5);printf("\tAPOTEK");
    gotoxy(25,7);while(b--){printf("-");Sleep(2);}
    gotoxy(25,10);while(c--){printf("-");Sleep(2);}
    gotoxy(35,8);printf("MAKSIMAL DATA YANG DAPAT DIINPUT ADALAH %d\n",max);
    gotoxy(35,9);printf("Masukkan Jumlah Data yang Ingin di Tambah : ");scanf("%d",&s);

    if(s>max){
        gotoxy(40,12);printf("DATA YANG DI INPUT MAKSIMAL %d!!!",max);
        gotoxy(43,14);printf("Tekan enter untuk kembali");getch();
        system("cls");addData();
    }
    else{
       for(i=0;i<s;i++){
            current = (struct Apotek*)malloc(sizeof(struct Apotek));
            gotoxy(40,12+(i*6));printf("Masukan Nomor Pasien            : "); scanf("%d", &current->noPasien);
            gotoxy(40,13+(i*6));printf("Masukan Nama Pasien             : "); scanf(" %[^\n]", current->namaPasien);strupr(current->namaPasien);
            gotoxy(40,14+(i*6));printf("Masukan Jenis Kelamin Pasien    : "); scanf(" %[^\n]", current->jenisKelamin);strupr(current->jenisKelamin);
            gotoxy(40,15+(i*6));printf("Masukan Umur Pasien             : "); scanf("%i", &current->umurPasien);
            gotoxy(40,16+(i*6));printf("Masukan Nama Obat Pasien        : "); scanf(" %[^\n]", current->namaObat);strupr(current->namaObat);
            printf("\n");
        if(isEmpty(head))
        {
            head = tail = current;
        }else {
            tail->next = current;
            tail = current;
        }tail->next = NULL;
        bdata++;
        }sprintf(isi,"Admin menambah %i data baru",s);
        insertHistory(isi);
        gotoxy(35,14+(i*6));printf("Kata Berhasil Dibuat dan Ditambahkan");
        gotoxy(35,15+(i*6));printf("Tekan enter untuk kembali");getch();menu();
     }
}

void displayHistory(){
    int a=70,b=70,c=11;
    gotoxy(25, 2); while(a--){printf("="); Sleep(5);}
    gotoxy(40, 4); printf("\tRiwayat penggunaan Database");
    gotoxy(25, 6); while(b--){printf("="); Sleep(5);}

    hcurrent=hhead;
    if(hhead==NULL){
        gotoxy(53,c);printf("Tidak Ada Data");a++;
    }int m=0;
    while(hcurrent!=NULL){
        gotoxy(28,c);printf("%i.\t %s",m+1,hcurrent->Hist);m++;c++;
        hcurrent=hcurrent->nextt;
    }

   gotoxy(47,2+c);printf("Klik terserah untuk lanjut");getch();menu();
}

void DisplayData(){
    int a=14,b=89,c=89,d=89;char isi[100];
    gotoxy(18,2);while(c--){printf("=");Sleep(2);}
    gotoxy(50,4);printf("CETAK DATABASE APOTEK");
    gotoxy(52,5);printf("\tNAMA APOTEK");
    gotoxy(18,7);while(d--){printf("-");Sleep(2);}
    noData();

    int i=3;
    current = head;
    gotoxy(18,11);printf("----------------------------------------------------------------------------------------\n");
    gotoxy(18,12);printf("| %-12s | %-25s | %-15s | %-5s | %-15s |\n","NO.PASIEN","NAMA PASIEN","JENIS KELAMIN","UMUR","NAMA OBAT");
    gotoxy(18,13);printf("----------------------------------------------------------------------------------------\n");
    while(current != NULL){
        gotoxy(18,a);printf("| %-12d | %-25s | %-15s | %-5d | %-    15s |\n", current->noPasien,current->namaPasien ,current->jenisKelamin,current->umurPasien,current->namaObat);a++;
        current = current->next;
        printf("\n");
    }
    gotoxy(18,a);printf("----------------------------------------------------------------------------------------\n");
    gotoxy(45,a+5);printf("Tekan enter untuk kembali");
    getch();
    menu();
    sprintf(isi,"Admin melihat data");
    insertHistory(isi);
}

void login(){
    char u[10];int a=45,b=45,c=5,d=5;
    char p[10];
    time_t tm;
    int i = 0;char ch;
    time(&tm);

    system("cls"); system("color 90");
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
        loading(44,18);
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
system("cls");
    char a = 177, b = 219;
    gotoxy(40,15);
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\tLoading...\n\n");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++)
        printf("%c", a);

    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) {
        printf("%c", b);
        Sleep(30);
    }
}

void author(){
    int a=45,b=45,c=9,d=9,x=0;
    gotoxy(35,8);printf("+");while(a--){printf("=");Sleep(7);}printf("+");
    gotoxy(81,18);printf("+");
    while(c--){gotoxy(81,17-c);printf("|");Sleep(7);}
    while(b--){gotoxy(36+b,18);printf("=");Sleep(7);}
    gotoxy(35,18);printf("+");
    while(d--){gotoxy(35,9+d);printf("|");Sleep(7);}
    gotoxy(52,10);printf("ADI KURNIAWAN");
    gotoxy(54,12);printf("672021172");
    gotoxy(47,14);printf("ROBERTOS HARTANTO WIJAYA");
    gotoxy(54,16);printf("672021146");

    Sleep(1000);
    for(int i=5; i>-1; i--){
        gotoxy(43, 20);printf("Program will end in %i seconds!", i); Sleep(1000);
    }
system("cls"); system("color 07");
exit(0);
}

void deleteData(){
    int h=70,l=70,hapus;char isi[100];
    gotoxy(25,2);while(h--){printf("=");Sleep(2);}
    gotoxy(45,4);printf("MENGHAPUS DATA PASIEN APOTEK");
    gotoxy(55,5);printf("APOTEK FTI");
    gotoxy(25,7);while(l--){printf("-");Sleep(2);}
    noData();

    int a=0,nomor,b,ada=0;char del,y;
    struct Apotek *temp = head;
    current=head;
    gotoxy(38,11);printf("Cari nomor pasien yang mau dihapus : ");scanf("%d", &nomor);
    while(current!=NULL){
        if(current->noPasien == nomor){
            gotoxy(45,13);printf("Data yang dicari ditemukan! : \n\n");
            gotoxy(45,14);printf("Nomor Pasien            : %d\n", current->noPasien);
            gotoxy(45,15);printf("Nama Pasien             : %s\n", current->namaPasien);
            gotoxy(45,16);printf("Jenis Kelamin Pasien    : %s\n", current->jenisKelamin);
            gotoxy(45,17);printf("Umur Pasien             : %d\n", current->umurPasien);
            gotoxy(45,18);printf("Nama Obat Pasien        : %s\n\n", current->namaObat);
            gotoxy(45,20);printf("Apakah ada yakin ingin menghapus data? (Y/N) :          ");
            ada=1;
            break;
        } current=current->next;
    }if(ada==0){
        gotoxy(52,14);printf("Data tidak ada");
        gotoxy(43,18);printf("TEKAN ENTER UNTUK MENGULANG...");
        getch();system("cls");
        deleteData();
        }
    scanf(" %c",&del);
     if(del=='Y' || del=='y'){
            delPasien(nomor);
            sprintf(isi,"Admin menghapus data nomor pasien %i",nomor);
            insertHistory(isi);
            gotoxy(45,22);printf("Data berhasil dihapus");
            back();
     }
    else if(del=='n'||del=='N'){
            gotoxy(45,22);printf("Data batal dihapus");sprintf(isi,"Admin batal menghapus data nomor pasien %i",nomor);
            insertHistory(isi);gotoxy(45,23);printf("Klik terserah untuk lanjut");back();
    }
}

void delPasien(int nomor){
    if(head->noPasien==nomor){
        current = head;
        if(head==tail){
            head = tail = NULL;
            free(current);
        }else {
            head = head->next;
            free(current);
        }
    } else if(tail->noPasien==nomor){
        if(head==tail){
            head = tail = NULL;
            free(current);
        }else{
            struct Apotek *temp = head;
                while(temp->next!=tail){
                    temp = temp->next;
                }
                current = tail;
                tail = temp;
                free(current);
                tail->next = NULL;
        }
    } else {
        struct Apotek *temp = head;
        while(temp->next->noPasien!=nomor && temp!=tail){
            temp = temp->next;
        }
        current = temp->next;
        temp->next = temp->next->next;
        free(current);
    }
}

void searchData(){
    int h=70,l=70;
    system("cls");
    gotoxy(25,2);while(h--){printf("=");Sleep(2);}
    gotoxy(45,4);printf("MENCARI DATA PASIEN APOTEK");
    gotoxy(53,5);printf("APOTEK FTI");
    gotoxy(25,7);while(l--){printf("-");Sleep(2);}
    noData();

    int noP, found = 0,f,uP;
    char naP[30],jeK[30],naO[30],isi[100];
    current=head;
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
                    sprintf(isi,"Admin mencari nomor pasien %i",noP);insertHistory(isi);
                    displaySearch();
                    found = 1;
                    break;
                }
                current = current->next;
            }
            break;
        case 2:
            gotoxy(40,15);printf("Masukan nama pasien yang ingin dicari : "); scanf(" %[^\n]", &naP);strupr(naP);
            while(current != NULL){
                if(strcmp(current->namaPasien,naP)==0){
                    sprintf(isi,"Admin mencari nama pasien %s",naP);insertHistory(isi);
                    displaySearch();
                    found = 1;
                    break;
                }
                current = current->next;
            }
            break;
        case 3:
            gotoxy(40,15);printf("Masukan jenis kelamin pasien yang ingin dicari : "); scanf(" %[^\n]", &jeK);strupr(jeK);
            while(current != NULL){
                    if(strcmp(current->jenisKelamin , jeK)==0){
                        sprintf(isi,"Admin mencari jenis kelamin pasien %s",jeK);insertHistory(isi);
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
                        sprintf(isi,"Admin mencari umur pasien %i",uP);insertHistory(isi);
                        displaySearch();
                        found = 1;
                        break;
                    }
                    current = current->next;
            }
            break;
        case 5:
            gotoxy(40,15);printf("Masukan nama obat pasien yang ingin dicari : "); scanf(" %[^\n]", &naO);strupr(naO);
            while(current != NULL){
            if(strcmp(current->namaObat,naO)==0){
                sprintf(isi,"Admin mencari nama obat pasien %s",naO);insertHistory(isi);
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
            gotoxy(50,17);printf("Data yang dicari tidak ditemukan!");getch();searchData();
            sprintf(isi,"Admin gagal melakukan pencarian");
            insertHistory(isi);
        }
        back();
}

void displaySearch(){
    int c=89,d=89;char isi[100];
    system("cls");
    gotoxy(18,2);while(c--){printf("=");Sleep(2);}
    gotoxy(45,4);printf("HASIL PENCARIAN DATABASE APOTEK");
    gotoxy(52,5);printf("\tAPOTEK FTI");
    gotoxy(18,7);while(d--){printf("-");Sleep(2);}
    gotoxy(20,11);printf("----------------------------------------------------------------------------------------\n");
    gotoxy(20,12);printf("| %-12s | %-25s | %-15s | %-5s | %-15s |\n","NO.PASIEN","NAMA PASIEN","JENIS KELAMIN","UMUR","NAMA OBAT");
    gotoxy(20,13);printf("----------------------------------------------------------------------------------------\n");
    gotoxy(20,14);printf("| %-12d | %-25s | %-15s | %-5d | %-15s |\n", current->noPasien,current->namaPasien ,current->jenisKelamin,current->umurPasien,current->namaObat);
    gotoxy(20,15);printf("----------------------------------------------------------------------------------------\n");
    back();
}

void sortData(){
    int ad=0,a=70,b=70;
    gotoxy(25, 2); while(a--){printf("="); Sleep(2);}
    gotoxy(35, 4); printf("\t PENGURUTAN DATABASE BERDASARKAN");
    gotoxy(25, 6); while(b--){printf("="); Sleep(2);}
    noData();

    gotoxy(40,8);printf("Pilih (1/2)");
    gotoxy(42,9); printf("1. Ascending");
    gotoxy(42,10);printf("2. Descending");
    gotoxy(40,12);printf("Masukkan pilihan : ");scanf("%d",&ad);

    switch(ad){
        case 1:system("cls");sortDataAscend();break;
        case 2:system("cls");sortDataDescend();break;
        default:gotoxy(45,25);printf("Pilihan tidak tersedia");gotoxy(45,26);printf("Tekan enter untuk kembali");getch();sortData();break;
    }
}

void sortDataAscend(){
    struct Apotek *i, *j;
    int tempInt,pilih,a=70,b=70;
    char tempChar[100],isi[100];
    gotoxy(25, 2); while(a--){printf("="); Sleep(2);}
    gotoxy(37, 4); printf("\t PENGURUTAN SECARA ASCENDING");
    gotoxy(25, 6); while(b--){printf("="); Sleep(2);}
    gotoxy(40,9);printf("Apa yang ingin anda sortir?");
    gotoxy(40,10);printf("1. Nomor Pasien \t\t4. Umur");
    gotoxy(40,11);printf("2. Nama Pasien\t\t\t5. Nama Obat");
    gotoxy(40,12);printf("3. Jenis Kelamin");
    gotoxy(40,14);printf("Masukan data yang ingin sortir : "); scanf("%d", &pilih);loading();

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
            }sprintf(isi,"Admin mengurutkan nomor pasien secara ascending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan nama pasien secara ascending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan jenis kelamin pasien secara ascending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan umur pasien secara ascending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan nama obat pasien secara ascending");
            insertHistory(isi);
            break;
        default:
            printf("inputan salah");gotoxy(45,26);printf("Tekan enter untuk mengulang");getch();sortDataAscend();break;
    }
    system("cls");DisplayData();
}

void sortDataDescend(){
    noData();
    struct Apotek *i, *j;
    int tempInt,pilih,a=70,b=70;
    char tempChar[100],isi[100];

    gotoxy(25, 2); while(a--){printf("="); Sleep(5);}
    gotoxy(37, 4); printf("\t PENGURUTAN SECARA DESCENDING");
    gotoxy(25, 6); while(b--){printf("="); Sleep(5);}
    gotoxy(40,9);printf("Apa yang ingin anda sortir?");
    gotoxy(40,10);printf("1. Nomor Pasien \t\t4. Umur");
    gotoxy(40,11);printf("2. Nama Pasien\t\t\t5. Nama Obat");
    gotoxy(40,12);printf("3. Jenis Kelamin");
    gotoxy(40,14);printf("Masukan data yang ingin sortir : "); scanf("%d", &pilih);loading();

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
            }sprintf(isi,"Admin mengurutkan nomor pasien secara descending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan nama pasien secara descending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan nama pasien secara descending");
            insertHistory(isi);
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
            }sprintf(isi,"Admin mengurutkan nama pasien secara descending");
            insertHistory(isi);
            break;
        default:
            gotoxy(45,25);printf("inputan salah");gotoxy(45,26);printf("Tekan enter untuk mengulang");getch();sortDataDescend();break;
    }
    system("cls");DisplayData();
}

void updateData(){
    int k=70,w=70;
    gotoxy(25,2);while(k--){printf("=");Sleep(2);}
    gotoxy(45,4);printf("MENCARI DATA PASIEN APOTEK");
    gotoxy(53,5);printf("NAMA APOTEK\n");
    gotoxy(25,7);while(w--){printf("-");Sleep(2);}
    noData();

    struct Apotek *current;
    char namabaru[100],kelaminbaru[100],obatbaru[100],ch,isi[100];
    int edit=0,umurbaru,ada=0,i=0,j,found=0,nop,nobaru,pil,a=70,b=70,c=70,h=30,l=30,t=7;
    current=head;

    gotoxy(35, 9); printf("\tEdit Data Berdasarkan Nomor Pasien");
    gotoxy(40,10);printf("1. Nomor Pasien \t 4. Nama Obat");
    gotoxy(40,11);printf("2. Nama Pasien\t\t 5. Umur");
    gotoxy(40,12);printf("3. Jenis Kelamin");
    gotoxy(40,13);printf("Masukan data yang ingin diedit : "); scanf("%d", &pil);
    gotoxy(40,14);printf("Masukkan No Pasien: ");scanf("%d", &nop);

    switch(pil){
        case 1://nopasien
            while (current != NULL) {
                if (current->noPasien==nop){
                    gotoxy(45,16);printf("Data saat ini : %d ",current->noPasien);
                    gotoxy(45,17);printf("Data baru : ");scanf("%d",&nobaru);
                    current->noPasien = nobaru;
                    gotoxy(45,20);printf("Data berhasil diedit");
                    sprintf(isi,"Admin merubah nomor pasien");
                    insertHistory(isi);
                    found=1;
                    break;
                }
                current=current->next;
            }
            break;
        case 2://namapasien
            while (current != NULL) {
                if (current->noPasien==nop){
                    gotoxy(45,16);printf("Data saat ini : %s ",current->namaPasien);
                    gotoxy(45,17);printf("Data baru : ");scanf(" %[^\n]",&namabaru);strupr(namabaru);
                    strcpy(current->namaPasien, namabaru);
                    gotoxy(45,20);printf("Data berhasil diedit");
                    found=1;
                    sprintf(isi,"Admin merubah nama pasien");insertHistory(isi);
                    break;
                }
                current=current->next;

            }
            break;
        case 3://kelaminpasien
            while (current != NULL) {
                if (current->noPasien==nop){
                    gotoxy(45,16);printf("Data saat ini : %s ",current->jenisKelamin);
                    gotoxy(45,17);printf("Data baru : ");scanf(" %[^\n]",&kelaminbaru);strupr(kelaminbaru);
                    strcpy(current->jenisKelamin, kelaminbaru);
                    gotoxy(45,20);printf("Data berhasil diedit");
                    found=1;
                    sprintf(isi,"Admin merubah jenis kelamin pasien");insertHistory(isi);
                    break;
                }
                current=current->next;
            }
            break;
        case 4://obatpasien
            while (current != NULL) {
                if (current->noPasien==nop){
                    gotoxy(45,16);printf("Data saat ini : %s ",current->namaObat);
                    gotoxy(45,17);printf("Data baru : ");scanf(" %[^\n]",&obatbaru);strupr(obatbaru);
                    strcpy(current->namaObat,obatbaru);
                    gotoxy(45,20);printf("Data berhasil diedit");
                    found=1;
                    sprintf(isi,"Admin merubah nama obat pasien");insertHistory(isi);
                    break;
                }
                current=current->next;
            }
            break;
        case 5://umur pasien
            while (current != NULL) {
                if (current->noPasien==nop){
                    gotoxy(45,16);printf("Data saat ini : %d ",current->umurPasien);
                    gotoxy(45,17);printf("Data baru : ");scanf("%d",&umurbaru);
                    current->umurPasien = umurbaru;
                    gotoxy(45,20);printf("Data berhasil diedit");
                    found=1;
                    sprintf(isi,"Admin merubah umur pasien");insertHistory(isi);
                    break;
                }
                current=current->next;
            }
            break;
        default:
            gotoxy(52,25);printf(" Inputan salah");gotoxy(49,26);printf("Tekan enter untuk mengulang");getch();break;
        }

        if(found==0){
            gotoxy(45,25);printf("data tidak tersedia");
            gotoxy(45,26);printf("Tekan enter untuk kembali");
            getch();system("cls");
            sprintf(isi,"Admin gagal merubah data");insertHistory(isi);
            updateData();
            }
            back();
}

int main(){
    loading();
    login();
    menu();
}
