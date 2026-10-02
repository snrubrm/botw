// ActorAtk::Struct7 / AttackInfo (TU 0x79e8ec-0x79f2d8, separate from ActorAtk: not inlined into it).
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace ksys::act {

ActorAtk::Struct7::AttackInfo::AttackInfo() = default;

void ActorAtk::Struct7::reset() {
    for (int i = 0; i < mNumAttackInfo; ++i) {
        mAttackInfos[i].resetFlags();
        mAttackInfos[i]._50.reset();
    }
    mNumAttackInfo = 0;
    _3c2 = 0;
}

}  // namespace ksys::act
