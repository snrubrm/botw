#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/Sound/sndReverbMgr.h"
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundReverbAreaTagAction : public AreaTagAction, public ksys::snd::Unk_7101059828 {
    SEAD_RTTI_OVERRIDE(SoundReverbAreaTagAction, AreaTagAction)
public:
    explicit SoundReverbAreaTagAction(const InitArg& arg);
    ~SoundReverbAreaTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void draw(sead::PrimitiveDrawer* drawer, bool a, bool b) override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_a0; }

    // map_unit_param at offset 0x70
    const float* mReverbSendAdd_m{};
    // map_unit_param at offset 0x78
    const float* mReverbTimeAdd_m{};
    // map_unit_param at offset 0x80
    const float* mEarlyReflectionFeedbackAdd_m{};
    // map_unit_param at offset 0x88
    const float* mRoomHfAdd_m{};
    // map_unit_param at offset 0x90
    const float* mReverbAdd_m{};
    // map_unit_param at offset 0x98
    const float* mMerginDistance_m{};

    sead::Buffer<Payload> _a0;
    // Whole ff2a50 indexes the 32 area contact-distance values here.
    sead::SafeArray<f32, 32> _b0;
    bool _130 = false;
    // Whole ff28f0 copies the six map parameters here, consumed by ff2a50.
    f32 _134 = 0.0f;
    f32 _138 = 0.0f;
    f32 _13c = 0.0f;
    f32 _140 = 0.0f;
    f32 _144 = 0.0f;
    f32 _148 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(SoundReverbAreaTagAction, 0x150);

}  // namespace uking::action
