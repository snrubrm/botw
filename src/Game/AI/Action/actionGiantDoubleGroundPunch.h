#pragma once

#include "Game/AI/Action/actionForkSeqNoWeaponAttack.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantDoubleGroundPunch : public ForkSeqNoWeaponAttack {
    SEAD_RTTI_OVERRIDE(GiantDoubleGroundPunch, ForkSeqNoWeaponAttack)
public:
    explicit GiantDoubleGroundPunch(const InitArg& arg);
    ~GiantDoubleGroundPunch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_710018823C();

    // static_param "RotOffset%d" at offset 0xd0
    const float* mRotOffset_s[3]{};
    // static_param at offset 0xe8
    sead::SafeString mASName_s{};
    // static_param at offset 0xf8
    sead::SafeString mASName2_s{};
    // static_param at offset 0x108
    const float* mRotSpeedMax_s{};
    // static_param "PunchAimPosL%d" / "PunchAimPosR%d" at offsets 0x110 / 0x128
    const sead::Vector3f* mPunchAimPosL_s[3]{};
    const sead::Vector3f* mPunchAimPosR_s[3]{};
    // dynamic2_param at offset 0x140
    sead::Vector3f* mTargetPos_d{};
    // static_param "CoBodyName%d" at offset 0x148 (+ 0x20 each)
    struct CoBody {
        sead::SafeString mName_s;
        bool _10 = false;
        void* _18 = nullptr;
    };
    CoBody mCoBody[4];
    /* 0x1c8 */ s32 _1c8 = 0;
    /* 0x1cc */ bool _1cc = true;
    /* 0x1cd */ bool _1cd = false;
    /* 0x1d0 */ sead::Matrix33f _1d0;
    /* 0x1f4 */ u32 _1f4 = 0;
    // Never accessed by the functions decompiled so far (the factory allocates 0x220 bytes).
    /* 0x1f8 */ u8 _1f8[0x220 - 0x1f8];
};
KSYS_CHECK_SIZE_NX150(GiantDoubleGroundPunch, 0x220);

}  // namespace uking::action
