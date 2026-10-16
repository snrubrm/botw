#include "Game/Actor/AI/aiMotorcycleRoot.h"
#include "Game/gameMotorcycleMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actMotorcycle.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

MotorcycleRoot::MotorcycleRoot(const InitArg& arg) : HorseRiddenStatusSelector(arg) {}

MotorcycleRoot::~MotorcycleRoot() = default;

bool MotorcycleRoot::init_(sead::Heap* heap) {
    return HorseRiddenStatusSelector::init_(heap);
}

void MotorcycleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRiddenStatusSelector::enter_(params);
    updateASFlags();
    _80 = false;
    _70 = nullptr;
    _78 = nullptr;
    _81.resetBit(Flag::_2);
    _81.resetBit(Flag::_4);
    _81.resetBit(Flag::_5);

    auto* motorcycle = sead::DynamicCast<act::Motorcycle>(mActor);
    if (!motorcycle)
        return;

    motorcycle->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    motorcycle->_1128 = true;
    motorcycle->_112c = 0.0f;
    if (!testRootAiFlag(ksys::act::ai::RootAiFlag::_7)) {
        if (auto* stuff = mActor->getMotorcyclePriorityStuffMaybe()) {
            if (_78) {
                mActor->setMtx(*_78, false, true);
                _78 = nullptr;
            }
            changeChild("出現");
            ksys::act::disableAllAttClients(mActor);
            stuff->_8 = 0x200;
            _81.setBit(Flag::_3);
        }
        mActor->getASList()->startAnimationMaybe(-1.0f, 1.0f, "Close", 0, 0, true);
        mActor->getASList()->startAnimationMaybe(-1.0f, 1.0f, "MatAnim", 3, 0, true);
    }

    if (auto* mgr = MotorcycleMgr::instance())
        mgr->_17b = 0;

    if (auto* body = mActor->findPhysicsBodyByName("Body", "MotorcycleChassis"))
        body->clearFlag2000000(false);
    if (auto* body = mActor->findPhysicsBodyByName("Body", "MotorcycleFrontWheel"))
        body->clearFlag2000000(false);
    if (auto* body = mActor->findPhysicsBodyByName("Body", "MotorcycleRearWheel"))
        body->clearFlag2000000(false);
}

void MotorcycleRoot::updateASFlags() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (auto* motorcycle = sead::DynamicCast<act::Motorcycle>(actor))
        as_list->x_2(0x42, 0x2c, motorcycle->sub_710007A4A8() != 0.0f, false);
    else
        as_list->x_2(0x42, 0x2c, false, false);

    auto* stuff = mActor->getMotorcyclePriorityStuffMaybe();
    if (!stuff) {
        as_list->x_2(0x42, 0x1a, false, false);
    } else {
        const act::Unk_7100e8b2b8::Unk8 type = stuff->_8 & 0xff;
        if (int(type) == act::Unk_7100e8b2b8::Unk8::_0)
            as_list->x_2(0x42, 0x1a, false, false);
    }

    auto* mgr = MotorcycleMgr::instance();
    if (mgr && mgr->x(mActor))
        as_list->x_2(0x42, 0x29, mgr->mEnergy <= 0.0f, false);
    else
        as_list->x_2(0x42, 0x29, false, false);
}

void MotorcycleRoot::leave_() {
    HorseRiddenStatusSelector::leave_();
    auto* mgr = MotorcycleMgr::instance();
    if (mgr) {
        if (mgr->x(mActor))
            mgr->_17c = 0;
    }
    mgr->_17a = 1;
}

void MotorcycleRoot::loadParams_() {
    HorseRiddenStatusSelector::loadParams_();
    getStaticParam(&mInWaterRateForDisappear_s, "InWaterRateForDisappear");
    getStaticParam(&mDistanceToPlayerForDisappear_s, "DistanceToPlayerForDisappear");
    getStaticParam(&mNoiseEnergyEmpty_s, "NoiseEnergyEmpty");
    getStaticParam(&mNoiseNotRidden_s, "NoiseNotRidden");
    getStaticParam(&mNoiseThrottleClose_s, "NoiseThrottleClose");
    getStaticParam(&mNoiseThrottleOpen_s, "NoiseThrottleOpen");
    getStaticParam(&mForestFogRatioForDisappear_s, "ForestFogRatioForDisappear");
}

}  // namespace uking::ai
