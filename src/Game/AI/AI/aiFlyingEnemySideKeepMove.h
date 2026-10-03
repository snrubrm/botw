#pragma once

#include <math/seadVector.h>

#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class FlyingEnemySideKeepMove : public FlyingEnemyKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemySideKeepMove, FlyingEnemyKeepMove)
public:
    explicit FlyingEnemySideKeepMove(const InitArg& arg);
    ~FlyingEnemySideKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    void m34(sead::Vector3f* out) override;

    virtual void m37(sead::Vector3f* out);
    virtual void m38(sead::Vector3f* out);

    // 0x71003d342c (declared only, 540 bytes; placeholder name)
    void sub_71003D342C();

protected:
    // static_param at offset 0x80
    const int* mSideDirType_s{};
    sead::Vector3f _88;
    u32 _94;
    ksys::act::Unk_7100d3bc4c _98{nullptr};
};

}  // namespace uking::ai
