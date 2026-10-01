#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NPCTravelBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCTravelBase, ksys::act::ai::Ai)
public:
    explicit NPCTravelBase(const InitArg& arg);
    ~NPCTravelBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x38: unknown polymorphic object (vtable 0x710240bc58) holding a BaseProcLink at +0x18
    u8 _38[0x30];
    ksys::Timer _68;
};

}  // namespace uking::ai
