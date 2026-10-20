#pragma once

#include "Game/Actor/Horse/Action/actionHorseSwim.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace ksys::phys {
class Unk_7102372790;
}

namespace uking::action {

// Placeholder name: the face query HorseSwimAction::calc_ allocates (0x58 bytes). m0 keeps a face whose
// area and normal clear the two thresholds and whose material the horse can stand on.
class HorseSwimFaceQuery : public ksys::phys::NavMeshFaceQuery {
    SEAD_RTTI_OVERRIDE(HorseSwimFaceQuery, ksys::phys::NavMeshFaceQuery)
public:
    bool m0(const ksys::phys::Unk_7100f7e9f0& face) override;
    void* m1() override { return nullptr; }

    /* 0x34 */ f32 _34 = 0;
    /* 0x38 */ f32 _38 = 0;
    /* 0x40 */ ksys::phys::Unk_7100f7e9f0 _40;
};
KSYS_CHECK_SIZE_NX150(HorseSwimFaceQuery, 0x58);

class HorseSwimAction : public HorseSwim {
    SEAD_RTTI_OVERRIDE(HorseSwimAction, HorseSwim)
public:
    explicit HorseSwimAction(const InitArg& arg);
    ~HorseSwimAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLandSearchRadius_s{};
    // static_param at offset 0x28
    const float* mLandSearchNormalCos_s{};
    // static_param at offset 0x30
    const float* mLandSearchMinArea_s{};
    // static_param at offset 0x38
    const float* mLandSearchIntervalFrames_s{};
    // static_param at offset 0x40
    const float* mResolvePenetrationRadiusScale_s{};
    // static_param at offset 0x48
    const float* mResolvePenetrationSearchRadius_s{};
    int _50 = 0;
    ksys::phys::Unk_7102372790* _58{};
    bool _60 = false;
};

}  // namespace uking::action
