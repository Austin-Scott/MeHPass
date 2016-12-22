#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <locale>

using namespace std;

fstream fNouns;
vector<string> Nouns;
fstream fVerbs;
vector<string> Verbs;
fstream fAdjectives;
vector<string> Adjectives;
locale loc;


int randInt(int lowest, int highest)   {
    return rand()%((highest+1)-lowest)+lowest;
}

int loadFiles()   {
    fNouns.open("noun.txt");
    if(fNouns.is_open())   {
        while(!fNouns.eof())  {
            string read="";
            getline(fNouns,read);
            Nouns.push_back(read);
        }
        fNouns.close();

        fVerbs.open("verbs.txt");
        if(fVerbs.is_open())   {
            while(!fVerbs.eof())    {
            string read="";
            getline(fVerbs,read);
            Verbs.push_back(read);
        }

            fVerbs.close();

            fAdjectives.open("adjectives.txt");
            if(fAdjectives.is_open())   {
                while(!fAdjectives.eof())   {
            string read="";
            getline(fAdjectives,read);
            Adjectives.push_back(read);
        }

                fAdjectives.close();

            } else  {
                cout<<"Error opening \"adjectives.txt\""<<endl;
                return 1;
            }
        } else {
            cout<<"Error opening \"verbs.txt\""<<endl;
            return 1;
        }
    } else {
        cout<<"Error opening \"noun.txt\""<<endl;
        return 1;
    }
    return 0;
}

string gfc(string input)   { //return the first character of input in the range a-z converting numbers into letter Ex: 3 to e
    //TODO:write this function
    string result = input;
    string lowercase="";
    for(string::size_type i=0;i<result.length();i++)   {
    lowercase+=tolower(result[i],loc);
    }
    result=lowercase;

    return result;
}

string getNoun(string input)   {
    vector<string> selections;
    for(int i=0;i<Nouns.size();i++)   {
        if(Nouns.at(i).substr(0,1).compare(input)==0)   {
            selections.push_back(Nouns.at(i));
        }
    }
    return selections.at(randInt(0,selections.size()-1));
}

string getVerb(string input)   {
    vector<string> selections;
    for(int i=0;i<Verbs.size();i++)   {
        if(Verbs.at(i).substr(0,1).compare(input)==0)   {
            selections.push_back(Verbs.at(i));
        }
    }
    return selections.at(randInt(0,selections.size()-1));
}

string getAdjective(string input)    {
    vector<string> selections;
    for(int i=0;i<Adjectives.size();i++)   {
        if(Adjectives.at(i).substr(0,1).compare(input)==0)   {
            selections.push_back(Adjectives.at(i));
        }
    }
    return selections.at(randInt(0,selections.size()-1));
}

string Convert(string input)    {
    string result="";
    if(input.length()==1)   {
        result+="The "+getNoun(gfc(input.substr(0,1)))+".";
    } else if(input.length()==2)   {
        result+="The "+getAdjective(gfc(input.substr(0,1)))+" "+getNoun(gfc(input.substr(1,1)))+".";
    } else if(input.length()==3)   {
        result+="The "+getAdjective(gfc(input.substr(0,1)))+" "+getNoun(gfc(input.substr(1,1)))+" will "+getVerb(gfc(input.substr(2,1)))+".";
    } else if(input.length()==4)   {
        result+="Many "+getAdjective(gfc(input.substr(0,1)))+" "+getNoun(gfc(input.substr(1,1)))+"s and "+getNoun(gfc(input.substr(2,1)))+"s like to "+getVerb(gfc(input.substr(3,1)))+".";
    } else if(input.length()==5)   {
        result+="Will the "+getAdjective(gfc(input.substr(0,1)))+" "+getNoun(gfc(input.substr(1,1)))+" "+getVerb(gfc(input.substr(2,1)))+" near the "+getAdjective(gfc(input.substr(3,1)))+" "+getNoun(gfc(input.substr(4,1)))+"?";
    } else  {
        int mode=0;
        for(string::size_type i=0;i<input.length();i++)    {
            if(mode==0)   {
                result+="The";
                mode++;
            }
            if(mode==1)   {
                result+=" "+getAdjective(gfc(input.substr(i,1)));
                mode++;
            } else if(mode==2)  {
                result+=" "+getNoun(gfc(input.substr(i,1)));
                mode++;
            } else if(mode==3)  {
                result+=" "+getVerb(gfc(input.substr(i,1)))+"s";
                mode++;
            }
            if(mode==4)   {
                result+=", and the";
                mode=1;
            }
        }
        result+=".";
    }
    return result;
}

int main(int argc, char* argv[])   {
    srand(time(nullptr));
    if(argc!=2)   {
        cout<<"Proper usage: \"mehpass.exe password\""<<endl;
    } else {
        if(loadFiles()==0)
        cout<<"Generated mnemonic for "<<argv[1]<<":"<<endl<<"\""<<Convert(argv[1])<<"\""<<endl;
    }
}
