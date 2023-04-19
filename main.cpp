#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "basketballplayer.h"
#include "functions.h"
using namespace std;

// Directions here:
// https://umkc.app.box.com/s/1jti79n05j1nnxi7e9hsl00ifkwog26w

vector<BasketBallPlayer*> sortVector(vector<BasketBallPlayer*> input) {
    int size = input.size(), largestIndex, removeCount = 0;
    vector<BasketBallPlayer*> sortedInput;
    for (int i = 0; i < size - removeCount; i++) {
        // cout << "Processing size: "<< size << " of " << removeCount+1 << endl; // use for testing.
        largestIndex = 0;
        for (int j = 0; j < size - removeCount; j++) {
            // Find the index of the best player (highest playerValue and Eff Rating).
            if (input[j]->getValue() > input[largestIndex]->getValue()) {
                largestIndex = j;
            }
            else if (input[j]->getValue() == input[largestIndex]->getValue()) {
                if (input[j]->getEffRating() > input[largestIndex]->getEffRating()) {
                    largestIndex = j;
                }
            }
        }
        // Push back the player at largestIndex to sortedInput, and erase the player from input,
        // to prevent duplication.
        sortedInput.push_back(input[largestIndex]);
        input.erase(input.begin() + largestIndex);
        removeCount++; i--;
    }
    return sortedInput;
}

