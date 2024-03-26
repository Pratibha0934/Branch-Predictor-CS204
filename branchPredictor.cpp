// Main file containing Branch Predictor Logic

#include <bits/stdc++.h>
#include <fstream>       // For reading and writing in files
#include "utilities.cpp" // For utility functions
#include "static.cpp"    // For static/common data elements

using namespace std;

// -------------------------------------------------------------------------------------------------------------
// Function for "ALWAYS TAKEN" predictor model
void alwaysTakenBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in); // Opening file

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open()) // if file opened successfully
    {
        while (getline(file, line) && i < 100000) // reading first million lines of file
        {
            if (line == "") // continue if line is empty
            {
                continue;
            }

            tokens = split(line);    // split line into tokens
            pc = tokens[2];          // extracting pc
            instruction = tokens[4]; // extracting instruction

            if (instruction[0] == 'b') // if instruction is a branch instruction
            {
                streampos prev = file.tellg();                   // store current file read state
                getline(file, nextLine);                         // get next line
                npc = split(nextLine)[2];                        // extract oc of next instruction
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16); // find difference in pc

                if (pcDiff == 4) // if branch not taken
                {
                    historyTable[pc] = false; // update history table
                }
                else // if branch taken
                {
                    historyTable[pc] = true; // update history table
                    correctPredictions++;    // increment correct predictions
                }

                offset = stoull(pc, 0, 16) + stoll(tokens[tokens.size() - 2] + tokens[tokens.size() - 1]);
                branchTargetBuffer[pc] = decToHex(offset); // update branch target buffer
                totalBranchInstructions++;                 // increment total branch instruction number
                file.seekg(prev);                          // restore file read state
            }

            i++;
        }
    }
    else // Exception Handling
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close(); // closing file
}

// -------------------------------------------------------------------------------------------------------------

// Function for "ALWAYS NOT TAKEN" predictor model
void alwaysNotTakenBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in); // if file opened successfully

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open()) // if file opened successfully
    {
        while (getline(file, line) && i < 100000) // reading first million lines of file
        {
            if (line == "") // continue if line is empty
            {
                continue;
            }

            tokens = split(line);    // split line into tokens
            pc = tokens[2];          // extracting pc
            instruction = tokens[4]; // extracting instruction

            if (instruction[0] == 'b') // if instruction is a branch instruction
            {
                streampos prev = file.tellg();                   // store current file read state
                getline(file, nextLine);                         // get next line
                npc = split(nextLine)[2];                        // extract oc of next instruction
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16); // find difference in pc

                if (pcDiff == 4) // if branch not taken
                {
                    historyTable[pc] = false; // update history table
                    correctPredictions++;     // increment correct predictions
                }
                else // if branch taken
                {
                    historyTable[pc] = true; // update history table
                }

                offset = stoull(pc, 0, 16) + 4;
                branchTargetBuffer[pc] = decToHex(offset); // update branch target buffer
                totalBranchInstructions++;                 // increment total branch instruction number
                file.seekg(prev);                          // restore file read state
            }

            i++;
        }
    }
    else // Exception Handling
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close(); // closing file
}

// -------------------------------------------------------------------------------------------------------------

// Function for "1-BIT DYNAMIC" predictor model
void oneBitDynamicBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in); // if file opened successfully

    string line, pc, npc, instruction, nextLine;
    long long pcDiff;
    vector<string> tokens;

    int i = 0;
    if (file.is_open()) // if file opened successfully
    {
        while (getline(file, line) && i < 100000) // reading first million lines of file
        {
            if (line == "") // continue if line is empty
            {
                continue;
            }

            tokens = split(line);    // split line into tokens
            pc = tokens[2];          // extracting pc
            instruction = tokens[4]; // extracting instruction

            if (instruction[0] == 'b') // if instruction is a branch instruction
            {
                streampos prev = file.tellg();                   // store current file read state
                getline(file, nextLine);                         // get next line
                npc = split(nextLine)[2];                        // extract oc of next instruction
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16); // find difference in pc

                if (predictionsTable.find(pc) != predictionsTable.end()) // if prediction available
                {
                    if (predictionsTable[pc] == (pcDiff != 4)) // if prediction is correct
                    {
                        correctPredictions++; // increment correct predictions
                    }
                    else // if prediction is incorrect
                    {
                        predictionsTable[pc] = !predictionsTable[pc]; // set new prediction
                    }
                }
                else // if prediction not available
                {
                    if (pcDiff == 4) // if branch not taken
                    {
                        predictionsTable[pc] = false;
                        // assuming initial prediction to be 'branch not taken'
                        correctPredictions++; // increment correct predictions
                    }
                    else // if branch taken
                    {
                        predictionsTable[pc] = true;
                    }
                }

                historyTable[pc] = (pcDiff != 4); // update history table
                branchTargetBuffer[pc] = npc;     // pudate branch target buffer
                totalBranchInstructions++;        // increment total branch instruction number
                file.seekg(prev);                 // restore file read state
            }
            i++;
        }
    }
    else // Exception Handling
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close(); // closing file
}

