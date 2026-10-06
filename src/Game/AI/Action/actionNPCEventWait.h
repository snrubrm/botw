#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCEventWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCEventWait, ksys::act::ai::Action)
public:
    explicit NPCEventWait(const InitArg& arg);
    ~NPCEventWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    f32 _1c = 0;  // frame counter (float in the original)
    sead::FixedSafeString<32> _20;
};
KSYS_CHECK_SIZE_NX150(NPCEventWait, 0x58);

}  // namespace uking::action
