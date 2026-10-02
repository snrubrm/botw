#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class TargetCircle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TargetCircle, ksys::act::ai::Action)
public:
    explicit TargetCircle(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~TargetCircle() override { ; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual void m33(ksys::phys::CharacterController* controller, f32 speed,
                     const sead::Vector3f& dir);

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mRotDist_s{};
    // dynamic_param at offset 0x38
    int* mRotDir_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRValue _48;
    sead::Matrix33f _54;
    f32 _78 = 0;
    s8 _7c = 0;
};

KSYS_CHECK_SIZE_NX150(TargetCircle, 0x80);

}  // namespace uking::action
