#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalPartRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalPartRoot, ksys::act::ai::Ai)
public:
    explicit StalPartRoot(const InitArg& arg);
    ~StalPartRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void sub_71005A8A8C(bool a1);

protected:
    // FIXME: remove this
    u8 pad_0x38[0x50];
    // static_param at offset 0x88
    const float* mInvincibleTime_s{};
};

}  // namespace uking::ai
