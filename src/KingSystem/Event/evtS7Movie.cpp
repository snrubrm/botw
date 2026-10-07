#include "KingSystem/Event/evtS7.h"

namespace ksys::evt {

// 0x71008b8edc
S7Movie::S7Movie(sead::Heap* heap, EventFlowBase* flow) : S7(heap, flow) {
    _1c = 0;
    _20 = 0;
    _1c0 = false;
}

// D1 0x71008b8fc0, D0 0x71008b8fd4
// Written as `{ ; }` (as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }, user-approved): the original keeps
// the vtable store, which an empty destructor drops.
S7Movie::~S7Movie() {
    ;
}

}  // namespace ksys::evt
