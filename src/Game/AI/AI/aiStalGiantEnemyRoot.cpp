#include "Game/AI/AI/aiStalGiantEnemyRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StalGiantEnemyRoot::StalGiantEnemyRoot(const InitArg& arg) : StalEnemyRoot(arg) {}

StalGiantEnemyRoot::~StalGiantEnemyRoot() = default;

bool StalGiantEnemyRoot::init_(sead::Heap* heap) {
    return StalEnemyRoot::init_(heap);
}

void StalGiantEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    StalEnemyRoot::enter_(params);
}

void StalGiantEnemyRoot::leave_() {
    StalEnemyRoot::leave_();
}

void StalGiantEnemyRoot::loadParams_() {
    StalEnemyRoot::loadParams_();
    getStaticParam(&mActorNameChin_s, "ActorNameChin");
    getStaticParam(&mActorNameRib1_s, "ActorNameRib1");
    getStaticParam(&mActorNameRib2_s, "ActorNameRib2");
    getStaticParam(&mActorNameRib3_s, "ActorNameRib3");
    getStaticParam(&mActorNameRib4_s, "ActorNameRib4");
    getStaticParam(&mIsDamageToEnemy_s, "IsDamageToEnemy");
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
}

void StalGiantEnemyRoot::m35(ksys::act::ai::InlineParamPack* params) {
    bool is_sleep = false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        is_sleep = enemy->_e84.isOnBit(8);
    params->addBool(is_sleep, "IsSleep", -1);
}

bool StalGiantEnemyRoot::m34() {
    if (StalEnemyRoot::m34())
        return true;

    if (_2e8._8.isOnBit(0))
        return false;

    auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor);
    if (!giant)
        return false;

    if (giant->_e84.isOnBit(8)) {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            const s32 damage = damage_mgr->getDamage();
            if (damage > 0)
                return true;
        }
    }

    for (int i = 0; i < 4; ++i) {
        auto* part = sead::DynamicCast<ksys::act::Actor>(giant->_14c8._8[i].getProc(nullptr, nullptr));
        if (!part)
            continue;
        auto* chemical = part->getChemicalStuff();
        if (!chemical)
            continue;
        if (chemical->_c0 == 2 || chemical->_1b8 > 0)
            return true;
    }
    return false;
}

}  // namespace uking::ai
