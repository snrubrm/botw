#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class InstParamPack;

// Placeholder name: the list of drop actors created for one actor (DropMgr::Entry::list). Its functions are in the
// TU at 0x710124a690. Nodes come from the DropMgr node pool (DropMgr::freeNode).
class DropActorList {
public:
    struct Node {
        Node();
        ~Node();
        Actor* releaseActor();
        void createActor(const sead::SafeString& name, InstParamPack* params, s32 mode);

        Node* next;
        BaseProcHandle handle;
        s32 _18;
    };
    KSYS_CHECK_SIZE_NX150(Node, 0x20);

    // 0x710124a690 / 0x710124a698
    DropActorList();
    ~DropActorList();
    // 0x710124a704: deletes the drop actors and returns the nodes to the pool.
    void sub_710124A704();
    // 0x710124a770: whether every drop actor is ready or failed.
    bool sub_710124A770() const;
    // 0x710124a7c0: places the ready drop actors around `actor` and returns the nodes to the pool.
    void sub_710124A7C0(Actor* actor, bool clear_fade_in);

    void pushFront(Node* node);

    Node* mHead;
};
KSYS_CHECK_SIZE_NX150(DropActorList, 0x8);

class DropMgr {
    SEAD_SINGLETON_DISPOSER(DropMgr)
    // Value-initialize the direct array: D2B83C zeroes it before calling its constructor.
    DropMgr() : mEntries() {}
    // NON_MATCHING: the singleton disposer keeps the entry-array address across node-pool deletion.
    ~DropMgr() {
        for (auto& entry : mEntries)
            entry.list.sub_710124A704();
        delete[] static_cast<u8*>(mNodePool.work());
        mNodePool.reset();
    }

public:
    struct Entry {
        BaseProcLink link;
        DropActorList list;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x18);
    // CSV DropMgr::init: allocates the node pool.
    bool init(s32 num_nodes, sead::Heap* heap);
    // 0x7100d2bdbc (CSV DropMgr::__auto3): returns `node` to the pool.
    void freeNode(void* node);
    // 0x7100d2be00 (CSV DropMgr::__auto1; placeholder name): whether the drops created for `actor` are ready (true
    // if there are none).
    bool sub_7100D2BE00(Actor* actor);
    void createDrops(Actor* actor, bool clear_fade_in);
    // 0x7100d2c024 (CSV DropMgr::__auto2; placeholder name): creates the drops of `actor` into a free entry;
    // false if drops are disabled or no entry is free.
    bool sub_7100D2C024(Actor* actor);
    // 0x7100d2c114 (CSV DropMgr::x; placeholder name): the drop list of a free entry, now linked to `actor` (null if
    // `actor` already has one or none is free).
    DropActorList* sub_7100D2C114(Actor* actor);
    // 0x7100d2c204 (CSV name).
    void createDropsWithTable(Actor* actor, DropActorList* list,
                              const sead::Buffer<Unk_71025ae620::Unk1>* table);

private:
    // inline-only in the original; name is a guess (createDrops, sub_7100D2BE00 and sub_7100D2C114 repeat the
    // locked search over the entries).
    // Defined in actDropMgr.cpp (needs the complete Actor).
    inline s32 findEntry(Actor* actor);

    /* 0x20 */ sead::CriticalSection mNodeCS;
    // Pool of DropActorList::Node (allocated by init).
    /* 0x60 */ sead::FreeList mNodePool;
    /* 0x70 */ sead::CriticalSection mEntryCS;
    /* 0xb0 */ sead::SafeArray<Entry, 32> mEntries;
};
KSYS_CHECK_SIZE_NX150(DropMgr, 0x3b0);

bool getDropVel(const sead::SafeString& name, sead::Vector3f* velocity, Actor* actor, s32 kind);
bool getDropAngVel(sead::Vector3f* angular_velocity, Actor* actor, s32 kind, s32 mode,
                   const sead::Vector3f* velocity);

// CSV name; fills the drop actor matrix using the source actor and its drop mode.
void calculateDropPosition(sead::Matrix34f* matrix, Actor* actor, s32 mode);

}  // namespace ksys::act
