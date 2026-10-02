#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleEscapeFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleEscapeFromTarget, ksys::act::ai::Ai)
public:
    explicit SimpleEscapeFromTarget(const InitArg& arg);
    ~SimpleEscapeFromTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void sub_710056CF84();

    virtual bool m34();
    virtual void m35(bool finished);
    virtual void m36(sead::Vector3f* dir);

protected:
    // static_param at offset 0x38
    const int* mKeepTime_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const float* mSpaceDist_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    u32 _58 = 0;
    s32 _5c = 0;
    s32 _60 = 0;
};
KSYS_CHECK_SIZE_NX150(SimpleEscapeFromTarget, 0x68);

}  // namespace uking::ai
