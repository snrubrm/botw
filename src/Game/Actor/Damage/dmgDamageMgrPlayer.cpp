#include "Game/Actor/Damage/dmgDamageMgrPlayer.h"
#include "Game/Actor/Player/AI/aiPlayerNormal.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace uking::act {

DamageMgrPlayer::DamageMgrPlayer(ksys::act::Actor* actor) : DamageManager(actor) {}

void DamageMgrPlayer::resetDamage() {
    _22c = 0;
    DamageManager::resetDamage();
}

void DamageMgrPlayer::calcDamage() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<uking::act::PlayerBase>(actor)) {
        auto* player = static_cast<uking::act::PlayerBase*>(actor);
        if (_22c > 0.0f) {
            if (!player->_cec.isOnBit(31))
                ksys::Timer::update(&_22c, -1.0f);
            _230 = 1;
        } else {
            _230 = 0;
        }
    }
    DamageManager::calcDamage();
}

bool DamageMgrPlayer::m50(s32*, s32*, u32*, u32*, s32*, s32*) {
    // Discarded IsDerivedFrom (a real virtual call in the target asm); always false.
    sead::IsDerivedFrom<uking::act::PlayerBase>(mActor);
    return false;
}

bool DamageMgrPlayer::m51(const ksys::act::BaseProcLink* link) {
    bool result = false;
    if (DamageManager::m51(link)) {
        result = true;
    } else if (isSlowTimeMaybe()) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<uking::act::PlayerBase>(actor)) {
            auto* player = static_cast<uking::act::PlayerBase*>(actor);
            ksys::act::BaseProcLink tmp;
            if (player->sub_710084AA9C(&tmp) && link->hasProc())
                result = *link == tmp;
        }
    }
    return result;
}

s32 DamageMgrPlayer::m53() {
    // NON_MATCHING: the original keeps the full sub_7100D13BB8 result (mov) and masks
    // only at return; ours masks a bool at the save. The callee returns an integer in
    // the original, but changing its shared bool declaration would regress its other
    // (matching) callers, which test it with tst after the call.
    ksys::act::ActorLinkConstDataAccess accessor;
    const ksys::act::BaseProcLink* link;
    if (auto* impulse = mActor->getImpulseBaseProcLink())
        link = &impulse->mLink;
    else
        link = &ksys::act::getDummyBaseProcLink();
    ksys::act::acquireActor(link, &accessor);
    const bool result = accessor.sub_7100D13BB8();
    return result;
}


bool DamageMgrPlayer::m56() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<uking::act::PlayerBase>(actor)) {
        auto* player = static_cast<uking::act::PlayerBase*>(actor);
        if (player->_cf0.isOnBit(8))
            return false;
    }
    return DamageManager::m56();
}

s32 DamageMgrPlayer::m52() {
    return 12;
}

void DamageMgrPlayer::m54(const ConditionDamageInfo& info) {
    bool update_type;
    s32 f54;
    if (info.mFlags & 2) {
        _8c |= 0x1000;
        update_type = true;
        f54 = 30;
    } else if (info.mFlags & 0x20) {
        update_type = true;
        f54 = 28;
    } else if (info._8 & 4) {
        update_type = true;
        f54 = 22;
    } else if (info.mFlags & 0x10) {
        auto* param = getActorDamageParam();
        if (param && param->mProofBurnAtSmallDamage.ref()) {
            update_type = true;
            f54 = 15;
        } else {
            update_type = true;
            f54 = -1;
        }
    } else if (info._8 & 2) {
        update_type = true;
        f54 = 21;
    } else if (info._8 & 1) {
        update_type = true;
        f54 = 17;
    } else if (info.mFlags & 1) {
        f54 = 0;
        update_type = true;
    } else {
        update_type = mDamageType == -1;
        f54 = (info.mFlags & 0x40) ? -1 : 18;
    }

    s32 damage = info.mDamage;
    if (_214 & 0x40)
        damage = (info.mFlags & 1) ? damage : 0;
    const u32 prev_f50 = mField_50;
    const s32 prev_type = update_type ? -1 : mDamageType;
    const bool applied = sub_71006D357C(6, 5, info.mFlags & 8, damage, 0, 0, 9, f54, 0);
    if (!update_type) {
        mField_50 = prev_f50;
        mDamageType = prev_type;
        return;
    }
    if (!applied)
        return;
    _216.change(0x100, info.mFlags & 8);
    if (info.mFlags & 8)
        _88 = info._10;
}

void DamageMgrPlayer::m55(const ConditionDamageInfo& info) {
    if (_231)
        return;
    DamageManager::m55(info);
}

}  // namespace uking::act

// 0x7100852110
void Unk_710246ac48::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::act::DamageCallbackInfo* a6) {
    if (!mDamageManager)
        return;
    auto* actor = mDamageManager->mActor;
    if (!sub_71007A2604(actor))
        return;
    auto* attack = sub_71007A255C(actor, 0);
    if (attack && attack->sub_71007A1F68(0x4000))
        *a1 = 0;
}
