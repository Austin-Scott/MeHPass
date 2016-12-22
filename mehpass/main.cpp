#include <iostream>
#include <string>

using namespace std;

void loadFiles()   {

}

string Convert(string input)    {
    string result=input;
    return result;
}

int main(int argc, char* argv[])   {
    cout<<"Welcome to Memorize Hard Passwords or MeHPass for short!"<<endl;
    if(argc!=2)   {
        cout<<"Proper usage: \"mehpass.exe password\""<<endl;
    } else {
        loadFiles();
        cout<<"Generated mnemonic for "<<argv[1]<<":"<<endl<<Convert(argv[1])<<endl;
    }
}
