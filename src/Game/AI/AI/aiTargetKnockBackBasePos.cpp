#include "Game/AI/AI/aiTargetKnockBackBasePos.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetKnockBackBasePos::TargetKnockBackBasePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetKnockBackBasePos::~TargetKnockBackBasePos() = default;

bool TargetKnockBackBasePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

// NON_MATCHING: regalloc (the original keeps &_40 in x21 and the actor in x22; ours the other way round)
void TargetKnockBackBasePos::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005E2318(&_40, mActor, sub_710072BA90(mActor));
    _40 *= -3.0f;
    _40 += mActor->getMtx().getTranslation();
    auto* actor = mActor;
    sub_71005E2318(&_40, actor, sub_710072BA90(actor));
    _40 *= -3.0f;
    _40 = mActor->getMtx().getTranslation() + _40;
    TargetPosAI::enter_(params);
}

void TargetKnockBackBasePos::calc_() {
    TargetPosAI::calc_();
}

void TargetKnockBackBasePos::leave_() {
    TargetPosAI::leave_();
}

void TargetKnockBackBasePos::loadParams_() {
    TargetPosAI::loadParams_();
}

void TargetKnockBackBasePos::m35(sead::Vector3f* pos) {
    *pos = _40;
}

}  // namespace uking::ai
