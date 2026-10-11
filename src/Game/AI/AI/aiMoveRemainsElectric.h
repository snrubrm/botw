#pragma once

#include "Game/AI/AI/aiRailMoveRemains.h"
#include "Game/AI/aiUnk_7100720AB0.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class MoveRemainsElectric : public RailMoveRemains {
    SEAD_RTTI_OVERRIDE(MoveRemainsElectric, RailMoveRemains)
public:
    explicit MoveRemainsElectric(const InitArg& arg);
    ~MoveRemainsElectric() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m40() override;
    bool m39() override;
    f32 m43() override;

protected:
    // Full native helpers create the cannon / weak points, select their AS and update their life.
    void sub_71004B1A00();
    void sub_71004B1C40(sead::Heap* heap);
    void sub_71004B2288();
    void sub_71004B2718();
    // static_param at offset 0x80
    const float* mReactiveRange_s{};
    // static_param at offset 0x88
    const float* mDemoCallWaitTime_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mCannonOffset_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mWeakPointOffset_s{};
    // map_unit_param at offset 0xa0
    const bool* mIsJoinRemainsBattle_m{};

    // Four 0x98-byte records constructed by 4B14A0; 4B1C40 and 4B2718 write their life values.
    struct Part {
        s32 mLife = 0;
        sead::FixedSafeString<32> mBoneName;
        sead::FixedSafeString<32> mActorName;
        Unk_71012419b4 mHandle;
    };
    KSYS_CHECK_SIZE_NX150(Part, 0x98);
    sead::SafeArray<Part, 4> _a8;
    ksys::act::BaseProcLink _308;
    bool _318 = false;
    f32 _31c = 0.0f;
    Unk_7100720ab0 _320{mActor};
    ksys::evt::ResidentEvent _370;
};
KSYS_CHECK_SIZE_NX150(MoveRemainsElectric, 0x540);

}  // namespace uking::ai