int main() {
    // Reset output.txt
    ofstream outFS;
    outFS.open("output.txt");
    if (outFS.is_open()) {
        outFS << "";
        outFS.close();
    }


    // Input data from file to vector
    ifstream inFS;
    string content,word,PlayerFirst,PlayerLast,PlayerName,TM,POS;
    int G,TRB,AST,STL,BLK,TOV,PTS,YRS,AGE;
    float eFG;
    vector<BasketBallPlayer*> bbpVector;
    vector<string> strVector;
    vector<vector<string>> csvImport;

    csvImport = readFromCSV("playerStatsNCAA.csv");
    for (int i = 0; i < csvImport.size(); i++) {
        PlayerName = csvImport[i][0];
        if (PlayerName == "Player")
            continue;
        G   = stoi(csvImport[i][1]);
        eFG = stof(csvImport[i][2]);
        TRB = stoi(csvImport[i][3]);
        AST = stoi(csvImport[i][4]);
        STL = stoi(csvImport[i][5]);
        BLK = stoi(csvImport[i][6]);
        TOV = stoi(csvImport[i][7]);
        PTS = stoi(csvImport[i][8]);
        TM  = csvImport[i][9];

        bbpVector.push_back(new CollegeBasketballPlayer(PlayerName, G, eFG, TRB, AST, STL, BLK, TOV, PTS, TM));
    }

    csvImport = readFromCSV("playerStatsPro.csv");
    for (int i = 0; i < csvImport.size(); i++){
        PlayerName = csvImport[i][0];
        if (PlayerName == "Player")
            continue;
        G   = stoi(csvImport[i][1]);
        eFG = stof(csvImport[i][2]);
        TRB = stoi(csvImport[i][3]);
        AST = stoi(csvImport[i][4]);
        STL = stoi(csvImport[i][5]);
        BLK = stoi(csvImport[i][6]);
        TOV = stoi(csvImport[i][7]);
        PTS = stoi(csvImport[i][8]);
        AGE = stoi(csvImport[i][9]);
        YRS = stoi(csvImport[i][10]);
        POS = csvImport[i][11];
        
        bbpVector.push_back(new ProBasketballPlayer(PlayerName, G, eFG, TRB, AST, STL, BLK, TOV, PTS, YRS, POS));
    }

    // Sort the entire basketball player vector from best to worst.
    vector<BasketBallPlayer*> sortedBBPVector = sortVector(bbpVector);

    // Create teams based on given players.
    // Note: any players with 0 Eff Rating are ignored in team creation process.
    // 0 Eff Rating conditions are in basketballplayer.cpp, in setEffRating().

    // NCAA TEAM
    // Create a team of 12 best college basketball players.
    vector<BasketBallPlayer*> teamNCAA;
    int teamNCAACount = 0;
    for (int i = 0; i < sortedBBPVector.size(); i++) {
        if (teamNCAACount < 12) {
            if (sortedBBPVector[i]->getPlayerType() == 'C' && sortedBBPVector[i]->getEffRating() > 0.0) {
                teamNCAA.push_back(sortedBBPVector[i]);
                teamNCAACount++;
            }
        }
    }
   
    // Print the NCAA team with lables.
    cout << "NCAA TEAM LIST" << endl << endl;
    cout << left << setw(25) << "NCAA Player Name";
    cout << left << setw(15) << "Player Value";
    cout << left << setw(15) << "Eff Rating";
    cout << left << setw(15) << "Efg Rating";
    cout << endl;
    for (int i = 0; i < 12; i++){
    	teamNCAA[i]->print();
	}
    cout << endl;

    // PRO & NCAA TEAM
    // Get 2 best pro players for each position.
    vector<BasketBallPlayer*> teamProCol;
    int numCenter = 0, numForward = 0, numGuard = 0;
    for (int i = 0; i < sortedBBPVector.size(); i++) {
        if (numCenter < 2 && sortedBBPVector[i]->getPos() == "C" && sortedBBPVector[i]->getEffRating() > 0.0) {
            teamProCol.push_back(sortedBBPVector[i]);
            numCenter++;
        }
        if (numForward < 2 && (sortedBBPVector[i]->getPos() == "PF" || sortedBBPVector[i]->getPos() == "SF") && sortedBBPVector[i]->getEffRating() > 0.0) {
            teamProCol.push_back(sortedBBPVector[i]);
            numForward++;
        }
        if (numGuard < 2 && (sortedBBPVector[i]->getPos() == "PG" || sortedBBPVector[i]->getPos() == "SG") && sortedBBPVector[i]->getEffRating() > 0.0) {
            teamProCol.push_back(sortedBBPVector[i]);
            numGuard++;
        }
        if (numCenter == 2 && numForward == 2 && numGuard == 2) {
            break;
        }
    }
    // Fill the rest of the position with NCAA players.
    int NCAAPlayerCount = 0;
    for (int i = 0; i < sortedBBPVector.size(); i++) {
        if (NCAAPlayerCount < 6 && sortedBBPVector[i]->getPlayerType() == 'C' && sortedBBPVector[i]->getEffRating() > 0.0) {
            teamProCol.push_back(sortedBBPVector[i]);
            NCAAPlayerCount++;
        }
    }

    // Sort teamProCol from best to worst.
    vector<BasketBallPlayer*> sortedTeamProCol = sortVector(teamProCol);

    // Print the sorted Pro / College team.
    cout << "NCAA/PRO TEAM LIST" << endl << endl;
    cout << left << setw(25) << "NCAA Player Name";
    cout << left << setw(15) << "Type";
    cout << left << setw(15) << "Position";
    cout << left << setw(15) << "Player Value";
    cout << left << setw(15) << "Eff Rating";
    cout << left << setw(15) << "Efg Rating";
    cout << endl;
    for (int i = 0; i < sortedTeamProCol.size(); i++) {
        cout << left << setw(25) << sortedTeamProCol[i]->getPlayerName();
        cout << left << setw(15) << sortedTeamProCol[i]->getPlayerType();
        if (sortedTeamProCol[i]->getPos() == "PG" || sortedTeamProCol[i]->getPos() == "SG")
            cout << left << setw(15) << "G";
        else if (sortedTeamProCol[i]->getPos() == "PF" || sortedTeamProCol[i]->getPos() == "SF")
            cout << left << setw(15) << "F";
        else
            cout << left << setw(15) << sortedTeamProCol[i]->getPos();
        cout << left << setw(15) << sortedTeamProCol[i]->getValue();
        cout << left << setw(15) << sortedTeamProCol[i]->getEffRating();
        cout << left << setw(15) << sortedTeamProCol[i]->getEFG();
        cout << endl;
    }

    // PRO TEAM
    // Make a copy of the total team vector.
    vector<BasketBallPlayer*> bbpVectorCopy = sortedBBPVector;

    // First, choose a best center and 2 best forward and guard positions.
    // Selected players will be erased from the vector to prevent duplication.
    vector<BasketBallPlayer*> teamPro;
    int removeCount = 0;
    numCenter = 0; numForward = 0; numGuard = 0;
    for (int i = 0; i < bbpVectorCopy.size() - removeCount; i++) {
        if (i < 0) {
            i = 0;
        }
        if (numCenter < 1 && bbpVectorCopy[i]->getPos() == "C" && bbpVectorCopy[i]->getEffRating() > 0.0) {
            teamPro.push_back(bbpVectorCopy[i]);
            bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
            numCenter++; removeCount++; i--;
        }
        else if (numForward < 2 && (bbpVectorCopy[i]->getPos() == "PF" || bbpVectorCopy[i]->getPos() == "SF") && bbpVectorCopy[i]->getEffRating() > 0.0) {
            teamPro.push_back(bbpVectorCopy[i]);
            bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
            numForward++; removeCount++; i--;
        }
        else if (numGuard < 2 && (bbpVectorCopy[i]->getPos() == "PG" || bbpVectorCopy[i]->getPos() == "SG") && bbpVectorCopy[i]->getEffRating() > 0.0) {
            teamPro.push_back(bbpVectorCopy[i]);
            bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
            numGuard++; removeCount++; i--;
        }
        else if (numCenter == 1 && numForward == 2 && numGuard == 2) {
            break;
        }
    }
    // Calculate the current total contract value.
    int currContractVal = 0;
    for (int i = 0; i < teamPro.size(); i++) {
        currContractVal += teamPro[i]->getContractValue();
    }

    // Then, choose additional players based on max playervalue and contractvalue.
    // Pick: 1 Center, Forward, Guard player with max 8 player value, and within remaining contractMax amount.
    int contractMax = 98000000; removeCount = 0;
    bool isOtherFound = false;
    for (int i = 0; i < bbpVectorCopy.size() - removeCount; i++) {
        if (i < 0) {
            i = 0;
        }
        if (bbpVectorCopy[i]->getValue() <= 8 && numCenter < 2 && bbpVectorCopy[i]->getPos() == "C" && bbpVectorCopy[i]->getEffRating() > 0.0) {
            if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numCenter++; removeCount++; i--;
            }
        }
        else if (numCenter == 2 && bbpVectorCopy[i]->getValue() <= 8 && numForward < 3 && (bbpVectorCopy[i]->getPos() == "PF" || bbpVectorCopy[i]->getPos() == "SF") && bbpVectorCopy[i]->getEffRating() > 0.0) {
             if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numForward++; removeCount++; i--; isOtherFound = true;
            }
        }
        else if (isOtherFound && bbpVectorCopy[i]->getValue() <= 8 && numGuard < 3 && (bbpVectorCopy[i]->getPos() == "PG" || bbpVectorCopy[i]->getPos() == "SG") && bbpVectorCopy[i]->getEffRating() > 0.0) {
             if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numGuard++; removeCount++; i--;
            }
        }
        else if (numCenter == 2 && numForward == 3 && numGuard == 3) {
            isOtherFound = false;
            break;
        }
    }
    
    // Pick 1 Forward and Guard player, with player value <= 6, within remaining contractMax value, and find guard before forward player. 
    for (int i = 0; i < bbpVectorCopy.size() - removeCount; i++) {
        if (isOtherFound && bbpVectorCopy[i]->getValue() <= 6 && numForward < 4 && (bbpVectorCopy[i]->getPos() == "PF" || bbpVectorCopy[i]->getPos() == "SF") && bbpVectorCopy[i]->getEffRating() > 0.0) {
            if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numForward++; removeCount++; i--;
            }
        }
        else if (bbpVectorCopy[i]->getValue() <= 6 && numGuard < 4 && (bbpVectorCopy[i]->getPos() == "PG" || bbpVectorCopy[i]->getPos() == "SG") && bbpVectorCopy[i]->getEffRating() > 0.0) {
             if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numGuard++; removeCount++; i--; isOtherFound = true;
            }
        }
        else if (numForward == 4 && numGuard == 4) {
            isOtherFound = false;
            break;
        }
    }
    
    // Pick 1 Forward and Guard player, with player value <= 6, within remaining contractMax value, and find forward before guard player.
    for (int i = 0; i < bbpVectorCopy.size() - removeCount; i++) {
        if (bbpVectorCopy[i]->getValue() <= 5 && numForward < 5 && (bbpVectorCopy[i]->getPos() == "PF" || bbpVectorCopy[i]->getPos() == "SF") && bbpVectorCopy[i]->getEffRating() > 0.0) {
            if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numForward++; removeCount++; i--; isOtherFound = true;
            }
        }
        else if (isOtherFound && bbpVectorCopy[i]->getValue() <= 5 && numGuard < 5 && (bbpVectorCopy[i]->getPos() == "PG" || bbpVectorCopy[i]->getPos() == "SG") && bbpVectorCopy[i]->getEffRating() > 0.0) {
             if (contractMax - currContractVal - bbpVectorCopy[i]->getContractValue() > 0) {
                teamPro.push_back(bbpVectorCopy[i]);
                currContractVal += bbpVectorCopy[i]->getContractValue();
                bbpVectorCopy.erase(bbpVectorCopy.begin() + i);
                numGuard++; removeCount++; i--;
            }
        }
        else if (numForward == 5 && numGuard == 5) {
            isOtherFound = false;
            break;
        }
    }

    // Print the sorted teamPro.
    vector<BasketBallPlayer*> sortedTeamPro = sortVector(teamPro);
    cout << endl;
    cout << "PRO TEAM LIST" << endl << endl;
    cout << left << setw(25) << "Player Name";
    cout << left << setw(15) << "Type";
    cout << left << setw(15) << "Position";
    cout << left << setw(15) << "Player Value";
    cout << left << setw(15) << "Eff Rating";
    cout << right << setw(15) << "Contract Value";
    cout << endl;
    for (int i = 0; i < sortedTeamPro.size(); i++) {
        sortedTeamPro[i]->print();
    }
    cout << endl;
    cout << left << setw(85) << "TOTAL PAY: " << right << setw(15) << currContractVal << endl;
    return 0;
}
