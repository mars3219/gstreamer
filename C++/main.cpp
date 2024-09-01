#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main() {
    ifstream fin("/workspace/C++/test.txt");
    if(!fin){
        cout << "/workspace/C++/test.txt 파일이 없습니다.";
        return 0;
    }

    ofstream fout("/workspace/C++/test_output.txt");
    if(!fout){
        cout << "/workspace/C++/test_output.txt 파일이 없습니다.";
        return 0;
    }

    int ch;

    while((ch = fin.get()) != EOF){
        ch = toupper(ch);
        cout << (char)ch;
        fout.put(ch);
    }
    fin.close();
    fout.close();
}