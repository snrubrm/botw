#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

#include "Game/AI/aiUnk_NavMeshCallback.h"

// Vtable 0x71023e7178 (GOT 0x2586918, used only by EnemyEscapeMove::sub_710038AB40 which declares it as a local
// object): m0 is 0x7100389680 (964 B, declared only; it appends points to a list), m1 / m2 are the defaults. The
// members are not recovered.
class Unk_71023e7178 : public Unk_NavMeshCallback {
public:
    bool m0(const void* node) override;
};

namespace uking::ai {

class EnemyEscapeMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyEscapeMove, ksys::act::ai::Ai)
public:
    explicit EnemyEscapeMove(const InitArg& arg);
    ~EnemyEscapeMove() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100389d34: picks the escape target behind the actor and starts the escape child
    void sub_7100389D34();
    // 0x710038a5b0: `out` = a point in front of the actor (if the target is in its front cone) that is reachable
    bool sub_710038A5B0(sead::Vector3f* out);
    // 0x710038a78c: starts "直進逃走" towards _48
    void sub_710038A78C();
    // 0x710038a8ec: starts "ジャンプ" towards _d18
    void sub_710038A8EC();
    // 0x710038ab40 (declaration only): collects the candidate points around the actor into _58
    bool sub_710038AB40();

    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const f32* mBehindCheckDist_s{};
    /* 0x48 */ sead::Vector3f _48{0, 0, 0};
    /* 0x58 */ sead::FixedObjList<sead::Vector3f, 100> _58;
    /* 0xd08 */ s32 _d08 = -1;
    /* 0xd0c */ ksys::Timer _d0c{0, 0};
    /* 0xd18 */ sead::Vector3f _d18{0, 0, 0};
    /* 0xd24 */ bool _d24 = false;
    /* 0xd28 */ uking::act::Enemy::Unk_12d0* _d28{};
};
KSYS_CHECK_SIZE_NX150(EnemyEscapeMove, 0xd30);

}  // namespace uking::ai
