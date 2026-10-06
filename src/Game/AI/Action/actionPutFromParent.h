#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class PutFromParent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PutFromParent, ksys::act::ai::Action)
public:
    explicit PutFromParent(const InitArg& arg);
    ~PutFromParent() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71002255f4 (placeholder name): ray cast against the ground, objects and characters.
    bool sub_71002255F4(sead::Vector3f start, sead::Vector3f end, sead::Vector3f* hit_pos);

    // static_param at offset 0x20
    const int* mTimer_s{};
    // static_param at offset 0x28
    sead::SafeString mHoldOffXLinkKey_s{};
    ksys::act::ModelBindInfo _38;
    void* _d8 = nullptr;
    f32 _e0 = 0.0f;
    bool _e4 = false;
    bool _e5 = false;
    bool _e6 = false;
    f32 _e8 = -1.0f;
    f32 _ec = 0.0f;
    f32 _f0 = 0.0f;
    f32 _f4 = 0.0f;
    bool _f8 = false;
};

}  // namespace uking::action
