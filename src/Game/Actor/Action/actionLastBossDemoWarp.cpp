#include "Game/Actor/Action/actionLastBossDemoWarp.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

LastBossDemoWarp::LastBossDemoWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossDemoWarp::~LastBossDemoWarp() = default;

bool LastBossDemoWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossDemoWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F605F0();
    controller->sub_7100F5E764(false);
    controller->sub_7100F62CA8(false);
    {
        if (auto* physics = mActor->getPhysics()) {
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGround);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundObject);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundRough);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityGroundSmooth);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityNPC);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityPlayer);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityObject);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntitySmallObject);
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::EntityRagdoll);
        }
    }
    _40 = ksys::Timer(*mWarpTime_s, *mWarpTime_s);

    sead::Matrix34f mtx;
    if (auto* obj = ksys::act::findLinkReferenceObj(mActor, "DestinationAnchor", mWarpAnchorUniqName_s,
                                                     nullptr)) {
        mtx.makeRT(obj->getRotate(), obj->getTranslate());
    } else {
        mtx = mActor->getMtx();
    }
    _54 = mtx;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->sub_71002D38EC(mWarpAnchorUniqName_s);
    if (*mIsUpdateHomePos_s)
        mActor->sub_71011C8B04(mtx);
    _4c = 0;
    _50 = 0;
    sub_710073FA90(&_84, mActor);
    playAS("Wait_Battle", true, 2, 0, -1.0f);
}

void LastBossDemoWarp::leave_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    if (auto* body = controller->sub_7100F61A34()) {
        if (auto* physics = mActor->getPhysics())
            body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityHitOnlyGround,
                                            physics->get188(0));
    }
}

void LastBossDemoWarp::loadParams_() {
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mIsUpdateHomePos_s, "IsUpdateHomePos");
    getStaticParam(&mWarpAnchorUniqName_s, "WarpAnchorUniqName");
}

void LastBossDemoWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
