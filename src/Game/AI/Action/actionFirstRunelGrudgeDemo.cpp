#include "Game/AI/Action/actionFirstRunelGrudgeDemo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/actDragon.h"

namespace uking::action {

FirstRunelGrudgeDemo::FirstRunelGrudgeDemo(const InitArg& arg) : DragonPlayASForDemo(arg) {}

FirstRunelGrudgeDemo::~FirstRunelGrudgeDemo() = default;

bool FirstRunelGrudgeDemo::init_(sead::Heap* heap) {
    return DragonPlayASForDemo::init_(heap);
}

void FirstRunelGrudgeDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonPlayASForDemo::enter_(params);
    xlinkEventOn(mActor, 0x19, 0, false);
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._930 &= ~0x40;
        dragon->_1f70.set(0x80000);
    }
}

void FirstRunelGrudgeDemo::leave_() {
    DragonPlayASForDemo::leave_();
}

void FirstRunelGrudgeDemo::loadParams_() {
    DragonPlayASForDemo::loadParams_();
}

void FirstRunelGrudgeDemo::calc_() {
    DragonPlayASForDemo::calc_();
}

}  // namespace uking::action
