#include "Game/AI/AI/aiGanonFarAttackRootOnWall.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GanonFarAttackRootOnWall::GanonFarAttackRootOnWall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonFarAttackRootOnWall::~GanonFarAttackRootOnWall() = default;

bool GanonFarAttackRootOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonFarAttackRootOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0;
    sub_71003E8884();
}

void GanonFarAttackRootOnWall::leave_() {
    sub_71003E9150();
}

void GanonFarAttackRootOnWall::loadParams_() {
    getStaticParam(&mPillarMax_s, "PillarMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

bool GanonFarAttackRootOnWall::isFinished() const {
    if (getCurrentChild()) {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && !isCurrentChild("落雷") &&
            !isCurrentChild("落雷後待機")) {
            return true;
        }
    }
    return ActionBase::isFinished();
}

void GanonFarAttackRootOnWall::sub_71003E9150() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    const int max = *mPillarMax_s;
    for (int i = 0; i <= max; ++i) {
        sead::FormatFixedSafeString<64> name("IronPile%d", i);
        if (enemy->getActorPartsActor(name).hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                                nullptr, true);
        }
    }
}

void GanonFarAttackRootOnWall::changeToThrowSpear() {
    _54 = 2;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("槍投げ", &pack);
}

void GanonFarAttackRootOnWall::changeToFireball() {
    _54 = 3;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("火球", &pack);
}

void GanonFarAttackRootOnWall::changeToTornado() {
    _54 = 4;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("竜巻", &pack);
}

void GanonFarAttackRootOnWall::changeToIcePillar() {
    _54 = 6;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("氷柱", &pack);
}

void GanonFarAttackRootOnWall::changeToLightning() {
    _54 = 5;
    ++_50;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("落雷", &pack);
}

}  // namespace uking::ai
