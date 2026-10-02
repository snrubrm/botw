#include "Game/AI/AI/aiPreyDeadCauseSelector.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

PreyDeadCauseSelector::PreyDeadCauseSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyDeadCauseSelector::~PreyDeadCauseSelector() = default;

bool PreyDeadCauseSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyDeadCauseSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = sub_710072BA90(mActor);
    if (!mgr) {
        setFailed();
        return;
    }
    const s32 field54 = mgr->getField54();
    const s32 field50 = mgr->getField50();
    if (sub_7100736BD8(field54) || field50 == 15)
        changeChild("落下");
    else
        changeChild("通常");
}

void PreyDeadCauseSelector::calc_() {}

void PreyDeadCauseSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyDeadCauseSelector::loadParams_() {}

}  // namespace uking::ai
