#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeeSwarmNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(BeeSwarmNormal, EnemyNormal)
public:
    explicit BeeSwarmNormal(const InitArg& arg);
    ~BeeSwarmNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // DynamicCast of mActor to an Enemy-derived actor class (RTTI 0x71025b08b8, probably Swarm) that
    // is not declared yet.
    void* _3d0 = nullptr;
    Unk_71024504c8 _3d8;
    sead::Vector3f _450;
    u32 _45c;
};
KSYS_CHECK_SIZE_NX150(BeeSwarmNormal, 0x460);

}  // namespace uking::ai
