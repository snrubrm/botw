#include "Game/AI/Action/actionInCarryBox.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldChemicalMgr.h"

namespace uking::action {

InCarryBox::InCarryBox(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InCarryBox::~InCarryBox() = default;

bool InCarryBox::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InCarryBox::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsInitFromCarryBox_a = true;
    auto* actor = mActor;
    auto* scene = GameSceneSubsys12::instance();
    if (!_28 && scene)
        _28 = scene->sub_7100663278(actor);
    if (_28) {
        actor->setFlag(ksys::act::Actor::ActorFlag::_25, true);
        if (auto* lod = actor->getLodState())
            lod->mFlags10.set(0x40);
        if (auto* as = actor->getASList()) {
            if (as->sub_710115AA68("InCarryBox"))
                as->startAnimationMaybe(-1, -1, "InCarryBox", 0, 0, true);
        }
    } else {
        setFailed();
    }
}

void InCarryBox::leave_() {
    auto* actor = mActor;
    actor->setFlag(ksys::act::Actor::ActorFlag::_25, false);
    if (auto* lod = actor->getLodState())
        lod->mFlags10.reset(0x40);
    if (actor->getName() == "Item_Enemy_57") {
        const auto& group = ksys::act::getStr_EntitySensor();
        if (auto* body = actor->findPhysicsBodyByName(group.cstr(), "SwapBody"))
            body->removeFromWorld();
    }
    if (auto* chemical = actor->getChemicalStuff())
        chemical->sub_7100D8F124(ksys::world::Manager::instance()->getChemicalMgr()->_ae8);
}

void InCarryBox::loadParams_() {
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
}

void InCarryBox::calc_() {
    if (_28) {
        auto* actor = mActor;
        if (_28->_28 & 1) {
            _28->sub_7100661058(actor);
            setFinished();
            return;
        }
        _28->sub_7100661A58(actor);
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D8F194();
    }
}

bool InCarryBox::updateForPreDelete() {
    if (_28 && !(_28->_28 & 1))
        _28->sub_7100661058(mActor);
    return true;
}

bool InCarryBox::hasUpdateForPreDeleteCb() {
    return true;
}

}  // namespace uking::action
