#pragma once

#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildDeviceReflectArrow : public WithoutWeaponArrow {
    SEAD_RTTI_OVERRIDE(ChildDeviceReflectArrow, WithoutWeaponArrow)
public:
    explicit ChildDeviceReflectArrow(const InitArg& arg);
    ~ChildDeviceReflectArrow() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;


    void m35() override;
    f32 m42() override;
    f32 m43() override;
    s32 m47() override;
    bool m48() override;
    virtual bool m49();
    virtual void m50(bool a1);
    virtual s32 m51();
    virtual sead::Vector3f* m52();
    virtual void m53(const sead::Vector3f& a1);

protected:
    // static_param at offset 0x140
    const int* mReflectCountMax_s{};
    // static_param at offset 0x148
    const float* mReflectAimSpeed_s{};
    // static_param at offset 0x150
    const float* mReflectAccel_s{};
    bool _158 = false;
    bool _159 = false;
    bool _15a = false;
    u32 _15c = 0;
    u64 _160 = 0;
    u8 _168[0x174 - 0x168];
    sead::Vector3f _174;
    u64 _180 = 0;
    u32 _188 = 0;
};
KSYS_CHECK_SIZE_NX150(ChildDeviceReflectArrow, 0x190);

}  // namespace uking::ai
