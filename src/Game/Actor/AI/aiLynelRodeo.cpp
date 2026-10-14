#include "Game/Actor/AI/aiLynelRodeo.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.setBit(1);
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), &player.getActorMtx(),
                   &player.getPreviousPos());
    changeChild("暴れる");
}

void LynelRodeo::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
    *mLynelRodeoAttackHitNum_a = 0;
}

void LynelRodeo::sub_7100499D48() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (rideable &&
        int(act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff)) !=
            act::Unk_7100e8b2b8::Unk8::_0 &&
        (rideable->act::Unk_7100e8b2b8::_8.load() & 0x400)) {
        auto* actor = mActor;
        if (sub_71007A2604(actor)) {
            const s32 num = sub_71007A26AC(actor);
            for (s32 i = 0; i < num; ++i) {
                auto* info = sub_71007A255C(actor, i);
                if (info && ksys::act::isPlayerProfile(&info->_d8)) {
                    ++*mLynelRodeoAttackHitNum_a;
                    return;
                }
            }
        }
    }
}

// NON_MATCHING: the two enum temporaries use different stack locations.
void LynelRodeo::calc_() {
    sub_7100499D48();
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (isCurrentChild("振り落す"))
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("暴れる"))
            sub_7100499E08();
        else
            setFinished();
        return;
    }
    if (!child->isChangeable())
        return;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable) {
        setFailed();
        return;
    }
    if (isCurrentChild("暴れる") &&
        (int(act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff)) ==
             act::Unk_7100e8b2b8::Unk8::_0 ||
         (rideable->act::Unk_7100e8b2b8::_8.load() & 0x400) == 0 ||
         int(act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff)) !=
             act::Unk_7100e8b2b8::Unk8::_1)) {
        sub_7100499E08();
    }
}

void LynelRodeo::sub_7100499E08() {
    auto* actor = mActor;
    if (act::Unk_7100e8b2b8* rideable = actor->getHorseOptionsMaybe()) {
        rideable->m43();
        rideable->_c = 0;
    }
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild())) {
        if (auto* manager = child->getDamageMgr()) {
            act::Struct20_2 damage;
            damage.mField_18 = 22;
            damage.mField_14 = 5;
            damage.mField_8 = 1;
            damage.mField_30 = true;
            damage.mField_2C = 0.1f;
            sead::Vector3f direction(actor->getMtx().m[0][2], 0.0f,
                                     actor->getMtx().m[2][2]);
            direction.negate();
            direction.normalize();
            damage.mField_20 = direction;
            if (manager->mStruct20_a) {
                manager->mField_30.lock();
                manager->mStruct20_a->combineMaybe(&damage);
                manager->mField_30.unlock();
            }
        }
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("振り落す", &params);
}

void LynelRodeo::loadParams_() {
    getAITreeVariable(&mLynelRodeoAttackHitNum_a, "LynelRodeoAttackHitNum");
}

}  // namespace uking::ai
