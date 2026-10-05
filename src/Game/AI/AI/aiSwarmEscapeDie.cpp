#include "Game/AI/AI/aiSwarmEscapeDie.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

SwarmEscapeDie::SwarmEscapeDie(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmEscapeDie::~SwarmEscapeDie() = default;

bool SwarmEscapeDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the position copy combines stores and schedules its component loads differently.
void SwarmEscapeDie::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (ksys::sub_7100D8C4F8(pos))
        sub_71005B1464();
    else
        sub_71005B15F8();
}

void SwarmEscapeDie::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmEscapeDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseHeight_s, "RiseHeight");
    getStaticParam(&mRiseDist_s, "RiseDist");
    getStaticParam(&mEndDist_s, "EndDist");
}

// NON_MATCHING: vector temporaries and return-path scheduling differ.
void SwarmEscapeDie::calc_() {
    if (_58.value > *mTime_s) {
        setFinished();
        return;
    }
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f camera_position;
    ksys::sub_7100D8C6AC(&camera_position);
    if (ksys::util::sqXZDistance(camera_position, position) >
        sead::Mathf::square(*mEndDist_s)) {
        setFinished();
        return;
    }
    _58.update();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("集合"))
            sub_71005B1464();
        else if (isCurrentChild("上昇"))
            sub_71005B19F8();
        else
            setFinished();
        return;
    }
    if (isCurrentChild("逃走")) {
        auto* actor = mActor;
        sead::Vector3f direction = actor->getMtx().getBase(2);
        const sead::Vector3f position = actor->getMtx().getTranslation();
        direction.normalize();
        _64 = position + direction * *mEndDist_s;
    }
}

}  // namespace uking::ai
