#include "Game/Damage/dmgDamageMgrPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::dmg {

bool DamageMgrPlayer::checkDerivedRuntimeTypeInfoStatic(
    const sead::RuntimeTypeInfo::Interface* typeInfo) {
    return typeInfo == DamageMgrPlayer::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManager::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManagerBase::getRuntimeTypeInfoStatic() ||
           typeInfo == DamageManagerBase_UnknownBase1::getRuntimeTypeInfoStatic();
}

bool DamageMgrPlayer::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* DamageMgrPlayer::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

void DamageMgrPlayer::resetDamage() {
    _22c = 0;
    DamageManager::resetDamage();
}

void DamageMgrPlayer::m22() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<ksys::act::PlayerBase>(actor)) {
        auto* player = static_cast<ksys::act::PlayerBase*>(actor);
        if (_22c > 0.0f) {
            if (!player->_cec.isOnBit(31))
                ksys::Timer::update(&_22c, -1.0f);
            _230 = 1;
        } else {
            _230 = 0;
        }
    }
    DamageManager::m22();
}

s32 DamageMgrPlayer::m53() {
    // NON_MATCHING: the original keeps the full sub_7100D13BB8 result (mov) and masks
    // only at return; ours masks a bool at the save. The callee returns an integer in
    // the original, but changing its shared bool declaration would regress its other
    // (matching) callers, which test it with tst after the call.
    ksys::act::ActorConstDataAccess accessor;
    const ksys::act::BaseProcLink* link;
    if (auto* impulse = mActor->getImpulseBaseProcLink())
        link = &impulse->mLink;
    else
        link = &ksys::act::getDummyBaseProcLink();
    ksys::act::acquireActor(link, &accessor);
    const bool result = accessor.sub_7100D13BB8();
    return result;
}

s32 DamageMgrPlayer::m52() {
    return 12;
}

void DamageMgrPlayer::m55() {
    if (_231)
        return;
    DamageManager::m55();
}

}  // namespace uking::dmg
