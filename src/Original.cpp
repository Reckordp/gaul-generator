#include <iostream>
#include <map>
using namespace std;
 
/*BUATAN FARIKUN AZIZ
program mengganti huruf tertentu dengan angka tententu
huruf a/A = 4, i/I = 1, g = 9, G = 6 dst...
*/
 
int main(int maxArgs, char* args[]){
 
    map<string,string> data;
    string kalimat{}, kunci{}, nilai{}, hasil{};
    int outerPanjang{}, innerPanjang{};
    data["i"] = "1";
    data["I"] = "1";
    data["a"] = "4";
    data["A"] = "4";
    data["z"] = "2";
    data["Z"] = "2";
    data["g"] = "9";
    data["G"] = "6";
    data["s"] = "5";
    data["S"] = "5";
    data["t"] = "7";
    data["T"] = "7";
    data["o"] = "0";
    data["O"] = "0";
 
    //ekstrak key dan valuenya
    for(auto i = data.begin(); i != data.end(); i++){
        kunci += i->first;
        nilai += i->second;
    }
 
    cout<<"masukan kalimat : "<<"\n";
    getline(cin,kalimat);
    outerPanjang = kalimat.length();
    innerPanjang = kunci.length();
   
    //pengecekan ini masih per huruf, bukan per kata, sehingga belum bisa merubah kata 'aku' menjadi 'q/Q', 'miliknya' menjadi 'milikx' atau kata2 allay lainnya, saya pribadi tidak suka bentuk penulisan seperti itu, barangkali dari kalian mau melanjutkan PEKERJAAN YANG MULIA INI? :)
    for(auto i {0}; i<outerPanjang; ++i){
        for(auto j {0}; j<innerPanjang; ++j){
            if(kalimat.at(i) == kunci.at(j)){
                hasil = kalimat.replace(i, 1, nilai.substr(j,1));
            }else{
                hasil = kalimat;
            }
        }
    }
    cout<<"\n"<<hasil<<"\n";
    return 0;
}