// -------------------------------------------------------------------------------------------------------------

// Function for "2-BIT DYNAMIC" predictor model
void twoBitDynamicBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in); // if file opened successfully

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open()) // if file opened successfully
    {
        while (getline(file, line) && i < 100000) // reading first million lines of file
        {
            if (line == "") // continue if line is empty
            {
                continue;
            }

            tokens = split(line);    // split line into tokens
            pc = tokens[2];          // extracting pc
            instruction = tokens[4]; // extracting instruction

            if (instruction[0] == 'b') // if instruction is a branch instruction
            {
                streampos prev = file.tellg();                   // store current file read state
                getline(file, nextLine);                         // get next line
                npc = split(nextLine)[2];                        // extract oc of next instruction
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16); // find difference in pc

                if (twoBitDynamicState.find(pc) == twoBitDynamicState.end()) // if dynamic state not available
                {
                    twoBitDynamicState[pc] = 0; // set initial state
                    if (pcDiff == 4)            // if branch not taken
                    {
                        correctPredictions++; // increment correct predictions
                    }
                    else // if branch taken
                    {
                        twoBitDynamicState[pc] = twoBitDynamicState[pc] + 1; // update state
                    }
                }
                else // if dynamic state available
                {
                    if (pcDiff == 4) // if branch not taken
                    {
                        if (twoBitDynamicState[pc] < 2) // for correct prediction
                        {
                            correctPredictions++; // increment correct predictions
                        }
                        twoBitDynamicState[pc] = (twoBitDynamicState[pc] == 0) ? 0 : twoBitDynamicState[pc] - 1; // update state
                    }
                    else // if branch taken
                    {
                        if (twoBitDynamicState[pc] > 1) // for correct prediction
                        {
                            correctPredictions++; // increment correct predictions
                        }
                        twoBitDynamicState[pc] = (twoBitDynamicState[pc] == 3) ? 3 : twoBitDynamicState[pc] + 1; // update state
                    }
                }

                // update branch target buffer
                if (twoBitDynamicState[pc] < 2)
                {
                    offset = stoull(pc, 0, 16) + 4;
                    branchTargetBuffer[pc] = decToHex(offset);
                }
                else
                {
                    offset = stoull(pc, 0, 16) + stoll(tokens[tokens.size() - 2] + tokens[tokens.size() - 1]);
                    branchTargetBuffer[pc] = decToHex(offset);
                }

                historyTable[pc] = (pcDiff != 4); // update history table
                totalBranchInstructions++;        // increment total branch instruction number
                file.seekg(prev);                 // restore file read state
            }
            i++;
        }
    }
    else // Exception Handling
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close(); // closing file
}

// -------------------------------------------------------------------------------------------------------------

// Function for printing output
void writeOutput(string predictionModel)
{
    double accuracy = (correctPredictions / (double)totalBranchInstructions) * 100; // claculating accuracy

    cout << "Prediction Method : " << predictionModel << endl;
    cout << "\nAccuracy : " << accuracy << "%" << endl;

    cout << "\nBranch Target Buffer for each Instruction (pc)" << endl;
    cout << "\nProgram Counter     : Target PC" << endl;

    for (auto i : branchTargetBuffer)
    {
        cout << i.first << "          : " << i.second << endl;
    }
}

// -------------------------------------------------------------------------------------------------------------

// MAIN FUNCTION
int main()
{

    initiateStatic(); // initiate static data elements

    cout << "==================== BRANCH PREDICTOR ====================" << endl;

    cout << "Enter the name/location if the file containing the trace : " << endl;
    string fileName;
    cin >> fileName;

    cout << "\n== Select the prediction model:" << endl;
    cout << "-> (a) Always Taken" << endl;
    cout << "-> (b) Always NOT Taken" << endl;
    cout << "-> (c) 1-BIT DYNAIMC" << endl;
    cout << "-> (d) 2-BIT DYNAMIC" << endl;

    cout << "\nEnter option (a/b/c/d): ";
    char model;
    cin >> model;

    cout << "\n==========================================================\n\n";
    switch (model)
    {
    case 'a':
        alwaysTakenBranchPredictor(fileName);
        writeOutput("ALWAYS TAKEN");
        break;
    case 'b':
        alwaysNotTakenBranchPredictor(fileName);
        writeOutput("ALWAYS NOT TAKEN");
        break;
    case 'c':
        oneBitDynamicBranchPredictor(fileName);
        writeOutput("1-BIT DYNAMIC");
        break;
    case 'd':
        twoBitDynamicBranchPredictor(fileName);
        writeOutput("2-BIT DYNAMIC");
        break;
    default:
        cout << "Invalid Input." << endl;
        break;
    }

    cout << "==========================================================" << endl;

    return 0;
}

// ------------------------------------------------- END -------------------------------------------------------