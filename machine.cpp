// بسم الله الرحمن الرحيم //

// File: Task_3 Machine Vole Simulator 
// Purpose: OOP Assignment 2
// Authors: Abdallah Gasem El-Sayed(20221101) , Ahmad karam Gamal(20221012) & Mohamed Abdelhamid Wagdy(20220294)
// Section: s25
// TA: maya ahmad 
// Date: 23 Nov 2023
// VERSION : 1.1

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<array>
#include<fstream>
using namespace std;

class Machine
{

private:
    // machine components:

    array<string,256>RAM ;
    array<int,16>Registers ;
    vector<string>Instructions ;
    // int program_counter ; not used yet
    string Instruction_Register ;

    // instruction slicing
    int Op_Code ;
    int register_location ; 
    int register_location1 ;  
    int register_location2 ;
    int Numerical_pattern_address ;

    string str_Op_Code ;
    string str_register_location ;
    string str_register_location1 ;
    string str_register_location2 ;
    string str_Numerical_pattern_address ;

    // useful variables ;
    string instruc ;
    string First_Byte ;
    string Second_Byte ;
    int count;
    int Reg_Pattern1 ; // for case 3
    string str_Jump_Value ;
    int Jump_Value ;
public:

    Machine(); // done
    void load_Instruction() ; // done till now 
    void load_RAM() ; // done
    void Instruction_Execution() ; // done 
    void Read_RAM() ; // done
    void Read_Registers() ; // done
    /*TESTING*/ // 
    friend string decimal_to_hex(int num) ;

 // doxesgyn comment ??


};

// USEFUL in opcode 3 
// a function that takes an integer number and returns a string of the conversion of this decimal integer to hexadecimal
string decimal_to_hex(int num) 
{
    string hex = ""; // an empty string to store the hexadecimal digits
    const string digits = "0123456789ABCDEF"; // a string of hexadecimal digits
    while (num > 0) { // while the number is positive
        int rem = num % 16; // find the remainder when dividing by 16
        hex += digits[rem]; // append the corresponding hexadecimal digit to the string
        num /= 16; // divide the number by 16
    }
    if (hex.empty()) { // if the string is empty, the number was zero
        hex = "00"; // return "00" as the hexadecimal string
    }
    else { // otherwise, the string has the hexadecimal digits in reverse order
        std::reverse(hex.begin(), hex.end()); // reverse the string
        if (hex.size() == 1) { // if the string has only one digit
            hex = "0" + hex; // add a leading zero
        }
    }
    return hex; // return the string
}

// TESTED
Machine :: Machine()
{
    // intializing variables
    register_location = 0 ;
    register_location1 = 0 ;
    register_location2 = 0 ;
    Numerical_pattern_address = 0 ;
    count = 0 ;
    Jump_Value = 0 ;

    // intializing registers 
    for (int i = 0 ; i < 16 ; i++)
    {
        Registers[i] = 0 ;
    }
    
    // intializing RAM
    for (int i = 0 ; i < 256 ; i++)
    {
        RAM[i] = "00" ;
    }


}

// TESTED
void Machine :: load_Instruction()
{
    // retrevieng the instructions from the a selected file :
    string filename ;
    std :: cout << "pls enter file name and its extension : " ;
    cin >> filename ;
    fstream file ;
    file.open(filename , ios :: in) ;

    if (!file.is_open())
    {
        cout << "an error happened while opening the file ! " ;
    }

    while (getline(file , instruc))
    {
        Instructions.push_back(instruc) ;
    }
    
    
    count = Instructions.size();




    // user defined instructions :
    // while (true)
    // {
    //     getline(cin , instruc) ;
    //     Instructions.push_back(instruc) ;

    //     if (instruc == "C000")
    //     {
    //         break;
    //     }
        
        
    // }

    // // useful in execution

    
}


// TESTED 
void Machine :: load_RAM()
{
    int j = 0 ;
    string lol = "" ;
    for ( int i = 0 ; i < Instructions.size() ; i++ )
    {
        lol = Instructions[i] ;
        First_Byte = lol.substr(0,2) ; 
        Second_Byte = lol.substr(2,4) ;

        // cout <<"1st byte : " << First_Byte << endl; // FOR TESTING
        // cout << "2nd byte : "<< Second_Byte << endl;

        RAM[j] = First_Byte ;
        RAM[j+1] = Second_Byte ;
        lol.clear() ;
        j += 2 ;
    }



}


