#include "Game/AI/AI/aiDgnObj_DLC_CogWheel2.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

DgnObj_DLC_CogWheel2::DgnObj_DLC_CogWheel2(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CogWheel2::~DgnObj_DLC_CogWheel2() {
    if (_88) {
        ksys::phys::Constraint::destroy(_88);
        _88 = nullptr;
    }
}

// NON_MATCHING (init_, enter_, leave_): the original tests each name for emptiness with an inlined
// SafeString-style loop (3x unrolled, bounded by 0x80000, reading sead::SafeString::cNullChar)
// before calling findPhysicsBodyByName; the source form that produces it is unknown.
// The bodies that are fixed to the main body by init_ and added to / removed from the world by
// enter_ / leave_.
static const char* const sBodyNames[] = {"Camera_Col", "Air_Col"};

bool DgnObj_DLC_CogWheel2::init_(sead::Heap* heap) {
    if (auto* gear_mgr = GearMgr::instance())
        gear_mgr->sub_7100669144(*mGearRatio_m);
    if (*mRegistFromBeginning_m)
        m34();
    if (auto* actor = mActor) {
        if (auto* main_body = actor->getMainBody()) {
            for (const char* name : sBodyNames) {
                if (auto* body = actor->findPhysicsBodyByName("BodyParts_00", name)) {
                    ksys::phys::FixedCs::Param param;
                    param.body_a = main_body;
                    param.body_b = body;
                    _88 = ksys::phys::FixedCs::make(param, heap);
                    break;
                }
            }
        }
        if (*mCorrectConstraint_s)
            actor->sub_71011DA824(this);
    }
    for (s32 i = 0; i < 3; ++i)
        _90[i] = 0;
    return true;
}

void DgnObj_DLC_CogWheel2::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* actor = mActor) {
        for (const char* name : sBodyNames) {
            if (auto* body = actor->findPhysicsBodyByName("BodyParts_00", name)) {
                body->addToWorld();
                break;
            }
        }
    }
    if (auto* fixed = sead::DynamicCast<ksys::phys::FixedCs>(_88)) {
        sead::Matrix34f mtx;
        mtx.makeIdentity();
        fixed->sub_7100F6D6D8(mtx, mtx);
        fixed->sub_7100F69FF0();
    }
    _90 = {};
    changeChild("待機");
}

void DgnObj_DLC_CogWheel2::calc_() {
    if (auto* gear_mgr = GearMgr::instance()) {
        if (auto* actor = mActor) {
            const bool registered = gear_mgr->sub_71006690B8(actor);
            bool run;
            if (actor->hasPlacementLinkForBasicSig()) {
                const bool basic = actor->checkBasicSig();
                if (registered) {
                    if (!basic)
                        m35();
                    run = true;
                } else {
                    if (basic)
                        m34();
                    run = false;
                }
            } else {
                run = registered;
            }

            if (run) {
                if (isCurrentChild("待機") && (gear_mgr->_10a4 & 8)) {
                    ksys::act::ai::InlineParamPack params;
                    params.addBool(registered, "IsRegisteredFrame", -1);
                    changeChild("回転", &params);
                }
            } else if (isCurrentChild("回転")) {
                changeChild("待機");
            }
        }
    }

    _90[_9c] = mActor->getAngVelocity().length();
    f32 sum = 0;
    for (s32 i = 0; i < 3; ++i)
        sum += _90[i];
    const f32 average = sum / 3;
    _9c = _9c > 1 ? 0 : _9c + 1;
    sub_71012412E4(mActor, 3, average, false);
}

// NON_MATCHING: the original null-checks the message pointer (`cbz x1`).
bool DgnObj_DLC_CogWheel2::handleMessage_(const ksys::Message& message) {
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr)
        return false;
    auto* actor = mActor;
    if (!actor)
        return false;

    const bool registered = gear_mgr->sub_71006690B8(actor);
    const auto type = message.getType();
    if (registered) {
        if (type == 0x3000003) {
            gear_mgr->sub_71006698B0(true);
        } else if (type == 0x3000004) {
            gear_mgr->sub_71006698B0(false);
            return true;
        } else {
            return false;
        }
    } else {
        if (type == 0x3000003) {
            m36();
        } else if (type == 0x3000004) {
            m37();
            return true;
        } else {
            return false;
        }
    }
    sub_71012412E4(actor, 3, 0.0f, false);
    return false;
}

void DgnObj_DLC_CogWheel2::leave_() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (auto* gear_mgr = GearMgr::instance())
        gear_mgr->sub_71006694B4(actor);
    if (_88 && (_88->_50 & 1))
        _88->sub_7100F6A074();
    for (const char* name : sBodyNames) {
        if (auto* body = actor->findPhysicsBodyByName("BodyParts_00", name)) {
            body->removeFromWorld();
            break;
        }
    }
    if (*mCorrectConstraint_s)
        actor->sub_71011DA834(this);
}


void DgnObj_DLC_CogWheel2::loadParams_() {
    getStaticParam(&mCorrectConstraint_s, "CorrectConstraint");
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getMapUnitParam(&mJoinSystemGroup_m, "JoinSystemGroup");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_CogWheel2::m34() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006692F0(mActor, *mJoinSystemGroup_m);
}

void DgnObj_DLC_CogWheel2::m35() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006694B4(mActor);
}

void DgnObj_DLC_CogWheel2::m36() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_710066956C(mActor, *mJoinSystemGroup_m);
}

void DgnObj_DLC_CogWheel2::m37() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && mActor)
        gear_mgr->sub_71006695DC(mActor);
}

bool DgnObj_DLC_CogWheel2::m4(ksys::act::BaseProc* proc) {
    return false;
}

}  // namespace uking::ai
