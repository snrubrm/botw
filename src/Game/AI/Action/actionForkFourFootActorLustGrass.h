#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "Game/AI/aiUnk_71007444AC.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFourFootActorLustGrass : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFourFootActorLustGrass, ksys::act::ai::Action)
public:
    explicit ForkFourFootActorLustGrass(const InitArg& arg);
    ~ForkFourFootActorLustGrass() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;
    bool updateForPreDelete() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mGanonBeastGrudgeMarkMgr_a{};
    // static_param at offset 0x28
    const float* mMaxRadius_s{};
    // static_param at offset 0x30
    const float* mMinRadius_s{};
    // static_param at offset 0x38
    const float* mRadSpd_s{};
    // static_param at offset 0x40
    sead::SafeString mNode1Name_s{};
    // static_param at offset 0x50
    sead::SafeString mNode2Name_s{};
    // static_param at offset 0x60
    sead::SafeString mNode3Name_s{};
    // static_param at offset 0x70
    sead::SafeString mNode4Name_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mWorldOffset_s{};

    // Local class of the object the "GanonBeastGrudgeMarkMgr" AI tree variable points to (embedded in
    // the action; its vtable is only referenced by this action's constructor).
    class Unit : public Unk_71025afb58 {
        SEAD_RTTI_OVERRIDE(Unit, Unk_71025afb58)
    public:
        ~Unit() override = default;

        struct Data {
            Unk_71007444ac _0;
            f32 _10;
            f32 _14;
            f32 _18;
            f32 _1c;
        };
        KSYS_CHECK_SIZE_NX150(Data, 0x20);

        Data _8;
    };

    Unit _88;
    gsys::BoneAccessKeyEx _b0[4];
    s64 _190;
    s64 _198;
    u8 _1a0 = 0;
};
KSYS_CHECK_SIZE_NX150(ForkFourFootActorLustGrass, 0x1a8);

}  // namespace uking::action
