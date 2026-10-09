#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <thread/seadAtomic.h>
#include <thread/seadEvent.h>
#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMeshInstance.h>
#include <Havok/Ai/Pathfinding/Streaming/hkaiStreamingCollection.h>

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

Unk_7100f7e9f0::Unk_7100f7e9f0(hkaiStreamingCollection* collection, s32 key,
                                   Unk_7100f7e9f0Event* event)
    : _0(collection), _8(key), _10(event) {
    if (event) {
        while (true) {
            const s32 count = event->mRefCount;
            if (u32(count) > 0xff)
                break;
            if (event->mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    event->mEvent.resetSignal();
                break;
            }
        }
    }
}

Unk_7100f7e9f0& Unk_7100f7e9f0::operator=(const Unk_7100f7e9f0& other) {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
    _0 = other._0;
    _8 = other._8;
    _10 = other._10;
    event = _10;
    if (event) {
        while (true) {
            const s32 count = event->mRefCount;
            if (u32(count) > 0xff)
                break;
            if (event->mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    event->mEvent.resetSignal();
                break;
            }
        }
    }
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

f32 Unk_7100f7e9f0::sub_7100F7ED6C(sead::Vector3f* normal_out) const {
    auto* instance = _0->m_instances[u32(_8) >> 22].m_instancePtr;
    if (!instance)
        return 0.0f;
    hkVector4 normal;
    const f32 area = instance->sub_71015214B0(_8 & 0x3fffff, normal);
    if (normal_out)
        normal.store<3>(normal_out->e.data());
    return area;
}

}  // namespace ksys::phys
