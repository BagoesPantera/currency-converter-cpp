#include <iostream>
#include <stdio.h>
#include <algorithm> //for transform
#include <ctime>//for time
#include <iomanip>//for setprecision (digit after decimal point)
#include <fstream>//for history
#include <sstream>//for history

using namespace std;

// Menu
int pilihan(){
    int pilihan;
    system("cls");
    cout << "Program Konversi Mata Uang" << endl;
    cout << "1. Konversi" << endl;
    cout << "2. Lihat Riwayat Konversi" << endl;
    cout << "3. Hapus Riwayat Konversi" << endl;
    cout << "4. Tutup" << endl;
    cout << "Pilih [1-4] : ";
    cin >> pilihan;

    return pilihan;
}
// History
int addHistory(string output, string date){
    ofstream File;
    FILE* fout = fopen("history.txt", "a+");
    fprintf(fout, "%s, Tanggal :  %s", output.c_str(), date.c_str());
    fclose(fout);
    return 0;
}
int readHistory(){
    char buf[1000];
    FILE* fout = fopen("history.txt", "r");

    if(!fout){
        cout << endl << "Tidak ada riwayat konversi.";
        return 0;
    }

    cout << endl << "Riwayat Konversi" << endl;
    while (fgets(buf, sizeof buf, fout) != NULL) {
        cout << buf;
    }
    fclose(fout);
   return 0;
}
int removeHistory(){
    string choice;
    int rmStatus;

    cout << endl << "Yakin ingin menghapus semua riwayat konversi ? (Y/N) : ";
    cin >> choice;

    //upper
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    
    if (choice == "Y"){
        rmStatus = remove("history.txt");
        if(rmStatus == 0){
            cout << "Riwayat berhasil dihapus !";
            return 0;
        }else{
            cout << "Riwayat gagal dihapus, coba lagi !";
            cout << endl << rmStatus;
            return 0;
        }
    }else if (choice == "N"){
        return 0;
    }else{
        cout << "Input tidak valid.";
        return 0;
    }
    
    return 0;
}
int convertion(){
    //var
    string from,to;
    string currencySym[7] = {"USD", "IDR", "JPY", "KRW", "RUB", "EUR", "GBP"};
    float currencyNum[7] = {1, 14319.32, 113.84, 1192.3, 74.03, 0.886, 0.755};
    int arrLength = sizeof(currencySym) / sizeof(currencySym[0]);
    int INTfrom = 9 ,INTto = 9, amount;
    float total;

    //menu
    cout << endl << "Konversi Mata Uang";
    cout << endl << "Mata Uang yang Tersedia : ";
    for (int i = 0; i < arrLength; i++){
        cout << currencySym[i] << " ";
    }
    cout << endl;
    cout << "Dari Mata Uang : ";
    cin >> from;
    cout << "Ke Mata Uang : ";
    cin >> to;
    cout << "Jumlah Uang (Tanpa ,) : ";
    cin >> amount;

    // UPPERCASE
    transform(from.begin(), from.end(), from.begin(), ::toupper);
    transform(to.begin(), to.end(), to.begin(), ::toupper);

    // Convert to integer for EVERYTHING
    for(int i = 0; i < arrLength; i++){
        if(from == currencySym[i]){
            INTfrom = i;
        }
        if(to == currencySym[i]){
            INTto = i;
        }
    }

    // Validating wannabe
    if(INTfrom == 9 || INTto == 9){
        cout << "Input Mata Uang Tidak Valid";
        return 0;
    }
    if(INTfrom == INTto){
        cout << "Mata Uang Tidak Boleh Sama !";
        return 0;
    }
    if(amount < 1){
        cout << "Jumlah Uang Harus Lebih Dari 0 !";
        return 0;
    }
    
    total = (currencyNum[INTto]/currencyNum[INTfrom]) * amount; //pemikiran random, tiba2 aja kepikiran

    // PREPARING OUTPUT
    //output
    stringstream outputString, outputDate;
    string outputs, outputd;

    outputString << amount << " " << from << " = " << fixed << setprecision(2) << total << " " << to;
    outputs = outputString.str();
    
    // Update Time (kinda sus xD)
    time_t now = time(0);
    char* time_now = ctime(&now);// ctime parameter must be pointer
    outputDate << time_now;
    outputd = outputDate.str();
    
    now = now - (24*60*60);// yesterday
    char* time_update = ctime(&now);

    
    // DA REAL OUTPUT RIGHT HERE
    cout << endl << "Hasil";
    cout << endl << outputs << endl;
    cout << "Tanggal di update : " << time_update << endl;

    //addhistory
    addHistory(outputs,outputd);

    return 0;
}
int main(){
    int choice = pilihan();
    while (choice){
        switch (choice){
            case 1:
                convertion();
                break;
            case 2:
                readHistory();
                break;
            case 3:
                removeHistory();
                break;
            case 4:
                cout << "Program ditutup...";
                return 0;
                break;
            default:
                break;
        }

        string lanjut;
        cout << endl << "Lanjutkan ? (Y/N) : ";
        cin >> lanjut;

        transform(lanjut.begin(), lanjut.end(), lanjut.begin(), ::toupper);

        if (lanjut == "Y"){
            choice = pilihan();
        }else if (lanjut == "N"){
            cout << "Program ditutup";
            return 0;
        }else{
            cout << "Input tidak valid.";
            return 0;
        }
    }

    return 0;
}
