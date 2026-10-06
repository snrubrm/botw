#pragma once

#include <container/seadListImpl.h>
#include "aal/aalNamedObj.h"

namespace aal {

/// Places a listener (every listener poser is registered in the ListenerMgr). TODO: incomplete.
class ListenerPoser : public NamedObj {
public:
    static constexpr s32 getListNodeOffset() { return 0x60; }

protected:
    u8 _18[0x60 - 0x18];
    sead::ListNode mListNode;
};

}  // namespace aal
