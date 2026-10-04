#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::action {

EquipedAction::EquipedAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void EquipedAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    m32();
    m34();
}

void EquipedAction::leave_() {
    m35();
}

void EquipedAction::loadParams_() {
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void EquipedAction::calc_() {
    sub_7100E141F0();
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor)) {
        if (weapon->m216()) {
            sead::SafeString name;
            if (auto* weapon2 = sead::DynamicCast<ksys::act::WeaponBase>(mActor)) {
                if (weapon2->m217(&name)) {
                    if (auto* weapon3 = sead::DynamicCast<ksys::act::WeaponBase>(mActor)) {
                        weapon3->_a00._28 = name.cstr();
                        weapon3->_a00._30.getKey().reset();
                    }
                }
            }
        }
    }
}

void EquipedAction::m32() {}

ksys::act::ModelBindInfo* EquipedAction::sub_7100E14604() {
    auto* actor = mActor;
    return sead::IsDerivedFrom<ksys::act::WeaponBase>(actor) ?
               &static_cast<ksys::act::WeaponBase*>(actor)->_a00 :
               nullptr;
}

void EquipedAction::sub_7100E141F0() {
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor))
        weapon->_a00._68.makeRT(*mRotOffset_d * sead::Mathf::deg2rad(1), *mTransOffset_d);
}

// NON_MATCHING: the original keeps `bind` (actor + 0xa00) in one register (vtable load at [bind]); ours
// folds the offset into the addressing modes (regalloc / address folding only)
void EquipedAction::sub_7100E144FC() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<ksys::act::WeaponBase>(actor)) {
        auto* bind = &static_cast<ksys::act::WeaponBase*>(actor)->_a00;
        bind->x(m33());
        bind->_28 = mNodeName_d.cstr();
        bind->_30.getKey().reset();
        sub_7100E141F0();
        mActor->sub_71011DA824(bind);
    }
}

void EquipedAction::m34() {
    if (auto* bound = mActor->getModelBindInfo()) {
        if (bound->sub_7100D3C5E0(mActor) == m33())
            return;
        auto* actor = mActor;
        actor->sub_71011DA834(sead::IsDerivedFrom<ksys::act::WeaponBase>(actor) ?
                                  &static_cast<ksys::act::WeaponBase*>(actor)->_a00 :
                                  nullptr);
    }
    sub_7100E144FC();
}

void EquipedAction::m35() {
    if (mActor->getRootAi()->getNewChildIdx() != 0) {
        auto* actor = mActor;
        actor->sub_71011DA834(sead::IsDerivedFrom<ksys::act::WeaponBase>(actor) ?
                                  &static_cast<ksys::act::WeaponBase*>(actor)->_a00 :
                                  nullptr);
        return;
    }
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor);
    if (!weapon || !weapon->isMasterSword())
        return;
    if (weapon->getParentActor() && !weapon->m187())
        return;
    auto* actor = mActor;
    actor->sub_71011DA834(sead::IsDerivedFrom<ksys::act::WeaponBase>(actor) ?
                              &static_cast<ksys::act::WeaponBase*>(actor)->_a00 :
                              nullptr);
}

ksys::act::Actor* EquipedAction::m33() {
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor))
        return weapon->getParentActor();
    return nullptr;
}

}  // namespace uking::action
