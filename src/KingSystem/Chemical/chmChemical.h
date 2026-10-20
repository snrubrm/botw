#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act { class ActorChemicals; class Chemical; class Unk_71024dd490; class Unk_71024e6428; }
class Element;
class Unk_7102518688;
class Unk_71025187d0;

namespace ksys::world {
struct Unk_ChemicalMgrM2Arg;
Unk_71025187d0* sub_71010CBF7C(act::Unk_71024dd490* holder, Unk_ChemicalMgrM2Arg* arg);
}  // namespace ksys::world

namespace ksys::chm {

// D997B4 combines each component, keeping the larger magnitude when the signs agree.
void sub_7100D997B4(sead::Vector3f* out, const sead::Vector3f& value);
f32 sub_7100D99B74(f32 value);
const char* sub_7100D99CD4(f32 value);

// Name from Chemical::createInstance in the CSV. Allocation and both destructors prove this layout.
class Chemical : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Chemical)
    Chemical() = default;
    virtual ~Chemical();

public:
    void createChmresAndHeap(sead::Heap* heap);
    // Adds / removes an element holder (act::Unk_71024dd490).
    void sub_7100D99738(act::Unk_71024dd490* holder);
    void sub_7100D99760(act::Unk_71024dd490* holder);
    s32 sub_7100D9979C();

private:
    sead::CriticalSection _28;
    friend class act::Chemical;
    // ActorChemicals lifetime and holder updates notify the chemical watch.
    friend class act::ActorChemicals;
    // E3B144 performs the native watch notification using the element owner pointer.
    friend class act::Unk_71024e6428;
    // lane1 s90: the elements read the heap and the watch flags.
    friend class ::Element;
    friend class ::Unk_7102518688;
    // lane1 s91: the element factories (Unk_71024dd490::createElement) use the heap, lock and flags.
    friend class act::Unk_71024dd490;
    friend ::Unk_71025187d0* world::sub_71010CBF7C(act::Unk_71024dd490* holder,
                                                  world::Unk_ChemicalMgrM2Arg* arg);
    sead::PtrArray<act::Unk_71024dd490> _68;
    sead::Heap* _78 = nullptr;
    // Original d9979c obtains a unique id with a relaxed exclusive increment.
    sead::Atomic<s32> _80 = 1;
    u8 _84 = 0;
    u8 _85 = 0;
    sead::CriticalSection _88;
};
KSYS_CHECK_SIZE_NX150(Chemical, 0xc8);

}  // namespace ksys::chm
