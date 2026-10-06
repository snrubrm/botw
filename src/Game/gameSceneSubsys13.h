#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (GameSceneSubsys13::createInstance 0x71008a52e0, init 0x71008a53d8,
// setGameOverPosition 0x71008a53f0). A small polymorphic sead singleton (the CSV name has no namespace).
// TODO: incomplete (the members at 0x28-0x38 are only partially understood).
class GameSceneSubsys13 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys13)
    GameSceneSubsys13() = default;
    virtual ~GameSceneSubsys13();

public:
    // 0x71008a53d8 / 0x71008a53e4: identical copies.
    void init();
    void sub_71008A53E4();
    // 0x71008a53f0: remembers the position the player is put back at after a game over.
    void setGameOverPosition(sead::Vector3f pos);

private:
    sead::Vector3f _28;
    s32 _34 = -1;
    s32 _38 = 0;
};
KSYS_CHECK_SIZE_NX150(GameSceneSubsys13, 0x40);
