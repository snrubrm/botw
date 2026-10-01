#include "Game/AI/AI/aiTargetMyUp.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetMyUp::TargetMyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetMyUp::~TargetMyUp() = default;

bool TargetMyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetMyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (pos.y > *mEndHeight_s) {
        changeChild("終了");
        return;
    }

    ksys::act::ai::InlineParamPack pack;
    pos.y = *mEndHeight_s;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
}

void TargetMyUp::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("行動")) {
            changeChild("終了");
            return;
        }
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (child->isChangeable() && isCurrentChild("行動") &&
        mActor->getMtx().getTranslation().y > *mEndHeight_s) {
        changeChild("終了");
    }
}

void TargetMyUp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetMyUp::loadParams_() {
    getStaticParam(&mEndHeight_s, "EndHeight");
}

}  // namespace uking::ai
