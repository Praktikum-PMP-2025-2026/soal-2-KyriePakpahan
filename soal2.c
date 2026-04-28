/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : 3
 *   Hari dan Tanggal    : Selasa, 28 April 2026 
 *   Nama (NIM)          : Kyrie Eleison Jacob Pakpahan (13224006)
 *   Nama File           : soal2.c
 *   Deskripsi           : Program yang mengimplementasikan dynamic array untuk menyimpan data barang, kemudian menampilkan 3 barang dari sesuai dengan prefix 
 *                          yang diinnputkan pengguna.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 100


/* Contoh Input
N nama1 nama2 ... namaN prefix 
*/

/*Contoh Output
Jika barang yang dicari ada
SUGGESTION nama1 nama2 nama3 

Jika barang yang dicari tidak ada
TIDAK ADA 
*/


/*
Testcase
5 carrier carabiner campstove matras compass ca 

Output Testcase
SUGGESTION campstove carabiner carrier 
*/


/*
Testcase
4 alpha beta gamma delta zz

Output Testcase
TIDAK ADA
*/


typedef struct {
    char *nama;
} Barang;

typedef struct {
    Barang *data;
    int size;
    int capacity;
} Inventory;

void init_inventory(Inventory *inv) {
    inv->size = 0;
    inv->capacity = 2;
    inv->data = (Barang *)malloc(inv->capacity * sizeof(Barang));
}

void add_barang(Inventory *inv, const char *nama) {
    // resize if full
    if (inv->size >= inv->capacity) {
        inv->capacity *= 2;
        Barang *temp = (Barang *)realloc(inv->data, inv->capacity * sizeof(Barang));
        if (!temp) {
            printf("Error: Gagal mengalokasikan memori.\n");
            return;
        }
        inv->data = temp;
    }
    inv->data[inv->size].nama = strdup(nama);
    inv->size++;
}



void free_inventory(Inventory *inv) {
    for (int i = 0; i < inv->size; i++) {
        free(inv->data[i].nama);
    }
    free(inv->data);
    inv->size = 0;
    inv->capacity = 0;
}

int main () {
    Inventory inv;
    init_inventory(&inv);

    int N;
    char prefix[MAX_NAME_LEN];

    // baca input dari user
    if (scanf("%d", &N) != 1){
        return 0;
    }

    for (int i = 0; i < N; i++) {
        char nama[MAX_NAME_LEN];
        if (scanf("%s", nama) != 1){
            free_inventory(&inv);
            return 0;
        }
        add_barang(&inv, nama);
    }

    if (scanf("%s", prefix) != 1){
        free_inventory(&inv);
        return 0;
    }

    int count = 0;
    for (int i = 0; i < inv.size; i++) {
        if (strncmp(inv.data[i].nama, prefix, strlen(prefix)) == 0) {
            if (count < 3) {
                if (count == 0) {
                    printf("SUGGESTION");
                }
                printf(" %s", inv.data[i].nama);
                count++;
            } else {
                break;
            }
        }
    }
    if (count == 0) {
        printf("TIDAK ADA");
    }
    printf("\n");

    free_inventory(&inv);
    return 0;
}
