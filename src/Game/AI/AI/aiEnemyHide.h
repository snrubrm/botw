#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyHide : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyHide, ksys::act::ai::Ai)
public:
    explicit EnemyHide(const InitArg& arg);
    ~EnemyHide() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100393ec4: requests a path (the points of the path are collected in `_38`); returns the request state.
    s32 sub_7100393EC4();
    // 0x710039439c
    void sub_710039439C();
    // 0x7100394648
    void sub_7100394648();

    /* 0x038 */ sead::FixedObjList<sead::Vector3f, 15> _38;
    /* 0x248 */ sead::Vector3f _248{0, 0, 0};
    /* 0x254 */ ksys::Timer _254{0, 0};
    struct Params {
        // dynamic_param at offset 0x260
        sead::Vector3f* mTargetPos_d{};
        // static_param at offset 0x268
        const float* mTurnStartAng_s{};
        // static_param at offset 0x270
        const int* mRepathTime_s{};
    };
    Params mParams;
    /* 0x278 */ uking::act::Enemy::Unk_12d0* _278{};
};
KSYS_CHECK_SIZE_NX150(EnemyHide, 0x280);

}  // namespace uking::ai
