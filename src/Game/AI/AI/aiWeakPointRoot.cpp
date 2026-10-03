#include "Game/AI/AI/aiWeakPointRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WeakPointRoot::WeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeakPointRoot::~WeakPointRoot() = default;

bool WeakPointRoot::init_(sead::Heap* heap) {
    _60 = mActor->getCreateArgBaseProcLink();
    _60.hasProc();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void WeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    _70._24 = *mIsShowCriticalEffect_s;
    _70._25 = mActor->getParam()->getRes().mDamageParam->mWeakPointNoUIFlag.ref();
    if (auto* mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<dmg::DamageManager>(mgr))
            manager->addDamageCallback(0, &_70);
    }
    _70._28 = false;
    _70._29 = false;
    changeChild("通常");
}

void WeakPointRoot::leave_() {
    if (auto* mgr = mActor->getDamageMgr())
        mgr->removeDamageCallback(&_70);
}

void WeakPointRoot::loadParams_() {
    getStaticParam(&mOwnerDamage_s, "OwnerDamage");
    getStaticParam(&mIsBreakable_s, "IsBreakable");
    getStaticParam(&mIsSyncDamage_s, "IsSyncDamage");
    getStaticParam(&mIsShowCriticalEffect_s, "IsShowCriticalEffect");
    getStaticParam(&mIsNoReaction_s, "IsNoReaction");
}

bool WeakPointRoot::handleMessage_(const ksys::Message* message) {
    if (_a0.m2(*message)) {
        _d8.x();
        return true;
    }
    if (_d8.m2(*message)) {
        _a0.x();
        return true;
    }
    if (_110.m2(*message)) {
        sub_71007A36BC(mActor);
        _110.x();
        return true;
    }
    if (_148.m2(*message)) {
        sub_71007A3540(mActor);
        _148.x();
        return true;
    }
    return false;
}

s32 WeakPointRoot::m34(dmg::DamageManagerBase* mgr) {
    return mgr->getField54();
}

s32 WeakPointRoot::m35(dmg::DamageManagerBase* mgr) {
    if (auto* manager = sead::DynamicCast<dmg::DamageManager>(mgr))
        return manager->_8c;
    return 0;
}

}  // namespace uking::ai
