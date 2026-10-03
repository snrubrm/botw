#include "Game/AI/AI/aiAssassinBossFirstRoot.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_710072BA90.h"

namespace uking::ai {

void Unk_71023d7798::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    _25 = false;
    if (*a1 <= 0 && *a5 == -1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (damage_manager && !sub_71007368A4(damage_manager->getAttacker()) &&
        damage_manager->mActor->getASList()->x(14, nullptr, 0, 0,
                                                &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        *a1 = 0;
        if (*a4 == 4) {
            *a1 = 0;
            *a5 = -1;
            _24 = true;
        } else {
            *a5 = 12;
            if (*a4 == 3)
                _25 = true;
        }
        return;
    }
    *a5 = 15;
}

AssassinBossFirstRoot::AssassinBossFirstRoot(const InitArg& arg) : AssassinBossRootBase(arg) {}

AssassinBossFirstRoot::~AssassinBossFirstRoot() = default;

bool AssassinBossFirstRoot::init_(sead::Heap* heap) {
    return AssassinBossRootBase::init_(heap);
}

void AssassinBossFirstRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossRootBase::enter_(params);
    _2d8 = false;
    sub_71007A3910(mActor, "TgtBarrier");
}

void AssassinBossFirstRoot::calc_() {
    AssassinBossRootBase::calc_();
    if (isCurrentChild("撤退"))
        return;

    sub_710031C2C8(s32(f32(mActor->getMaxLife()) * *mChangeModeLifeRatio_s));
    if (_2b0._25)
        _2b0._25 = false;

    auto* actor = mActor;
    if (actor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        if (!_2d8) {
            sub_71007A3778(actor, "TgtBarrier");
            _2d8 = true;
        }
    } else if (_2d8) {
        sub_71007A3910(actor, "TgtBarrier");
        _2d8 = false;
    }

    if (isCurrentChild("リアクション")) {
        if (mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                   true)) {
            setDamageCallbackTiming(mActor, 0, &_2b0);
        } else {
            sub_71005DA114(mActor, &_2b0);
        }
    } else {
        setDamageCallbackTiming(mActor, 0, &_2b0);
        if (_2b0._24)
            m46();
    }
}

void AssassinBossFirstRoot::leave_() {
    AssassinBossRootBase::leave_();
    _2d8 = false;
    sub_71007A3910(mActor, "TgtBarrier");
    sub_71005DA114(mActor, &_2b0);
}

void AssassinBossFirstRoot::loadParams_() {
    AssassinBossRootBase::loadParams_();
}

bool AssassinBossFirstRoot::m35() {
    if (mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        auto* damage_manager = sub_710072BA90(mActor);
        if (damage_manager && damage_manager->getField54() == 12)
            return false;
    }
    return EnemyRoot::m35();
}

bool AssassinBossFirstRoot::m45() {
    return _2b0._24;
}

void AssassinBossFirstRoot::m46() {
    AssassinBossRootBase::m46();
    _2b0._24 = false;
    _2b0._25 = false;
}

}  // namespace uking::ai
