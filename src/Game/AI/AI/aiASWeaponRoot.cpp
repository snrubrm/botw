#include "Game/AI/AI/aiASWeaponRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ASWeaponRoot::ASWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
ASWeaponRoot::~ASWeaponRoot() { ; }

bool ASWeaponRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void ASWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor))
        weapon->_f89 = false;
}

void ASWeaponRoot::calc_() {
    WeaponRootAI::calc_();
    sub_7100323494();
}

void ASWeaponRoot::sub_7100323494() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* as_list = weapon->getASList();
    if (!as_list)
        return;

    if (auto* parent = weapon->getParentActor()) {
        auto* chemical = parent->getChemicalStuff();
        if (chemical && chemical->_c0 == 1) {
            as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
            return;
        }
    }
    as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, 1.0f);
}

void ASWeaponRoot::leave_() {
    WeaponRootAI::leave_();
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor))
        weapon->_f89 = true;
}

void ASWeaponRoot::m36() {
    if (mEquiped_s.isEmpty())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mEquiped_s.cstr(), 0, 0, true);
}

void ASWeaponRoot::m37() {
    if (mUnEquiped_s.isEmpty())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mUnEquiped_s.cstr(), 0, 0, true);
}

void ASWeaponRoot::m38() {
    if (mThrown_s.isEmpty())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mThrown_s.cstr(), 0, 0, true);
}

void ASWeaponRoot::m39() {
    if (mStick_s.isEmpty())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mStick_s.cstr(), 0, 0, true);
}

void ASWeaponRoot::m40() {
    if (mCancelStick_s.isEmpty())
        return;
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mCancelStick_s.cstr(), 0, 0, true);
}

void ASWeaponRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getStaticParam(&mEquiped_s, "Equiped");
    getStaticParam(&mUnEquiped_s, "UnEquiped");
    getStaticParam(&mThrown_s, "Thrown");
    getStaticParam(&mStick_s, "Stick");
    getStaticParam(&mCancelStick_s, "CancelStick");
}

}  // namespace uking::ai
