#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

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
