#include "Game/AI/Action/actionHorseWaitForEventAction.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HorseWaitForEventAction::HorseWaitForEventAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitForEventAction::~HorseWaitForEventAction() = default;

bool HorseWaitForEventAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling differs in the no-rideable animation start arguments.
void HorseWaitForEventAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mHasToCue_d && mActor->getASList()->x_1(0, 0) == act::sUnk_7102603110)
        return;

    sub_7100E5AD10();
    auto* rideable = mActor->m132();
    if (*mHasToCue_d && *mIsNoMorph_d) {
        mActor->getASList()->sub_710115B01C(0, 0, true);
        mActor->getASList()->startAnimationMaybe(0.0f, -1.0f, act::sUnk_7102603110, 0, 0, true);
    } else if (rideable) {
        auto* list = mActor->getASList();
        const s32 bank = rideable->_18._9 ? rideable->_18._2e : rideable->_18.sub_7100E76CEC();
        list->sub_710115B140(act::sUnk_7102603110, 0, 0, 0, bank);
    } else {
        mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_7102603110, 0, 0, true);
    }
    if (rideable) {
        rideable->_18.sub_7100E770C4(false);
        rideable->sub_7100E633AC();
    }
}

void HorseWaitForEventAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseWaitForEventAction::loadParams_() {
    getDynamicParam(&mIsAngryEnable_d, "IsAngryEnable");
    getDynamicParam(&mIsEatEnable_d, "IsEatEnable");
    getDynamicParam(&mIsLoveEnable_d, "IsLoveEnable");
    getDynamicParam(&mHasToCue_d, "HasToCue");
    getDynamicParam(&mIsNoMorph_d, "IsNoMorph");
}

// NON_MATCHING: same instructions; the last two argument moves (w2 / v0) are scheduled in the other order
void HorseWaitForEventAction::sub_7100E5AD10() {
    auto* as_list = mActor->getASList();
    if (!*mIsAngryEnable_d)
        as_list->x_6(14, 0, 0.0f);
    if (!*mIsEatEnable_d)
        as_list->x_2(66, 3, false, false);
    if (!*mIsLoveEnable_d)
        as_list->x_2(66, 12, false, false);
    as_list->x_6(1, 0, 0.0f);
    as_list->x_6(2, 0, 0.0f);
    as_list->x_6(9, 0, 0.0f);
}

void HorseWaitForEventAction::calc_() {
    sub_7100E5AD10();
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    if (auto* controller = mActor->getCharacterController())
        act::sub_7100E7F698(rideable, as_list, controller);
}

}  // namespace uking::action
