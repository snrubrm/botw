#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterChaseBulletRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterChaseBulletRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWaterChaseBulletRoot(const InitArg& arg);
    ~RemainsWaterChaseBulletRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void sub_710054AAD8();

protected:
    bool _38 = false;
    bool _39 = false;
    bool _3a = false;
    bool _3b = false;
    bool _3c = false;
    u8 _40[0x10];
    struct Params {
        // static_param at offset 0x50
        const int* mAtkMinDamage_s{};
        // static_param at offset 0x58
        const float* mCheckPower_s{};
        // static_param at offset 0x60
        const float* mHighDamageAddSpd_s{};
        // static_param at offset 0x68
        const float* mLowDamageAddSpd_s{};
        // static_param at offset 0x70
        const float* mShootAddSpd_s{};
        // static_param at offset 0x78
        sead::SafeString mResetASName_s{};
    };
    Params mParams;
};

KSYS_CHECK_SIZE_NX150(RemainsWaterChaseBulletRoot, 0x88);

}  // namespace uking::ai
