#include "Game/AI/AI/aiCastleLynelBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CastleLynelBattle::CastleLynelBattle(const InitArg& arg) : LynelBattle(arg) {}

CastleLynelBattle::~CastleLynelBattle() = default;

bool CastleLynelBattle::init_(sead::Heap* heap) {
    return LynelBattle::init_(heap);
}

void CastleLynelBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelBattle::enter_(params);
}

void CastleLynelBattle::calc_() {
    LynelBattle::calc_();
}

void CastleLynelBattle::m34(bool skip_prepare) {
    if (sub_710072CB78(mActor, sub_71005D9330(mActor), nullptr, sub_71007320F0(mActor, 0), -1)) {
        if (sub_710048DEEC()) {
            changeToMeleeBattle();
        } else if ((*mLynelAIFlags_a & 0x180) && sub_710048E778()) {
            return;
        } else {
            changeToChargeOrSixLegAttack(true);
        }
    } else if (getCurrentChild()) {
        setFailed();
    } else {
        changeToMeleeBattle();
    }
}

void CastleLynelBattle::leave_() {
    LynelBattle::leave_();
}

void CastleLynelBattle::loadParams_() {
    LynelBattle::loadParams_();
}

}  // namespace uking::ai
