#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class DoorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DoorRoot, ksys::act::ai::Ai)
public:
    explicit DoorRoot(const InitArg& arg);
    ~DoorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    bool sub_7100366D0C();
    void sub_7100366B9C(const ksys::act::BaseProcLink& link, const sead::SafeString& as_name);
    void sub_7100366ED0(const ksys::act::BaseProcLink& link, const sead::SafeString& as_name);

    // static_param at offset 0x38
    const float* mCloseWaitFrame_s{};
    // static_param at offset 0x40
    const bool* mIsCheckBack_s{};
    // static_param at offset 0x48
    sead::SafeString mOpen_L_AS_s{};
    // static_param at offset 0x58
    sead::SafeString mOpen_R_AS_s{};
    // static_param at offset 0x68
    sead::SafeString mClose_L_AS_s{};
    // static_param at offset 0x78
    sead::SafeString mClose_R_AS_s{};
    // map_unit_param at offset 0x88
    sead::SafeString mNpcCanOpenFlag_m{};
    // aitree_variable at offset 0x98
    bool* mIsOpenDoor_a{};
    // aitree_variable at offset 0xa0
    bool* mIsOpenToInside_a{};
    Unk_7102450828 _a8{0x1800005};
    ksys::Timer _e8;
};

}  // namespace uking::ai
