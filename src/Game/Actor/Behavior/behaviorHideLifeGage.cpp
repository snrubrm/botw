#include "Game/Actor/Behavior/behaviorHideLifeGage.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

HideLifeGage::HideLifeGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HideLifeGage::~HideLifeGage() = default;

bool HideLifeGage::init_(sead::Heap* heap) {
    return true;
}

void HideLifeGage::calc() {}

void HideLifeGage::loadParams() {

}

void HideLifeGage::enter() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        _28 = enemy->_e90;
        enemy->_e90 = 1;
    }
}

void HideLifeGage::leave() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = _28;
}

}  // namespace uking::behavior
