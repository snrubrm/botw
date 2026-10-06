#include "Game/AI/Action/actionTurnAndLookToObject.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnAndLookToObject::TurnAndLookToObject(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookToObject::~TurnAndLookToObject() = default;

bool TurnAndLookToObject::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    switch (_30) {
    case 0:
        if (!m34(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    case 4:
        if (!m35(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    }

    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);

    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        switch (_34) {
        case 0:
            npc->sub_7100022E3C(_45);
            break;
        case 1:
            npc->sub_7100022D44(_45, 0, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
            break;
        }
    } else {
        setFailed();
    }
    m40();
}

// NON_MATCHING: the original loads NPC::_fe8 as a full word (`ldr w8, [x19, #0xfe8]; and w8, w8, #0x40100000`; the plain u32
// gets narrowed to `ldrh` of the upper half here; an Atomic<u32> load would not be), and keeps `this` in x20 / the actor in x19.
void TurnAndLookToObject::m33() {
    LookAtObject::m33();
    auto* actor = mActor;
    auto* npc = sead::DynamicCast<uking::act::NPC>(actor);
    if (!npc) {
        setFailed();
        return;
    }
    _d0 = false;
    _d1 = false;
    if (npc->_fe8 & 0x40100000) {
        _d0 = true;
        if (_34 == 0)
            setFailed();
    }
    if (mActor->getPlayerRideInfo() && (mActor->getPlayerRideInfo()->_30 & 1)) {
        _d0 = true;
        if (_34 == 0)
            setFailed();
    }
    if (auto* schedule = npc->getSchedule()) {
        if (!schedule->_88.isEmpty())
            npc->_104c = _30 == -1 ? 2 : 1;
    }
}

void TurnAndLookToObject::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void TurnAndLookToObject::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookToObject::calc_() {
    LookAtObject::calc_();
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    auto* controller = mActor->getCharacterController();
    if (isFinished())
        playAS("Wait", true, 0, 0, -1.0f);
    if (isFinished() || isFailed()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    if (controller)
        m41(controller);
}

// NON_MATCHING: the original stores the initial front vector (x, 0 / z) after the length computation; ours stores x first.
void TurnAndLookToObject::m41(ksys::phys::CharacterController* controller) {
    if (_d1) {
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        front.y = 0.0f;
        front.normalize();
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, front, _38, sead::Vector3f::ey);
        const sead::Vector3f& velocity = mActor->getASList()->sub_710115D3B8();
        if (angle < sead::Mathf::abs(velocity.y)) {
            const sead::Vector3f turn_velocity(0.0f, angle * axis.y * 30.0f, 0.0f);
            controller->sub_7100F5FB24(turn_velocity);
            _d1 = true;
        } else {
            controller->sub_7100F5FB24(velocity * 30.0f);
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
