#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include <evfl/ResTimeline.h>
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/VFR.h"

s32 getSceneStatus();

namespace ksys::evt {

EventFlowBase* sUnk_7102601528;

// NON_MATCHING (all four destructors below): the original destructors destroy members that are not modelled
// yet (EventFlowBase::~EventFlowBase is 324 bytes). They are defaulted here so that the classes' vtables (and with them
// the RTTI functions, which match) are emitted.
EventFlowBase::~EventFlowBase() = default;
EventFlowTimeline::~EventFlowTimeline() = default;
EventFlowMovie::~EventFlowMovie() = default;

// 0x7100db8c9c (CSV evt::EventFlowBase::m4_null)
void EventFlowBase::m4() {}

// 0x7100db8ca0 (CSV evt::EventFlowBase::m7)
void* EventFlowBase::m7() {
    return nullptr;
}

// 0x7100db8ca8 (CSV evt::EventFlowBase::m8_null)
void EventFlowBase::m8() {}

// 0x7100db8cac (CSV evt::EventFlowBase::m10)
s32 EventFlowBase::m10() {
    return 0;
}

// 0x7100db627c
BaseProcLinkForEvent* EventFlowBase::getBaseProcLink() {
    return &_118->mLink;
}

// 0x7100db6288
bool EventFlowBase::byte3FlagIsSet() const {
    return _340_bytes[3] & 1;
}

// 0x7100db8bb8
bool EventFlowBase::sub_7100DB8BB8(bool a1) {
    if (!_108)
        return true;
    return _108->load(a1);
}

// 0x7100db8b84
void EventFlowBase::x(bool set) {
    _340 = set ? (_340 | 0xa0) : ((_340 & ~0xa0ull) | 0x20);
    if (_108)
        _108->sub_7100DC3698();
}

// 0x7100db8b68
void EventFlowBase::exitEventMaybe() {
    _340 |= 0x40;
    if (_108)
        _108->sub_7100DC3698();
}

// 0x7100db7888
void EventFlowBase::setFlag4() {
    _340 |= 4;
}

// 0x7100db6cfc
void EventFlowBase::sub_7100DB6CFC() {
    _100->m6();
}

// 0x7100db6ad0
bool EventFlowBase::calc() {
    sUnk_7102601528 = this;
    const bool result = _100->m5();
    sUnk_7102601528 = nullptr;
    ++_2c8;
    return result;
}

// 0x7100db7148
void EventFlowBase::setupActors() {
    _110->mResource = _108;
    _110->allocActors(_108->mActorBindings, mHeap, mSlot);
    _340 |= 1;
}

// 0x7100db718c
void EventFlowBase::initActors() {
    _110->sub_7100DA2618(_108->mActorBindings);
}

// 0x7100db7540
bool EventFlowBase::x_0(bool a1, bool a2) {
    if (!_110->x_3(a1, a2) || !_108->areCameraAndModelAndXlinkReady())
        return false;
    delete _110;
    _110 = nullptr;
    if (_108->_1e0_bytes[1] & 8) {
        if (_108->_1b8)
            _108->_1b8->x_0();
        mSlot->setState3();
        mSlot = nullptr;
    } else {
        delete _108;
    }
    _108 = nullptr;
    return true;
}

// 0x7100db8abc
void EventFlowBase::x_7() {
    _2c8 = 0;
    _340 |= 0x3000;
    _110->x_2();
    _340 &= ~0x2000001000ull;
}

// 0x7100db8994
void EventFlowBase::x_5(EventFlowBase* other) {
    _100->m9();
    if ((other->getEventFlowType() == 0 && (other->_340_bytes[1] & 0x20)) ||
        (other->getEventFlowType() != 0 && (other->_340_bytes[6] & 1)))
        _340 |= 0x800000000000;
    else
        _340 &= ~0x800000000000ull;
}

// 0x7100db6c94
s32 EventFlowBase::x_1() {
    if (_108->_1e0_bytes[1] & 8)
        return 1;
    if (!_108->processResourceLoad(false))
        return 0;
    if ((_108->_1e0_bytes[1] & 0x10) || _108->mActorBindings->getNumBindings() == 0)
        return 2;
    _108->EventAddExtraModelRes_stuff(&_2e8);
    return 1;
}

// 0x7100db67c0
bool EventFlowBase::isEventTypeNotMovieWithNoPath() const {
    return int(getType()) != EventFlowType::MovieWithNoPath && mType != EventFlowType::MovieWithNoPath;
}

// 0x7100db6c64
bool EventFlowBase::x_3() const {
    if (_340 & 0x200000000ull)
        return int(getType()) != EventFlowType::MovieWithNoPath;
    return (_340 >> 24) & 1;
}

// 0x7100db8b04
bool EventFlowBase::x_4() const {
    if (mType == EventFlowType::MovieWithNoPath)
        return false;
    if (_340_bytes[0] & 0x60)
        return false;
    if (getSceneStatus() == 4)
        return false;
    return !(_340_bytes[4] & 0x10);
}

// NON_MATCHING: the original addresses the two guard variables as `_MergedGlobals + 0x18 / 0x20` (GlobalMerge of this
// TU's statics: three other guards come first); the code is otherwise the same.
// 0x7100db6900
const char* getCurrentEventForReport() {
    if (sUnk_7102601528) {
        static sead::FixedSafeString<128> sStatus0;
        sStatus0.format("[evt:%s<%s>]", sUnk_7102601528->mEventName.cstr(),
                        sUnk_7102601528->mEntryPointName.cstr());
        return sStatus0.cstr();
    }
    if (sUnk_7102601530) {
        static sead::FixedSafeString<128> sStatus1;
        sStatus1.format("[evt:%s<%s>]", sUnk_7102601530->mEventName.cstr(),
                        sUnk_7102601530->mEntryPointName.cstr());
        return sStatus1.cstr();
    }
    return "[evt ファイル不明]";
}

// 0x7100db8a34
void EventFlowBase::printStatus(sead::BufferedSafeString* out) {
    if (_100->isPlaying())
        out->format("%5.2f", getFrameCount());
    else
        out->format("%s", _100->m7());
}

// 0x7100db67ec
void EventFlowBase::initEventAndReport(bool a1) {
    _340 &= ~0x40000000008ull;
    if (a1)
        _340 |= 0x40000000000ull;
    _108 = new (mHeap, 8) EventResource(mHeap);
    _110 = new (mHeap, 8) EventActorSet(this);
    sUnk_7102601528 = this;
    if (auto* report_mgr = PlayReportMgr::instance())
        report_mgr->reportDebug("Event", getCurrentEventForReport());
    _100->m4();
    sUnk_7102601528 = nullptr;
    if (_340 & 0x400000000000ull)
        act::Awareness::instance()->setEventActive(true);
    _340 |= 0x20000000000ull;
}

// 0x7100db6b1c
void EventFlowBase::acquireEventFlow() {
    EventFlow* slot = Manager::instance()->getEventFlowMgr()->acquireEventFlow(mEventName, mEntryPointName);
    if (slot) {
        delete _108;
        _108 = slot->mResource;
        mSlot = slot;
    } else {
        m15();
    }
    if (x_3()) {
        auto* actor = sead::DynamicCast<act::Actor>(_118->mLink.mLink.getProc(nullptr, nullptr));
        if (actor)
            actor->x_15(this, nullptr);
    }
    _340 |= 2;
}

// 0x7100db8a14
const char* EventFlowBase::sub_7100DB8A14() {
    return _100->m7();
}

// 0x7100db8a24
bool EventFlowBase::isPlaying() {
    return _100->isPlaying();
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
    _108->initTimeline(mEventName);
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

bool EventFlowBase::sub_7100DB8AB4() {
    return _110->sub_7100DA3698();
}

}  // namespace ksys::evt
