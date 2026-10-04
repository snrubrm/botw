#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

// Placeholder names (0x71007444ac TU; lane3 s18): the set of "grudge marks" shared by ForkGanonAscendingCreateManage
// (+0x38) and the GanonBeastGrudgeMarkMgr object of ForkFourFootActorLustGrass (Unit::_8). `_8` points to `_0`
// elements of 0x48 bytes. Only the functions used by the actions are declared (all declaration only).
struct Unk_71007444acElem {
    void sub_710074424C();
    // 0x7100744310 (called for every element by ForkGanonAscendingCreateManage::leave_)
    void sub_7100744310();
    ksys::act::BaseProcLink _0;
    f32 _10;
    sead::Matrix34f _14;
    s32 _44;
};
KSYS_CHECK_SIZE_NX150(Unk_71007444acElem, 0x48);

struct Unk_71007444ac {
    // 0x710074431c (ForkGanonAscendingCreateManage::init_): allocates the elements of the set named `name`.
    void sub_710074431C(sead::Heap* heap, const char* name, s32 count);
    // 0x71007444ac (updateForPreDelete of both actions)
    void sub_71007444AC();
    // 0x71007445bc (ForkGanonAscendingCreateManage::handleMessage_)
    void sub_71007445BC(const sead::Matrix34f& mtx, u32 a2);
    void sub_710074456C();

    s32 _0 = 0;
    Unk_71007444acElem* _8 = nullptr;
};
