#include "Game/AI/AI/aiEnemyMimicrySelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Utils/MathUtil.h"

bool sub_71005DCD84(s32* material, ksys::act::Actor* actor, f32 range, bool unused);

namespace uking::ai {

EnemyMimicrySelect::EnemyMimicrySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMimicrySelect::~EnemyMimicrySelect() = default;

bool EnemyMimicrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original materialises the "IsMimicry" string before loading the root AI's parameters
// (the same call matches in MimicCliffStopEnemyNormal::sub_71004A..; only the scheduling differs).
void EnemyMimicrySelect::sub_71003988E0(ksys::act::ai::InlineParamPack* params) {
    s32 material = 0;
    if (sub_71005DCD84(&material, mActor, 1.5f, false)) {
        sub_71005DD27C(mActor, material, 1.0f);
        *mMimicryMaterial_a = material;
        _50 = 0;
    }
    sub_71005DD34C(mActor, false);
    ksys::act::disableAllAttClients(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x10000);
    mActor->getRootAi()->getMapUnitParams().setAITreeVariable("IsMimicry", ksys::AIDefParamType::Bool,
                                                              false);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB0();
    changeChild("擬態", params);
}

void EnemyMimicrySelect::sub_7100398A34(ksys::act::ai::InlineParamPack* params) {
    sub_71005DD34C(mActor, true);
    sub_71005DD2E8(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x10000);
    sub_7100398DD4();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
    changeChild("通常", params);
}

void EnemyMimicrySelect::sub_7100398DD4() {
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        front.normalize();
        const sead::Vector3f up = getUpDir(controller->get70());
        sead::Matrix34f mtx;
        ksys::util::sub_71011F00EC(&mtx, front, up, mActor->getMtx().getTranslation(), false);
        controller->sub_7100F60500(mtx);
    }
}

void EnemyMimicrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0xff;
    if (*mIsMimicry_m)
        sub_71003988E0(params);
    else
        sub_7100398A34(params);
}

bool EnemyMimicrySelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyMimicrySelect::leave_() {
    if (isCurrentChild("擬態"))
        *mIsStartResetMimicry_a = true;
    sub_71005DD34C(mActor, true);
    sub_71005DD2E8(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (!enemy->m151(3))
            enemy->_e84.reset(0x10000);
    }
    sub_7100398DD4();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
}

void EnemyMimicrySelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("擬態")) {
            *mIsStartResetMimicry_a = true;
            sub_7100398A34(nullptr);
        } else if (isCurrentChild("通常")) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
        }
        return;
    }
    if (isCurrentChild("擬態")) {
        sub_71005DD34C(mActor, false);
        if (_50 == 0xff && ksys::map::PlacementMgr::instance()->isStaticCompoundReady(
                              mActor->getMtx().getTranslation(), false)) {
            s32 material = 0;
            if (sub_71005DCD84(&material, mActor, 1.5f, false)) {
                sub_71005DD27C(mActor, material, 1.0f);
                *mMimicryMaterial_a = material;
                _50 = 0;
            } else {
                _50 = 1;
                *mIsStartResetMimicry_a = true;
                sub_7100398A34(nullptr);
            }
        }
    }
}

void EnemyMimicrySelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
