#include "Game/AI/AI/aiMimicCliffStopEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

MimicCliffStopEnemyNormal::MimicCliffStopEnemyNormal(const InitArg& arg)
    : MimicCliffStopEnemyNormalBase(arg) {}

MimicCliffStopEnemyNormal::~MimicCliffStopEnemyNormal() = default;

bool MimicCliffStopEnemyNormal::init_(sead::Heap* heap) {
    return MimicCliffStopEnemyNormalBase::init_(heap);
}

void MimicCliffStopEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    MimicCliffStopEnemyNormalBase::enter_(params);
    ksys::act::disableAllAttClients(mActor);
    setDamageCallbackTiming(mActor, 4, &_1e8);
}

void MimicCliffStopEnemyNormal::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("擬態解除")) {
        setFinished();
        return;
    }

    if (getCurrentChild()->isChangeable() && !isCurrentChild("擬態解除")) {
        if (mActor->checkBasicSig()) {
            sub_71004A6730(false);
            return;
        }
        if (sub_71004A69A4()) {
            sub_71004A6730(true);
            return;
        }
    }

    MimicCliffStopEnemyNormalBase::calc_();
}

// NON_MATCHING: the translation and the Y axis are loaded as integers and the X/Y sums are stored per
// branch in the original (operand order of the additions differs)
void MimicCliffStopEnemyNormal::sub_71004A6730(bool a1) {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f target;
    mtx.getTranslation(target);
    const sead::Vector3f up = mtx.getBase(1);
    f32 height;
    if (a1) {
        target += up;
        height = 0.5f;
    } else {
        target += up * *mJumpDistXZ_s;
        height = 5.0f;
    }
    target.y -= height;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    *mIsStartResetMimicry_a = true;
    sub_71005DD34C(mActor, true);
    sub_71005DD2E8(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x10000);
    mActor->getRootAi()->getMapUnitParams().setAITreeVariable(
        "IsMimicry", ksys::AIDefParamType::Bool, false);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();

    if (!a1) {
        sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    }
    changeChild("擬態解除", &params);
}

bool MimicCliffStopEnemyNormal::sub_71004A69A4() {
    auto* actor = mActor;
    if (!actor)
        return false;
    if (!sub_71007A4178(actor, false))
        return false;

    const s32 count = sub_71007A425C(actor);
    for (s32 i = 0; i < count; ++i) {
        auto* contact = sub_71007A40D0(actor, i);
        if (!contact)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&contact->_50, &accessor);
        if (accessor.hasProc() && accessor.sub_7100D13BB8())
            return true;
    }
    return false;
}

void MimicCliffStopEnemyNormal::leave_() {
    sub_71005DD2E8(mActor);
    sub_71005DA114(mActor, &_1e8);
    MimicCliffStopEnemyNormalBase::leave_();
}

void MimicCliffStopEnemyNormal::loadParams_() {
    MimicCliffStopEnemyNormalBase::loadParams_();
    getStaticParam(&mJumpDistXZ_s, "JumpDistXZ");
}

}  // namespace uking::ai
