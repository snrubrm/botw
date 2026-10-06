#include "Game/AI/AI/aiGanonBattleOnWallRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonBattleOnWallRoot::GanonBattleOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnWallRoot::~GanonBattleOnWallRoot() = default;

bool GanonBattleOnWallRoot::init_(sead::Heap* heap) {
    _60 = ksys::Timer(900.0f, 900.0f);
    return true;
}

void GanonBattleOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        _48 = controller->_70;
        _48.normalize();
    }
    _54 = 0;
    _58 = 0;
    auto* life = mActor->getLife();
    _5c = life ? *life : 1;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

void GanonBattleOnWallRoot::changeToWait() {
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void GanonBattleOnWallRoot::changeToLongRangeAttack() {
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(pos, "ViewPos", -1);
    changeChild("遠距離攻撃", &pack);
    ++_58;
}

void GanonBattleOnWallRoot::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        if (boss->_14f8._30.isOnBit(2))
            _60 = ksys::Timer(900, 900);
    }
}

void GanonBattleOnWallRoot::loadParams_() {
    getStaticParam(&mGuardianActivateHP_s, "GuardianActivateHP");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
