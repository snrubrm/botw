#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "Game/AI/aiUnk_71006F3044.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeamosStaticBeam : public StopASPlay {
    SEAD_RTTI_OVERRIDE(BeamosStaticBeam, StopASPlay)
public:
    explicit BeamosStaticBeam(const InitArg& arg);
    ~BeamosStaticBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    virtual void m32(sead::Vector3f* muzzle_offset, sead::Vector3f* beam_direction);

    // static_param at offset 0x48
    const float* mBeamRange_s{};
    // static_param at offset 0x50
    const float* mBeamSpeed_s{};
    // static_param at offset 0x58
    const bool* mUseDynamicCutting_s{};
    // static_param at offset 0x60
    sead::SafeString mBeamBoneName_s{};
    // static_param at offset 0x70
    sead::SafeString mBeamActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mBeamActorKey_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mMuzzleOffset_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mBeamDirection_s{};
    // map_unit_param at offset 0xa0
    const float* mBeamRange_m{};
    /* 0xa8 */ Unk_71006f3044 _a8{mActor};
    bool _168 = false;
};

}  // namespace uking::action
