#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::act {

void Player::x_40() {
    _1d6c = 1.0f;
    _c40.reset(0x1200000);
    _1d64 = 0.0f;
    _1d68 = 0.0f;
    _1f8c = 0;
    _1f84 = 0;
    if (_c44.isOnBit(8)) {
        if (mASList->x_1(1, 1) != "WeaponThrow") {
            _c44.resetBit(8);
            x_18(true);
        }
    }
}

// These two sit in their own file: Player::m296 / m298 tail-call them in the original.
s32 Player::sub_7100892824() {
    if (_cf4.isOnBit(15))
        return _17f1 ? 1 : 2;
    if (!m224())
        return 0;
    if (_d24 != 0)
        return 0;
    if (mASList->sub_710115ED5C(0x42, 0x24) && mASList->sub_710115ED5C(0x42, 0x26))
        return 0;
    return _1f8c == 2 ? 1 : 2;
}

s32 Player::sub_71008923B0(int a1) {
    switch (a1) {
    case 0:
        return 4;
    case 1:
        return 2;
    case 2:
        return 5;
    default:
        return 0;
    }
}

// Placeholder name: whether AS slot 0 plays a sword cut (CutL1, CutS1-4, CutSF, CutDash).
bool Player::sub_71008923D0() {
    return mASList->x_1(0, 0) == "CutL1" || mASList->x_1(0, 0) == "CutS1" ||
           mASList->x_1(0, 0) == "CutS2" || mASList->x_1(0, 0) == "CutS3" ||
           mASList->x_1(0, 0) == "CutS4" || mASList->x_1(0, 0) == "CutSF" ||
           mASList->x_1(0, 0) == "CutDash";
}

// NON_MATCHING: the inlined copy of x_40 has its stores scheduled differently (the original keeps the order of the
// out-of-line x_40)
void Player::x_16() {
    _c40.resetBit(24);
    if (x_17())
        x_18(true);
    x_40();
    x_19(-1.0f);
}

}  // namespace ksys::act
