#include <iostream>
#include <iomanip>
#include <fstream>
#include "basketballplayer.h"

using namespace std;

BasketBallPlayer::BasketBallPlayer(){
    playerType = ' ';
    playerName = "unknown";
    games = 0;
    efg = 0.0f;
    trb = 0;
    ast = 0;
    stl = 0;
    blk = 0;
    tov = 0;
    pts = 0;
    effRating = 0.0f;
    value = 0;
}

BasketBallPlayer::BasketBallPlayer(char newPlayerType, string newPlayerName, int newGames, float newEfg, int newTrb, int newAst, int newStl, int newBlk, int newTov, int newPts){
    playerType = newPlayerType;
    playerName = newPlayerName;
    games = newGames;
    efg = newEfg;
    trb = newTrb;
    ast = newAst;
    stl = newStl;
    blk = newBlk;
    tov = newTov;
    pts = newPts;
    setEffRating();
    setValue();
}

void BasketBallPlayer::setPlayerType(char input){
    playerType = input;
}
char BasketBallPlayer::getPlayerType(){
    return playerType;
}
void BasketBallPlayer::setPlayerName(string input){
    playerName = input;
}
string BasketBallPlayer::getPlayerName(){
    return playerName;
}
void BasketBallPlayer::setGames(int input){
    games = input;
}
int BasketBallPlayer::getGames(){
    return games;
}
void BasketBallPlayer::setEFG(float input){
    efg = input;
}
float BasketBallPlayer::getEFG(){
    return efg;
}
void BasketBallPlayer::setTRB(int input){
    trb = input;
}
int BasketBallPlayer::getTRB(){
    return trb;
}
void BasketBallPlayer::setAST(int input){
    ast = input;
}
int BasketBallPlayer::getAST(){
    return ast;
}
void BasketBallPlayer::setSTL(int input){
    stl = input;
}
int BasketBallPlayer::getSTL(){
    return stl;
}
void BasketBallPlayer::setBLK(int input){
    blk = input;
}
int BasketBallPlayer::getBLK(){
    return blk;
}
void BasketBallPlayer::setTOV(int input){
    tov = input;
}
int BasketBallPlayer::getTOV(){
    return tov;
}
void BasketBallPlayer::setPoints(int input){
    pts = input;
}
int BasketBallPlayer::getPoints(){
    return pts;
}
void BasketBallPlayer::setEffRating(){
    if (games <= 5) {
        ofstream outFS;
        outFS.open("output.txt", ios_base::app);
        outFS << left << setw(30) << playerName;
        if (playerType == 'C')
            outFS << left << setw(15) << "NCAA Player";
        else
            outFS << left << setw(15) << "Pro Player";
        outFS << left << setw(5) << ":";
        outFS << "Insufficient game count: " << games;
        outFS << endl;
        outFS.close();
        effRating = 0;
    }
    else {
        effRating = (pts + trb + ast + stl + blk - (pts / efg - pts + tov)) / games;
    }
}
float BasketBallPlayer::getEffRating(){
    return effRating;
}
void BasketBallPlayer::setValue(){
    if (efg > 0.7f || effRating > 20)
        value = 10;
    else if (efg > 0.65f || effRating > 15)
        value = 9;
    else if ((efg > 0.65f && (float) stl/games > 2) && (float) pts/games > 20 && (float) trb/games > 5 && (float) tov/games <= 1)
        value = 9;
    else if (efg > .6f || effRating > 13)
        value = 8;
    else if ((efg > .6f && (float) blk/games > 3) && (float) pts/games > 15 && (float) trb/games > 5)
        value = 8;
    else if (efg > .6f && (float) pts/games > 15 && (float) trb/games > 5 && (float) tov/games < 2)
        value = 8;
    else if (efg > .55f || effRating > 10)
        value = 7;
    else if (efg > .55f && (float) pts/games > 15 && (float) trb/games > 5)
        value = 7;
    else if ((efg > .55f && (float) blk/games > 3) && (float) pts/games > 10 && (float) trb/games > 4)
        value = 6;
    else if (efg > .45f && (float) pts/games > 10 && (float) trb/games > 4)
        value = 5;
    else if (efg > .40f && (float) pts/games > 5 && (float) trb/games > 3)
        value = 3;
    else if (efg > .35f && (float) pts/games > 5 && (float) trb/games > 3)
        value = 2;
    else
        value = 0;
}
int BasketBallPlayer::getValue(){
    return value;
}

