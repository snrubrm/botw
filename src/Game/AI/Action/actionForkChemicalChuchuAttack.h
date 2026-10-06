#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::phys {
class SphereRigidBody;
}

namespace uking::action {

class ForkChemicalChuchuAttack : public ForkNoWeaponAttackAllTime {
    SEAD_RTTI_OVERRIDE(ForkChemicalChuchuAttack, ForkNoWeaponAttackAllTime)
public:
    explicit ForkChemicalChuchuAttack(const InitArg& arg);
    ~ForkChemicalChuchuAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710014a0d0: starts the "ChemicalAttack" effect and sound at the land attack radius.
    void sub_710014A0D0();

    // static_param at offset 0xc0
    const int* mLandAtkTime_s{};
    // static_param at offset 0xc8
    const float* mLandAtkRadius_s{};
    ksys::phys::SphereRigidBody* _d0{};
    f32 _d8 = 0.0f;
    f32 _dc = 1.0f;
    int _e0 = 0;
    // The "ChemicalAttack" effect and sound handles.
    Unk_71012419b4 _e8;
};
KSYS_CHECK_SIZE_NX150(ForkChemicalChuchuAttack, 0x108);

}  // namespace uking::action
