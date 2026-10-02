#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeepBackSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeepBackSelect, ksys::act::ai::Ai)
public:
    explicit KeepBackSelect(const InitArg& arg);
    ~KeepBackSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mKeepTime_s{};
    // static_param at offset 0x40
    const int* mBaseAxis_s{};
    // static_param at offset 0x48
    const float* mBackAngle_s{};
    // static_param at offset 0x50
    const bool* mXZOnly_s{};
    // static_param at offset 0x58
    sead::SafeString mNodeName_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mLocalOffset_s{};
    gsys::BoneAccessKeyEx _70;
    f32 _a8{};
    s32 _ac{};
    s32 _b0{};
};

}  // namespace uking::ai
