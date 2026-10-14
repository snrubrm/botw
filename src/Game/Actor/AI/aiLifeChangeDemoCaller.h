#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::ai {

class LifeChangeDemoCaller : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LifeChangeDemoCaller, ksys::act::ai::Ai)
public:
    explicit LifeChangeDemoCaller(const InitArg& arg);
    ~LifeChangeDemoCaller() override;
    bool isChangeable() const override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLifeRatio_s{};
    // static_param at offset 0x40
    const bool* mOnlyOnce_s{};
    // static_param at offset 0x48
    const bool* mIsIgnorePlayerLand_s{};
    // static_param at offset 0x50
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x60
    sead::SafeString mDemoEntryPoint_s{};
    ksys::evt::ResidentEvent _70;
    s32 _240 = 0;
    bool _244 = false;
};
KSYS_CHECK_SIZE_NX150(LifeChangeDemoCaller, 0x248);

}  // namespace uking::ai
