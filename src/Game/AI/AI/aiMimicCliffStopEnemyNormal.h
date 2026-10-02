#pragma once

#include "Game/AI/AI/aiMimicCliffStopEnemyNormalBase.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicCliffStopEnemyNormal : public MimicCliffStopEnemyNormalBase {
    SEAD_RTTI_OVERRIDE(MimicCliffStopEnemyNormal, MimicCliffStopEnemyNormalBase)
public:
    explicit MimicCliffStopEnemyNormal(const InitArg& arg);
    ~MimicCliffStopEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x71004a6730: switches to 擬態解除 (jumping off when `a1` is false).
    void sub_71004A6730(bool a1);
    // 0x71004a69a4: whether a contact of the actor passes ActorConstDataAccess::sub_7100D13BB8.
    bool sub_71004A69A4();

protected:
    // static_param at offset 0x1e0
    const float* mJumpDistXZ_s{};
    Unk_7102451970 _1e8;
};
KSYS_CHECK_SIZE_NX150(MimicCliffStopEnemyNormal, 0x210);

}  // namespace uking::ai
