#include "Game/AI/Behavior/behaviorForceDispLifeGage.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

ForceDispLifeGage::ForceDispLifeGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceDispLifeGage::~ForceDispLifeGage() = default;

bool ForceDispLifeGage::m6(sead::Heap* heap) {
    return true;
}

void ForceDispLifeGage::loadParams() {
    getStaticParam(&mIsOnlyPlayer_s, "IsOnlyPlayer");
}

void ForceDispLifeGage::m8() {
    if (*mIsOnlyPlayer_s)
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.set(0x20000);
}

void ForceDispLifeGage::m9() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.reset(0x20000);
}

}  // namespace uking::behavior
