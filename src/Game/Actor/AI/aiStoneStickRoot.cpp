#include "Game/Actor/AI/aiStoneStickRoot.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

// 0x71005abeec
bool Unk_71024257f8::invoke(const ksys::act::ActorLinkConstDataAccess& accessor) {
    return accessor.hasTag(mTag);
}


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

void StoneStickRoot::enter_(ksys::act::ai::InlineParamPack*) {
    if (_60)
        _60->addToWorld();
    if (_68)
        _68->addToWorld();
    auto* actor = mActor;
    if (!actor)
        return;
    s32 index = -1;
    Unk_71024257f8 predicate(ksys::act::tags::IsMagneStickAcceptor);
    _50 = sub_71005AB22C(actor, &index, &predicate);
    if ((actor->hasPlacementLinkForBasicSig() && actor->checkBasicSig()) || sub_71005AB83C())
        sub_71005AB6B8();
    else
        changeChild("通常", nullptr);
}

// Fixes the stone to the linked acceptor: switches to the fixed child, makes the body keyframed and attaches the
// constraint at the current pose (in the acceptor's static compound space if it has one).
void StoneStickRoot::sub_71005AB6B8() {
    auto* actor = mActor;
    if (!actor)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!_50)
        return;
    _50->getActorWithAccessor(accessor);
    if (!_58 || !accessor.hasProc())
        return;

    changeChild("固定");
    sead::Matrix34f mtx = actor->getMtx();
    sead::Matrix34f transform = sead::Matrix34f::ident;
    if (auto* body = actor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->enableGroundCollision(false);
        actor->sub_71011C8B04(mtx);
    }

    auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr();
    auto& group = accessor.getFieldBodyGroup();
    if (mgr && group) {
        _58->sub_7100F6A9D4(group);
        transform = mgr->getTransformedMatrix(group, sead::Matrix34f::ident);
    }
    _58->sub_7100F6D420(mtx, transform, mtx);
    _58->sub_7100F69FF0();
    actor->emitBasicSigOn();

    if (auto* gear = GearMgr::instance()) {
        if (auto* owner = mActor) {
            gear->sub_71006692F0(owner, false);
            _48 = gear->_1050;
            if (auto* physics = owner->getPhysics())
                physics->sub_7100FBDFA4(_48);
        }
    }
}

// 0x71005ab83c
// NON_MATCHING: the accessor and output matrix occupy opposite stack slots.
bool StoneStickRoot::sub_71005AB83C() {
    sead::Vector3f fixed_position;
    fixed_position.setMul(mActor->getMtx(), *mFixPoint_s);
    ksys::act::ActorLinkConstDataAccess accessor;
    bool near = false;
    if (_50) {
        _50->getActorWithAccessor(accessor);
        if (accessor.hasProc()) {
            sead::Matrix34f matrix;
            accessor.sub_7100D105A8(&matrix);
            near = (matrix.getTranslation() - fixed_position).squaredLength() < 0.0064f;
        }
    }
    return near;
}

// NON_MATCHING: the two stores to _78 are merged into one (the original keeps one per branch)
void StoneStickRoot::calc_() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    if (actor->hasPlacementLinkForBasicSig()) {
        const bool sig = actor->checkBasicSig();
        if (_40 != sig) {
            auto* gear = GearMgr::instance();
            if (sig) {
                if (gear) {
                    if (auto* owner = mActor) {
                        gear->sub_71006692F0(owner, false);
                        _48 = gear->_1050;
                        if (auto* physics = owner->getPhysics())
                            physics->sub_7100FBDFA4(_48);
                    }
                }
            } else if (gear) {
                if (auto* owner = mActor) {
                    if (auto* physics = owner->getPhysics())
                        physics->sub_7100FBDFA4(nullptr);
                }
                _48 = nullptr;
            }
            _40 = sig;
        }
    }

    body->getTransform();

    s32 contact_frames;
    if (_70 && _70->getNumContactPoints() != 0 && !_70->begin().isEnd()) {
        contact_frames = 10;
        _78 = 10;
    } else {
        contact_frames = _78;
        if (contact_frames >= 1)
            _78 = --contact_frames;
    }

    if (isCurrentChild("固定開始")) {
        if (getCurrentChild()->isFinished()) {
            const bool is_near = sub_71005AB83C();
            if (contact_frames > 0 || !is_near) {
                changeChild("通常");
            } else {
                sub_71005AB6B8();
                ksys::eft::searchAndEmitSLink(mActor, "Put", false);
            }
        } else if (contact_frames >= 1) {
            changeChild("通常");
        }
    } else if (isCurrentChild("通常")) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (_50) {
            _50->getActorWithAccessor(accessor);
            if (accessor.hasProc()) {
                const bool is_near = sub_71005AB83C();
                if (contact_frames <= 0 && is_near)
                    changeChild("固定開始");
            }
        }
    }
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

bool StoneStickRoot::handleMessage_(const ksys::Message* message) {
    if (!message || !_48)
        return false;
    auto* mgr = GearMgr::instance();
    if (!mgr)
        return false;

    if (message->getType() == 0x3000003) {
        mgr->sub_71006698B0(true);
        return false;
    }
    if (message->getType() == 0x3000004) {
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
