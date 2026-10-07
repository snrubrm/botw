#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtEventFlowBinder.h"
#include "KingSystem/Event/evtResourceFlowchart.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/System/VFR.h"

namespace ksys::evt {

EventFlowFlowchart::~EventFlowFlowchart() = default;

void EventFlowFlowchart::m11() {
    _108->mFlowchart->buildFlowchart(&mContext, mHeap);
    auto* actors = _110;
    EventActorBinder actor_binder(actors);
    bindActors(mContext, actor_binder);
    EventActionBinder action_binder(actors);
    bindActorActions(mContext, action_binder);
    EventQueryBinder query_binder(actors);
    bindActorQueries(mContext, query_binder);
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
    _108->initFlowchart(mEventName, mEntryPointName);
}

// 0x7100dbb258 (CSV evt::EventFlowFlowchart::calc)
void EventFlowFlowchart::m12() {
    ++_6b0;
    _6b4 += _20c * VFR::instance()->getDeltaFrame();
}

// 0x7100dbb208
void EventFlowFlowchart::m13() {
    mContext.Start(&mMetaData);
    _6b0 = 0;
    _6b4 = 0.0f;
}

// 0x7100dbb234 (CSV evt::EventFlowFlowchart::isFinished; vtable slot 14)
bool EventFlowFlowchart::m14() {
    const s32 state = mContext.GetNumAllocatedNodes();
    if (state == 0)
        _340 &= ~0x2400ull;
    return state == 0;
}

}  // namespace ksys::evt
