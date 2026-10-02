#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

CircleMove::CircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMove::~CircleMove() = default;

bool CircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
