#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWindBatteryRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWindBatteryRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWindBatteryRoot(const InitArg& arg);
    ~RemainsWindBatteryRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710054ea4c: with `damage_state` > 0 starts the "MaterialDamage" animation, otherwise calls sub_710054EB78 once the
    // animation has finished (or is not playing)
    void sub_710054EA4C(s32 damage_state);
    // 0x710054eb78 (declaration only, 308 bytes)
    void sub_710054EB78();
    u32 _38 = 3;
    u32 _3c = 0;
    bool _40 = true;
    bool _41 = false;
    gsys::BoneAccessKeyEx _48;  // Head
    gsys::BoneAccessKeyEx _80;  // Neck
    u64 _b8 = 0;
    sead::Vector3f _c0 = sead::Vector3f::zero;
    u32 _cc = 0;
};
KSYS_CHECK_SIZE_NX150(RemainsWindBatteryRoot, 0xd0);

}  // namespace uking::ai
