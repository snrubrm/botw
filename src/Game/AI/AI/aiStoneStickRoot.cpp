#include "Game/AI/AI/aiStoneStickRoot.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

StoneStickRoot::StoneStickRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneStickRoot::~StoneStickRoot() {
    if (_58) {
        ksys::phys::Constraint::destroy(_58);
        _58 = nullptr;
    }
}

bool StoneStickRoot::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (!actor)
        return false;
    ksys::phys::FixedCs::Param param;
    param.body_a = actor->getMainBody();
    _58 = ksys::phys::FixedCs::make(param, heap);
    _60 = actor->findPhysicsBodyByName("BodyParts_00", "left_Stopper");
    _68 = actor->findPhysicsBodyByName("BodyParts_00", "right_Stopper");
    if (auto* physics = actor->getPhysics()) {
        const s32 idx = physics->findContactPointInfo("Body");
        if (idx < 0)
            _70 = nullptr;
        else
            _70 = physics->getContactPointInfoAt(idx);
        if (_70)
            _70->setAllLayerMask2();
    }
    return true;
}

void StoneStickRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StoneStickRoot::leave_() {
    if (_58)
        _58->sub_7100F6A074();
    if (_60)
        _60->removeFromWorld();
    if (_68)
        _68->removeFromWorld();

    if (GearMgr::instance()) {
        if (mActor) {
            if (auto* physics = mActor->getPhysics())
                physics->sub_7100FBDFA4(nullptr);
        }
        _48 = nullptr;
    }
}

void StoneStickRoot::loadParams_() {
    getStaticParam(&mFixPoint_s, "FixPoint");
}

// NON_MATCHING: the original null-checks the message reference (`cbz x1`; see lane2 log s17)
bool StoneStickRoot::handleMessage_(const ksys::Message& message) {
    if (!_48)
        return false;
    auto* mgr = GearMgr::instance();
    if (!mgr)
        return false;

    if (message.getType() == 0x3000003) {
        mgr->sub_71006698B0(true);
        return false;
    }
    if (message.getType() == 0x3000004) {
        mgr->sub_71006698B0(false);
        return true;
    }
    return false;
}

bool StoneStickRoot::updateForPreDelete() {
    if (_58 && _58->_50 & 1)
        return false;
    return true;
}

}  // namespace uking::ai
