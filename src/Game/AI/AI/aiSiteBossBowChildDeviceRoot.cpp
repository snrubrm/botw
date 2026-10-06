#include "Game/AI/AI/aiSiteBossBowChildDeviceRoot.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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

// 0x71005749a4
void SiteBossBowChildDeviceRoot::sub_71005749A4() {
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000057), &_50, true);
    }
    if (auto* body = mActor->getMainBody())
        body->resetFlag1000000();
    changeChild("破壊", nullptr);
}

// 0x7100574c2c
void SiteBossBowChildDeviceRoot::sub_7100574C2C() {
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000057), &_50, true);
    }
    if (auto* body = mActor->getMainBody())
        body->resetFlag1000000();
    changeChild("自然消滅", nullptr);
}

// 0x7100574a74
// NON_MATCHING: stack slot order only (the original has the ActorConstDataAccess / SafeString temporaries at the
// highest slot, then the pack, then `pos` at sp+0)
void SiteBossBowChildDeviceRoot::sub_7100574A74() {
    _64 = 7;
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    if (_80.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_80, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    } else {
        mActor->getMtx().getTranslation(pos);
    }
    pack.addVec3(pos, "TargetPos", -1);
    pack.addInt(_50, "ID", -1);
    pack.addActor(_70, "ParentActor", -1);
    pack.addFloat(_9c, "XRotateAngle", -1);
    changeChild("通常待機", &pack);
}

// 0x7100574840
// NON_MATCHING: block layout only: the original turns the final hasTag() result into a constant true / false on a branch
// (every path ends in `mov w0, w19`); ours returns the call result (`and w0, w19, #1`)
bool SiteBossBowChildDeviceRoot::sub_7100574840() {
    auto* manager = sub_710072BA90(mActor);
    if (!manager)
        return false;
    if (s32(manager->getDamage()) <= 0 && manager->getField54() == -1)
        return false;
    auto* attacker = manager->getAttacker();
    if (!attacker->hasProc())
        return true;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(attacker, &accessor);
    if (accessor.isPlayerProfile())
        return true;
    if (manager->getField50() == 4)
        return true;
    if (accessor.getName() == "PlayerBeam")
        return true;
    return accessor.hasTag(0x19f6c13a);
}

}  // namespace uking::ai
