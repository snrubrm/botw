#include "KingSystem/Event/evtEventFlow.h"
#include <evfl/ResTimeline.h>
#include "KingSystem/Event/evtManager.h"

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

// 0x7100dbaca8 (CSV evt::EventFlowFlowchart::init2)
void EventFlowFlowchart::m15() {
    _108->initFlowchart(_10, _68);
}

// 0x7100dbb234 (CSV evt::EventFlowFlowchart::isFinished)
s32 EventFlowFlowchart::m10() {
    const s32 state = _69c;
    if (state == 0)
        _340 &= ~0x2400ull;
    return state == 0;
}

// 0x7100dbd370
f32 EventFlowTimeline::getFrameCount() const {
    if (!_628)
        return 0.0f;
    return _628->GetTime();
}

// 0x7100dbccd8 (CSV evt::EventFlowTimeline::start)
void EventFlowTimeline::m13() {
    _630 = 0;
    _628->Start(0.0f);
    if (_340 & 0x20000) {
        _340 &= ~0x2400ull;
    } else {
        const bool forbid_skip = _108->mDemoInfo.isForbidSkip();
        _340 &= ~0x2400ull;
        if (!forbid_skip)
            _340 |= 0x400;
    }
}

// 0x7100dbd318 (CSV evt::EventFlowTimeline::update)
// NON_MATCHING: same logic, but the original computes `(time >= duration) & !(flag & 8)` as tst / cset eq / and where
// every source form gives `bic w0, w9, w8, lsr #3` (or a branch for `&&`); register numbers differ as well.
bool EventFlowTimeline::m14() {
    const f32 time = _628->GetTime();
    const f32 duration = _628->GetTimeline()->duration;
    if (time >= duration)
        _340 &= ~0x2400ull;
    const bool not_skipped = !(Manager::instance()->_1d2f4_bytes[0] & 8);
    return (time >= duration) & not_skipped;
}

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
