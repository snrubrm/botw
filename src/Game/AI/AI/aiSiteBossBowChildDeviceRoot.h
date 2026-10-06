#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossBowChildDeviceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossBowChildDeviceRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossBowChildDeviceRoot(const InitArg& arg);
    ~SiteBossBowChildDeviceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;

protected:
    // 0x7100574840: whether the hit counts: (damage or a valid field 0x54) and no attacker, the player, field 0x50 == 4, the "PlayerBeam" actor or an actor with the tag 0x19f6c13a
    bool sub_7100574840();
    // 0x7100574a74: "通常待機" with the target position (linked actor or own), id, parent actor and X rotation
    void sub_7100574A74();
    // 0x7100574c2c: tells the linked actor (message 0x8000057, payload _50), clears the main body flag 0x1000000 and changes to the "自然消滅" child
    void sub_7100574C2C();
    // 0x71005749a4: tells the linked actor (message 0x8000057, payload _50), clears the main body flag 0x1000000 and changes to the "破壊" child
    void sub_71005749A4();
    // static_param at offset 0x38
    const float* mXRotateSpeed_s{};
    // static_param at offset 0x40
    const float* mSlowRate_s{};
    // map_unit_param at offset 0x48
    const int* mCount_m{};
    s32 _50 = -1;
    bool _54 = false;
    bool _55 = false;
    bool _56 = false;
    sead::Vector3f _58;
    s32 _64 = 7;
    s32 _68 = 7;
    ksys::act::BaseProcLink _70;
    ksys::act::BaseProcLink _80;
    ksys::Timer _90{0, 0, 0};
    f32 _9c = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossBowChildDeviceRoot, 0xa0);

}  // namespace uking::ai
