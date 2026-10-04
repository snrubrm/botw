#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::act {

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

}  // namespace ksys::act
