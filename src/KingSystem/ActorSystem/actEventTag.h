#pragma once

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Names from the CSV (EventTag::construct 0x7100d2cb94: new(0x8e8); sead::Delegate<ksys::act::EventTag> rows).
// Profile actor for the "EventTag" and "SignalFlowchart" actors (vtable 0x71024d9160). Its root AI runs in a job
// of its own (calcAi).
class EventTag : public Actor {
    SEAD_RTTI_OVERRIDE(EventTag, Actor)
public:
    explicit EventTag(const CreateArg& arg);
    ~EventTag() override;
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    bool shouldSkipJobPush_(JobType type) override;
    void onJobPush2_(JobType type) override;
    void initMaybe() override;
    void m107() override;

    // 0x7100d2cd94: the job function of both job handlers: runs the root AI unless the actor is deleted.
    void calcAi();

private:
    /* 0x840 */ BaseProcJobHandlerT<EventTag> mJob0{this, &EventTag::calcAi};
    /* 0x890 */ BaseProcJobHandlerT<EventTag> mJob1{this, &EventTag::calcAi};
    /* 0x8e0 */ bool _8e0 = false;
    /* 0x8e1 */ bool mIsSignalFlowchart = false;
    /* 0x8e2 */ s8 _8e2 = -1;
};
KSYS_CHECK_SIZE_NX150(EventTag, 0x8e8);

}  // namespace ksys::act
