#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace ksys::phys {
class Constraint;
}

// Contact callback installed on the block's rigid body (vtable 0x7102406e88; placeholder name).
// Requests that a contact with EntityGround be disabled unless its normal is close to _8.
class Unk_7102406e88 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;

    sead::Vector3f _8 = sead::Vector3f::ex;
};

namespace uking::ai {

class MagneSliderBlockRootThunder : public MagneShaftRootBase {
    SEAD_RTTI_OVERRIDE(MagneSliderBlockRootThunder, MagneShaftRootBase)
public:
    explicit MagneSliderBlockRootThunder(const InitArg& arg);
    ~MagneSliderBlockRootThunder() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    ksys::phys::RigidBody* m52() override;

protected:
    ksys::phys::Constraint* _a0{};
    Unk_7102406e88 _a8;
};
KSYS_CHECK_SIZE_NX150(MagneSliderBlockRootThunder, 0xc0);

}  // namespace uking::ai
