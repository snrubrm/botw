#pragma once

#include <container/seadSafeArray.h>

#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseSwarmRoam : public CircleMove {
    SEAD_RTTI_OVERRIDE(KeeseSwarmRoam, CircleMove)
public:
    explicit KeeseSwarmRoam(const InitArg& arg);
    ~KeeseSwarmRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m34(sead::Vector3f* out) override;
    void m38(sead::Vector3f* out, f32 angle, f32 radius) override;

protected:
    // Declaration only; the original method name and void return are inferred.
    void sub_7100454C9C(f32 angle);
    // 0x7100455054 (placeholder name): the height offset of the swarm at `angle` (called by m38): periodic linear
    // interpolation of the ten samples of _68 over a full turn.
    f32 sub_7100455054(f32 angle);

    // dynamic_param at offset 0x60
    sead::Vector3f* mCentralPos_d{};
    sead::SafeArray<f32, 10> _68{};
};
KSYS_CHECK_SIZE_NX150(KeeseSwarmRoam, 0x90);

}  // namespace uking::ai
