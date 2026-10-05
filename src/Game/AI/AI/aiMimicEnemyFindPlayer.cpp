#include "Game/AI/AI/aiMimicEnemyFindPlayer.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

MimicEnemyFindPlayer::MimicEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

MimicEnemyFindPlayer::~MimicEnemyFindPlayer() = default;

void MimicEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710037E9A4();
    sub_710037EDA4();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

bool MimicEnemyFindPlayer::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MimicEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
    sub_71005DB3EC(mActor);
}

void MimicEnemyFindPlayer::calc_() {
    const sead::Vector3f position = sub_71005D960C(mActor);
    sub_71005DB068(mActor, position);
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("戦闘")) {
        setFinished();
        return;
    }
    if (getCurrentChild()->isChangeable() && isCurrentChild("気づき")) {
        if (!sub_71005D8F28(mActor)) {
            setFailed();
            return;
        }
        if (m35()) {
            m40();
            *mIsStartResetMimicry_a = true;
            sub_71005DD34C(mActor, true);
            sub_71005DD2E8(mActor);
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
                enemy->_e84.reset(0x10000);
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F62BB8();
            sub_71004A70B4();
            return;
        }
        if (m43())
            _108.sub_7100D3BC4C(-1.0f);
        else
            _108.mValue = _118 == _11c ? _118 :
                sead::GlobalRandom::instance()->getS32Range(_118, _11c);
        if (_108.mValue <= 0.0f) {
            setFailed();
            return;
        }
    }
    auto* current = getCurrentChild();
    current->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void MimicEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

bool MimicEnemyFindPlayer::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("戦闘"))
        return getCurrentChild()->isFinished();
    return false;
}

bool MimicEnemyFindPlayer::m35() {
    const auto& player_pos = sub_71005D9330(mActor);
    const auto& mtx = mActor->getMtx();
    const sead::Vector2f player_xz(player_pos.x, player_pos.z);
    const sead::Vector2f actor_xz(mtx(0, 3), mtx(2, 3));
    if ((player_xz - actor_xz).length() <= *mPlayerForceFindDist_s)
        return true;
    return EnemyBaseFindPlayer::m35();
}

}  // namespace uking::ai
