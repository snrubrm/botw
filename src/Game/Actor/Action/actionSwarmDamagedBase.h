#pragma once

#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

class SwarmDamagedBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwarmDamagedBase, ksys::act::ai::Action)
public:
    explicit SwarmDamagedBase(const InitArg& arg);
    ~SwarmDamagedBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100284798 (declared only): calls the Swarm helpers 0x7100729d5c(*_48 (f32), swarm, null, null, null, false) and
    // 0x710072a108(swarm, Vector3f::ey).
    virtual void m32(act::Swarm* swarm);
    // 0x7100284a40 (CSV swarmStuff, declared only): puts `unit` into a free slot of _78 (creating a dead-actor
    // proc with AI tree params CreateDeadConditionType / DropTable "Swarm") or finishes it at once.
    void swarmStuff(act::Swarm::Unit* unit, s32 deadConditionType);
    // 0x7100284d00 (placeholder name): whether one of the tracked entries has this pointer.
    bool sub_7100284D00(void* ptr) const;

    // static_param at offset 0x20
    const int* mIgnoreHitGroundTime_s{};
    // static_param at offset 0x28
    const int* mTime_s{};
    // static_param at offset 0x30
    const float* mRiseSpeedMin_s{};
    // static_param at offset 0x38
    const float* mSubAccRateMin_s{};
    // static_param at offset 0x40
    const float* mSubAccRateMax_s{};
    // static_param at offset 0x48
    const float* mSpeed_s{};
    // static_param at offset 0x50
    const bool* mIsCreateDeadActor_s{};
    // map_unit_param at offset 0x58
    const int* mSubUnitNum_m{};
    // map_unit_param at offset 0x60
    const int* mPatternID_m{};
    sead::Vector3f _68{0, 0, 0};

    struct Entry {
        ksys::act::BaseProcHandle mHandle;
        void* mPtr{};
        s32 mIdx = -1;
    };
    Entry _78[10];
};
KSYS_CHECK_SIZE_NX150(SwarmDamagedBase, 0x1b8);

}  // namespace uking::action
