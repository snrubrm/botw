#include "Game/Actor/Action/actionDragonReleaseGrudgeForDemo.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/System/Timer.h"

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

// NON_MATCHING: flag-mask and nested-state address registers are exchanged.
void DragonReleaseGrudgeForDemo::leave_() {
    DragonPlayASForDemo::leave_();
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._930 &= ~0x40;
        dragon->_14c8.sub_71006FD830(-1.f, -1.f);
    }
}

void DragonReleaseGrudgeForDemo::loadParams_() {
    DragonPlayASForDemo::loadParams_();
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mHeadTransSmoothStartFrame_s, "HeadTransSmoothStartFrame");
    getStaticParam(&mHeadTransSmoothEndFrame_s, "HeadTransSmoothEndFrame");
    getStaticParam(&mHeadTransSmoothRate_s, "HeadTransSmoothRate");
    getStaticParam(&mHeadTransSmoothSklRootRate_s, "HeadTransSmoothSklRootRate");
}

// NON_MATCHING: the _14c8 address is computed before the two parameter loads (after them in the original).
void DragonReleaseGrudgeForDemo::calc_() {
    DragonPlayASForDemo::calc_();
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;

    auto* as_list = dragon->getASList();
    const bool flag = dragon->sub_710000FDFC();
    dragon->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_1000000, flag);
    if (as_list)
        as_list->x_2(66, 1, flag, false);

    const f32 prev = _e8;
    ksys::Timer::update(&_e8, 1.0f);
    if (prev < *mReleaseTime_s && _e8 >= *mReleaseTime_s) {
        dragon->sub_710000E500("Color_Ice");
        if (auto* bgm = ksys::snd::sub_7100FFE094())
            bgm->sub_7101001808(false);
    }
    if (prev < *mHeadTransSmoothStartFrame_s && _e8 >= *mHeadTransSmoothStartFrame_s)
        dragon->_14c8.sub_71006FD830(*mHeadTransSmoothRate_s, *mHeadTransSmoothSklRootRate_s);
    if (prev < *mHeadTransSmoothEndFrame_s && _e8 >= *mHeadTransSmoothEndFrame_s)
        dragon->_14c8.sub_71006FD830(-1.0f, -1.0f);
}

}  // namespace uking::action
