// Helper file containing Utility Functions to support the main logic of branch predictor

#include <bits/stdc++.h>

using namespace std;

long long totalBranchInstructions; // stores total number of branch instruction encounteres
long long correctPredictions;      // stores total number of correct predictions made

map<string, string> branchTargetBuffer;        // maps the pc of a branch instruction to its predicted target pc
unordered_map<string, bool> predictionsTable;  // maps the pc of a branch instruction to it prediction
unordered_map<string, bool> historyTable;      // stores whether a branch instruction was taken/not taken in last encounter
unordered_map<string, int> twoBitDynamicState; // maps the pc of branch predictor to its 2-bit dynamic state

// Function to initialise all static data elemets
void initiateStatic()
{
    totalBranchInstructions = 0;
    correctPredictions = 0;
    predictionsTable.clear();
    branchTargetBuffer.clear();
    historyTable.clear();
}