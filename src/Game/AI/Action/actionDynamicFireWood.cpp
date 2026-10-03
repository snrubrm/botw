#include "Game/AI/Action/actionDynamicFireWood.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DynamicFireWood::DynamicFireWood(const InitArg& arg) : FireWood(arg) {}

DynamicFireWood::~DynamicFireWood() = default;

bool DynamicFireWood::init_(sead::Heap* heap) {
    return FireWood::init_(heap);
}

void DynamicFireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireWood::enter_(params);
    _41 = false;
}

void DynamicFireWood::leave_() {
    FireWood::leave_();
}

void DynamicFireWood::loadParams_() {
    FireWood::loadParams_();
}

void DynamicFireWood::calc_() {
    FireWood::calc_();
    if (_41) {
        if (auto* info = mActor->m135())
            info->_4 = 1;
        mActor->killWithDropsAndEffects(0);
    }
}

int DynamicFireWood::m33() {
    if (_41)
        return 0;
    return FireWood::m33();
}

}  // namespace uking::action
