/*
Author: Fahid Ahmed
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int main() {
  // Initialize counters for correct answers and total questions
  int numCorrect = 0;
  int totalQuestions = 0;

  // Open the CSV file containing questions and answers
  ifstream fin("numbers.csv");
  if (fin.fail()){
    cerr<<"File cannot be opened";   // Error handling if the file fails to open
    exit(1);
  }

  string txt, ans, junk;  // Variables to store the question, answer, and any junk data
  float percent = 0.0;  // Variable to store the user's percentage of correct answers

  // Arrays to store the questions and answers
  string question[20];
  string answer[20];
  int index = 0;
  
  // Read questions and answers from the file and store them in arrays
  while (getline(fin, txt, ',')){   // Read each question (separated by commas in the CSV)
    getline(fin, ans);   // Read the corresponding answer
    totalQuestions+=1;   // Increment total number of questions
    question[index]=txt;  // Store question in the array
    answer[index]=ans;  // Store corresponding answer in the array
    index++;  // Move to the next index
  }

  // Save the total number of questions for later use in percentage calculation
  int totalq = totalQuestions;
  
  while(totalQuestions>0 && percent<60.0){
    srand(time(NULL));   // Seed the random number generator to ensure randomness in question selection
    int num = rand()%totalQuestions;   // Randomly select a question from the remaining questions
   
    cout<<"What is "<<question[num] << "?" << endl;  // Display the randomly selected question
    double user_answer;
    cin >> user_answer;   // Get user's answer
    cout << endl;
    
    // Compare user's answer with the correct answer (converted to a float)
    if (user_answer == stof(answer[num])){
      cout << "True"<<endl;  // If the answer is correct, print "true"
      numCorrect+=1.0;   // Increment the number of correct answers
    }
    else{
      cout << "False" << endl;  // If the answer is incorrect, print "false"
    }
    
     // Calculate the percentage of correct answers
    percent = double(numCorrect)/totalq*100.0;
    cout<< percent << "%"; // Display the current percentage of correct answers
    
     // If the user has answered at least 60% of questions correctly, display a message
    if (percent >= 60.0){
      cout << "At least 60% is correct." << endl;
      cout << "Percentage Correct: " << percent << "%" << endl;
    }
    
      // Move the used question and answer to the end of the arrays, effectively removing it
    swap(question[num], question[totalQuestions-1]);
    swap(answer[num], answer[totalQuestions-1]);
    totalQuestions--;  // Decrease the number of remaining questions
  }
 
  // Close the file after reading all the data
fin.close();
}