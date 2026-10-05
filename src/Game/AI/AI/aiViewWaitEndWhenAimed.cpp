#include "Game/AI/AI/aiViewWaitEndWhenAimed.h"
#include "KingSystem/ActorSystem/actActor.h"

// Declaration only; the original source namespace is unknown and input constness is inferred.
bool sub_71005E0CB0(bool* out, ksys::act::Actor* actor, const gsys::BoneAccessKeyEx* key,
                    bool mode, f32 angle, f32 range);

namespace uking::ai {

ViewWaitEndWhenAimed::ViewWaitEndWhenAimed(const InitArg& arg) : TimeredViewWait(arg) {}

ViewWaitEndWhenAimed::~ViewWaitEndWhenAimed() = default;

bool ViewWaitEndWhenAimed::init_(sead::Heap* heap) {
    if (!TimeredViewWait::init_(heap))
        return false;

    if (!mBoneName_s.isEmpty() && mActor->getModel())
        _a0.search(mActor->getModel(), mBoneName_s);
    else
        _a0.getKey().reset();
    return true;
}

void ViewWaitEndWhenAimed::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredViewWait::enter_(params);
}

void ViewWaitEndWhenAimed::calc_() {
    bool direction = false;
    if (sub_71005E0CB0(&direction, mActor, &_a0, true, *mAimedAngle_s, *mBowRange_s)) {
        const int end_time = *mEndTime_s;
        if (end_time <= 0) {
            setFinished();
            return;
        }
        if (_70 >= end_time)
            _70 = end_time;
    }
    TimeredViewWait::calc_();
}

void ViewWaitEndWhenAimed::leave_() {
    TimeredViewWait::leave_();
}

void ViewWaitEndWhenAimed::loadParams_() {
    TimeredViewWait::loadParams_();
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mAimedAngle_s, "AimedAngle");
    getStaticParam(&mBowRange_s, "BowRange");
    getStaticParam(&mBoneName_s, "BoneName");
}

}  // namespace uking::ai
