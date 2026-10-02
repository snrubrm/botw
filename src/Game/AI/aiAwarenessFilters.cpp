#include "Game/AI/aiAwarenessFilters.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

using ksys::act::Unk_71024dc858;
using ksys::act::Unk_71024dc978;

bool Unk_7102451358::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.sub_7100D10FB8();
}

bool Unk_71024513d0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::isDoor(&target->mLink);
}

bool Unk_7102451448::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isEnemyProfile(&target->mLink))
        return true;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::AwarenessEnemySearchTarget);
}

bool Unk_7102451538::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::ExplosivesEnemyAI);
}

bool Unk_7102451588::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.getProfile() == "Horse";
}

bool Unk_7102451628::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isPlayerProfile(&target->mLink))
        return true;
    return ksys::act::isNPCProfile(&target->mLink);
}

bool Unk_7102451678::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::isPlayerProfile(&target->mLink);
}

bool Unk_71024516a0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::IsPressBreakByEnNPC);
}

bool Unk_7102451768::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    return target->mLink.getId() == _28;
}

bool Unk_7102451830::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (!target->mLink.hasProc() || !ksys::act::isAlive(&target->mLink))
        return false;
    if (ksys::act::isEnemyProfile(&target->mLink))
        return true;
    return ksys::act::isWolfOrBear(&target->mLink);
}
