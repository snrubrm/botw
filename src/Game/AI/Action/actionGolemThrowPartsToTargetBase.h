#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace ksys::phys {
class RigidBody;
}

class Unk_71025afb58;
namespace uking::act { class Enemy; }

namespace uking::action {

class GolemThrowPartsToTargetBase : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(GolemThrowPartsToTargetBase, ActionWithAS)
public:
    explicit GolemThrowPartsToTargetBase(const InitArg& arg);
    ~GolemThrowPartsToTargetBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710018d8dc (declared only): out of line in the original.
    void sub_710018D8DC();
    void sub_710018D998();
    void sub_710018DC70(act::Enemy* enemy, const Unk_71005e1be8& part, bool burning, bool ice);
    void calc_() override;
    // The body's transform and its velocities per frame (all four arguments are required).
    virtual void m32(sead::Vector3f* linear_velocity, sead::Vector3f* angular_velocity,
                     sead::Matrix34f* mtx, ksys::phys::RigidBody* body);

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    sead::SafeString mTgtBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mChmObjectName_s{};
    Unk_71005e1be8 _60;
    Unk_71005e1be8 _a0;
    bool _e0;
    bool _e1;
    // aitree_variable at offset 0xe8
    Unk_71025afb58** mGolemChemicalController_a{};
    Unk_7102451ba0 _f0;
};

}  // namespace uking::action
