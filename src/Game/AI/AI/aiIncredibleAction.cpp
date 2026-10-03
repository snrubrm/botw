#include "Game/AI/AI/aiIncredibleAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

void Unk_71023fd380::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (!_38) {
        *a1 = 0;
        return;
    }

    auto* manager = sead::DynamicCast<uking::dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;

    auto* attacker = manager->getAttacker();
    ksys::act::ActorConstDataAccess acc;
    if (attacker->hasProc())
        ksys::act::acquireActor(attacker, &acc);
}

namespace uking::ai {

IncredibleAction::IncredibleAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IncredibleAction::~IncredibleAction() = default;

bool IncredibleAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IncredibleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100448C0C(true);
    _58._38 = false;
    changeChild("インクレディブル", params);
}

void IncredibleAction::leave_() {
    sub_7100448C0C(false);
}

void IncredibleAction::loadParams_() {
    getStaticParam(&mIsInvincible_s, "IsInvincible");
    getStaticParam(&mIsUnmoving_s, "IsUnmoving");
    getStaticParam(&mIsNoCollide_s, "IsNoCollide");
    getStaticParam(&mIsUseIncredibleActionDCCallback_s, "IsUseIncredibleActionDCCallback");
}

// NON_MATCHING: block layout (the original keeps &mActor in a register, forms it with a pre-indexed
// load and puts the mField_34 / removeDamageCallback arms after the callback arm)
void IncredibleAction::sub_7100448C0C(bool enable) {
    if (*mIsInvincible_s) {
        auto* mgr = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
        if (!mgr) {
            setFailed();
            return;
        }
        if (*mIsUseIncredibleActionDCCallback_s) {
            if (enable)
                mgr->addDamageCallback(0, &_58);
            else
                mgr->removeDamageCallback(&_58);
        } else {
            mgr->mField_34 = enable;
        }
    }

    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    if (*mIsUnmoving_s) {
        controller->mFlags.changeBit(10, enable);
        controller->mFlags.changeBit(11, enable);
    }

    if (*mIsNoCollide_s) {
        if (enable) {
            controller->sub_7100F605F0();
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            controller->disableContactLayer(ksys::phys::ContactLayer::EntityHitOnlyGround);
        } else {
            controller->sub_7100F60604();
        }
    }
}

void IncredibleAction::calc_() {
    if (isFinished() || isFailed())
        return;

    if (*mIsUseIncredibleActionDCCallback_s) {
        bool value = false;
        if (auto* as_list = mActor->getASList()) {
            value = !as_list->x(0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                true);
        } else {
            setFailed();
        }
        _58._38 = value;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::ai
