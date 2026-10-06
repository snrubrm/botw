#pragma once

#include "Game/AI/Action/actionSimpleLineBeam.h"
#include "Game/AI/aiUnkMessagePayloads.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

// vtable 0x7102392778 (GanonBeastBeamMove::_50..): sends message 0x800005d (a matrix; the payload is
// Unk_7102450a38_Payload, named after its listener). Its D0 / m2 are at 0x710017631c / 0x7100176320.
// Constructed without a transceiver (GanonBeastBeamMove::init_ sets _8).
class Unk_7102392768 : public Unk_7102357d20 {
public:
    Unk_7102392768() : Unk_7102357d20(0x800005d) {}
    void* m2() override { return &_18; }

    Unk_7102450a38_Payload _18;
};

namespace uking::action {

class GanonBeastBeamMove : public SimpleLineBeam {
    SEAD_RTTI_OVERRIDE(GanonBeastBeamMove, SimpleLineBeam)
public:
    explicit GanonBeastBeamMove(const InitArg& arg);
    ~GanonBeastBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    Unk_7102392768 _50[6];
    // static_param at offset 0x230
    const int* mRestDistTime_s{};
    // static_param at offset 0x238
    const int* mRestDistTimeAdd_s{};
    // static_param at offset 0x240
    const int* mRestNumMax_s{};
    // static_param at offset 0x248
    const float* mRestDistLimit_s{};
    // static_param at offset 0x250
    const float* mRestDistMinLimit_s{};
    // static_param at offset 0x258
    const float* mRestDistInterval_s{};
    // static_param at offset 0x260
    sead::SafeString mRestActor_s{};
    sead::Vector3f _270;
    f32 _27c = 0;
    f32 _280 = 0;
    s32 _284 = 0;
    s32 _288 = 0;
    bool _28c = false;
};
KSYS_CHECK_SIZE_NX150(GanonBeastBeamMove, 0x290);

}  // namespace uking::action
