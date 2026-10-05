#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

CircleMove::CircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMove::~CircleMove() = default;

bool CircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: Direct margin branches and vector stack placement differ from the original.
void CircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = 1.0f;
    sead::Vector3f offset;
    m34(&offset);
    offset = mActor->getMtx().getTranslation() - offset;
    const f32 distance = sead::Vector2f(offset.x, offset.z).length();
    const f32 difference = distance - m37();
    if (sead::Mathf::abs(difference) > *mRadiusMargin_s) {
        if (difference < 0.0f) {
            sub_710034E838();
        } else {
            sead::Vector3f target;
            m34(&target);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("近づき", &pack);
        }
    } else {
        sub_710034E90C(false);
    }
}

void CircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusMargin_s, "RadiusMargin");
    getStaticParam(&mSpeed_s, "Speed");
}

void CircleMove::m35(const sead::Vector3f& target_pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void CircleMove::m36(const sead::Vector3f& target_pos) {
    getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
}

void CircleMove::m38(sead::Vector3f* out, f32 angle, f32 radius) {
    if (!out)
        return;
    m34(out);
    out->x += sead::Mathf::sin(angle) * radius;
    out->z += sead::Mathf::cos(angle) * radius;
}

}  // namespace uking::ai
