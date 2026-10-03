#include "Game/AI/AI/aiLastBossRoot.h"
#include "Game/gameLastBossMgr.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LastBossRoot::LastBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossRoot::~LastBossRoot() = default;

bool LastBossRoot::init_(sead::Heap* heap) {
    if (auto* mgr = LastBossMgr::instance())
        mgr->sub_7100677FFC(mActor);
    _b4 = false;
    _b5 = false;
    return true;
}

void LastBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LastBossRoot::hasPreDeleteCb() {
    return true;
}

void LastBossRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossRoot::loadParams_() {
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mAuraHPRate_s, "AuraHPRate");
    getStaticParam(&mAuraDemoName_s, "AuraDemoName");
    getStaticParam(&mAuraEntryName_s, "AuraEntryName");
    getStaticParam(&mAuraWallEntry_s, "AuraWallEntry");
    getStaticParam(&mAuraDemoDownEntry_s, "AuraDemoDownEntry");
}

}  // namespace uking::ai
