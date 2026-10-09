#include "Game/AI/AI/aiLynelArrowAttackSelectBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

LynelArrowAttackSelectBase::LynelArrowAttackSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LynelArrowAttackSelectBase::~LynelArrowAttackSelectBase() = default;

bool LynelArrowAttackSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelArrowAttackSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mLynelAIFlags_a & 0x20) {
        changeToShootUp(params);
        return;
    }
    const s32 state = sub_71005D9744(mActor);
    if (state == 2 || state == 3)
        changeChild("通常撃ち", params);
    else
        changeToShootUp(params);
}

void LynelArrowAttackSelectBase::changeToShootUp(ksys::act::ai::InlineParamPack* params) {
    *mLynelAIFlags_a |= 0x20;
    changeChild("上空撃ち", params);
}

bool LynelArrowAttackSelectBase::sub_710048B2B8() {
    const s32 state = sub_71005D9744(mActor);
    return state == 2 || state == 3;
}

void LynelArrowAttackSelectBase::calc_() {}

void LynelArrowAttackSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelArrowAttackSelectBase::loadParams_() {
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
