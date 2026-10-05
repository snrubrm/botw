#include "Game/AI/AI/aiStalHeadLifted.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

StalHeadLifted::StalHeadLifted(const InitArg& arg) : Lifted(arg) {}

StalHeadLifted::~StalHeadLifted() = default;

bool StalHeadLifted::init_(sead::Heap* heap) {
    return Lifted::init_(heap);
}

void StalHeadLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    Lifted::enter_(params);
}

// NON_MATCHING: vector normalization keeps an intermediate stack copy and schedules products differently.
void StalHeadLifted::calc_() {
    Lifted::calc_();
    if (isCurrentChild("所持") && sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
        sead::Vector3f direction = *mEscapeDir_s;
        direction.normalize();
        direction *= *mEscapeSpeed_s;
        direction *= ksys::act::sub_7100EDD218(mActor);
        sub_71005A66E8(direction, false);
    } else {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && isCurrentChild("逃走"))
            setFinished();
    }
}

void StalHeadLifted::leave_() {
    Lifted::leave_();
}

void StalHeadLifted::loadParams_() {
    Lifted::loadParams_();
    getStaticParam(&mEscapeSpeed_s, "EscapeSpeed");
    getStaticParam(&mEscapeDir_s, "EscapeDir");
}

}  // namespace uking::ai
