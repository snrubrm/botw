#pragma once

#include "Game/AI/aiUnkMessagePayloads.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

// vtable 0x7102363858 (AlarmLynelTag::_28): sends message 0x80000ac (payload = Unk_71024056a8_Payload, the alarm
// point). Its functions are in the AlarmLynelTag TU (0x710008b844 D0, 0x710008b848 m2).
class Unk_7102363858 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(const int* value) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_18.mLock);
        _18._0 = *value;
    }

    Unk_71024056a8_Payload _18;
};

namespace uking::action {

class AlarmLynelTag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AlarmLynelTag, ksys::act::ai::Action)
public:
    explicit AlarmLynelTag(const InitArg& arg);
    ~AlarmLynelTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710008b5a4 (declared only): JobQueueLock-guarded sender payload fill, then sends to the linked actors.
    void sub_710008B5A4();

    // map_unit_param at offset 0x20
    const int* mAlarmPoint_m{};
    Unk_7102363858 _28{mActor, 0x80000ac};
};
KSYS_CHECK_SIZE_NX150(AlarmLynelTag, 0x48);

}  // namespace uking::action
