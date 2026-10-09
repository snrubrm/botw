#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Native factory 0x7100EDB87C allocates 0x260 bytes and clears flags +0x54.
// GameScene::StageMgrRun reads bit 0; unloadStage clears that bit.
class GameTool {
public:
    static GameTool* instance() { return sInstance; }
    static GameTool* sInstance;

    u8 _0[0x54];
    sead::BitFlag8 _54;
    u8 _55[0x260 - 0x55];
};
KSYS_CHECK_SIZE_NX150(GameTool, 0x260);

}  // namespace ksys
