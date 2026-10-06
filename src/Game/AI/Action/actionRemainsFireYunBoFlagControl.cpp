#include "Game/AI/Action/actionRemainsFireYunBoFlagControl.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

RemainsFireYunBoFlagControl::RemainsFireYunBoFlagControl(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsFireYunBoFlagControl::~RemainsFireYunBoFlagControl() = default;

bool RemainsFireYunBoFlagControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the copy of the anchor translation loads x/y before z in the original (scheduling).
void RemainsFireYunBoFlagControl::enter_(ksys::act::ai::InlineParamPack* params) {
    using namespace ksys::gdt;
    switch (*mRemainsFireYunBoFlagType_m) {
    case 0:
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Bridge00(true, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon1st(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon2nd(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon3nd(false, false);
        break;
    case 1:
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon1st(true, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Bridge00(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon2nd(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon3nd(false, false);
        break;
    case 2:
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon2nd(true, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Bridge00(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon1st(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon3nd(false, false);
        break;
    case 3:
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon3nd(true, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Bridge00(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon1st(false, false);
        setFlag_Fire_Relic_BattlePlaying_ForceSavePos_YunBo_Cannon2nd(false, false);
        break;
    }
    if (auto* anchor = ksys::act::findLinkReferenceObj(mActor, "ForceSetPosDirAutoSaveAnchor", sead::SafeString::cEmptyString, nullptr)) {
        const sead::Vector3f pos = anchor->getTranslate();
        setFlag_PlayerSavePos(pos, false);
        setFlag_PlayerSavePosAngleYDegree(anchor->getRotate().y * sead::Mathf::rad2deg(1), false);
    }
    mFlags.set(Flag::Changeable);
    setFinished();
}

void RemainsFireYunBoFlagControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireYunBoFlagControl::loadParams_() {
    getMapUnitParam(&mRemainsFireYunBoFlagType_m, "RemainsFireYunBoFlagType");
}

void RemainsFireYunBoFlagControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
