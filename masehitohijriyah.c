#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//======================================================
//  Deklarasi Prosedur
void menu();
void konversiHijriyah();
void konversiKeHijriyah(int tanggal, int bulan, int tahun);
int validasiAngka(int min, int max, char *teks);
int validasiTahun(char *teks);
int isLeapYear(int year);
void clearBuffer();

//======================================================
//  Clear input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//======================================================
//  Validasi Input Angka
int validasiAngka(int min, int max, char *teks) {
    int i, salah = 0;
    char angka[100];
    int val;
    int panjang;

    if (fgets(angka, sizeof(angka), stdin) != NULL) {
        // Hapus newline character jika ada
        angka[strcspn(angka, "\n")] = 0;
        panjang = strlen(angka);

        // Cek jika input kosong
        if (panjang == 0) {
            printf("INPUT TIDAK BOLEH KOSONG!\n");
            printf("Masukkan %s : ", teks);
            return validasiAngka(min, max, teks);
        }

        for (i = 0; i < panjang; i++) {
            if (angka[i] < '0' || angka[i] > '9') {
                salah++;
                break; // Keluar loop jika sudah ada karakter tidak valid
            }
        }

        if (salah > 0) {
            printf("INPUT HARUS ANGKA YANG SESUAI PADA KETENTUAN!\n");
            printf("Masukkan %s : ", teks);
            return validasiAngka(min, max, teks);
        } else {
            val = atoi(angka);
            if (val < min || val > max) {
                printf("INPUT HARUS ANTARA %d - %d!\n", min, max);
                printf("Masukkan %s : ", teks);
                return validasiAngka(min, max, teks);
            } else {
                return val;
            }
        }
    }
    return -1; // Fallback
}

//======================================================
//  Validasi Input Tahun (bisa berapa saja)
int validasiTahun(char *teks) {
    int i, salah = 0;
    char angka[100];
    int val;
    int panjang;

    if (fgets(angka, sizeof(angka), stdin) != NULL) {
        // Hapus newline character jika ada
        angka[strcspn(angka, "\n")] = 0;
        panjang = strlen(angka);

        // Cek jika input kosong
        if (panjang == 0) {
            printf("INPUT TIDAK BOLEH KOSONG!\n");
            printf("Masukkan %s : ", teks);
            return validasiTahun(teks);
        }

        for (i = 0; i < panjang; i++) {
            if (angka[i] < '0' || angka[i] > '9') {
                salah++;
                break; // Keluar loop jika sudah ada karakter tidak valid
            }
        }

        if (salah > 0) {
            printf("INPUT HARUS ANGKA!\n");
            printf("Masukkan %s : ", teks);
            return validasiTahun(teks);
        } else {
            val = atoi(angka);
            
            // Validasi tahun minimal 1 (tidak ada batas maksimal)
            if (val < 1) {
                printf("TAHUN TIDAK BOLEH KURANG DARI 1!\n");
                printf("Masukkan %s : ", teks);
                return validasiTahun(teks);
            } else {
                return val;
            }
        }
    }
    return -1; // Fallback
}

// Cek tahun kabisat
int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0)   return 1;
    return 0;
}

