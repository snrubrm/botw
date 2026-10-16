#include "Game/Actor/Behavior/behaviorForceDispLifeGage.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/Damage/dmgDamageManager.h"

namespace uking::behavior {

ForceDispLifeGage::ForceDispLifeGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceDispLifeGage::~ForceDispLifeGage() = default;

bool ForceDispLifeGage::init_(sead::Heap* heap) {
    return true;
}

void ForceDispLifeGage::loadParams() {
    getStaticParam(&mIsOnlyPlayer_s, "IsOnlyPlayer");
}

bool ForceDispLifeGage::sub_71006232EC() {
    if (sub_71005D94AC(mActor).hasProcInCalcState())
        return sub_71005D8FBC(mActor);
    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(mActor->getDamageMgr());
    if (mgr && (mgr->getFlags2() & 0xffff0000) == 0x10000)
        return true;
    return false;
}

void ForceDispLifeGage::calc() {
    if (!*mIsOnlyPlayer_s)
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.change(0x20000, sub_71006232EC());
}

void ForceDispLifeGage::enter() {
    if (*mIsOnlyPlayer_s)
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.set(0x20000);
}

void ForceDispLifeGage::leave() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e84.reset(0x20000);
}

}  // namespace uking::behavior
