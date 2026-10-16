#include "Game/Actor/Action/actionGiveCookResultForNpc.h"
#include "Game/Cooking/cookManager.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

GiveCookResultForNpc::GiveCookResultForNpc(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiveCookResultForNpc::~GiveCookResultForNpc() = default;

bool GiveCookResultForNpc::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the literal comparison retains temporary SafeString storage.
s32 GiveCookResultForNpc::sub_710018B630() {
    if (mCookEffectType_d == "None")
        return s32(CookEffectId::None);
    if (mCookEffectType_d == "ResistHot")
        return s32(CookEffectId::ResistHot);
    if (mCookEffectType_d == "ResistCold")
        return s32(CookEffectId::ResistCold);
    if (mCookEffectType_d == "ResistElectric")
        return s32(CookEffectId::ResistElectric);
    if (mCookEffectType_d == "AttackUp")
        return s32(CookEffectId::AttackUp);
    if (mCookEffectType_d == "DefenseUp")
        return s32(CookEffectId::DefenseUp);
    if (mCookEffectType_d == "Quietness")
        return s32(CookEffectId::Quietness);
    if (mCookEffectType_d == "AllSpeed")
        return s32(CookEffectId::MovingSpeed);
    if (mCookEffectType_d == "Fireproof")
        return s32(CookEffectId::Fireproof);
    if (mCookEffectType_d == "GutsRecover")
        return s32(CookEffectId::GutsRecover);
    if (mCookEffectType_d == "ExGutsMaxUp")
        return s32(CookEffectId::ExGutsMaxUp);
    if (mCookEffectType_d == "LifeMaxUp")
        return s32(CookEffectId::LifeMaxUp);
    return s32(CookEffectId::None);
}

bool GiveCookResultForNpc::oneShot_() {
    for (s32 i = 0; i < *mCount_d; ++i) {
        if (mCookEffectType_d == "AllOK")
            ui::sub_7100A9E540(mPorchItemName_d);
        else
            ui::pouchDeleteCookResultFromFlow(mPorchItemName_d, sub_710018B630());
    }
    return true;
}

void GiveCookResultForNpc::loadParams_() {
    getDynamicParam(&mCount_d, "Count");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
    getDynamicParam(&mCookEffectType_d, "CookEffectType");
}

}  // namespace uking::action
