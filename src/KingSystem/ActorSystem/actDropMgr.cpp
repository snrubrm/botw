#include "KingSystem/ActorSystem/actDropMgr.h"
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(DropMgr)

inline s32 DropMgr::findEntry(Actor* actor) {
    mEntryCS.lock();
    s32 i = 0;
    for (auto& entry : mEntries) {
        if (entry.link.hasProcById(actor)) {
            mEntryCS.unlock();
            return i;
        }
        ++i;
    }
    mEntryCS.unlock();
    return -1;
}

bool DropMgr::init(s32 num_nodes, sead::Heap* heap) {
    const u32 node_size = sizeof(DropActorList::Node);
    auto* work = new (heap, 4) u8[num_nodes * node_size];
    if (!work)
        return false;
    mNodePool.setWork(work, node_size, num_nodes);
    return true;
}

void DropMgr::freeNode(void* node) {
    auto lock = sead::makeScopedLock(mNodeCS);
    mNodePool.free(node);
}

bool DropMgr::sub_7100D2BE00(Actor* actor) {
    mEntryCS.lock();
    for (auto& entry : mEntries) {
        if (entry.link.hasProcById(actor)) {
            mEntryCS.unlock();
            return entry.list.sub_710124A770();
        }
    }
    mEntryCS.unlock();
    return true;
}

// NON_MATCHING: entry-search register allocation and temporary stack placement.
void DropMgr::createDrops(Actor* actor, bool clear_fade_in) {
    auto* drop_data = actor->getDropData();
    if (drop_data && drop_data->isFlag1Set())
        return;
    if (actor->isWaitRevivalForDrop())
        return;
    actor->setRevivalFlagForDrop(true);

    const s32 idx = findEntry(actor);
    if (idx >= 0) {
        mEntries[idx].list.sub_710124A7C0(actor, clear_fade_in);
        mEntries[idx].link.reset();
        return;
    }

    if (auto* data = actor->getDropData()) {
        sead::Vector3f pos;
        actor->getMtx().getTranslation(pos);
        sead::Buffer<Unk_71025ae620::Unk1> table;
        sead::Buffer<Unk_71025ae620::Unk1> table2;
        data->getTable(&table, &table2, pos);
        createDropsWithTable(actor, nullptr, &table);
        createDropsWithTable(actor, nullptr, &table2);
    }
}

bool DropMgr::sub_7100D2C024(Actor* actor) {
    auto* drop_data = actor->getDropData();
    if (drop_data && drop_data->isFlag1Set())
        return false;
    auto* list = sub_7100D2C114(actor);
    if (!list)
        return false;
    if (auto* data = actor->getDropData()) {
        sead::Vector3f pos;
        actor->getMtx().getTranslation(pos);
        sead::Buffer<Unk_71025ae620::Unk1> table;
        sead::Buffer<Unk_71025ae620::Unk1> table2;
        data->getTable(&table, &table2, pos);
        createDropsWithTable(actor, list, &table);
        createDropsWithTable(actor, list, &table2);
    }
    return true;
}

// NON_MATCHING: the inlined entry search and free-entry loop use different registers and branches.
DropActorList* DropMgr::sub_7100D2C114(Actor* actor) {
    auto lock = sead::makeScopedLock(mEntryCS);
    if (findEntry(actor) >= 0)
        return nullptr;
    for (auto& entry : mEntries) {
        if (!entry.link.hasProc()) {
            entry.link.acquire(actor, false);
            auto& list = entry.list;
            if (list.mHead)
                list.sub_710124A704();
            return &list;
        }
    }
    return nullptr;
}

// NON_MATCHING: parameter address selection retains the Parameter base and value offset.
bool getDropVel(const sead::SafeString& name, sead::Vector3f* velocity, Actor* actor, s32 kind) {
    auto* data = actor->getDropData();
    auto* global = GlobalParameter::instance();
    const auto* param = global ? global->getGlobalParam() : nullptr;
    f32 random;
    if (!data->getDropVelocity(name, velocity, &random)) {
        switch (kind) {
        case 2:
            random = param->mDropItemVelRandomLarge.ref();
            velocity->y = param->mDropItemVelYLarge.ref();
            velocity->z = param->mDropItemVelXZLarge.ref();
            break;
        case 1:
            random = param->mDropItemVelRandomSmall.ref();
            velocity->y = param->mDropItemVelYSmall.ref();
            velocity->z = param->mDropItemVelXZSmall.ref();
            break;
        default:
            return false;
        }
    }
    const f32 y_random = sead::GlobalRandom::instance()->getF32();
    velocity->y += random * y_random;
    const f32 z_random = sead::GlobalRandom::instance()->getF32();
    velocity->z += random * z_random;
    f32 sine, cosine;
    sead::Mathf::sinCosIdx(&sine, &cosine, sead::GlobalRandom::instance()->getU32());
    velocity->x = velocity->z * sine;
    velocity->z *= cosine;
    return true;
}

// NON_MATCHING: parameter address selection retains the Parameter base and value offset.
bool getDropAngVel(sead::Vector3f* angular_velocity, Actor* actor, s32 kind, s32 mode,
                   const sead::Vector3f* velocity) {
    auto* data = actor->getDropData();
    auto* global = GlobalParameter::instance();
    const auto* param = global ? global->getGlobalParam() : nullptr;
    f32 angle, random;
    if (!data->getDropAngVelFromBomb(&angle, &random)) {
        switch (kind) {
        case 2:
            random = param->mDropItemAngVelRandomLarge.ref();
            angle = param->mDropItemAngVelLarge.ref();
            break;
        case 1:
            random = param->mDropItemAngVelRandomSmall.ref();
            angle = param->mDropItemAngVelSmall.ref();
            break;
        default:
            return false;
        }
    }
    if (mode == 2) {
        angular_velocity->set(0.0f, 1.0f, 0.0f);
    } else {
        angular_velocity->set(velocity->z, 0.0f, -velocity->x);
        angular_velocity->normalize();
    }
    *angular_velocity *= sead::Mathf::deg2rad(angle + sead::GlobalRandom::instance()->getF32() * random);
    return true;
}

// NON_MATCHING: makeRIdx interpolation/math scheduling differs; actor position paths match.
void calculateDropPosition(sead::Matrix34f* matrix, Actor* actor, s32 mode) {
    if (mode == 1) {
        *matrix = actor->getMtx();
        return;
    }
    const u32 x = sead::GlobalRandom::instance()->getU32();
    if (mode == 2) {
        matrix->makeRIdx(0, x, 0);
    } else {
        const u32 y = sead::GlobalRandom::instance()->getU32();
        const u32 z = sead::GlobalRandom::instance()->getU32();
        matrix->makeRIdx(x, y, z);
    }
    if (auto* root_ai = actor->getRootAi()) {
        sead::Vector3f* forced_position;
        if (root_ai->getAITreeVariable2(&forced_position, "ForceSetDropPos") && actor->getDropData()->m5()) {
            matrix->setTranslation(*forced_position);
            return;
        }
    }
    sead::Vector3f position;
    actor->x_18(&position);
    matrix->setTranslation(position);
}

}  // namespace ksys::act
