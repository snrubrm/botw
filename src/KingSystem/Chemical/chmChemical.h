#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act { class Chemical; }

namespace ksys::chm {

// D997B4 combines each component, keeping the larger magnitude when the signs agree.
void sub_7100D997B4(sead::Vector3f* out, const sead::Vector3f& value);

// Name from Chemical::createInstance in the CSV. Allocation and both destructors prove this layout.
class Chemical : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Chemical)
    Chemical() = default;
    virtual ~Chemical();

public:
    void createChmresAndHeap(sead::Heap* heap);
    void sub_7100D99738(act::Chemical* chemical);
    void sub_7100D99760(act::Chemical* chemical);
    s32 sub_7100D9979C();

private:
    sead::CriticalSection _28;
    friend class act::Chemical;
    sead::PtrArray<act::Chemical> _68;
    sead::Heap* _78 = nullptr;
    // Original d9979c obtains a unique id with a relaxed exclusive increment.
    sead::Atomic<s32> _80 = 1;
    u8 _84 = 0;
    u8 _85 = 0;
    sead::CriticalSection _88;
};
KSYS_CHECK_SIZE_NX150(Chemical, 0xc8);

}  // namespace ksys::chm
