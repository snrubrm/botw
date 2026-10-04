#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

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
};

}  // namespace uking::action
