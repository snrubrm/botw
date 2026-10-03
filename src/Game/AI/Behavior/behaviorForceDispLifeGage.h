#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceDispLifeGage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceDispLifeGage, ksys::act::ai::Behavior)
public:
    explicit ForceDispLifeGage(const InitArg& arg);
    ~ForceDispLifeGage() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    // 0x71006232ec: whether the life gauge is forced for the actor (the player's target, or the damage
    // manager's flags2 high half is 1).
    bool sub_71006232EC();

    /* 0x28 */ const bool* mIsOnlyPlayer_s{};
};
KSYS_CHECK_SIZE_NX150(ForceDispLifeGage, 0x30);

}  // namespace uking::behavior
