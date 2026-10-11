#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

// Descriptive name. EDCAE0 constructs the string at 0 and link at 98;
// complete producers EBE30, 540108 and 7E95E0 bind EDCC10 and reset the link.
// The only table is the existing FixedSafeString<128> member's table 235AC40.
class ActorUniqueNameSearch {
public:
    explicit ActorUniqueNameSearch(const sead::SafeString& unique_name);
    void sub_7100EDCC10(BaseProc* proc);

    sead::FixedSafeString<128> mUniqueName;
    BaseProcLink mLink;
};
static_assert(sizeof(ActorUniqueNameSearch) == 0xa8);

}  // namespace ksys::act
