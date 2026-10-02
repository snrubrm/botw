#include "Game/AI/Behavior/behaviorEyeBlink.h"

namespace uking::behavior {

EyeBlink::EyeBlink(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void EyeBlink::loadParams() {
    getStaticParam(&mTimerMin_s, "TimerMin");
    getStaticParam(&mTimerMax_s, "TimerMax");
    getStaticParam(&mBlinkCount_s, "BlinkCount");
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
