#include "Game/AI/AI/aiTargetPredictRotSpdTargetPos.h"
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TargetPredictRotSpdTargetPos::TargetPredictRotSpdTargetPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPredictRotSpdTargetPos::~TargetPredictRotSpdTargetPos() = default;

bool TargetPredictRotSpdTargetPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPredictRotSpdTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPredictRotSpdTargetPos::calc_() {
    TargetPosAI::calc_();
}

void TargetPredictRotSpdTargetPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPredictRotSpdTargetPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

// NON_MATCHING: register allocation / scheduling only (the translation's x / z land in s9 / s10 in the
// original and the actor matrix elements are loaded after the cross-product operands)
void TargetPredictRotSpdTargetPos::m35(sead::Vector3f* pos) {
    *pos = sub_71005D9330(mActor);

    sead::Vector3f trans;
    mActor->getMtx().getTranslation(trans);
    sead::Vector3f dir = *pos;
    dir -= trans;

    const sead::Vector3f& velocity = sub_71005D9548(mActor);
    sead::Vector3f perp = velocity;
    perp.y = 0;
    sead::Vector3f dir_xz = dir;
    dir_xz.y = 0;
    dir_xz.normalize();
    ksys::util::sub_71011EFA00(&perp, perp, dir_xz);

    const f32 perp_len = std::sqrt(perp.x * perp.x + perp.z * perp.z);
    const f32 dist = std::sqrt(dir.x * dir.x + dir.z * dir.z);

    f32 angle = perp_len / dist * *mAddSpeed_s;
    if ((velocity.x + pos->x - trans.x) * mActor->getMtx()(2, 2) -
            (velocity.z + pos->z - trans.z) * mActor->getMtx()(0, 2) <
        0)
        angle = -angle;

    ksys::util::sub_71011EF010(&dir, angle);
    *pos += dir;
}

}  // namespace uking::ai
