#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCAttack, ksys::act::ai::Ai)
public:
    explicit NPCAttack(const InitArg& arg);
    ~NPCAttack() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004c064c: NPC flag 0x1000, ASList::x_6(9, 0, 0), then the "接近" child
    void sub_71004C064C();
    // static_param at offset 0x38
    const int* mActionBaseTime_s{};
    // static_param at offset 0x40
    const int* mActionTimePlay_s{};
    // static_param at offset 0x48
    const int* mActionRate_s{};
    // static_param at offset 0x50
    const int* mAttackRate_s{};
    // static_param at offset 0x58
    const int* mAttackModeTime_s{};
    // static_param at offset 0x60
    const int* mGuardModeTime_s{};
    // static_param at offset 0x68
    const int* mEnemyChanceTime_s{};
    // dynamic_param at offset 0x70
    float* mTerrorLevel_d{};
    // dynamic_param at offset 0x78
    bool* mIsBattleStart_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mEnemyLink_d{};
    bool _90 = true;
    bool _91 = false;
    bool _92 = false;
    u32 _94 = 0;
    act::NPC* _98 = nullptr;
    ksys::Timer _a0{};
    ksys::Timer _ac{};
    ksys::Timer _b8{};
};
KSYS_CHECK_SIZE_NX150(NPCAttack, 0xc8);

}  // namespace uking::ai
