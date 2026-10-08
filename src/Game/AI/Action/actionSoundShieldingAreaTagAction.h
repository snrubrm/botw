#pragma once

#include <container/seadBuffer.h>
#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::action {

class SoundShieldingAreaTagAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SoundShieldingAreaTagAction, AreaTagAction)
public:
    explicit SoundShieldingAreaTagAction(const InitArg& arg);
    ~SoundShieldingAreaTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // The original (placeholder) name was m32: this overrides ActorObserver::m15 (primary slot 32, with a
    // this-adjusting thunk in the ActorObserver vtable group that returns the constant true).
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_48; }

    // map_unit_param at offset 0x38
    const float* mMerginDistance_m{};
    // map_unit_param at offset 0x40
    const bool* mIsShieldChemicalWind_m{};
    sead::Buffer<Payload> _48;
    u8 _58[0x40]{};
    f32 _98 = 0.0f;
    u32 _9c = 0;
    ksys::snd::Unk_SoundInstance* _a0 = nullptr;
};

}  // namespace uking::action
