#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

// exercise 1.10.1 Age
// Write a program that asks input from the keyboard and prints the result on the screen and write it to a file.
// The question asked is : "What is your age?"

// This helper function give us the current time since 1970
// it's not required for the exercise 1, but I wanted to play with time a bit.
int current_time(){
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );

    return int(ms.count());
}

int age_logger () {
    // Variable initialization
    int age;
    std::ofstream age_db;

    // Getting inputs with a prompt
    std::cout << "What is your age?\n";
    std::cin >> age;

    // Output to the screen
    std::cout << "Your age is : " << age << " years old!\n";
    
    // Output to the file
    // Here the two flag out and app means its open for writing and appending
    age_db.open("age_db.txt",std::ofstream::out | std::ofstream::app);
    age_db << "time: " << current_time() << ",  age: " <<  age << std::endl;
    age_db.close();
}

// exercise 1.10.2 Arrays and Pointers
// Write the following declarations: 
// 1.a) pointer to a character 
// 1.b) array of 10 integers
// 1.c) pointer to an array of 10 integers
// 1.d) pointer to an array of character strings
// 1.e) pointer to pointer to a character
// 1.f) integer constant
// 1.g) pointer to an integer constant
// 1.h) constant pointer to an integer
// 1.i) Initialize all these object

int ptr_initialization(){
    // 1.a)
    std::unique_ptr<char> char_ptr{new char};
    // 1.b)
    int int_array[10];
    // 1.c) 
    std::unique_ptr<int[]> int_array_ptr{new int[10]};
    // 1.d)
    std::unique_ptr<char[]> char_array_ptr{new char[10]};
    // 1.e)
    std::unique_ptr<char>& char_ptr_ptr = char_ptr;

    // 1.f)
    const int CONSTANT_INTEGER = 10;

    // 1.g)
    const int& cont_int_ptr = CONSTANT_INTEGER;

    // 1.h
    const std::unique_ptr<int> int_const_ptr{new int};

    // Initialization
    *char_ptr = 'c';

    for (unsigned i = 0; i < 10; i++){
        int_array[i] = i;
    }

    for (unsigned i = 0; i < 10; ++i){
        int_array_ptr[i] = 0;
    }
    
    for (unsigned i = 0; i < 10; i++){
        char_array_ptr[i] = 'a'+i;
    }

    *int_const_ptr = 10;


    

}

// Make a small program that create arrays on the stack (fixed-size arrays)
// and arrays on the heap (using allocation). 
// Use valgrind to check what happens when you do not delete them correctly
// To run valgrind need to do :
// > valgrind ./a.out 
// after compiling the code with g++
int memory_leak(){
    const int num_element = 10;
    int num_array = 10;
    for(int i = 0; i < num_array; i++){
        int stack_array[10] = {};
        int *heap_array = new int[10];
    }
}

// exercices 1.10.3 Read the Header of a Matrix Market File
// need to read the matrix market file using fstream and print the number of rows
// and columns, and the number of non-zeroes on the screen
// there is an example matrix_market file in .txt format taken from the book
int main(){
    // Variable initialization
    std::string line;
    std::string delimiter = "\t";
    std::ifstream matrix_market ("matrix_market.txt");
    
    if (matrix_market.is_open()){
        while (getline(matrix_market, line)){
            // only read the first line of the header (without comments)
            if(line[0] != '%'){

                // Here we will parse using stream
                std::string buffer;                 
                std::stringstream stream(line);

                std::vector<std::string> tokens; // Create vector to hold our words
                while(stream >> buffer){
                    tokens.push_back(buffer);
                }

                // now tokens contain the #row, #col and #non zero element
                std::cout << "# row = " << tokens[0] << std::endl;
                std::cout << "# col = " << tokens[1] << std::endl;
                std::cout << "# non-zero elements = " << tokens[2] << std::endl;

                break;
            }

        }
        matrix_market.close();
    }
    else {
        std::cout << "Unable to open file";
    } 
}