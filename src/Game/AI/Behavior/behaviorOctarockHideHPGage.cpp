#include "Game/AI/Behavior/behaviorOctarockHideHPGage.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

OctarockHideHPGage::OctarockHideHPGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockHideHPGage::~OctarockHideHPGage() = default;

bool OctarockHideHPGage::m6(sead::Heap* heap) {
    return true;
}

void OctarockHideHPGage::m8() {}

void OctarockHideHPGage::loadParams() {
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockHideHPGage::m9() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = 0;
}

}  // namespace uking::behavior
