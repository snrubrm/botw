#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

class Unk_7102450fa8;

namespace uking::action {

class PriestBossClonesSpawnForDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossClonesSpawnForDemo, ksys::act::ai::Action)
public:
    explicit PriestBossClonesSpawnForDemo(const InitArg& arg);
    ~PriestBossClonesSpawnForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100066884 (declared only): out of line in the original.
    bool sub_7100066884();
    // 0x7100066ce4: stores the delay in _54; for a positive delay runs sub_71000668A0(0) and sets Actor flag2 _20.
    void sub_7100066CE4(int delay);
    // 0x71000668a0 (declared only; 724 B)
    void sub_71000668A0(f32 t);
    void calc_() override;

    // 0x71000664e4 (placeholder name): the meta AI unit (null if it is not a Unk_7102450fa8).
    Unk_7102450fa8* sub_71000664E4();
    virtual int m32();
    virtual f32 m33(f32 t);

    // dynamic_param at offset 0x20
    int* mDurationFrame_d{};
    // dynamic_param at offset 0x28
    int* mDecelerationFrame_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mASName_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mOffset_d{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
    int _50 = -1;
    int _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    sead::Vector3f _60 = sead::Vector3f::zero;
    f32 _6c = 0;
    f32 _70 = 0;
    f32 _74 = 0;
    int _78 = 1;
    int _7c = 0;
    u16 _80 = 0x100;
    u8 _82 = 1;
    u8 _83;
    bool _84 = false;
};

}  // namespace uking::action
