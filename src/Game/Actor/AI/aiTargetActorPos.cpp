#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetActorPos::TargetActorPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetActorPos::~TargetActorPos() = default;

bool TargetActorPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    m35(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
}

void TargetActorPos::calc_() {
    if (*mOnEnterOnly_s)
        return;

    sead::Vector3f pos;
    m35(&pos);
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
}

void TargetActorPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetActorPos::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
