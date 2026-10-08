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

void ActorAtk::Struct7::sub_710079F208(const Struct7& other) {
    mNumAttackInfo = other.mNumAttackInfo;
    for (int i = 0; i < mNumAttackInfo; ++i) {
        auto& entry = mAttackInfos[i];
        const auto& source = other.mAttackInfos[i];
        // C++14 evaluation order: the original evaluates the destination first.
        entry._50.operator=(source._50);
        entry.Struct8Base::operator=(source);
    }
}

}  // namespace ksys::act
