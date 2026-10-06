#include "Game/AI/AI/aiGanonBattleRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonBattleRoot::GanonBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleRoot::~GanonBattleRoot() = default;

bool GanonBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBattleRoot::sub_71003E3A3C(const sead::Vector3f& position) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB0();
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.reset(0x2008);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("壁", &pack);
    _38 = false;
}

void GanonBattleRoot::sub_71003E3BA0(const sead::Vector3f& position) {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDE8(sead::Vector3f::ey);
        controller->sub_7100F5EE1C(sead::Vector3f::ey * -29.0f);
        controller->sub_7100F62BB8();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    pack.addBool(_38, "IsNoWait", -1);
    changeChild("床", &pack);
    _38 = false;
}

void GanonBattleRoot::changeToStateChange(const sead::Vector3f& position) {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.setBit(3);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("状態遷移", &pack);
    _38 = false;
}

void GanonBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sead::DynamicCast<act::LastBoss>(mActor)) {
        auto* actor = mActor;
        if (actor) {
            auto* target = sub_71005D9050(actor);
            if (target && target->hasProc() && ksys::act::isPlayerProfile(target))
                sub_71005D9330(actor);
            else
                getPlayerPosition();
        }
    }
    sub_71003E3644();
    _38 = false;
}

void GanonBattleRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    sead::Vector3f position;
    auto* actor = mActor;
    if (actor) {
        auto* target = sub_71005D9050(actor);
        if (target && target->hasProc() && ksys::act::isPlayerProfile(target))
            position = sub_71005D9330(actor);
        else
            position = getPlayerPosition();
    }
    child->setDynamicParam(position, "TargetPos");
    if (!_38) {
        if (auto* damage = sub_710072BA90(mActor))
            _38 = s32(damage->getDamage()) > 0;
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("状態遷移")) {
            const bool finished = child->isFinished();
            auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
            if (finished) {
                if (boss)
                    boss->_14e4 = 1;
                sub_71003E3A3C(position);
            } else {
                if (boss)
                    boss->_14e4 = 0;
                sub_71003E3BA0(position);
            }
        } else {
            sub_71003E3644();
        }
    }
    if (isCurrentChild("床"))
        sub_71005DB068(mActor, position);
    else
        sub_71005DB3EC(mActor);
}

void GanonBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleRoot::loadParams_() {}

}  // namespace uking::ai
