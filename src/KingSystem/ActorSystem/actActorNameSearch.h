#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

class Actor;

// PlayerPullSword 0x71008077fc constructs this 0x50-byte stack record and
// binds sub_7100EDC9E8 through Delegate1<BaseProc*>. Table 0x71024f1488
// has only the two destructor entries. Name is descriptive.
class ActorNearestSearch {
public:
    ActorNearestSearch(const char* unique_name, Actor* actor, BaseProc** result,
                       const sead::Vector3f& origin);
    virtual ~ActorNearestSearch() = default;
    void sub_7100EDC810(BaseProc* proc);
    void sub_7100EDC9E8(BaseProc* proc);

    sead::Vector3f mOrigin;
    f32 mClosestDistance;
    s32 mCount;
    sead::SafeString mName;
    sead::SafeString mUniqueName;
    Actor* mActor;
    BaseProc** mResult;
};
static_assert(sizeof(ActorNearestSearch) == 0x50);

// Name is a guess: the native camera search producer binds sub_7100EDCED0 to this record.
class ActorNameSearch {
public:
    ActorNameSearch(const sead::Vector3f& origin, const sead::SafeString& unique_name);
    void sub_7100EDCED0(BaseProc* proc);

    sead::Vector3f mOrigin;
    sead::FixedSafeString<128> mUniqueName;
    BaseProcLink mLink;
    f32 mClosestDistanceSquared;
};
static_assert(sizeof(ActorNameSearch) == 0xc0);

}  // namespace ksys::act
