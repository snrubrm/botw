#include "Game/AI/AI/aiBalloonPlantNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"

namespace uking::ai {

BalloonPlantNormal::BalloonPlantNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BalloonPlantNormal::~BalloonPlantNormal() = default;

bool BalloonPlantNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BalloonPlantNormal::sub_7100327C24() {
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_50, "RopeActorHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addString(_60, "ConnectRigidName", -1);
    pack.addVec3(_b8, "ConnectRigidOffset", -1);
    changeChild("寄生する", &pack);
}

bool BalloonPlantNormal::sub_7100327B54() {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (actor && _c8 == actor->getId() && actor->findPhysicsBodyByName("Body", _60.cstr()))
        return true;
    return false;
}

// NON_MATCHING: block layout of the contact-point loop and stack slot assignment.
void BalloonPlantNormal::sub_7100327D48() {
    if (_c4)
        return;

    auto* actor = mActor;
    ksys::phys::SphereCast cast{ksys::phys::ContactLayer::EntitySmallObject,
                                ksys::phys::GroundHit::HitAll,
                                sub_710072E804(actor, 0),
                                8,
                                ksys::phys::ShapeCast::Mode::_1,
                                sead::Vector3f::zero,
                                0.5f,
                                sead::SafeString::cEmptyString,
                                ksys::phys::LowPriority::No};
    auto* info = cast.getContactPointInfo();
    if (!info)
        return;

    info->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityTree);
    info->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
    info->subscribeLayer(ksys::phys::ContactLayer::EntitySmallObject);

    const sead::Vector3f start = actor->getMtx().getTranslation();
    cast.setStartAndDisplacementScaled(start, -sead::Vector3f::ey, 0.1f);
    // called through a pointer in the original (not devirtualised)
    if (!(&cast)->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes))
        return;

    for (auto it = info->begin(), end = info->end(); it != end; ++it) {
        sead::Vector3f pos;
        it.getPointPosition(&pos, ksys::phys::ContactPointInfo::Iterator::Point::BodyB);
        auto* body = it.getPoint()->body_b;
        if (!body || body->getMotionType() != ksys::phys::MotionType::Dynamic)
            continue;

        ksys::act::ActorLinkConstDataAccess accessor;
        if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag()))
            tag->acquireActor(&accessor);
        if (accessor.hasProc() && !accessor.hasConnectedCalcParent() &&
            accessor.hasTag(ksys::act::tags::CanBalloonParasite)) {
            _60.copy(body->getHkBodyName());
            if (_60.isEmpty())
                continue;

            _c8 = accessor.getId();
            sead::Matrix34f mtx;
            body->getTransform(&mtx);
            mtx.setInverse(mtx);
            _b8 = mtx * pos;
            accessor.setThisActorAsChild(actor, false);
            _c4 = true;
            break;
        }
    }
}

void BalloonPlantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710032782C();
    _60.copy("Body");
    ksys::act::disableAllAttClients(mActor);
    _c4 = false;
    _b8.set(sead::Vector3f::zero);
    _60.clear();
    _c8 = 0;
    changeChild("準備待機");
}

void BalloonPlantNormal::leave_() {
    if (_50.hasProcCreationFailed())
        _50.deleteProcIfFailed();
    if (_50.isAllocatedOrFailed())
        _50.deleteProc();
}

void BalloonPlantNormal::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備待機")) {
            _c4 = false;
            _b8.set(sead::Vector3f::zero);
            _60.clear();
            _c8 = 0;
            mActor->resetConnectedCalcChild(false);
            changeChild("失敗");
        } else {
            setFinished();
        }
    } else if (isCurrentChild("準備待機") && _50.isProcReady()) {
        if (_c4) {
            if (sub_7100327B54()) {
                sub_7100327C24();
                _c4 = false;
                _b8.set(sead::Vector3f::zero);
                _60.clear();
                _c8 = 0;
            } else {
                _c4 = false;
                _b8.set(sead::Vector3f::zero);
                _60.clear();
                _c8 = 0;
                sub_7100327D48();
            }
        } else {
            sub_7100327D48();
        }
    }
}

void BalloonPlantNormal::loadParams_() {
    getStaticParam(&mRopeLength_s, "RopeLength");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
}

void BalloonPlantNormal::sub_710032782C() {
    if (_50.isAllocatedOrFailed())
        _50.deleteProc();

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation() + sead::Vector3f(0, 0, 0));
    pack->addScale(sead::Vector3f(1.0f, *mRopeLength_s, 1.0f));
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mRopeActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_50,
        &pack, nullptr, 2);
}

}  // namespace uking::ai
