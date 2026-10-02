#pragma once

#include "Game/AI/AI/aiMagneStickRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class MagneShaftRootBase : public MagneStickRoot {
    SEAD_RTTI_OVERRIDE(MagneShaftRootBase, MagneStickRoot)
public:
    explicit MagneShaftRootBase(const InitArg& arg);
    ~MagneShaftRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m41(const sead::Matrix34f* mtx, const sead::Vector3f* a, const sead::Vector3f* b) override;
    f32 m42() override { return *mCollideRadius_m; }
    void m48(f32 radius, const sead::Matrix34f* mtx, const sead::Vector3f* a,
             const sead::Vector3f* b) override;
    void m50() override;
    void m51() override;
    virtual ksys::phys::RigidBody* m52() { return nullptr; }

protected:
};

}  // namespace uking::ai
