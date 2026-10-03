#include "Game/AI/AI/aiNPCTerrorAI.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NPCTerrorAI::NPCTerrorAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTerrorAI::~NPCTerrorAI() = default;

void NPCTerrorAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 level = s32(*mTerrorLevel_d);

    bool is_sitting = true;
    if (sead::SafeString(mActor->getASList()->sub_710115ECF4(59, 1)) != "SitOnObject") {
        mActor->getASList()->goLimpFromHeadShotMaybe(59, "", 0);
        is_sitting = false;
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(*mIsReturnFromDemo_d, "IsReturnFromDemo", -1);
    pack.addBool(*mIsTimeOver_d, "IsTimeOver", -1);
    pack.addInt(level, "TerrorLevel", -1);
    pack.addBool(*mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon", -1);
    pack.addBool(is_sitting, "IsSitting", -1);
    pack.addVec3(*mTargetVel_d, "TargetVel", -1);
    pack.addActor(*mTerrorEmitter_d, "TerrorEmitter", -1);
    pack.addInt(*mTerrorLayer_d, "TerrorLayer", -1);

    _8c = level;
    switch (level) {
    case 1:
        changeChild("身構える", &pack);
        break;
    case 2:
        changeChild("驚く", &pack);
        break;
    case 3:
        changeChild("敵遭遇", &pack);
        break;
    case 4:
        changeChild("逃走", &pack);
        break;
    case 5:
        changeChild("全力逃走", &pack);
        break;
    default:
        changeChild("身構える", &pack);
        setFailed();
        break;
    }
}

void NPCTerrorAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCTerrorAI::loadParams_() {
    getStaticParam(&mTerrorEndTime_s, "TerrorEndTime");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

bool NPCTerrorAI::isChangeable() const {
    return (isCurrentChild("逃走") || isCurrentChild("全力逃走")) &&
           getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
