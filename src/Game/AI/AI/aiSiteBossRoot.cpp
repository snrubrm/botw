#include "Game/AI/AI/aiSiteBossRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SiteBossRoot::SiteBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRoot::~SiteBossRoot() {
    x();
    if (ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R) &&
        !mIsPlayed_DemoFlagName_s.isEmpty()) {
        ksys::gdt::setBoolByKey(false, mIsPlayed_DemoFlagName_s);
    }
}

void SiteBossRoot::x() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor("WeakPoint");
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC("WeakPoint");
}

bool SiteBossRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossRoot::onPreDelete() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->x_0();
}

void SiteBossRoot::m34(act::SiteBoss* boss) {}

void SiteBossRoot::loadParams_() {
    getStaticParam(&mOffFlagIndexAtClipping_s, "OffFlagIndexAtClipping");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mBlownOffAtWeakPointHitNum_s, "BlownOffAtWeakPointHitNum");
    getStaticParam(&mDemoPlayHPRate_s, "DemoPlayHPRate");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mIsRemainBoss_s, "IsRemainBoss");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mNormalEntryName_s, "NormalEntryName");
    getStaticParam(&mAtDownEntryName_s, "AtDownEntryName");
    getStaticParam(&mIsPlayed_DemoFlagName_s, "IsPlayed_DemoFlagName");
    getMapUnitParam(&mUniqueNameMessageLabel_m, "UniqueNameMessageLabel");
}

bool SiteBossRoot::handleMessage_(const ksys::Message* message) {
    return message->getType() == 0x3000007;
}

}  // namespace uking::ai
