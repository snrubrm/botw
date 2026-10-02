#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class AwarenessInstance;
}

namespace ksys::res {
class GParamListObjectWolfLink;
}

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

// vtable 0x7102432a80 (functions in this TU): accepts message type 0.
class Unk_7102432a80 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType() != 0)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

class WolfLinkNormalRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkNormalRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkNormalRoot(const InitArg& arg);
    ~WolfLinkNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // static_param at offset 0x38
    const float* mShiekSensorLeadDistance_s{};
    // static_param at offset 0x40
    const float* mShiekSensorGoalTolerance_s{};
    // static_param at offset 0x48
    const float* mShiekSensorTargetFowardOffset_s{};
    // static_param at offset 0x50
    const float* mBattleAggressionRange_s{};
    // static_param at offset 0x58
    const float* mHowlAtEnemyRange_s{};
    // static_param at offset 0x60
    const float* mUtilityWantsToHunt_s{};
    // static_param at offset 0x68
    const float* mWarpToPlayerDistance_s{};
    act::WolfLink* _70{};
    const ksys::res::GParamListObjectWolfLink* _78{};
    ksys::act::AwarenessInstance* _80{};
    Unk_7102450648 _88{0x1800025};
    Unk_7102450648 _c8{0x1800024};
    Unk_7102450bb8 _108;
    Unk_7102432a80 _140;
    sead::Vector3f _178 = {0, 0, 0};
    sead::Vector3f _184 = {0, 0, 0};
    sead::Vector3f _190 = {0, 0, 0};
    sead::Vector3f _19c = {0, 0, 0};
    s32 _1a8 = 0;
    s32 _1ac = 4;
    u32 _1b0 = 0;
    u32 _1b4 = 0;
    u16 _1b8 = 0;
    sead::Vector3f _1bc = {0, 0, 0};
    f32 _1c8 = 0;
};
KSYS_CHECK_SIZE_NX150(WolfLinkNormalRoot, 0x1d0);

}  // namespace uking::ai
