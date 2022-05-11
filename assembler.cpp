#include<iostream>
#include<fstream>
#include<string>
#include <map>
using namespace std;

string decToBinary(int n)
{

    int binaryNum[32];
    string binary;


    int i = 0;
    while (n > 0) {


        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }


    for (int j = i - 1; j >= 0; j--)

        binary += to_string(binaryNum[j]);
    return binary;
}

string addZeros(string s){
    int n = s.length();
    int req = 15-n;
    while(req>0){
        s = "0" + s;
        req--;
    }
    return s;
}

// bool variable(string s){

// }

bool symbol(string s){
    if(s[0]=='('){
        return true;
    }
    return false;
}

bool A_inst(string s){
    string sub = s.substr(1);
    if(s[0]=='@'){
    // if(sub.find_first_not_of("0123456789")!=string::npos){
    //     return true;
    // }
    return true;
    }
    return false;
}

// bool C_inst(string s){
//     if()
// }

int main(){
    map<string,string> preDef;
    map<string,string> compTable;
    map<string,string> destTable;
    map<string,string> jumpTable;
    preDef["R0"]="0";
    preDef["R1"]="1";
    preDef["R2"]="2";
    preDef["R3"]="3";
    preDef["R4"]="4";
    preDef["R5"]="5";
    preDef["R6"]="6";
    preDef["R7"]="7";
    preDef["R8"]="8";
    preDef["R9"]="9";
    preDef["R10"]="10";
    preDef["R11"]="11";
    preDef["R12"]="12";
    preDef["R13"]="13";
    preDef["R14"]="14";
    preDef["R15"]="15";

    string c_inst = "111";


    // computing instructions
    compTable["0"] = "0101010";
    compTable["1"] = "0111111";
    compTable["-1"] = "0111010";
    compTable["D"] = "0001100";
    compTable["A"] = "0110000";
    compTable["!D"] = "0001101";
    compTable["!A"] = "0110001";
    compTable["-D"] = "0001111";
    compTable["-A"] = "0110011";
    compTable["D+1"] = "0011111";
    compTable["A+1"] = "0110111";
    compTable["D-1"] = "0001110";
    compTable["A-1"] = "0110010";
    compTable["D+A"] = "0000010";
    compTable["D-A"] = "0010011";
    compTable["A-D"] = "0000111";
    compTable["D&A"] = "0000000";
    compTable["D|A"] = "0010101";
    compTable["M"] = "1110000";
    compTable["!M"] = "1110001";
    compTable["-M"] = "1110011";
    compTable["M+1"] = "1110111";
    compTable["M-1"] = "1110010";
    compTable["D+M"] = "1000010";
    compTable["D-M"] = "1010011";
    compTable["M-D"] = "1000111";
    compTable["D&M"] = "1000000";
    compTable["D|M"] = "1010101";

    // destination instructions
    destTable[""] = "000";
    destTable["M"] = "001";
    destTable["D"] = "010";
    destTable["MD"] = "011";
    destTable["A"] = "100";
    destTable["AM"] = "101";
    destTable["AD"] = "110";
    destTable["AMD"] = "111";

    // jump table instrucitons
    jumpTable[""] = "000";
    jumpTable["JGT"] = "001";
    jumpTable["JEQ"] = "010";
    jumpTable["JGE"] = "011";
    jumpTable["JLT"] = "100";
    jumpTable["JNE"] = "101";
    jumpTable["JLE"] = "110";
    jumpTable["JMP"] = "111";
    // cout<<compTable["1"]<<endl;
    string destination;
    string comp1;
    string comp2;
    string dest;
    string jump;
    string comp_binary;
    string dest_binary;
    string jump_binary;

    string instruction;

    string line;
    ifstream File("input.asm");
    ofstream output;
    output.open("output.asm");

    while(getline(File,instruction)){

        if(A_inst(instruction)){
            // cout<<line<<endl;
        if(instruction[1]=='R'){
            // cout<<line<<endl;
            string sub = instruction.substr(1);

            // sub.erase(sub.length()-1);
            string num1 = preDef[sub];
            // cout<<sub<<endl;
            string temp3 = decToBinary(stoi(num1));
            string temp4 = addZeros(temp3);
            string final1 = "0" + temp4;
            output<<final1<<endl;
        }
        else{
            string num = instruction.substr(1);
            // cout<<num;
            string temp1 = decToBinary(stoi(num));
            string temp2 = addZeros(temp1);
            string final = "0" + temp2;
            output<<final<<endl;
        }


        }

    if(A_inst(instruction)==false && symbol(instruction)==false){
        int equalSignPosition = instruction.find("=");
        int semiColonPosition = instruction.find(";");
    // if(equalSignPosition!=string::npos){
    //     destination = instruction.substr(0,equalSignPosition);
    // }
        if(equalSignPosition!=string::npos){
            destination = instruction.substr(0,equalSignPosition);
            if(semiColonPosition!=string::npos){
                comp1 = instruction.substr(equalSignPosition+1,semiColonPosition - equalSignPosition - 1);
                jump = instruction.substr(semiColonPosition + 1,instruction.length() - semiColonPosition - 1);

            }
            else{
                comp1 = instruction.substr(equalSignPosition+1,instruction.length() - equalSignPosition - 1);
            }
        }
        else  {
        // Case 3: comp ; jump
            comp1 = instruction.substr(0,semiColonPosition);
            jump = instruction.substr(semiColonPosition + 1,instruction.length() - semiColonPosition - 1);
        }
        // cout<<destination<<endl;
        // cout<<comp1<<endl;
        // cout<<jump<<endl;
        if (destTable.find(destination) != destTable.end()) {
            dest_binary = destTable[destination];
        }
        if (compTable.find(comp1) != compTable.end()) {
            comp_binary = compTable[comp1];
        }
        if (jumpTable.find(dest) != jumpTable.end()) {
            jump_binary = jumpTable[jump];
        }
        string c_binary = c_inst + comp_binary + dest_binary  + jump_binary;
        // cout<<c_binary.length()<<endl;
        // cout<<c_binary<<endl;
        output<<c_binary<<endl;
        }


    }
}
