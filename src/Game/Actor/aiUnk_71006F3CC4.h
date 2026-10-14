#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {
class ActionBase;
}

// Placeholder name = vtable address (0x7102450038; constructor 0x71006f3cc4, D2 0x71006f3ce4 (empty,
// out of line), D0 0x71006f3ce8). Small helper embedded in LevelFlyMoveBase (+0x118) and
// BattleCloseLevelFlyMoveBase (+0xd0); its method 0x71006f3cec (declared only) reads `*_8` (a float
// param pointer of the owner), samples the ground below the owner's actor with sub_710072E500 and
// keeps the resulting height in `_1c` (re-sampled when the countdown `_18` runs out).
class Unk_7102450038 {
public:
    explicit Unk_7102450038(ksys::act::ai::ActionBase* owner);
    virtual ~Unk_7102450038();

    // 0x71006f3de8: resets the countdown and the height.
    void sub_71006F3DE8();
    // 0x71006f3df4: empty.
    void sub_71006F3DF4();
    // 0x71006f3df8: reads the owner's static param "FlyHeightMin" into `_8` (protected getStaticParam:
    // friend of ActionBase).
    void sub_71006F3DF8();
    // 0x71006f3cec (declared only)
    void sub_71006F3CEC(f32 a1);

    /* 0x08 */ const f32* _8 = nullptr;
    /* 0x10 */ ksys::act::ai::ActionBase* mOwner;
    /* 0x18 */ s32 _18 = 0;
    /* 0x1c */ f32 _1c = -100.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450038, 0x20);
