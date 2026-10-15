#include "KingSystem/ActorSystem/actDropMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace ksys::act
