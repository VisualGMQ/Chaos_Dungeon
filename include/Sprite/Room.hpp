#ifndef ROOM_HPP
#define ROOM_HPP
#include "Wall.hpp"
#include <list>
using namespace std;

class Room final : public GameObject{
public:
    static Room* Create();
    void Generate(int col, int row);
    ~Room();
private:
    Room();
    void update() override;
    void draw() override;
    list<Wall*> walls; 
    int row;
    int col;
};

#endif
