#include "Game/AI/AI/aiSiteBossBowChildDeviceRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

SiteBossBowChildDeviceRoot::SiteBossBowChildDeviceRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossBowChildDeviceRoot::~SiteBossBowChildDeviceRoot() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FB835C();
}

bool SiteBossBowChildDeviceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: regalloc / scheduling of the last stores
void SiteBossBowChildDeviceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        body->setContactAll();
        body->setGravityFactor(0.0f);
    }
    if (auto* body = mActor->getTgtBody())
        body->setContactAll();
    changeAS("Wait_Battle", true, 1, 0);
    changeChild("生成待機");
    _64 = 7;
    _68 = 7;
    _56 = false;
    xlinkEventOn(mActor, 25, 0, false);
    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D8EEE0();
        chemical->sub_7100D90F60(true);
    }
    _50 = *mCount_m;
    _90 = ksys::Timer(300, 300);
    _9c = *mXRotateSpeed_s;
    _70 = mActor->getCreateArgBaseProcLink();
}

void SiteBossBowChildDeviceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original loads each system group handler (`physics->get188(i)`) before the
// rigid body it is applied to (four sites; named locals for them fix it, see the log) and returns
// through the shared return-false block instead of a cset
bool SiteBossBowChildDeviceRoot::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;

    if (message->getType() == 0x800002f) {
        if (_56)
            return true;
        if (auto* physics = mActor->getPhysics()) {
            if (auto* body = mActor->getMainBody()) {
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityNoHit,
                                                physics->get188(0));
            }
            if (auto* body = mActor->getTgtBody()) {
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorNoHit,
                                                physics->get188(1));
            }
        }
        _56 = true;
        return true;
    }
    if (message->getType() == 0x8000030) {
        auto* physics = mActor->getPhysics();
        if (!physics)
            return true;
        if (auto* body = mActor->getMainBody()) {
            body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntitySmallObject,
                                            physics->get188(0));
        }
        if (auto* body = mActor->getTgtBody()) {
            if (!isCurrentChild("生成待機")) {
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorEnemy,
                                                physics->get188(1));
            }
        }
        _56 = false;
        return true;
    }

    if (message->getUserData()) {
        if (message->getType() == 0x800004d || message->getType() == 0x800004e ||
            message->getType() == 0x800004f || message->getType() == 0x8000050 ||
            message->getType() == 0x8000053 || message->getType() == 0x8000055) {
            auto* payload = static_cast<uking::act::SiteBoss::Unk_71002cf2ac::Payload*>(
                message->getUserData());
            if (payload->owner)
                _70.acquire(payload->owner, false);
            if (payload->target)
                _80 = *payload->target;
            _55 = false;
            _50 = payload->idx;

            if (message->getType() == 0x800004d) {
                if (_64 != 7)
                    _68 = _64;
                _64 = 1;
                return true;
            }
            if (message->getType() == 0x800004e) {
                if (_64 != 7)
                    _68 = _64;
                _64 = 2;
                return true;
            }
            if (message->getType() == 0x800004f) {
                _64 = 3;
                return true;
            }
            if (message->getType() == 0x8000050) {
                _64 = 4;
                return true;
            }
            if (message->getType() == 0x8000053) {
                _55 = payload->flags >> 1 & 1;
                _58 = payload->pos;
                _64 = 5;
                return true;
            }
            if (message->getType() == 0x8000055) {
                _54 = payload->flags & 1;
                _55 = payload->flags >> 1 & 1;
                _58 = payload->pos;
                _64 = 6;
                return true;
            }
        }
    }
    if (message->getType() == 0x3000007)
        return true;
    return false;
}

void SiteBossBowChildDeviceRoot::loadParams_() {
    getStaticParam(&mXRotateSpeed_s, "XRotateSpeed");
    getStaticParam(&mSlowRate_s, "SlowRate");
    getMapUnitParam(&mCount_m, "Count");
}

}  // namespace uking::ai
