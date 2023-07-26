#include <iostream> //input/output strea
#include <fstream> //file stream
#include <string>
#include <vector>
#include <stdexcept> //This program uses exceptions to handle issues with opening files
using namespace std;


//Function definitions
int FahrenheitToCelcius(int); //Converts temp from F to C
void InputData(vector<string>&, vector<int>&); //Saves and converts data from file into

// vectors
void OutputData(vector<string>&, vector<int>&); //Outputs data from vectors into a
// different file

int main() {
    vector<string> nameList; //Stores city names
    vector<int> tempList; //Stores city temperatures in Fahrenheit
    try {
        InputData(nameList, tempList);
        OutputData(nameList, tempList);
    }
    catch (exception& runtime_error) {
        cout << runtime_error.what();
    }
    return 0;
}

int FahrenheitToCelcius(int temperatureF) {
    int temperatureC; //Temperatures are returned as integers
    temperatureC = static_cast<int>(temperatureF - 32) * (5.0 / 9);
    return temperatureC;
}

void InputData(vector<string>& nameList, vector<int>& tempList) {
    ifstream inFS;
    string cityName;
    int cityTemperatureF;
    int cityTemperatureC;
    inFS.open("FahrenheitTemperature.txt");
    if (!inFS.is_open()) { //Throws an exception and exits function if input file is not opened
      throw "Unable to open input file";
    }
    inFS >> cityName;
    while (!inFS.fail()) {
        nameList.push_back(cityName);
        inFS >> cityTemperatureF;
        if (inFS.fail()) { //Executes if there is no temperature by city name
            cout << "Line " << nameList.size() << ": No temperature found for "
            << cityName << endl;
            tempList.push_back(NULL);
        }
        else { //If there are no errors reading temperature
            cityTemperatureC = FahrenheitToCelcius(cityTemperatureF);
            tempList.push_back(cityTemperatureC); //Adds converted temperature to tempList vector
        }
        inFS.ignore(); //Ignores the new line character at the end of line.
        //It's not needed in this case.
        inFS.clear(); //Ignores any potential errors by inFS.fail(), so the next loop iteration may continue
        inFS >> cityName;
    }
    inFS.close(); //Closes input stream from file
}

void OutputData(vector<string>& nameList, vector<int>& tempList) {
    ofstream outFS;
    outFS.open("CelsiusTemperature.txt");
    if (!outFS.is_open()) { //Throws an exception and exits function if output file is not opened
        throw "Unable to open output file";
    }
    for (int i = 0; i < nameList.size(); i++) {
        outFS << nameList.at(i) << " " << tempList.at(i) << endl;
    }
    outFS.close(); //Closes output stream from file
}