//======================================================
//  Fungsi konversi Masehi ke Hijriyah (ALGORITMA YANG LEBIH AKURAT)
void konversiKeHijriyah(int tanggal, int bulan, int tahun) {
    // Algoritma konversi yang lebih sederhana dan akurat
    // Berdasarkan perhitungan: 1 tahun Hijriyah ≈ 354.36708 hari
    // Tanggal referensi: 16 Juli 622 M = 1 Muharram 1 H
    
    // Hitung Julian Day untuk tanggal input
    int a = (14 - bulan) / 12;
    int y = tahun + 4800 - a;
    int m = bulan + 12 * a - 3;
    
    long jd = tanggal + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    
    // Julian Day untuk tanggal referensi (16 Juli 622 M)
    long jdRef = 16 + (153 * 4 + 2) / 5 + 365 * (622 + 4800) + (622 + 4800) / 4 - (622 + 4800) / 100 + (622 + 4800) / 400 - 32045;
    
    // Selisih hari sejak 1 Muharram 1 H
    long selisihHari = jd - jdRef;
    
    // Hitung tahun Hijriyah (perkiraan)
    int tahunHijriyah = (int)(selisihHari / 354.36708) + 1;
    
    // Sisa hari dalam tahun Hijriyah
    int sisaHari = (int)(selisihHari - (tahunHijriyah - 1) * 354.36708);
    
    // Nama bulan Hijriyah
    char *namaBulanHijriyah[] = {
        "Muharram", "Safar", "Rabiul Awal", "Rabiul Akhir",
        "Jumadil Awal", "Jumadil Akhir", "Rajab", "Sya'ban",
        "Ramadan", "Syawal", "Dzulqa'dah", "Dzulhijjah"
    };
    
    // Distribusi hari per bulan Hijriyah (bergantian 30-29)
    int hariPerBulan[] = {30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29};
    
    // Tentukan bulan dan tanggal Hijriyah
    int bulanHijriyah = 1;
    int tanggalHijriyah = sisaHari + 1; // +1 karena mulai dari tanggal 1
    
    for (int i = 0; i < 12; i++) {
        if (tanggalHijriyah <= hariPerBulan[i]) {
            break;
        }
        tanggalHijriyah -= hariPerBulan[i];
        bulanHijriyah++;
    }
    
    // Jika bulan melebihi 12, tambah tahun
    if (bulanHijriyah > 12) {
        bulanHijriyah = 1;
        tahunHijriyah++;
    }
    
    // Nama bulan Masehi
    char *namaBulanMasehi[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    
    // Tampilkan hasil konversi
    printf("\n=================================================================\n");
    printf("||                   HASIL KONVERSI KALENDER                   ||\n");
    printf("=================================================================\n");
    printf("|| Tanggal Masehi  : %2d %s %4d M                        ||\n", tanggal, namaBulanMasehi[bulan-1], tahun);
    printf("|| Tanggal Hijriyah: %2d %s %4d H                        ||\n", tanggalHijriyah, namaBulanHijriyah[bulanHijriyah-1], tahunHijriyah);
    printf("=================================================================\n");
}

//======================================================
//  Main Program
int main() {
    menu();
    return 0;
}

//======================================================
//  Menu Utama
void menu() {
    int pilihan;

    printf("=================================================================\n");
    printf("||              PROGRAM KONVERSI MASEHI KE HIJRIYAH            ||\n");
    printf("=================================================================\n");
    printf("||                      Oleh Kalelfarrel97                     ||\n");
    printf("=================================================================\n");
    printf("|| 1. Mulai Program                                            ||\n");
    printf("|| 2. Keluar                                                   ||\n");
    printf("=================================================================\n");
    printf("Masukkan Nomor Menu yang Anda Inginkan : ");
    pilihan = validasiAngka(1, 2, "Pilihan Menu");

    if (pilihan == 1) {
        konversiHijriyah();
    } else {
        printf("Terima kasih telah menggunakan program ini.\n");
        exit(0);
    }
}

//======================================================
//  Fungsi Konversi Hijriyah (dengan validasi tanggal)
void konversiHijriyah() {
    int tanggal, bulan, tahun, pilih;
    int maxDay;
    int valid = 0;
    
    system("cls"); // Untuk membersihkan layar (Windows)

    printf("=================================================================\n");
    printf("||              PROGRAM KONVERSI MASEHI KE HIJRIYAH           ||\n");
    printf("=================================================================\n");
    printf("||                      Oleh Kalelfarrel97                    ||\n");
    printf("=================================================================\n");

    printf("|| Daftar Bulan Masehi:                                        ||\n");
    printf("|| [1] Januari       [7] Juli                                  ||\n");
    printf("|| [2] Februari      [8] Agustus                               ||\n");
    printf("|| [3] Maret         [9] September                             ||\n");
    printf("|| [4] April         [10] Oktober                              ||\n");
    printf("|| [5] Mei           [11] November                             ||\n");
    printf("|| [6] Juni          [12] Desember                             ||\n");
    printf("=================================================================\n");

    // Input dan validasi tanggal, bulan, tahun
    do {
        printf("Masukkan Tahun Masehi: ");
        tahun = validasiTahun("Tahun");
        
        printf("Masukkan Bulan (1-12): ");
        bulan = validasiAngka(1, 12, "Bulan");
        
        printf("Masukkan Tanggal (1-31): ");
        tanggal = validasiAngka(1, 31, "Tanggal");

        // Hitung maksimal hari untuk bulan & tahun tersebut
        if (bulan == 2) {
            if (isLeapYear(tahun)) maxDay = 29;
            else maxDay = 28;
        } else if (bulan == 4 || bulan == 6 || bulan == 9 || bulan == 11) {
            maxDay = 30;
        } else {
            maxDay = 31;
        }

        // Validasi tanggal sesuai dengan bulan dan tahun
        if (tanggal > maxDay) {
            printf("ERROR: Tanggal %d tidak valid untuk bulan %d tahun %d!\n", tanggal, bulan, tahun);
            printf("Tanggal harus antara 1 - %d\n\n", maxDay);
            valid = 0;
        } else {
            valid = 1;
        }
    } while (!valid);

    // Lakukan konversi
    konversiKeHijriyah(tanggal, bulan, tahun);

    printf("\n=================================================================\n");
    printf("|| 1. Ulangi Program                                            ||\n");
    printf("|| 2. Kembali ke Menu Utama                                     ||\n");
    printf("|| 3. Keluar                                                    ||\n");
    printf("=================================================================\n");
    printf("Masukkan Pilihan Anda : ");
    pilih = validasiAngka(1, 3, "Pilihan");

    if (pilih == 1)
        konversiHijriyah();
    else if (pilih == 2)
        menu();
    else {
        printf("Terima kasih telah menggunakan program ini.\n");
        exit(0);
    }
}