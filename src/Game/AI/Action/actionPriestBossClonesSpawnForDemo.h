#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

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
    void calc_() override;
    virtual int m32();

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
    f32 _54 = 0;
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
