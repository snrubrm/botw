#pragma once

#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::act {
class Actor;
class BaseProc;
}  // namespace ksys::act

namespace uking::act {

// Placeholder name (ctor 0x7100d3cd74, dtor 0x7100d3cd84, functions up to 0x7100d3d3a4). A list of
// named, reference-counted links to other actors (CSV getActorPartsActor looks one up by name).
// Embedded in Enemy at 0x1128 and in NPC at 0xfa8; Actor vtable slot 101 returns it.
class Unk_7100d3cd74 {
public:
    // 0x38-byte list entry
    struct Unk1 {
        Unk1() : mListNode(this) {}

        sead::TListNode<Unk1*> mListNode;
        ksys::act::BaseProcLink mLink;
        s32 mRefCount = 1;
        u32 mNameHash = -1;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x38);

    explicit Unk_7100d3cd74(ksys::act::Actor* actor);
    ~Unk_7100d3cd74();

    void sub_7100D3CE30();
    bool sub_7100D3CED8(const sead::SafeString& name, sead::Heap* heap);
    bool sub_7100D3CFEC(const sead::SafeString& name);
    bool sub_7100D3D108(const sead::SafeString& name, ksys::act::BaseProc* proc);
    bool sub_7100D3D1E0(const sead::SafeString& name, const ksys::act::BaseProcLink& link);
    bool sub_7100D3D2B4(const sead::SafeString& name);
    ksys::act::BaseProcLink& getActorPartsActor(const sead::SafeString& name);

private:
    Unk1* find(const sead::SafeString& name) const;

public:

    /* 0x00 */ sead::TList<Unk1*> mList;
    /* 0x18 */ ksys::act::Actor* mActor;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d3cd74, 0x20);

}  // namespace uking::act
