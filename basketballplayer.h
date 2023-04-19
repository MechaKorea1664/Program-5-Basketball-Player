#include <iostream>

using namespace std;

class BasketBallPlayer{
protected:
    char playerType;
    string playerName;
    int games;
    float efg;
    int trb;
    int ast;
    int stl;
    int blk;
    int tov;
    int pts;
    float effRating;
    int value;
public:
    BasketBallPlayer();
    BasketBallPlayer(char playerType, string playerName, int games, float efg, int trb, int ast, int stl, int blk, int tov, int pts);
    void setPlayerType(char);
    char getPlayerType();
    void setPlayerName(string);
    string getPlayerName();
    void setGames(int);
    int getGames();
    void setEFG(float);
    float getEFG();
    void setTRB(int);
    int getTRB();
    void setAST(int);
    int getAST();
    void setSTL(int);
    int getSTL();
    void setBLK(int);
    int getBLK();
    void setTOV(int);
    int getTOV();
    void setPoints(int);
    int getPoints();
    void setEffRating();
    float getEffRating();
    void setValue();
    int getValue();
    virtual string getPos() const;
    virtual int getContractValue() const;
    virtual void print() const;
};

class CollegeBasketballPlayer: public BasketBallPlayer{
private:
string team;
public:
CollegeBasketballPlayer();
CollegeBasketballPlayer(string newPlayerName, int newGames, float newEfg, int newTrb, int newAst, int newStl, int newBlk, int newTov, int newPts, string newTeam);
void setTeam(string);
string getTeam();
void print() const override;
};

class ProBasketballPlayer:public BasketBallPlayer{
private:
    int years;
    string pos;
    int contractValue;
public:
    ProBasketballPlayer();
    ProBasketballPlayer(string newPlayerName, int newGames, float newEfg, int newTrb, int newAst, int newStl, int newBlk, int newTov, int newPts, int newYears, string newPos);
    void setYears(int);
    int getYears();
    void setPos(string);
    string getPos() const override;
    void setContractValue();
    int getContractValue() const override;
    void print() const override;
};
