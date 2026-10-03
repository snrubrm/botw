#pragma once

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class HideHover : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HideHover, ksys::act::ai::Action)
public:
    explicit HideHover(const InitArg& arg);
    ~HideHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTimer_s{};
    // static_param at offset 0x28
    const bool* mIsKeepLifeGage_s{};
    // static_param at offset 0x30
    const bool* mIsChangeable_s{};
    // static_param at offset 0x38
    sead::SafeString mEffectName_s{};
    /* 0x48 */ f32 _48 = 0;  // remaining time
    /* 0x50 */ Unk_71012419b4 _50{};
    /* 0x70 */ TeleportBase::SavedState _70;
    /* 0x7c */ bool _7c = false;
    /* 0x7d */ bool _7d = false;
};
KSYS_CHECK_SIZE_NX150(HideHover, 0x80);

}  // namespace uking::action
