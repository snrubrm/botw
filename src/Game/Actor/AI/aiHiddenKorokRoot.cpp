#include "Game/Actor/AI/aiHiddenKorokRoot.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

HiddenKorokRoot::HiddenKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenKorokRoot::~HiddenKorokRoot() {
    if (_78) {
        ksys::phys::CollisionInfo::free(_78);
        _78 = nullptr;
    }
}

// NON_MATCHING: the original clears both layer masks of _78 with one 8-byte store
bool HiddenKorokRoot::init_(sead::Heap* heap) {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 |= 0x20000000;

    _78 = ksys::phys::CollisionInfo::make(heap, mActor->getName());
    _78->getLayerMask(ksys::phys::ContactLayerType::Entity).makeAllZero();
    _78->getLayerMask(ksys::phys::ContactLayerType::Sensor).makeAllZero();
    _78->enableLayer(ksys::phys::ContactLayer::EntityObject);
    _78->enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    _78->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    return true;
}

void HiddenKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenKorokRoot::leave_() {
    if (_82)
        _82 = false;
}

bool HiddenKorokRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x1800010)
        return false;

    if (auto* schedule = mActor->getSchedule())
        schedule->_122 = false;
    xlinkEventOn(mActor, 26, 0, false);
    callHiddenKorokFoundDemo();
    return true;
}

void HiddenKorokRoot::invokedTalk() {
    if (auto* event_mgr = ksys::evt::Manager::instance()) {
        ksys::evt::Metadata metadata(mActor->getName().cstr(), "Talk", "");
        event_mgr->callEvent(metadata, mActor);
    }
}

void HiddenKorokRoot::invokedExamine() {
    xlinkEventOn(mActor, 26, 0, false);
    callHiddenKorokFoundDemo();
}

void HiddenKorokRoot::callHiddenKorokFoundDemo() {
    if (!_80) {
        _82 = true;
        _80 = true;
    }

    auto* event_mgr = ksys::evt::Manager::instance();
    if (!event_mgr)
        return;

    ksys::evt::Metadata metadata;
    metadata.setEventStartWaitFrame(*mKorokEventStartWaitFrame_m);
    if (mPlacementType_m == "Ground")
        metadata.init("Demo017_0", "HiddenKorok_Ground");
    else if (mPlacementType_m == "Air")
        metadata.init("Demo017_0", "HiddenKorok_Air");
    else
        return;
    event_mgr->callEvent(metadata, mActor);
}

// NON_MATCHING: the two body pointer null tests are compared in the other order (cmp / ccmp).
void HiddenKorokRoot::calc_() {
    if (_82) {
        callHiddenKorokFoundDemo();
    } else if (_80) {
        if (isCurrentChild("ひるむ") && getCurrentChild()->isFinished()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "TerrorOccurring", -1);
            pack.addVec3(getPlayerPosition(), "TargetPos", -1);
            changeChild("振り向く", &pack);
        } else if (isCurrentChild("振り向く")) {
            bool hit = sub_71007A274C(mActor);
            if (!hit) {
                auto* info = mActor->getCharacterController()->sub_7100F6367C();
                if (info && info->getCollidingBodies().size() != 0) {
                    auto* bodies = info->getCollidingBodies().front();
                    info->lock();
                    for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
                        auto* body = bodies->bodies[1];
                        if (!(bodies->bodies[0] && body))
                            continue;
                        sead::Vector3f dir = body->getLinearVelocity();
                        if (!(body->getLinearVelocity().length() > *mPainTalkHitSpeed_s))
                            continue;
                        if (body->getHkBodyName().findIndex("Motorcycle") != -1 &&
                            body->getLinearVelocity().length() <= 4.75f) {
                            continue;
                        }
                        dir.normalize();
                        if (dir.y <= 0.6f)
                            break;
                    }
                    info->unlock();
                    hit = bodies != nullptr;
                }
            }

            if (hit && (getPlayerPosition() - mActor->getMtx().getTranslation()).length() <=
                           *mPainTalkDistance_s) {
                changeChild("ひるむ");
                sead::FixedSafeString<64> label;
                label.format("near%02d", sead::GlobalRandom::instance()->getU32(3));
                _a8.set(0.0f, label);
            }
        }
    }

    if (*mIsAppearCheck_m && !_80)
        xlinkEventOn(mActor, 26, 1, false);
    if (*mIsAppearCheck_m && !_80 && !_81) {
        if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24D0())) {
            auto* body = set->findBodyByHavokName("Body");
            if (body && body->isAddedToWorld()) {
                sub_71007A36BC(mActor);
                _81 = true;
            }
        }
    }

    getCurrentChild()->setDynamicParam(getPlayerPosition(), "TargetPos");
    _a8.sub_7100721C48();
}

void HiddenKorokRoot::loadParams_() {
    getStaticParam(&mPainTalkHitSpeed_s, "PainTalkHitSpeed");
    getStaticParam(&mPainTalkDistance_s, "PainTalkDistance");
    getMapUnitParam(&mKorokEventStartWaitFrame_m, "KorokEventStartWaitFrame");
    getMapUnitParam(&mIsAppearCheck_m, "IsAppearCheck");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
    getMapUnitParam(&mIsHiddenKorokLiftAppear_m, "IsHiddenKorokLiftAppear");
    getMapUnitParam(&mIsInvisibleKorok_m, "IsInvisibleKorok");
}

}  // namespace uking::ai
