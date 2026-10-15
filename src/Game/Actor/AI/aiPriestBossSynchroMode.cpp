#include "Game/Actor/AI/aiPriestBossSynchroMode.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossSynchroMode::PriestBossSynchroMode(const InitArg& arg) : PriestBoss(arg) {}

PriestBossSynchroMode::~PriestBossSynchroMode() = default;

bool PriestBossSynchroMode::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

// NON_MATCHING: the original threads `case 2` (mode 0) straight to the index store (index 0) instead of
// testing the mode again after the switch.
void PriestBossSynchroMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
    auto* unit = sub_7100505BE4();
    if (!unit) {
        changeChild(4);
        _50 = 4;
    } else {
        const s32 formation = unit->sub_7100719FA4();
        const s32 type = unit->sub_7100719F70();
        s32 mode;
        switch (formation) {
        case 1:
            mode = type == 1 ? 1 : 3;
            break;
        case 2:
            mode = 0;
            break;
        case 3:
            mode = 2;
            break;
        default:
            mode = 4;
            break;
        }
        s32 index;
        if (mode == 0)
            index = 0;
        else if (mode == 4)
            index = -1;
        else
            index = 1;
        *mEquipWeaponBufIndex_a = index;
        changeChild(Mode::text(mode));
        _50 = mode;
        const int idx = unit->sub_7100719534(mActor);
        mActor->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_20, unit->sub_7100719978(idx));
    }
    *mReturnFromBananaMode_a = false;
}

void PriestBossSynchroMode::leave_() {
    PriestBoss::leave_();
}

void PriestBossSynchroMode::loadParams_() {
    PriestBoss::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
