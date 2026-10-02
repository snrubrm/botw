#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

FlyingEnemyKeepMove::FlyingEnemyKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyingEnemyKeepMove::~FlyingEnemyKeepMove() = default;

bool FlyingEnemyKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyingEnemyKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FlyingEnemyKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyingEnemyKeepMove::loadParams_() {
    getStaticParam(&mLostDistance_s, "LostDistance");
    getStaticParam(&mAngleRange_s, "AngleRange");
    getStaticParam(&mSpaceDistance_s, "SpaceDistance");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mBaseHeight_s, "BaseHeight");
    getStaticParam(&mLowHeight_s, "LowHeight");
    getStaticParam(&mHighHeight_s, "HighHeight");
}

void FlyingEnemyKeepMove::m35(sead::Vector3f* out, const sead::Vector3f& dir) {
    if (!out)
        return;
    const auto& mtx = sub_71005D96A8(mActor);
    sead::Vector3f offset = dir;
    offset *= *mBaseDist_s;
    offset.y += *mBaseHeight_s;
    out->setMul(mtx, offset);
}

void FlyingEnemyKeepMove::m36(sead::Vector3f* out) {
    out->set(sub_71005D9330(mActor));
    out->y += *mBaseHeight_s;
}

}  // namespace uking::ai
