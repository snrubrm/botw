#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <thread/seadAtomic.h>
#include <thread/seadEvent.h>

namespace ksys::phys {

// Placeholder: a sead::Event with a reference count (released by ~Unk_7100f7e9f0).
class Unk_7100f7e9f0Event {
public:
    // inline-only in the original; name is a guess. The bounded increment and
    // zero-count reset repeat in 0x7100f7ea04 and 0x7100f7ea64.
    void addRef() {
        while (true) {
            const s32 count = mRefCount;
            if (u32(count) > 0xff)
                return;
            if (mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    mEvent.resetSignal();
                return;
            }
        }
    }

    sead::Event mEvent;
    sead::Atomic<s32> mRefCount;
};
static_assert(offsetof(Unk_7100f7e9f0Event, mRefCount) == 0x30);

// Separate translation unit: the original calls the constructor out of line from
// NavMeshCharacter::sub_7100F76078.
Unk_7100f7e9f0::Unk_7100f7e9f0() : _0(nullptr), _8(-1), _10(nullptr) {}

Unk_7100f7e9f0::Unk_7100f7e9f0(hkaiStreamingCollection* collection, s32 key,
                                   Unk_7100f7e9f0Event* event)
    : _0(collection), _8(key), _10(event) {
    if (event)
        event->addRef();
}

Unk_7100f7e9f0& Unk_7100f7e9f0::operator=(const Unk_7100f7e9f0& other) {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
    _0 = other._0;
    _8 = other._8;
    _10 = other._10;
    if (_10)
        _10->addRef();
    return *this;
}

Unk_7100f7e9f0::~Unk_7100f7e9f0() {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
}

bool Unk_7100f7e9f0::sub_7100F7EB40() const {
    return _0 && _8 != -1;
}

}  // namespace ksys::phys
