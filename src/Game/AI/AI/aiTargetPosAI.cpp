#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetPosAI::TargetPosAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosAI::~TargetPosAI() = default;

bool TargetPosAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m35(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
}

void TargetPosAI::calc_() {
    if (*mOnEnterOnly_s)
        return;

    sead::Vector3f pos;
    m35(&pos);
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
}

void TargetPosAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosAI::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
