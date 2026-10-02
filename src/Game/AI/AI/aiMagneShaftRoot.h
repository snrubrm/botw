#pragma once

#include "Game/AI/AI/aiMagneShaftRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class Constraint;
}

namespace uking::ai {

class MagneShaftRoot : public MagneShaftRootBase {
    SEAD_RTTI_OVERRIDE(MagneShaftRoot, MagneShaftRootBase)
public:
    explicit MagneShaftRoot(const InitArg& arg);
    ~MagneShaftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m50() override;
    ksys::phys::RigidBody* m52() override;

protected:
    ksys::phys::Constraint* _a0{};
};

}  // namespace uking::ai
