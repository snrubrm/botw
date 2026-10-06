#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (GameScene320::ctor 0x7100897974, dtor 0x7100897998; GameScene::_320). Small
// polymorphic helper object embedded in GameScene; reset by GameScene::NewSaveLeave.
// TODO: incomplete (member meanings unknown).
class GameScene320 {
public:
    GameScene320();
    virtual ~GameScene320();

    // 0x71008979cc
    void reset();

private:
    void* _8 = nullptr;
    s32 _10 = -1;
    u8 _14[13] = {};
    u8 _21 = 0;
};
KSYS_CHECK_SIZE_NX150(GameScene320, 0x28);
