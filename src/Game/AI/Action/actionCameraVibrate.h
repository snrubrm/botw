#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraVibrate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraVibrate, ksys::act::ai::Action)
public:
    explicit CameraVibrate(const InitArg& arg);
    ~CameraVibrate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message& message) override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const bool* mIsSound_s{};
    // static_param at offset 0x28
    sead::SafeString mStartSoundName_s{};
    // static_param at offset 0x38
    sead::SafeString mLoopSoundName_s{};
    // map_unit_param at offset 0x48
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x50
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x58
    const float* mCameraRange_m{};
    bool _60 = false;
    int _64 = -1;
    void* _68{};
};

}  // namespace uking::action
