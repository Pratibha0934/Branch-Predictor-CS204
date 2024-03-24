#include <bits/stdc++.h>
#include <fstream>
#include "utilities.cpp"
#include "static.cpp"

using namespace std;

void alwaysTakenBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in);

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open())
    {
        int x = 0;
        while (getline(file, line) && i < 100000)
        {
            if (line == "")
            {
                continue;
            }

            tokens = split(line);
            pc = tokens[2];
            instruction = tokens[4];

            if (instruction[0] == 'b')
            {
                streampos prev = file.tellg();
                getline(file, nextLine);
                npc = split(nextLine)[2];
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16);

                if (pcDiff == 4)
                {
                    historyTable[pc] = false;
                }
                else
                {
                    historyTable[pc] = true;
                    correctPredictions++;
                }

                offset = stoull(pc, 0, 16) + stoll(tokens[tokens.size() - 2] + tokens[tokens.size() - 1]);
                branchTargetBuffer[pc] = decToHex(offset);
                totalBranchInstructions++;
                file.seekg(prev);
            }

            i++;
        }
    }
    else
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close();
}

void alwaysNotTakenBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in);

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open())
    {
        int x = 0;
        while (getline(file, line) && i < 100000)
        {
            if (line == "")
            {
                continue;
            }

            tokens = split(line);
            pc = tokens[2];
            instruction = tokens[4];

            if (instruction[0] == 'b')
            {
                streampos prev = file.tellg();
                getline(file, nextLine);
                npc = split(nextLine)[2];
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16);

                if (pcDiff == 4)
                {
                    historyTable[pc] = false;
                    correctPredictions++;
                }
                else
                {
                    historyTable[pc] = true;
                }

                offset = stoull(pc, 0, 16) + 4;
                branchTargetBuffer[pc] = decToHex(offset);
                totalBranchInstructions++;
                file.seekg(prev);
            }

            i++;
        }
    }
    else
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close();
}

void oneBitDynamicBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in);

    string line, pc, npc, instruction, nextLine;
    long long pcDiff;
    vector<string> tokens;

    int i = 0;
    if (file.is_open())
    {
        while (getline(file, line) && i < 100000)
        {
            if (line == "")
            {
                continue;
            }
            tokens = split(line);
            pc = tokens[2];
            instruction = tokens[4];

            if (instruction[0] == 'b')
            {
                streampos prev = file.tellg();
                getline(file, nextLine);
                npc = split(nextLine)[2];
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16);

                if (predictionsTable.find(pc) != predictionsTable.end())
                {
                    if (predictionsTable[pc] == (pcDiff != 4))
                    {
                        correctPredictions++;
                    }
                    else
                    {
                        predictionsTable[pc] = !predictionsTable[pc];
                    }
                }
                else
                {
                    if (pcDiff == 4)
                    {
                        predictionsTable[pc] = false;
                        correctPredictions++;
                    }
                    else
                    {
                        predictionsTable[pc] = true;
                    }
                }

                historyTable[pc] = (pcDiff != 4);
                branchTargetBuffer[pc] = npc;
                totalBranchInstructions++;
                file.seekg(prev);
            }
            i++;
        }
    }
    else
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close();
}

void twoBitDynamicBranchPredictor(string fileName)
{
    fstream file;
    file.open(fileName, ios::in);

    string line, pc, npc, instruction, nextLine;
    long long pcDiff, offset;
    vector<string> tokens;

    int i = 0;
    if (file.is_open())
    {
        while (getline(file, line) && i < 100000)
        {
            if (line == "")
            {
                continue;
            }
            tokens = split(line);
            pc = tokens[2];
            instruction = tokens[4];

            if (instruction[0] == 'b')
            {
                streampos prev = file.tellg();
                getline(file, nextLine);
                npc = split(nextLine)[2];
                pcDiff = stoull(npc, 0, 16) - stoull(pc, 0, 16);

                if (twoBitDynamicState.find(pc) == twoBitDynamicState.end())
                {
                    twoBitDynamicState[pc] = 0;
                    if (pcDiff == 4)
                    {
                        correctPredictions++;
                    }
                    else
                    {
                        twoBitDynamicState[pc] = twoBitDynamicState[pc] + 1;
                    }
                }
                else
                {
                    if (pcDiff == 4)
                    {
                        if (twoBitDynamicState[pc] < 2)
                        {
                            correctPredictions++;
                        }
                        twoBitDynamicState[pc] = (twoBitDynamicState[pc] == 0) ? 0 : twoBitDynamicState[pc] - 1;
                    }
                    else
                    {
                        if (twoBitDynamicState[pc] > 1)
                        {
                            correctPredictions++;
                        }
                        twoBitDynamicState[pc] = (twoBitDynamicState[pc] == 3) ? 3 : twoBitDynamicState[pc] + 1;
                    }
                }

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

                historyTable[pc] = (pcDiff != 4);
                totalBranchInstructions++;
                file.seekg(prev);
            }
            i++;
        }
    }
    else
    {
        cout << "Error : Unable to open \"" << fileName << "\"" << endl;
        exit(-1);
    }

    file.close();
}

void writeOutput(string predictionModle)
{
    double accuracy = (correctPredictions / (double)totalBranchInstructions) * 100;

    cout << "Prediction Method : " << predictionModle << endl;
    cout << "\nAccuracy : " << accuracy << "%" << endl;

    cout << "\nBranch Target Buffer for each Instruction (pc)" << endl;
    cout << "\nProgram Counter     : Target PC" << endl;

    for (auto i : branchTargetBuffer)
    {
        cout << i.first << "          : " << i.second << endl;
    }
}

int main(int argc, char *argv[])
{

    initiateStatic();

    string fileName = argv[1];
    twoBitDynamicBranchPredictor(fileName);
    // alwaysNotTakenBranchPredictor(fileName);
    writeOutput("Test");

    return 0;
}