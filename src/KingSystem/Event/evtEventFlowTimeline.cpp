#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include <evfl/ResTimeline.h>
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/VFR.h"

namespace ksys::evt {

// NON_MATCHING: the original destructor destroys members that are not modelled yet.
EventFlowTimeline::~EventFlowTimeline() {
    if (_628) {
        delete[] _628;
        _628 = nullptr;
        _620 = 0;
    }
    Manager::instance()->getStruct1()->sub_7101273334(_638, true);
}

// 0x7100dbd3b4
void EventFlowTimeline::m8(Command command) {
    switch (command) {
    case Command::_1:
        _644 |= 4;
        break;
    case Command::_2:
        _644 |= 0x20;
        break;
    case Command::_3:
        _644 |= 8;
        break;
    case Command::_4:
        _644 |= 1;
        eft::Effect::instance()->sub_71011B8584(true);
        eft::Effect::instance()->sub_71011B8658(true);
        break;
    case Command::_5:
        _644 &= ~1;
        eft::Effect::instance()->sub_71011B8584(false);
        eft::Effect::instance()->sub_71011B8658(true);
        break;
    case Command::_6:
        _644 = (_644 & ~3) | 2;
        break;
    case Command::_7:
        _644 |= 0x10;
        break;
    default:
        break;
    }
    Manager::instance()->_1d2f4 |= 0x800;
}

// 0x7100dbd370
f32 EventFlowTimeline::getFrameCount() const {
    if (!_628)
        return 0.0f;
    return _628->GetTime();
}

// 0x7100dbd388: whether the action's clip ends at or after the end of the timeline
bool EventFlowTimeline::m10(const evfl::ActionArg& arg) {
    return arg.res.clip->start_time + arg.res.clip->duration >= _628->GetTimeline()->duration;
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

// 0x7100dbd154
s32 EventFlowTimeline::sub_7100DBD154() {
    const f32 frame = getFrameCount();
    const auto* timeline = _628->GetTimeline();
    const auto* cuts = timeline->cuts.Get();
    for (s32 i = timeline->num_cuts - 1; i >= 0; --i) {
        if (cuts[i].start_time <= frame)
            return i;
    }
    return 0;
}

// 0x7100dbd4a4
// NON_MATCHING: the original converts each value to double right where it is computed and allocates two registers
// differently (it matches when the cut start / length are inline member helpers evaluated in the argument list)
void EventFlowTimeline::printStatus(sead::BufferedSafeString* out) {
    if (!isPlaying()) {
        out->format(_100->m7());
        return;
    }
    const s32 cut_number = sub_7100DBD154() + 1;
    const f32 frame = getFrameCount();
    const s32 start_cut = sub_7100DBD154();
    const f32 cut_start =
        _628->GetTimeline()->cuts.Get()[sead::Mathi::clamp(start_cut, 0, _628->GetTimeline()->num_cuts - 1)]
            .start_time;
    const f32 time_in_cut = frame - cut_start;
    const s32 len_cut = sub_7100DBD154();
    const auto* timeline = _628->GetTimeline();
    const f32 cut_end = len_cut < timeline->num_cuts - 1 ? timeline->cuts.Get()[len_cut + 1].start_time :
                                                           timeline->duration;
    const s32 cut_length = cut_end - timeline->cuts.Get()[len_cut].start_time;
    out->format("[カット%d] %5.2f/%d  総時間:%5.2f/%d", cut_number, time_in_cut, cut_length, getFrameCount(),
                s32(_628->GetTimeline()->duration));
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
    _108->initTimeline(mEventName);
}

// 0x7100dbd3ac
void EventFlowTimeline::m16() {}

// 0x7100dbd3b0
void EventFlowTimeline::m17() {}

}  // namespace ksys::evt
