#include "Game/AI/Action/actionDragonReleaseGrudgeForDemo.h"
#include "Game/Actor/actDragon.h"

namespace uking::action {

DragonReleaseGrudgeForDemo::DragonReleaseGrudgeForDemo(const InitArg& arg)
    : DragonPlayASForDemo(arg) {}

DragonReleaseGrudgeForDemo::~DragonReleaseGrudgeForDemo() = default;

bool DragonReleaseGrudgeForDemo::init_(sead::Heap* heap) {
    return DragonPlayASForDemo::init_(heap);
}

void DragonReleaseGrudgeForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonPlayASForDemo::enter_(params);
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._930 |= 0x40;
        playAS("Release_Grudge_Mat", false, 5, 1, -1.0f);
        _e8 = 0;
    }
}

void DragonReleaseGrudgeForDemo::leave_() {
    DragonPlayASForDemo::leave_();
}

void DragonReleaseGrudgeForDemo::loadParams_() {
    DragonPlayASForDemo::loadParams_();
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mHeadTransSmoothStartFrame_s, "HeadTransSmoothStartFrame");
    getStaticParam(&mHeadTransSmoothEndFrame_s, "HeadTransSmoothEndFrame");
    getStaticParam(&mHeadTransSmoothRate_s, "HeadTransSmoothRate");
    getStaticParam(&mHeadTransSmoothSklRootRate_s, "HeadTransSmoothSklRootRate");
}

void DragonReleaseGrudgeForDemo::calc_() {
    DragonPlayASForDemo::calc_();
}

}  // namespace uking::action
