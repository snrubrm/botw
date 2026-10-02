#include "Game/AI/AI/aiChemicalEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ChemicalEnemyFindPlayer::ChemicalEnemyFindPlayer(const InitArg& arg)
    : LandHumEnemyFindPlayer(arg) {}

ChemicalEnemyFindPlayer::~ChemicalEnemyFindPlayer() = default;

void ChemicalEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void ChemicalEnemyFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void ChemicalEnemyFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
}

void ChemicalEnemyFindPlayer::m40() {
    if (_1e2) {
        _1e2 = false;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        params.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
        changeChild("ケミカル攻撃", &params);
        return;
    }
    LandHumEnemyFindPlayer::m40();
}

void ChemicalEnemyFindPlayer::m41() {
    if (_1e2) {
        _1e2 = false;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        params.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
        changeChild("ケミカル攻撃", &params);
        return;
    }
    LandHumEnemyFindPlayer::m41();
}

}  // namespace uking::ai
