#include "Game/AI/AI/aiNPCAvoid.h"
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

NPCAvoid::NPCAvoid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAvoid::~NPCAvoid() = default;

void NPCAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAvoid::leave_() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (*mTargetTerrorLevel_s != 5)
            npc->_1048 = 3;
        npc->_fe8 &= ~0x10000000;
    }
    sub_71005D7518(mActor, true);
}

void NPCAvoid::loadParams_() {
    getStaticParam(&mTargetTerrorLevel_s, "TargetTerrorLevel");
    getStaticParam(&mReleaseCrouchTime_s, "ReleaseCrouchTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

bool NPCAvoid::isChangeable() const {
    return isCurrentChild("アラート") || isCurrentChild("脅威解除");
}

}  // namespace uking::ai
