#include "Game/AI/Action/actionDynamicFireWood.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

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

bool DynamicFireWood::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000be && !_40) {
        _41 = true;
        return true;
    }
    return FireWood::handleMessage_(message);
}

void DynamicFireWood::calc_() {
    FireWood::calc_();
    if (_41) {
        if (auto* info = mActor->m135())
            info->_4 = 1;
        mActor->killWithDropsAndEffects(0);
    }
}

bool DynamicFireWood::m33() {
    if (_41)
        return false;
    return FireWood::m33();
}

}  // namespace uking::action
