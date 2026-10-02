#include "Game/AI/Action/actionDragonPlayASForDemo.h"
#include "Game/Actor/actDragon.h"

namespace uking::action {

DragonPlayASForDemo::DragonPlayASForDemo(const InitArg& arg) : PlayASForDemo(arg) {}

DragonPlayASForDemo::~DragonPlayASForDemo() = default;

bool DragonPlayASForDemo::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void DragonPlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._8b8 = 0;
        sub_71000F7020();
    }
}

void DragonPlayASForDemo::leave_() {
    PlayASForDemo::leave_();
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor))
        dragon->_14c8._8b8 = 1.0f;
}

void DragonPlayASForDemo::loadParams_() {
    PlayASForDemo::loadParams_();
    getStaticParam(&mPosition_s, "Position");
    getStaticParam(&mRotate_s, "Rotate");
}

void DragonPlayASForDemo::calc_() {
    PlayASForDemo::calc_();
}

}  // namespace uking::action
