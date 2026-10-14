#pragma once

#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_Faucet : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_Faucet, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_Faucet(const InitArg& arg);
    ~DgnObj_DLC_Faucet() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710035ff4c: impulse callback (delegate _60): keeps only the part of the impulse along the actor's up axis;
    // a hit by the player pushes away from the attacker with the impulse's length.
    void sub_710035FF4C(ksys::act::Unk_71006dc134* arg);
    void sub_7100360230();
    void sub_710036052C();

protected:
    sead::Vector3f _38 = sead::Vector3f::zero;
    sead::Vector3f _44 = sead::Vector3f::ey;
    s32 _50 = 0;
    s32 _54 = 0;
    bool _58 = false;
    sead::Delegate1<DgnObj_DLC_Faucet, ksys::act::Unk_71006dc134*> _60{
        this, &DgnObj_DLC_Faucet::sub_710035FF4C};
    f32 _80 = 0;
    bool _84 = false;
};

}  // namespace uking::ai
