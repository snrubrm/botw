#include "Game/AI/AI/aiLynelRodeo.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void LynelRodeo::loadParams_() {
    getAITreeVariable(&mLynelRodeoAttackHitNum_a, "LynelRodeoAttackHitNum");
}

}  // namespace uking::ai
