#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeeSwarmNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(BeeSwarmNormal, EnemyNormal)
public:
    explicit BeeSwarmNormal(const InitArg& arg);
    ~BeeSwarmNormal() override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m49(Unk1* out, s32 idx) override;
    void m50(Unk1* out, s32 idx) override;
    bool handleMessage_(const ksys::Message& message) override;

    void m37() override;
    void m38() override;
    ksys::act::Unk_71024dc858* m47(ksys::act::AwarenessInstance* awareness,
                                   ksys::act::Unk_71024dccf8* filter, s32 a3) override;
    void m48(sead::Vector3f* pos) override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 9; }
    bool m73() override { return true; }

protected:
    act::Swarm* _3d0 = nullptr;  // DynamicCast of mActor (init_)
    Unk_71024504c8 _3d8;
    sead::Vector3f _450;
    u32 _45c;
};
KSYS_CHECK_SIZE_NX150(BeeSwarmNormal, 0x460);

}  // namespace uking::ai
