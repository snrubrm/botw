#include "Game/AI/AI/aiSwarmEscapeDie.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// 0x71005b1464
// NON_MATCHING: the original loads the direction as x then (y, z) pairs and keeps the scaled components in other registers
void SwarmEscapeDie::sub_71005B1464() {
    sead::Vector3f direction;
    ksys::sub_7100D8C7FC(&direction);
    direction.y = 0;
    direction.normalize();
    sead::Vector3f camera_position;
    ksys::sub_7100D8C6AC(&camera_position);
    _64 = camera_position + direction * *mRiseDist_s;
    _64.y += *mRiseHeight_s;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_64, "TargetPos", -1);
    changeChild("上昇", &params);
}

// 0x71005b15f8
// NON_MATCHING: the original loads the direction as x then (y, z) pairs and keeps the scaled components in other registers
void SwarmEscapeDie::sub_71005B15F8() {
    sead::Vector3f direction;
    ksys::sub_7100D8C7FC(&direction);
    direction.y = 0;
    direction.normalize();
    sead::Vector3f position;
    if (sub_71005D8F28(mActor)) {
        position = sub_71005D960C(mActor);
    } else {
        ksys::sub_7100D8C6AC(&position);
        position.y += 1.0f;
    }
    _64 = position + direction * (*mRiseDist_s * 0.1f);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_64, "TargetPos", -1);
    changeChild("集合", &params);
}

// 0x71005b19f8
// NON_MATCHING: register allocation of the scaled direction (the original keeps it in w registers longer)
void SwarmEscapeDie::sub_71005B19F8() {
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    sead::Vector3f direction;
    actor->getMtx().getBase(direction, 2);
    direction.normalize();
    _64 = position + direction * *mEndDist_s;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_64, "TargetPos", -1);
    changeChild("逃走", &params);
}

}  // namespace uking::ai
