#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchRightAndWrong : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchRightAndWrong, SwitchAI)
public:
    explicit SwitchRightAndWrong(const InitArg& arg);
    ~SwitchRightAndWrong() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m34() override;
    bool m35() override;
    bool m36() override;
    bool m37() override;
    bool m38() override;
    void m39() override;
    void m40() override;
    void m41() override;
    void m42() override;
    void m43() override;
    virtual bool m44();
    virtual void m45();

protected:
    // static_param at offset 0x38
    const float* mWaitTime_s{};
    f32 _40{};
    bool _44{};
    bool _45{};
    bool _46{};
    bool _47 = true;
};

}  // namespace uking::ai
