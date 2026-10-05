#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorPreLoadMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace ksys::act {

// NON_MATCHING: The compiler devirtualizes SafeString assignment and arranges stack locals differently.
void DropData::initFromActor(Actor* actor) {
    sead::SafeString drop_actor;
    const sead::SafeString key = "DropActor";
    auto* root_ai = actor->getRootAi();
    if (!root_ai || !root_ai->getMapUnitParam(&drop_actor, key)) {
        const char* value = nullptr;
        if (actor->getMapObjIter().tryGetParamStringByKey(&value, key))
            drop_actor = value;
        else
            drop_actor = sead::SafeString::cEmptyString;
    }
    init(actor, drop_actor);
}

// NON_MATCHING: the original keeps the null check of GlobalParameter::instance() (ours drops it)
bool DropData::getDropVelocity(const sead::SafeString& name, sead::Vector3f* velocity,
                               f32* random) {
    if (_c & 0x20) {
        auto* global = GlobalParameter::instance();
        const auto* param = global ? global->getGlobalParam() : nullptr;
        *random = param->mDropItemVelRandomFromBomb.ref();
        velocity->x = 0.0f;
        velocity->y = param->mDropItemVelYFromBomb.ref();
        velocity->z = param->mDropItemVelXZFromBomb.ref();
        return true;
    }

    if (_c & 0x200) {
        auto* global = GlobalParameter::instance();
        const auto* param = global ? global->getGlobalParam() : nullptr;
        *random = param->mDropItemVelRandomRupeeRabbit.ref();
        velocity->x = 0.0f;
        velocity->y = param->mDropItemVelYRupeeRabbit.ref();
        velocity->z = param->mDropItemVelXZRupeeRabbit.ref();
        return true;
    }

    if (hasTag(name, tags::Rupee)) {
        auto* global = GlobalParameter::instance();
        const auto* param = global ? global->getGlobalParam() : nullptr;
        *random = param->mDropItemVelRandomItemRupeeOnly.ref();
        velocity->x = 0.0f;
        velocity->y = param->mDropItemVelYItemRupeeOnly.ref();
        velocity->z = param->mDropItemVelXZItemRupeeOnly.ref();
        return true;
    }

    return false;
}

// NON_MATCHING: same as getDropVelocity
bool DropData::getDropAngVelFromBomb(f32* ang_velocity, f32* random) {
    if (!(_c & 0x20))
        return false;
    auto* global = GlobalParameter::instance();
    const auto* param = global ? global->getGlobalParam() : nullptr;
    *ang_velocity = param->mDropItemAngVelFromBomb.ref();
    *random = param->mDropItemAngVelRandomFromBomb.ref();
    return true;
}

void DropData::sub_71006DB89C(Unk_71025ae620* data) {
    if (data)
        delete data;
}

void DropData::clearFlags() {
    _c = 0;
}

bool DropData::isHappy() {
    return _c >> 1 & 1;
}

bool DropData::isFlag1Set() {
    return _c & 1;
}

bool DropData::m5() {
    return _c >> 7 & 1;
}

DropData::~DropData() = default;

// NON_MATCHING: the existing getHomePos definition is inlined into this caller.
bool DropData::preloadDropsMaybe(Actor* actor) {
    if (!(_c & 0x100))
        return false;

    auto* mgr = ActorPreLoadMgr::instance();
    auto* entry = mgr->x(actor);
    if (!entry)
        return false;

    sead::Vector3f home_pos;
    actor->getHomePos(&home_pos);
    for (s32 table = 0; table < 7; ++table) {
        for (s32 i = 0; i < 16; ++i) {
            if (_10[table][i]._0 < 1)
                break;
            mgr->preloadActorMaybe(entry, _10[table][i]._8);
        }
    }
    return true;
}

void DropData::resetPreloadActorsMaybe(Actor* actor) {
    ActorPreLoadMgr::instance()->sub_7100D58F28(actor);
}

}  // namespace ksys::act
