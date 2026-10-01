#include "Game/AI/AI/aiRepeatByLargeDamage.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RepeatByLargeDamage::RepeatByLargeDamage(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RepeatByLargeDamage::~RepeatByLargeDamage() = default;

bool RepeatByLargeDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RepeatByLargeDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = true;
    changeChild("吹っ飛び", params);
}

void RepeatByLargeDamage::calc_() {
    if (_38) {
        _38 = false;
        return;
    }

    auto* dmg_mgr = mActor->getDamageMgr();
    if (dmg_mgr && dmg_mgr->getField54() >= 16)
        changeChild("吹っ飛び");
}

void RepeatByLargeDamage::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RepeatByLargeDamage::loadParams_() {}

}  // namespace uking::ai
