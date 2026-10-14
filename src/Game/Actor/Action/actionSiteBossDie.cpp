#include "Game/Actor/Action/actionSiteBossDie.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossDie::SiteBossDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossDie::~SiteBossDie() = default;

bool SiteBossDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossDie::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Damage_Last", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F5EEB8(0.0f);
    }
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityPlayer);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGround);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundRough);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityObject);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityAirWall);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundSmooth);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntitySmallObject);
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityRagdoll);
    }
    _40.reset(*mWarpWaitTime_s);
    sub_710072BB28(mActor);

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->x();
        boss->_e90 = 1;
        if ((boss->_1534 & ~3) != 4)
            static_cast<act::Enemy*>(mActor)->incrementDefeatedCount();
        boss->sub_71002D20B8();
        boss->x_5(false);
        boss->x_6(false);
    }
    sub_71005DB3B8(mActor);
    sub_71005DB3EC(mActor);

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->_868 && actor->_868->sub_71006EDDD4())
            actor->sub_71006DD92C(true);
    }

    if (isSlowTimeMaybe()) {
        ksys::act::ActorLinkConstDataAccess player;
        ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &player);
        sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x80000b2), nullptr);
    }
}

void SiteBossDie::leave_() {
    _30.fade();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_2390.sub_71007224D4();
        boss->_2390._8 = false;
    }
}

void SiteBossDie::loadParams_() {
    getStaticParam(&mWarpWaitTime_s, "WarpWaitTime");
    getStaticParam(&mIsUseYAxisSignal_s, "IsUseYAxisSignal");
}

void SiteBossDie::calc_() {
    if (mActor->getASList()->x(0x3b, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _30 = ksys::eft::searchAndEmitELink(mActor, "WarpCharge");
        m32();
    }
    if (isFinishedAS(0, 0)) {
        _30.fade();
        setFinished();
    }
}

bool SiteBossDie::isFinished() const {
    if (isFinishedAS(0, 0))
        return true;
    return isFinishedAS(0, 0);
}

void SiteBossDie::m32() {
    if (*mIsUseYAxisSignal_s) {
        mActor->emitBasicSigOff();
        mActor->emitSignalAxisY_1();
    } else {
        mActor->emitBasicSigOn();
    }
}

}  // namespace uking::action
