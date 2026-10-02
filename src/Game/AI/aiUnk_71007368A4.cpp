#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEatTarget.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Utils/StringUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

bool sub_71007368A4(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.hasTag(ksys::act::tags::TypeKokko))
        return true;
    return accessor.getName() == "Kokko_Simple";
}

bool sub_710073697C(ksys::act::BaseProcLink* link, const sead::SafeString& name) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_71006DE298(name);
}

bool sub_71007369D0(ksys::act::BaseProcLink* link, const sead::SafeString& name) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_71006DE338(name);
}

sead::Vector3f sub_7100736A24(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.getPreviousPos();
}

bool sub_7100736B68(int value) {
    return value == 21 || sub_7100736B94(value);
}

bool sub_7100736B94(int value) {
    switch (value) {
    case 20:
    case 22:
    case 23:
    case 27:
    case 30:
    case 31:
        return true;
    default:
        return false;
    }
}

bool sub_7100736BBC(int value) {
    return value == 6 || value == 7 || value == 8;
}

bool sub_7100736BD8(int value) {
    return value == 25 || value == 26;
}

bool sub_7100736D98(ksys::act::Actor* actor) {
    auto* dmg = actor->getDamageMgr();
    if (!dmg)
        return false;
    return dmg->getField54() == 2 || dmg->getField54() == 1 || dmg->getField54() == 5;
}

bool sub_7100739930(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto* race = actor->getParam()->getRes().mGParamList->getEnemyRace();
    return ksys::util::sub_71010C2EE4(accessor.getName(), race->mEscapeAttackedActorType.ref(),
                                      ',');
}

bool sub_71007399B4(ksys::act::Actor* actor, const ksys::act::ActorConstDataAccess& accessor) {
    if (actor->getParam()->getRes().mGParamList->getEnemyRace()->mIsUseTargetTag.ref() &&
        accessor.hasTag(ksys::act::tags::EnemyTarget)) {
        return true;
    }
    return false;

}

bool sub_7100739E24(ksys::act::Actor* actor, ksys::act::BaseProcLink* link, int kind) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto* eat = actor->getParam()->getRes().mGParamList->getEatTarget();
    const sead::SafeString& name = accessor.getName();

    if (!eat->mEatActorTags.ref().isEmpty() &&
        ksys::act::hasOneTagAtLeast(link, eat->mEatActorTags.ref())) {
        return true;
    }
    if (!eat->mFavoriteEatActorTags.ref().isEmpty() &&
        ksys::act::hasOneTagAtLeast(link, eat->mFavoriteEatActorTags.ref())) {
        return true;
    }

    switch (kind) {
    case 0:
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames.ref(), ','))
            return true;
        break;
    case 1:
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames2.ref(), ','))
            return true;
        break;
    case 2:
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames3.ref(), ','))
            return true;
        break;
    case 3:
        if (ksys::util::sub_71010C2EE4(name, eat->mFavoriteEatActorNames.ref(), ','))
            return true;
        break;
    default:
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames.ref(), ','))
            return true;
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames2.ref(), ','))
            return true;
        if (ksys::util::sub_71010C2EE4(name, eat->mEatActorNames3.ref(), ','))
            return true;
        if (ksys::util::sub_71010C2EE4(name, eat->mFavoriteEatActorNames.ref(), ','))
            return true;
        break;
    }
    return false;
}

bool sub_710073A010(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    ksys::act::ActorConstDataAccess accessor(proc);
    const auto* eat = actor->getParam()->getRes().mGParamList->getEatTarget();
    const sead::SafeString& name = accessor.getName();
    if (!eat->mFavoriteEatActorTags.ref().isEmpty() &&
        ksys::act::hasOneTagAtLeast(accessor, eat->mFavoriteEatActorTags.ref())) {
        return true;
    }
    return ksys::util::sub_71010C2EE4(name, eat->mFavoriteEatActorNames.ref(), ',');
}

bool sub_7100739A10(ksys::act::Actor* actor, const sead::SafeString& name) {
    const auto* race = actor->getParam()->getRes().mGParamList->getEnemyRace();
    const sead::SafeString& types = race->mTargetActorType.ref();
    sead::FixedSafeString<32> type;
    for (auto it = types.tokenBegin(","); types.tokenEnd(",") != it; ++it) {
        it.get(&type);
        if (name == type)
            return true;
    }
    return false;
}
