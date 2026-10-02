#include "Game/AI/AI/aiNavViewMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NavViewMove::NavViewMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavViewMove::~NavViewMove() = default;

bool NavViewMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavViewMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_71004BABDC()) {
        sub_71004BAE20();
        return;
    }

    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

void NavViewMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavViewMove::loadParams_() {
    getStaticParam(&mSubsAngle_s, "SubsAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
