#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "Game/Damage/dmgDamageManager.h"
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

bool sub_71006D28AC(ksys::act::Actor* actor) {
    if (actor->getAtk())
        return true;
    auto* param = actor->getParam();
    if (!param->getRes().mDamageParam)
        return false;
    return !param->isDummyParam(ksys::res::ActorLink::User::DamageParam);
}
