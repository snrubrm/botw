#include "Game/AI/AI/aiYunBoCannonBallRoot.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

YunBoCannonBallRoot::YunBoCannonBallRoot(const InitArg& arg) : CannonBallRoot(arg) {}

YunBoCannonBallRoot::~YunBoCannonBallRoot() = default;

bool YunBoCannonBallRoot::init_(sead::Heap* heap) {
    return CannonBallRoot::init_(heap);
}

// NON_MATCHING: the original loads mActor before the comparison of *mCannonSpot_m (ours loads it after the branch)
void YunBoCannonBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    CannonBallRoot::enter_(params);
    const char* name;
    switch (*mCannonSpot_m) {
    case 0:
        name = "CustomFireBridge";
        break;
    case 1:
        name = "CustomFireBattle";
        break;
    default:
        return;
    }
    ksys::eft::sub_710105DF6C(mActor, name, false, true);
}

void YunBoCannonBallRoot::calc_() {
    CannonBallRoot::calc_();
}

void YunBoCannonBallRoot::leave_() {
    CannonBallRoot::leave_();
}

void YunBoCannonBallRoot::loadParams_() {
    CannonBallRoot::loadParams_();
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
}

}  // namespace uking::ai
