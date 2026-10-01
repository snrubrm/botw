#include "Game/AI/AI/aiInsectEscape.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

InsectEscape::InsectEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectEscape::~InsectEscape() = default;

bool InsectEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100449E98();
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
