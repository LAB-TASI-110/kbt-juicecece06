#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk exit()

#define MAX_TICKETS 100
#define MAX_NAME_LEN 50
#define NUM_DESTINATIONS 3

// Struktur data untuk tiket
typedef struct {
    char nama_penumpang[MAX_NAME_LEN + 1];
    int tujuan; // 1:Medan, 2:Tarutung, 3:Sibolga
    int jumlah_tiket;
    long total_harga;
} Ticket;

// Array untuk menyimpan data tiket
Ticket tickets[MAX_TICKETS];
int ticket_count = 0;

// Harga tiket berdasarkan tujuan
const long HARGA_TIKET[] = {0, 50000, 40000, 60000}; // Index 0 tidak digunakan
const char* NAMA_TUJUAN[] = {"", "Medan", "Tarutung", "Sibolga"}; // Index 0 tidak digunakan

// Fungsi untuk menampilkan menu
void display_menu() {
    printf("\n--- MENU PROGRAM KOPERASI BINTANG TAPANULI ---\n");
    printf("1. Pesan tiket\n");
    printf("2. Tampilkan daftar tiket\n");
    printf("3. Keluar\n");
    printf("----------------------------------------------\n");
    printf("Pilih menu: ");
}

// Fungsi untuk memesan tiket
void pesan_tiket() {
    if (ticket_count >= MAX_TICKETS) {
        printf("\nPenyimpanan tiket penuh. Tidak bisa memesan tiket lagi.\n");
        return;
    }

    Ticket new_ticket;
    int choice_tujuan;
    int choice_jumlah_tiket;
    char buffer[100]; // Buffer untuk input string

    printf("\n--- PEMESANAN TIKET ---\n");

    // Input nama penumpang
    printf("Masukkan nama penumpang (maks %d karakter): ", MAX_NAME_LEN);
    // Menggunakan fgets untuk membaca string dengan spasi dan mencegah buffer overflow
    if (fgets(new_ticket.nama_penumpang, sizeof(new_ticket.nama_penumpang), stdin) != NULL) {
        // Menghilangkan newline character jika ada
        new_ticket.nama_penumpang[strcspn(new_ticket.nama_penumpang, "\n")] = 0;
    } else {
        printf("Gagal membaca nama penumpang.\n");
        return;
    }

    // Input tujuan dengan validasi
    do {
        printf("Pilih tujuan:\n");
        printf("  1. Medan (Rp %ld)\n", HARGA_TIKET[1]);
        printf("  2. Tarutung (Rp %ld)\n", HARGA_TIKET[2]);
        printf("  3. Sibolga (Rp %ld)\n", HARGA_TIKET[3]);
        printf("Masukkan pilihan tujuan (1-%d): ", NUM_DESTINATIONS);
        // Menggunakan fgets dan sscanf untuk input integer yang lebih aman
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &choice_tujuan) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            choice_tujuan = 0; // Set ke nilai tidak valid agar loop berulang
        }
    } while (choice_tujuan < 1 || choice_tujuan > NUM_DESTINATIONS);
    new_ticket.tujuan = choice_tujuan;

    // Input jumlah tiket dengan validasi
    do {
        printf("Masukkan jumlah tiket (> 0): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &choice_jumlah_tiket) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            choice_jumlah_tiket = 0; // Set ke nilai tidak valid agar loop berulang
        }
    } while (choice_jumlah_tiket <= 0);
    new_ticket.jumlah_tiket = choice_jumlah_tiket;

    // Hitung total harga otomatis
    new_ticket.total_harga = (long)new_ticket.jumlah_tiket * HARGA_TIKET[new_ticket.tujuan];

    // Simpan tiket ke array
    tickets[ticket_count++] = new_ticket;

    printf("\n--- TIKET BERHASIL DIBUAT ---\n");
    printf("Nama: %s\n", new_ticket.nama_penumpang);
    printf("Tujuan: %s\n", NAMA_TUJUAN[new_ticket.tujuan]);
    printf("Jumlah tiket: %d\n", new_ticket.jumlah_tiket);
    printf("Total harga: Rp %ld\n", new_ticket.total_harga);
    printf("-------------------------------\n");
}

// Fungsi untuk menampilkan daftar tiket
void tampilkan_daftar_tiket() {
    printf("\n--- DAFTAR TIKET TERPESAN ---\n");
    if (ticket_count == 0) {
        printf("Belum ada tiket yang dipesan.\n");
        return;
    }

    for (int i = 0; i < ticket_count; i++) {
        printf("Tiket #%d\n", i + 1);
        printf("  Nama: %s\n", tickets[i].nama_penumpang);
        printf("  Tujuan: %s\n", NAMA_TUJUAN[tickets[i].tujuan]);
        printf("  Jumlah tiket: %d\n", tickets[i].jumlah_tiket);
        printf("  Total harga: Rp %ld\n", tickets[i].total_harga);
        printf("-------------------------------\n");
    }
}

int main() {
    int choice;
    char buffer[10]; // Buffer untuk input pilihan menu

    // Mengatur agar stdin tidak memiliki karakter newline yang tersisa setelah sscanf
    // Ini membantu fgets bekerja dengan baik setelah sscanf
    setbuf(stdout, NULL); 

    do {
        display_menu();
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &choice) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            choice = 0; // Set ke nilai tidak valid
        }

        switch (choice) {
            case 1:
                pesan_tiket();
                break;
            case 2:
                tampilkan_daftar_tiket();
                break;
            case 3:
                printf("Terima kasih telah menggunakan layanan Koperasi Bintang Tapanuli.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