string BasketBallPlayer::getPos() const {
    return "";
}

int BasketBallPlayer::getContractValue() const {
    return 0;
}

void BasketBallPlayer::print() const{
    cout << "bbplayer" << endl;
}

CollegeBasketballPlayer::CollegeBasketballPlayer() : BasketBallPlayer() {
    team = "unknown";
}
CollegeBasketballPlayer::CollegeBasketballPlayer(string newPlayerName, int newGames, float newEfg, int newTrb, int newAst, int newStl, int newBlk, int newTov, int newPts, string newTeam) 
                        :BasketBallPlayer('C', newPlayerName, newGames, newEfg, newTrb, newAst, newStl, newBlk, newTov, newPts) {
    team = newTeam;
}
void CollegeBasketballPlayer::setTeam(string newTeam){
    team = newTeam;
}
string CollegeBasketballPlayer::getTeam(){
    return team;
}
void CollegeBasketballPlayer::print() const {
    cout << left << setw(25) << playerName;
    cout << left << setw(15) << value;
    cout << left << setw(15) << setprecision(2) << fixed << effRating;
    cout << left << setw(15) << setprecision(2) << fixed << efg;
    cout << endl;
}

ProBasketballPlayer::ProBasketballPlayer(){
    playerType = 'P';
    playerName = "unknown";
    games = 0;
    efg = 0.0f;
    trb = 0;
    ast = 0;
    stl = 0;
    blk = 0;
    tov = 0;
    pts = 0;
    effRating = 0.0f;
    value = 0;
    years = 0;
    pos = "unknown";
    contractValue = 0;
}
ProBasketballPlayer::ProBasketballPlayer(string newPlayerName, int newGames, float newEfg, int newTrb, int newAst, int newStl, int newBlk, int newTov, int newPts, int newYears, string newPos)
                    :BasketBallPlayer('P', newPlayerName, newGames, newEfg, newTrb, newAst, newStl, newBlk, newTov, newPts) {
    years = newYears;
    pos = newPos;
    setContractValue();
}
void ProBasketballPlayer::setYears(int newYear){
    years = newYear;
}
int ProBasketballPlayer::getYears(){
    return years;
}
void ProBasketballPlayer::setPos(string newPos){
    pos = newPos;
}
string ProBasketballPlayer::getPos() const{
    return pos;
}
void ProBasketballPlayer::setContractValue(){
    if (value == 10)
        contractValue = 12000000;
    else if (value == 9)
        contractValue = 10000000;
    else if (value == 8)
        contractValue = 7500000;
    else if (value == 7)
        contractValue = 6000000;
    else if (value < 7 && value > 4)
        contractValue = 5000000;
    else if (value < 5 && value > 2)
        contractValue = 2500000;
    else
        contractValue = 500000;
}
int ProBasketballPlayer::getContractValue() const{
    return contractValue;
}
void ProBasketballPlayer::print() const{
    cout << left << setw(25) << playerName;
    cout << left << setw(15) << playerType;
    if (pos == "PG" || pos == "SG")
        cout << left << setw(15) << "G";
    else if (pos == "PF" || pos == "SF")
        cout << left << setw(15) << "F";
    else
        cout << left << setw(15) << pos;
    cout << left << setw(15) << value;
    cout << left << setw(15) << effRating;
    cout << right << setw(15) << contractValue;
    cout << endl;
}
