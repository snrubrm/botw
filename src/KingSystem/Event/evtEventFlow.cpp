#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

// NON_MATCHING (all four destructors below): the original destructors destroy members that are not modelled
// yet (EventFlow::~EventFlow is 324 bytes). They are defaulted here so that the classes' vtables (and with them
// the RTTI functions, which match) are emitted.
EventFlow::~EventFlow() = default;
EventFlowFlowchart::~EventFlowFlowchart() = default;
EventFlowTimeline::~EventFlowTimeline() = default;
EventFlowMovie::~EventFlowMovie() = default;

// 0x7100db8c9c (CSV evt::EventFlowBase::m4_null)
void EventFlow::m4() {}

// 0x7100db8ca0 (CSV evt::EventFlowBase::m7)
void* EventFlow::m7() {
    return nullptr;
}

// 0x7100db8ca8 (CSV evt::EventFlowBase::m8_null)
void EventFlow::m8() {}

// 0x7100db8cac (CSV evt::EventFlowBase::m10)
s32 EventFlow::m10() {
    return 0;
}

// 0x7100db627c
act::BaseProcLink* EventFlow::getBaseProcLink() {
    return &_118->mLink;
}

// 0x7100db6288
bool EventFlow::byte3FlagIsSet() const {
    return _340_bytes[3] & 1;
}

// 0x7100db8b84
void EventFlow::x(bool set) {
    _340 = set ? (_340 | 0xa0) : ((_340 & ~0xa0ull) | 0x20);
    if (_108)
        _108->sub_7100DC3698();
}

// 0x7100db8b68
void EventFlow::exitEventMaybe() {
    _340 |= 0x40;
    if (_108)
        _108->sub_7100DC3698();
}

// 0x7100db7888
void EventFlow::setFlag4() {
    _340 |= 4;
}

// 0x7100db8a24
bool EventFlow::isPlaying() {
    return _100->isPlaying();
}

// 0x7100dbb414
f32 EventFlowFlowchart::getFrameCount() const {
    return _6b4;
}

// 0x7100dbb41c
s32 EventFlowFlowchart::getEventFlowType() const {
    return 0;
}

// 0x7100dbb2e4
void EventFlowFlowchart::m16() {}

// 0x7100dbb2e8
void EventFlowFlowchart::m17() {}

// 0x7100dbd7bc
s32 EventFlowTimeline::getEventFlowType() const {
    return 1;
}

// 0x7100dbd7c4
void* EventFlowTimeline::m7() {
    return _638;
}

// 0x7100dbc90c
void EventFlowTimeline::m15() {
    _108->initTimeline(_10);
}

// 0x7100dbd3ac
void EventFlowTimeline::m16() {}

// 0x7100dbd3b0
void EventFlowTimeline::m17() {}

// 0x7100dbc710
void EventFlowMovie::m11() {}

// 0x7100dbc714
void EventFlowMovie::m15() {}

// 0x7100dbc718
void EventFlowMovie::m16() {}

// 0x7100dbc71c
void EventFlowMovie::m17() {}

}  // namespace ksys::evt
