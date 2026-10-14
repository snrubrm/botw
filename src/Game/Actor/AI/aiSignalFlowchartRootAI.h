#pragma once

#include <container/seadSafeArray.h>
#include <evfl/Action.h>
#include <evfl/Flowchart.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SignalFlowchartRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SignalFlowchartRootAI, ksys::act::ai::Ai)
public:
    explicit SignalFlowchartRootAI(const InitArg& arg);
    ~SignalFlowchartRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // An entry of the action / query tables: the AI and the resource's `res` pointer (action: 0x10 of the
    // flowchart's action binding).
    struct BoundEntry {
        SignalFlowchartRootAI* owner;
        void* res;
    };

    // map_unit_param at offset 0x38
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mEventFlowEntryName_m{};
    /* 0x58 */ void* _58;
    /* 0x60 */ void* _60;
    /* 0x68 */ evfl::FlowchartContext mContext;
    /* 0xf8 */ sead::SafeArray<BoundEntry, 8> _f8;
    /* 0x178 */ s32 _178;
    /* 0x180 */ sead::SafeArray<BoundEntry, 32> _180;
    /* 0x380 */ s32 _380;
    /* 0x388 */ evfl::ActionDoneHandler mActionDoneHandler;
    /* 0x3b8 */ bool _3b8;
    /* 0x3b9 */ bool _3b9;
    /* 0x3ba */ bool _3ba;
    /* 0x3bc */ u32 _3bc;
};
KSYS_CHECK_SIZE_NX150(SignalFlowchartRootAI, 0x3c0);

}  // namespace uking::ai
