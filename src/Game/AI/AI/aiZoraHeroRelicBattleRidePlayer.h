#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class ZoraHeroRelicBattleRidePlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleRidePlayer, ksys::act::ai::Ai)
public:
    explicit ZoraHeroRelicBattleRidePlayer(const InitArg& arg);
    ~ZoraHeroRelicBattleRidePlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_71006138CC();
    void sub_7100614194(const ksys::act::BaseProcLink& link);

protected:
    // 0x710061430c: true if nothing blocks the ray from the actor to `target` (ground / object layers)
    bool sub_710061430C(const sead::Vector3f& target);
    // 0x7100613ff0: unless the relic chance time flag is set: mode 1 of the message unit; then the "周回" child
    void sub_7100613FF0();
    // aitree_variable at offset 0x38
    void* mZoraHeroShowMsgUnit_a{};
    ksys::act::BaseProcLink _40;
    ksys::act::BaseProcLink _50;
    ksys::act::BaseProcLink _60;
    Unk_7102450558 _70;
    bool _c0 = false;
};
KSYS_CHECK_SIZE_NX150(ZoraHeroRelicBattleRidePlayer, 0xc8);

}  // namespace uking::ai
