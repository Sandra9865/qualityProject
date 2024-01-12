#include <iostream>
#include "game.h"
#include "ground.h"
#include "viewManager.h"
#include "CLIView.h"
#include <random>
#include <memory>
#include "adventurer.h"
#include "blindMonster.h"
#include "movementManager.h"
#include "smartMonsterMoveManager.h"
#include "blindMonsterMoveManager.h"
#include "adventurerMoveManager.h"
#include <fstream>


int main()
{
    game g{};
    g.play();
}
