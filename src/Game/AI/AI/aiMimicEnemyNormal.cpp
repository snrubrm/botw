#include "Game/AI/AI/aiMimicEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

MimicEnemyNormal::MimicEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

MimicEnemyNormal::~MimicEnemyNormal() = default;

bool MimicEnemyNormal::sub_71004A7BB4() {
    if (!sub_71007A4178(mActor, false))
        return false;
    auto* link = &sub_71007A40D0(mActor, 0)->_50;
    if (!ksys::act::isPlayerProfile(link))
        return false;
    if (!enemyTeamStuff(mActor, link))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("不審者発見", &pack);
    return true;
}

bool MimicEnemyNormal::sub_71004A7D18() {
    auto* actor = mActor;
    if (actor) {
        if (!sub_71007A4178(actor, false))
            return false;
        const s32 num = sub_71007A425C(actor);
        for (s32 i = 0; i < num; ++i) {
            if (auto* info = sub_71007A40D0(actor, i)) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&info->_50, &accessor);
                if (accessor.hasProc() && accessor.sub_7100D13BB8())
                    return true;
            }
        }
    }
    return false;
}

// NON_MATCHING: same instructions; the "IsMimicry" SafeString temporary is materialised before the load of the
// root AI parameters in the original (same scheduling difference as YunBoCannon::m36 / sub_7100731000).
void MimicEnemyNormal::sub_71004A7DDC() {
    *mIsStartResetMimicry_a = true;
    sub_71005DD34C(mActor, true);
    sub_71005DD2E8(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x10000);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
    mActor->getRootAi()->getMapUnitParams().setAITreeVariable("IsMimicry", ksys::AIDefParamType::Bool,
                                                              false);
    changeChild("擬態解除");
}

void MimicEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

bool MimicEnemyNormal::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MimicEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void MimicEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getStaticParam(&mRideHorseMaskPlayerFindDist_s, "RideHorseMaskPlayerFindDist");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

bool MimicEnemyNormal::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("プレイヤー発見") && getCurrentChild()->isFinished());
}

void MimicEnemyNormal::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("プレイヤー発見")) {
            if (getCurrentChild()->isFailed()) {
                sub_71005D8E9C(mActor);
                m37();
            } else {
                setFinished();
            }
            return;
        }
        if (isCurrentChild("待機")) {
            if (!sub_710039FFA8(false))
                m37();
            return;
        }
        if (isCurrentChild("擬態解除") || isCurrentChild("不審者発見")) {
            setFinished();
            return;
        }
    }
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("待機")) {
            if (sub_710039FFA8(false) || sub_71004A7894() || sub_71004A7BB4())
                return;
        }
        if (!isCurrentChild("擬態解除") && sub_71004A7D18()) {
            sub_71004A7DDC();
            return;
        }
    }
    if (isCurrentChild("プレイヤー発見") && sub_71005D8F28(mActor)) {
        auto* current = getCurrentChild();
        current->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    }
}

}  // namespace uking::ai
