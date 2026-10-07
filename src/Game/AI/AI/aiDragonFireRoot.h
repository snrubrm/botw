#pragma once

#include "Game/AI/AI/aiDragonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonFireRoot : public DragonRoot {
    SEAD_RTTI_OVERRIDE(DragonFireRoot, DragonRoot)
public:
    explicit DragonFireRoot(const InitArg& arg);
    ~DragonFireRoot() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    void m42() override;
    void m44(const sead::Vector3f& pos) override;

    void m45(ksys::act::Actor* actor) override;
    bool m47() override;

    // 0x7100367e70: registers with the DragonChallengeMgr (called from init_).
    void sub_7100367E70();
    void sub_7100367FE4();
    // 0x7100368674: sets / resets the challenge manager's flags 3 and 4 by the distance to the dragon.
    void sub_7100368674();
    // 0x71003687b4: the actor of the linked map object named "DragonFireEffectHolder".
    ksys::act::Actor* sub_71003687B4();
    // 0x710036899c: the demo camera position / view position (points relative to the dragon's "Head" bone).
    void sub_710036899C(sead::Vector3f* pos, sead::Vector3f* view_pos);

protected:
};

}  // namespace uking::ai
