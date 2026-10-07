#pragma once

#include <prim/seadSafeString.h>

class GameConfig {
public:
    static GameConfig* getInstance() { return sInstancePtr; }

    char _0[0x3dc];
    // VillagerMgr::init (0x7100d5e7f4) disables its updates when this byte is true.
    bool _3dc;
    bool _3dd;
    char _3de[0x3b];
    bool _419;
    sead::SafeString mPatrolFeatures;

private:
    static GameConfig* sInstancePtr;
};
