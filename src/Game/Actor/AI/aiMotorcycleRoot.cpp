#include "Game/Actor/AI/aiMotorcycleRoot.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/Event/evtManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"
#include "Game/gameMotorcycleMgr.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "Game/Actor/actMotorcycle.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// NON_MATCHING: the original tests the event manager before the motorcycle manager and keeps !x() as a value
// (eor + tbz); ours swaps the two null tests.
bool MotorcycleRoot::handleMessage_(const ksys::Message* message) {
    switch (message->getType()) {
    case 0x3800029:
        if (auto* motorcycle = sead::DynamicCast<act::Motorcycle>(mActor))
            motorcycle->x_9(true);
        return true;
    case 0x380001d:
        _78 = static_cast<sead::Matrix34f*>(message->getUserData());
        _80 = true;
        return true;
    case 0x1800027: {
        if (ksys::ui::sub_7100EDC4B8())
            return true;
        if (_81.isOnBit(Flag::_5))
            return true;
        if (_81.isOnBit(Flag::_2))
            return true;

        auto* subsys = GameSceneSubsys12::instance();
        if (!subsys)
            return true;
        auto* motorcycle_mgr = MotorcycleMgr::instance();
        auto* event_mgr = ksys::evt::Manager::instance();
        if (!subsys->sub_71006652C8())
            return true;
        const bool x = subsys->x();
        if (!event_mgr || !motorcycle_mgr || x)
            return true;

        motorcycle_mgr->sub_710067A7E4(nullptr, nullptr);
        ksys::evt::Metadata metadata("Demo649_0", "Demo649_0", "");
        ksys::evt::CallArg arg;
        arg.metadata = &metadata;
        arg.proc = mActor;
        if (event_mgr->callEvent(arg)) {
            ui::PauseMenuDataMgr::instance()->removeGrabbedItems();
            _81.setBit(Flag::_2);
        } else {
            subsys->_a78.fetchAnd(~1u);
        }
        return true;
    }
    default:
        return false;
    }
}

// NON_MATCHING: same 33 instructions; the shared tail block is laid out after the energy-empty arm
// instead of after the last (throttle-closed) arm.
void MotorcycleRoot::sub_71004AE954(act::Motorcycle* motorcycle, act::Unk_7100e8b2b8* rideable,
                                    MotorcycleMgr* motorcycle_mgr) {
    if (!motorcycle_mgr || motorcycle_mgr->mEnergy <= 0.0f) {
        sub_71005D8D4C(mActor, *mNoiseEnergyEmpty_s, 1, false);
        return;
    }
    if (int(act::Unk_7100e8b2b8::Unk8(rideable->_8 & 0xff)) ==
        act::Unk_7100e8b2b8::Unk8::_0) {
        sub_71005D8D4C(mActor, *mNoiseNotRidden_s, 1, false);
        return;
    }
    if (motorcycle->sub_710007A478()) {
        sub_71005D8D4C(mActor, *mNoiseThrottleOpen_s, 1, false);
        return;
    }
    sub_71005D8D4C(mActor, *mNoiseThrottleClose_s, 1, false);
}

void MotorcycleRoot::sub_71004AEDAC(act::Motorcycle* motorcycle, act::Unk_7100e8b2b8* rideable) {
    if (motorcycle->_dd0->_13d || motorcycle->_dd8->_13d || motorcycle->_f88.isOnBit(32)) {
        if (_81.isOnBit(Flag::_3)) {
            if (auto* attention = mActor->getAttention()) {
                if (auto* client = attention->getClientByName("Cook"))
                    client->enable();
            }
            rideable->sub_7100E8BD80();
            _81.resetBit(Flag::_3);
        }
    } else {
        if (!_81.isOnBit(Flag::_3)) {
            ksys::act::disableAllAttClients(motorcycle);
            _81.setBit(Flag::_3);
        }
    }
}

void MotorcycleRoot::sub_71004AE7E0(act::Unk_7100e8b2b8* rideable,
                                    const sead::SafeString& effect_name) {
    ksys::act::ai::InlineParamPack params;
    params.addString(effect_name, "DisappearEffectName", -1);
    changeChild("消失", &params);

    ksys::act::disableAllAttClients(mActor);
    rideable->_8 = 0x200;
    _81.setBit(Flag::_3);
    _70 = nullptr;
    _80 = 0;

    auto* motorcycle_mgr = MotorcycleMgr::instance();
    if (motorcycle_mgr && motorcycle_mgr->x(mActor) && _80 != 1)
        motorcycle_mgr->_17a = 0;

    _81.setBit(Flag::_5);
}

}  // namespace uking::ai
