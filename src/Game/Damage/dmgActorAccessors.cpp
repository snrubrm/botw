#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyShown.h"

// Accessor-based wrappers in the TU 0x71006de3d8-0x71006df0f8 (lane4 s44; placeholder names, the CSV has none): they cast
// the accessor's proc to an Actor / DynamicActor (the default value without one).

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

static inline ksys::act::Actor* getActorOfAccessor(const ksys::act::ActorConstDataAccess& accessor) {
    return static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
}

static inline ksys::act::DynamicActor* getDynamicActor(const ksys::act::ActorConstDataAccess& accessor) {
    return sead::DynamicCast<ksys::act::DynamicActor>(accessor.getProc());
}

// 0x71006de3d8: the EnemyShown GParam says IsHappy, or IsCasebyCase together with Actor::checkBasicSig.
bool sub_71006DE3D8(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    const auto* shown = actor->getParam()->getRes().mGParamList->getEnemyShown();
    if (shown->mIsHappy.ref())
        return true;
    if (shown->mIsCasebyCase.ref())
        return actor->checkBasicSig();
    return false;
}

// 0x71006de4a4: IsSit, or IsCasebyCase without Actor::checkBasicSig.
bool sub_71006DE4A4(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    const auto* shown = actor->getParam()->getRes().mGParamList->getEnemyShown();
    if (shown->mIsSit.ref())
        return true;
    if (shown->mIsCasebyCase.ref())
        return !actor->checkBasicSig();
    return false;
}

// 0x71006de574: IsNoise.
bool sub_71006DE574(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    return actor->getParam()->getRes().mGParamList->getEnemyShown()->mIsNoise.ref();
}

// 0x71006de628: DamageManagerBase::sub_71006E11F4(type) of the accessor's actor (false without a damage manager).
bool sub_71006DE628(const ksys::act::ActorConstDataAccess& accessor, s32 type) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    auto* manager = sead::DynamicCast<uking::dmg::DamageManagerBase>(actor->getDamageMgr());
    if (!manager)
        return false;
    return manager->sub_71006E11F4(type);
}

// 0x71006deb48 / 0x71006debec: DynamicActor::m151 / m152.
bool sub_71006DEB48(const ksys::act::ActorConstDataAccess& accessor, int bit) {
    auto* actor = getDynamicActor(accessor);
    return actor ? actor->m151(bit) : false;
}

bool sub_71006DEBEC(const ksys::act::ActorConstDataAccess& accessor, int mask) {
    auto* actor = getDynamicActor(accessor);
    return actor ? actor->m152(mask) : false;
}

// 0x71006df068 / 0x71006df0f8: bit 2 / 3 of DynamicActor::_a68.
bool sub_71006DF068(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getDynamicActor(accessor);
    return actor ? (actor->_a68 >> 2 & 1) : false;
}

bool sub_71006DF0F8(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getDynamicActor(accessor);
    return actor ? (actor->_a68 >> 3 & 1) : false;
}

// 0x71006de938 / 0x71006dea40: bit 0 / 1 of ActorAtk::_78.
bool sub_71006DE938(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    auto* atk = sead::DynamicCast<ksys::act::ActorAtk>(actor->getAtk());
    return atk ? (atk->_78 & 1) : false;
}

bool sub_71006DEA40(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = getActorOfAccessor(accessor);
    if (!actor)
        return false;
    auto* atk = sead::DynamicCast<ksys::act::ActorAtk>(actor->getAtk());
    return atk ? (atk->_78 >> 1 & 1) : false;
}

// 0x71006ded9c: sub_71005DC604 on the accessor's actor.
void sub_71006DED9C(const ksys::act::ActorConstDataAccess& accessor, ksys::act::BaseProc* proc) {
    if (auto* actor = getActorOfAccessor(accessor))
        sub_71005DC604(actor, proc);
}

// 0x71006def64: DamageManager::_68 of the accessor's actor.
s32 sub_71006DEF64(const ksys::act::ActorConstDataAccess* accessor) {
    auto* actor = getActorOfAccessor(*accessor);
    if (!actor)
        return 0;
    auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr());
    return manager ? manager->_68 : 0;
}

bool sub_71006D28AC(ksys::act::Actor* actor) {
    if (actor->getAtk())
        return true;
    auto* param = actor->getParam();
    if (!param->getRes().mDamageParam)
        return false;
    return !param->isDummyParam(ksys::res::ActorLink::User::DamageParam);
}