void Machine :: Instruction_Execution()
{
    for (int i = 0 ; count != 0 ; i++) 
    { 
        // b instruction exec considring the slicing of instruction  : 
        if (Jump_Value != 0)
        {
            Instruction_Register = RAM[Jump_Value] + RAM[Jump_Value+1] ;
            count++ ;       // new instruction is performed to logic the for loop  
        }
        else
        {
            Instruction_Register = Instructions[i] ;
            
        }
        
        // slicing the the rest of the instruction
        str_Op_Code = Instruction_Register[0] ;
        Op_Code = stoi(str_Op_Code, nullptr ,16) ;  // converting string of hex to int  
        
        switch (Op_Code)
        {
            // load register no. instruction register[1] dec. with bit pattern in memeory add. (ir[2]+ir[3])
            case 1 :

                // getting the register address to be loaded :
                str_register_location = Instruction_Register[1] ;   // carry a string of reg add. to be loaded
                register_location = stoi(str_register_location, nullptr ,16) ;

                // getting the memory adrress :
                str_Numerical_pattern_address = Instruction_Register.substr(2,4);
                Numerical_pattern_address = stoi(str_Numerical_pattern_address, nullptr ,16) ; 

                // exection :
                Registers[register_location] = stoi(RAM[Numerical_pattern_address],nullptr,16) ; // conversion of the string bit pattern found in the memory address to int to fit in the int registers 

                break;

            case 2 :

                // getting the register address to be loaded : 
                str_register_location = Instruction_Register[1] ;
                register_location = stoi(str_register_location, nullptr ,16) ;

                // getiing the bit pattern to be loaded : ( Numerical_pattern_address is the numerical bit pattern in this case )
                str_Numerical_pattern_address = Instruction_Register.substr(2,4) ;
                Numerical_pattern_address = stoi(str_Numerical_pattern_address, nullptr ,16) ; 

                // execution :
                Registers[register_location] = Numerical_pattern_address ;
            
                break;

            case 3 :
                
                // getting the register location :
                str_register_location = Instruction_Register[1] ;
                register_location = stoi(str_register_location, nullptr ,16) ;

                // getiing the bit pattern of the register :
                Reg_Pattern1 = Registers[register_location] ;

                // getting the memory address to store the bit pattern :
                str_Numerical_pattern_address = Instruction_Register.substr(2,4) ;
                Numerical_pattern_address = stoi(str_Numerical_pattern_address, nullptr ,16) ; 

                // execution :
                if (Numerical_pattern_address == 00)
                {
                    std :: cout << "screen :\n";
                    std :: cout << Reg_Pattern1 ;
                }
                else
                {
                    RAM[Numerical_pattern_address] = decimal_to_hex(Reg_Pattern1) ;    
                }

                break;



            case 4 :

                // getiing the main register to move(copy) the bit  pattern in it and the other register to store :
                str_register_location1 = Instruction_Register[2] ;
                register_location1 = stoi(str_register_location1, nullptr ,16) ;

                str_register_location2 = Instruction_Register[3] ;
                register_location2 = stoi(str_register_location2, nullptr ,16) ;

                // execution :
                Registers[register_location2] = Registers[register_location1] ;

                break;



            case 5 :
                
                /* getting the 3 Registers addresses */

                // First Register carries sum
                str_register_location = Instruction_Register[1] ;
                register_location = stoi(str_register_location, nullptr ,16) ;

                // Second Register // 1st parameter in summtion
                str_register_location1 = Instruction_Register[2] ;
                register_location1 = stoi(str_register_location1, nullptr ,16) ;

                // 3rd Register  // 2nd parameter in summtion
                str_register_location2 = Instruction_Register[3] ;
                register_location2 = stoi(str_register_location2, nullptr ,16) ;
                
                // execution :
                Registers[register_location] = Registers[register_location1] + Registers[register_location2] ;

                break ;



            case 11 : // B

                // getiing register 00 pit pattern :
                register_location = Registers[0] ;

                // getting the compared register :
                str_register_location1 = Instruction_Register[1] ;
                register_location1 = stoi(str_register_location1, nullptr ,16) ;


                // getting the memory location to jump :
                str_Numerical_pattern_address = Instruction_Register.substr(2,4) ;
                Numerical_pattern_address = stoi(str_Numerical_pattern_address, nullptr , 16) ;

                // execution :
                if (register_location == register_location1)
                {
                    str_Jump_Value = RAM[Numerical_pattern_address] ;
                    Jump_Value = stoi(str_Jump_Value , nullptr , 16) ;
                    
                }
                else
                {
                    continue;
                }
                

                break;
            
            default:
                break;
        }


        count-- ;
    }
    




}

// TESTED
void Machine :: Read_RAM()
{
    std :: cout << "RAM : " << std :: endl ;
    std :: cout << "_________" << std :: endl ;
    std :: cout << std :: endl ;

    for (int i = 0 ; i < 256 ; i++)
    {
        if (i <= 15 )
        {
            cout << hex << "0" << i << "  " ;
        }
        else
        {
            cout << hex << i << "  " ;
        }
        
        std :: cout << RAM[i] << std :: endl ;
    }

    
}

// TESTED
void Machine :: Read_Registers()
{
    std :: cout << "Registers : " << std :: endl ;
    std :: cout << "____________" << std :: endl ;
    std :: cout << std :: endl ;

    for (int i = 0 ; i < 16 ; i++)
    {

        if (Registers[i] <= 15)
        {
            cout << "0" << hex << i << "  " ;
            std :: cout << "0" << hex << Registers[i] << std :: endl ;
        }
        else
        {
            cout << "0" <<hex << i << "  " ;
            std :: cout << hex << Registers[i] << std :: endl ;
            
        }
        
    }
    


}



int main()
{
    Machine a ;

    a.load_Instruction();
    a.load_RAM();
    a.Instruction_Execution() ;
    a.Read_RAM() ;
    a.Read_Registers();
 

    return 0 ;
}







// Convert a hexadecimal string to a decimal number
// int main() {
//   string hex = "2A";
//   int num = stoi(hex, nullptr, 16); // converts "2a" to 42 in decimal
//   std :: cout << "The hexadecimal string " << hex << " is equal to the decimal number " << num << std :: endl; // prints 42
//   return 0;
// }





// int main() {
//     int num = 42; // an integer to convert
//     stringstream ss; // a stringstream object
//     ss << std::hex << num; // insert the integer in hexadecimal format
//     std::string hex = ss.str(); // extract the string
//     std::cout << "The hexadecimal representation of " << num << " is " << hex << std :: endl;
//     return 0;
// }
