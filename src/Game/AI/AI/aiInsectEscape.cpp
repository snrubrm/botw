#include "Game/AI/AI/aiInsectEscape.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

InsectEscape::InsectEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectEscape::~InsectEscape() = default;

bool InsectEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100449E98();
}

void InsectEscape::sub_7100449E98() {
    mActor->getMtx().getTranslation(_70);
    _7c = _70;
    sead::Vector3f dir = _70 - *mTargetPos_d;
    dir.y = 0;
    dir.normalize();
    sub_710044A218(dir, *mRunAwayDistanceMax_s);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_7c, "TargetPos", -1);
    params.addVec3(_70, "MoveAwayFromPos", -1);
    changeChild("移動", &params);
}

// NON_MATCHING: the rotation's multiply/add scheduling differs (dir is loaded before the random calls in the original)
bool InsectEscape::sub_710044A218(const sead::Vector3f& dir, f32 distance) {
    const f32 range_v = *mAllowRandAngleVertical_s;
    const f32 range_h = *mAllowRandAngleHorizontal_s;
    const f32 angle_v = sead::GlobalRandom::instance()->getF32Range(-range_v, range_v);
    const f32 angle_h = sead::GlobalRandom::instance()->getF32Range(-range_h, range_h);
    sead::Matrix33f rot;
    rot.makeR({angle_v, angle_h, 0});
    sead::Vector3f v;
    v.setMul(rot, dir);
    _7c = _70 + v * distance;
    _7c.y += *mRunAwayHeightOffset_s;
    if (*mInWater_s) {
        if (mActor->get68f().load()) {
            const f32 depth = mActor->get6f0() - mActor->getMtx().m[1][3];
            if (_7c.y - _70.y >= depth)
                _7c.y -= depth + 1.0f;
        } else {
            _7c.y = _70.y;
        }
    }
    return true;
}

// NON_MATCHING: the original keeps the "out of water" bool materialized (cset/cbnz)
void InsectEscape::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        setFinished();
        return;
    }

    child->isChangeable();

    bool out_of_water = true;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        out_of_water = mActor->get6f0() - y < 0.1f;
    }

    if (out_of_water && *mInWater_s)
        setFinished();
}

void InsectEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InsectEscape::loadParams_() {
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mRunAwayDistanceMin_s, "RunAwayDistanceMin");
    getStaticParam(&mRunAwayHeightOffset_s, "RunAwayHeightOffset");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mInWater_s, "InWater");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
