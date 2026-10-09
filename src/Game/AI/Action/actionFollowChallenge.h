#pragma once

#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class FollowChallenge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FollowChallenge, ksys::act::ai::Action)
public:
    explicit FollowChallenge(const InitArg& arg);
    ~FollowChallenge() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Native table 235BD60 ends with this bool slot; DragonFollow calls it virtually.
    virtual bool m32();
    void sub_710004D9A4();
    void sub_710004DFF4();
    void sub_710004E754();
    bool sub_710004F8A4();
    void sub_710004E108();
    // Full 4E2B4 tests the bool argument and adds/removes the challenge body and effects.
    void sub_710004E2B4(bool enable);
    bool sub_710004FA3C();

    // map_unit_param at offset 0x20
    const float* mGimmickTimeLimit_m{};
    // map_unit_param at offset 0x28
    const bool* mIsBillboard_m{};
    ksys::act::ActorConstDataAccess _30;
    // Native constructor and effect updates use 19 records at 48, stride 30.
    struct EffectEntry {
        f32 scale;
        u8 _4[0xc];
        Unk_71012419b4 handle;
    };
    static_assert(sizeof(EffectEntry) == 0x30);
    EffectEntry mEffects[19];
    u8 _3d8[0x4b8 - 0x3d8];
    bool _4b8 = false;
    bool _4b9 = false;
    bool _4ba;
    u8 _4bb;
    f32 _4bc;
    u8 _4c0[0x4c8 - 0x4c0];
    f32 _4c8;
    u8 _4cc[0xab0 - 0x4cc];
};

}  // namespace uking::action
