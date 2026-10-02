#pragma once

#include "Game/AI/AI/aiDragonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonIceRoot : public DragonRoot {
    SEAD_RTTI_OVERRIDE(DragonIceRoot, DragonRoot)
public:
    explicit DragonIceRoot(const InitArg& arg);
    ~DragonIceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    void m41() override;
    void m44(const sead::Vector3f& pos) override;
    bool m46() override;

    // 0x10-byte zero-initialised pair (only the constructor touches them). Placeholder.
    struct Unk3 {
        u64 _0 = 0;
        u32 _8 = 0;
    };

protected:
    Unk2 _260;
    // static_param at offset 0x270
    const int* mGrudgeBulletMaxNum_s{};
    // static_param at offset 0x278
    const int* mGrudgeBulletMinInterval_s{};
    // static_param at offset 0x280
    const int* mGrudgeSmokeTime_s{};
    // static_param at offset 0x288
    const float* mGrudgeEventRail_pre1stSpeed_s{};
    // static_param at offset 0x290
    const float* mGrudgeEventRail_1stSpeed_s{};
    // static_param at offset 0x298
    const float* mGrudgeEventRail_pre2ndSpeed_s{};
    // static_param at offset 0x2a0
    const float* mGrudgeEventRail_2ndSpeed_s{};
    // static_param at offset 0x2a8
    const float* mGrudgeEventRail_pre3rdSpeed_s{};
    // static_param at offset 0x2b0
    const float* mGrudgeEventRail_3rdSpeed_s{};
    // static_param at offset 0x2b8
    const float* mGrudgeEventRail_preEndSpeed_s{};
    // static_param at offset 0x2c0
    const float* mGrudgeEventRail_EndSpeed_s{};
    // static_param at offset 0x2c8
    const float* mGrudgeEventRail_ReturnSpeed_s{};
    // static_param at offset 0x2d0
    const float* mGrudgeBulletRate_s{};
    // static_param at offset 0x2d8
    sead::SafeString mGrudgeEventRail_Start_s{};
    // static_param at offset 0x2e8
    sead::SafeString mGrudgeEventRail_pre1st_s{};
    // static_param at offset 0x2f8
    sead::SafeString mGrudgeEventRail_1st_s{};
    // static_param at offset 0x308
    sead::SafeString mGrudgeEventRail_pre2nd_s{};
    // static_param at offset 0x318
    sead::SafeString mGrudgeEventRail_2nd_s{};
    // static_param at offset 0x328
    sead::SafeString mGrudgeEventRail_pre3rd_s{};
    // static_param at offset 0x338
    sead::SafeString mGrudgeEventRail_3rd_s{};
    // static_param at offset 0x348
    sead::SafeString mGrudgeEventRail_preEnd_s{};
    // static_param at offset 0x358
    sead::SafeString mGrudgeEventRail_End_s{};
    // static_param at offset 0x368
    sead::SafeString mGrudgeEventRail_ReturnToSky_s{};
    // static_param at offset 0x378
    sead::SafeString mGrudgeBulletActorName_s{};
    s32 _388 = 6;
    u32 _38c = 0;
    f32 _390 = 0;
    Unk3 _398;
    Unk3 _3a8;
    f32 _3b8 = 0;
    f32 _3bc = 0;
    f32 _3c0 = 0;
    f32 _3c4 = 0;
    f32 _3c8 = -99999.0f;
    void* _3d0 = nullptr;
};
KSYS_CHECK_SIZE_NX150(DragonIceRoot, 0x3d8);

}  // namespace uking::ai
