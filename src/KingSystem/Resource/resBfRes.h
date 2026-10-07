#pragma once

#include <container/seadListImpl.h>
#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

// Placeholder name (vtable 0x71025148f8, typeinfo 0x71025b71c8; ctor 0x71011fe300, size 0x1a8): the bfres
// resource of the texture handle manager. Only the type is modelled (for DynamicCast).
// TODO: incomplete.
class BfRes : public Resource {
    SEAD_RTTI_OVERRIDE(BfRes, Resource)
public:
    BfRes();
    ~BfRes() override;
    s32 getLoadDataAlignment() const override;

    // 0x71011ffecc (declared only)
    void sub_71011FFECC();

    u8 _38[0x50 - 0x38];
    void* _50;
    u8 _58[0x188 - 0x58];
    // The node of ResourceMgrTask::mBfResList.
    sead::ListNode mListNode;
    void* _198;
    void* _1a0;
};

KSYS_CHECK_SIZE_NX150(BfRes, 0x1a8);

}  // namespace ksys::res
