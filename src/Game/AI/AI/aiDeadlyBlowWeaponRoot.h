#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::evt {
class EventFlow;
}

namespace uking::ai {

class DeadlyBlowWeaponRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(DeadlyBlowWeaponRoot, WeaponRootAI)
public:
    explicit DeadlyBlowWeaponRoot(const InitArg& arg);
    ~DeadlyBlowWeaponRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710035C57C();

    void sub_710035CE18();

protected:
    bool _e8 = false;
    s32 _ec = -1;
    s32 _f0 = 0;
    ksys::evt::EventFlow* _f8 = nullptr;
    ksys::evt::EventFlow* _100 = nullptr;
};
KSYS_CHECK_SIZE_NX150(DeadlyBlowWeaponRoot, 0x108);

}  // namespace uking::ai
