#include <iostream>

using namespace std;

int pilihan(){
    int pilihan = 0;
    system("cls");
    cout << "Program Konversi Mata Uang" << endl;
    cout << "1. Konversi" << endl;
    cout << "2. Lihat Riwayat Konversi" << endl;
    cout << "3. Hapus Riwayat Konversi" << endl;
    cout << "4. Tutup" << endl;
    cout << "Pilih [1-4] : ";
    cin >> pilihan;
    if(cin.fail()){
        cout << "Masukan Angka !";
        exit(0);
    }

    return pilihan;
}
 
int validate(string *currencySym, int arrLength, char *curr){
    // Uppercase
    int i = 0;
    while(curr[i]!='\0'){ 
        if(curr[i]>='a' && curr[i]<='z'){ 
            curr[i]=curr[i]-32; 
        } 
        ++i; 
    }
    // Validate
    int result = 9;
    for(int i = 0; i < arrLength; i++){
        curr != currencySym[i] ?: result = i;
    }
    if (result == 9){
        cout << "Masukan mata uang tidak valid !";
        exit(0);
    }
    return result;
}

string convertion(){
    char from[1000],to[1000];
    string currencySym[9] = {"USD", "IDR", "JPY", "KRW", "RUB", "EUR", "GBP", "ETH", "BTC"};
    float currencyNum[9] = {1, 14319.32, 113.84, 1192.3, 74.03, 0.886, 0.755, 0.00030443, 0.00002336};
    int arrLength = sizeof(currencySym) / sizeof(currencySym[0]);
    int  amount;
    float total;

    cout << "Konversi Mata Uang" << endl;
    cout << "Mata Uang yang Tersedia : ";
    for (int i = 0; i < arrLength; i++){
        cout << currencySym[i] << " ";
    }
    cout << endl;

    // From
    cout << "Dari Mata Uang : ";
    cin >> from;
    int INTfrom = validate(currencySym, arrLength, from);

    // To
    cout << "Ke Mata Uang : ";
    cin >> to;
    int INTto = validate(currencySym, arrLength, to);

    // Validate from to
    if(INTfrom == INTto){   
        cout << "Mata Uang Tidak Boleh Sama !";
        exit(0);
    }

    // Amount
    cout << "Jumlah Uang (Tanpa titik / koma (1.000 = 1000)) : ";
    cin >> amount;
    // Validating
    // Check amount's input
    if(cin.fail()){
        cout << "Masukan Angka !";
        exit(0);
    }
    if(amount < 1){
        cout << "Jumlah Uang Harus Lebih Dari 0 !";
        exit(0);
    }
    
    total = (currencyNum[INTto]/currencyNum[INTfrom]) * amount;
    string output = to_string(amount) + " " + currencySym[INTfrom] + " = " + to_string(total) + " " + currencySym[INTto];

    return output;
}

int main(){

    int choice = pilihan();
    int id = 0, historySize = 2;
    string history[historySize];

    while (choice){
        switch (choice){
            case 1:
                {
                    string output = convertion();
                    cout << endl << "HASIL" << endl;
                    cout << output << endl;

                    // Getting user's date
                    time_t userTime = time(0);
                    char* time_now = ctime(&userTime);
                    // Input history
                    if (id == historySize){
                        for (int i = 0; i < historySize; i++){
                            history[i] = history[i + 1];
                        }
                        history[id - 1] = output + ", Tanggal " + time_now;
                    }else{
                        history[id] = output + ", Tanggal " + time_now;
                        ++id;
                    }
                    // ...and make it yesterday
                    time_t yesterday = userTime - (24*60*60);
                    char* time_yesterday = ctime(&yesterday);// ctime parameter must be pointer

                    cout << "Terakhir diupdate tanggal : " << time_yesterday << endl;
                }
                break;
            case 2:
                cout << endl << "Riwayat Konversi" << endl;
                if (id == 0){
                    cout << endl << "Tidak ada riwayat";
                }else{
                    for (int i = 0; i < id ; i++){
                        cout << i + 1 <<". " << history[i];
                    }
                }
                break;
            case 3:
                int choiceDel;
                cout << endl << "Yakin hapus semua riwayat ? 1. Ya, 2. Tidak : ";
                cin >> choiceDel;

                switch (choiceDel){
                    case 1:
                        id = 0;
                        cout << "Semua riwayat berhasil dihapus !";
                        break;
                    case 2:
                        cout << "Riwayat tidak di hapus.";
                        break;
                    default:
                        cout << "Tidak valid.";
                        break;
                }
                break;
            case 4:
                 if (id > 0){
                    cout << "Menghapus riwayat..." << endl;
                    cout << "Riwayat terhapus." << endl;
                }
                cout << "Terima kasih. Program ditutup.";
                return 0;
                break;
            default:
                cout << "Tidak valid";
                return 0;
                break;
        }
        int lanjut;
        cout << endl << "Lanjut ? 1.Ya 2.Tidak" << endl;
        cin >> lanjut;
        switch (lanjut){
            case 1:
                choice = pilihan();
                break;
            case 2:
                if (id > 0){
                    cout << "Menghapus riwayat..." << endl;
                    cout << "Riwayat terhapus." << endl;
                }
                cout << "Terima kasih. Program ditutup.";
                return 0;
                break;
            default:
                cout << "Masukan tidak valid, program ditutup !";
                return 0;
                break;  
        }
    }
    return 0;
}
