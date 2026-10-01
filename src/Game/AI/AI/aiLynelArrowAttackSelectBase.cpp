#include "Game/AI/AI/aiLynelArrowAttackSelectBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

LynelArrowAttackSelectBase::LynelArrowAttackSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LynelArrowAttackSelectBase::~LynelArrowAttackSelectBase() = default;

bool LynelArrowAttackSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the target duplicates the flag-set + changeChild block into both predecessors
void LynelArrowAttackSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!(*mLynelAIFlags_a & 0x20)) {
        const s32 state = sub_71005D9744(mActor);
        if (state == 2 || state == 3) {
            changeChild("通常撃ち", params);
            return;
        }
    }
    *mLynelAIFlags_a |= 0x20;
    changeChild("上空撃ち", params);
}

void LynelArrowAttackSelectBase::calc_() {}

void LynelArrowAttackSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelArrowAttackSelectBase::loadParams_() {
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
