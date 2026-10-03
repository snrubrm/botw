#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <thread/seadAtomic.h>
#include <thread/seadEvent.h>

namespace ksys::phys {

// Placeholder: a sead::Event with a reference count (released by ~Unk_7100f7e9f0).
class Unk_7100f7e9f0Event {
public:
    sead::Event mEvent;
    sead::Atomic<s32> mRefCount;
};
static_assert(offsetof(Unk_7100f7e9f0Event, mRefCount) == 0x30);

// Separate translation unit: the original calls the constructor out of line from
// NavMeshCharacter::sub_7100F76078.
Unk_7100f7e9f0::Unk_7100f7e9f0() : _0(nullptr), _8(-1), _10(nullptr) {}

Unk_7100f7e9f0::~Unk_7100f7e9f0() {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
}

bool Unk_7100f7e9f0::sub_7100F7EB40() const {
    return _0 && _8 != -1;
}

}  // namespace ksys::phys
