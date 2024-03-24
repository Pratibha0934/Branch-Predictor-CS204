#include <bits/stdc++.h>

using namespace std;

long long totalBranchInstructions;
long long correctPredictions;

map<string, string> branchTargetBuffer;
unordered_map<string, bool> predictionsTable;
unordered_map<string, bool> historyTable;
unordered_map<string, int> twoBitDynamicState;

void initiateStatic()
{
    totalBranchInstructions = 0;
    correctPredictions = 0;
    predictionsTable.clear();
    branchTargetBuffer.clear();
    historyTable.clear();
}