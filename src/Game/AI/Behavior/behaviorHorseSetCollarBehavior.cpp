#include "Game/AI/Behavior/behaviorHorseSetCollarBehavior.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

HorseSetCollarBehavior::HorseSetCollarBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseSetCollarBehavior::~HorseSetCollarBehavior() = default;

bool HorseSetCollarBehavior::m6(sead::Heap* heap) {
    return true;
}

void HorseSetCollarBehavior::m7() {}

// NON_MATCHING: bank selections and the random-range increment are scheduled differently.
void HorseSetCollarBehavior::m8() {
    const bool has_options = mActor->getHorseOptionsMaybe() != nullptr;
    const s32 shoe_bank = has_options ? 3 : 1;
    const s32 collar_bank = has_options ? 4 : 2;
    auto* list = mActor->getASList();
    if (*mHorseShoeFrame_s >= 0 && list->getSlot0BankCount() > shoe_bank) {
        list->startAnimationMaybe(-1.0f, -1.0f, "Horseshoe", 0, shoe_bank, true);
        list->x_3(0, shoe_bank, &ksys::as::ASList::Unk2::sub_7101163298,
                  *mHorseShoeFrame_s);
    }
    if (list->getSlot0BankCount() > collar_bank) {
        list->startAnimationMaybe(-1.0f, -1.0f, uking::act::sUnk_7102603410[0],
                                  0, collar_bank, true);
        const s32 last_frame = list->x_5(0, collar_bank,
                                       &ksys::as::ASList::Unk2::sub_710116323C);
        const s32 frame = sead::GlobalRandom::instance()->getU32(last_frame + 1);
        list->x_3(0, collar_bank, &ksys::as::ASList::Unk2::sub_7101163298, frame);
    }
}

void HorseSetCollarBehavior::m9() {}

void HorseSetCollarBehavior::loadParams() {
    getStaticParam(&mHorseShoeFrame_s, "HorseShoeFrame");
}

}  // namespace uking::behavior
