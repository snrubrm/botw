#include "Game/Actor/Player/Action/actionPlayerTurnAndLookToObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerTurnAndLookToObject::PlayerTurnAndLookToObject(const InitArg& arg)
    : PlayerLookAtObject(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerTurnAndLookToObject::~PlayerTurnAndLookToObject() {
    ;
}

bool PlayerTurnAndLookToObject::init_(sead::Heap* heap) {
    return PlayerLookAtObject::init_(heap);
}

void PlayerTurnAndLookToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_188 = static_cast<ksys::act::Player*>(mActor)->m188();
    TurnAndLookToObjBase::enter_(params);
    if (is_188)
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    if (*mIsTurnToLookAtPos_d)
        _44 = true;
    if (_30 == 0) {
        if (!m34(&link, &pos, _48, _58)) {
            _d8 = true;
            _34 = 0;
        }
    }
    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);
    switch (_34) {
    case 0:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859FC0(_45);
        break;
    case 1:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 0, &sead::Vector3f::zero, nullptr,
                                                               &sead::Vector3f::zero);
        break;
    }
    m40();
}

void PlayerTurnAndLookToObject::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PlayerTurnAndLookToObject::loadParams_() {
    PlayerLookAtObject::loadParams_();
    getDynamicParam(&mIsUseSlowTurn_d, "IsUseSlowTurn");
    getDynamicParam(&mIsTurnToLookAtPos_d, "IsTurnToLookAtPos");
}

// NON_MATCHING: regalloc (this / controller registers swapped: x19 / x20)
void PlayerTurnAndLookToObject::calc_() {
    PlayerLookAtObject::calc_();
    auto* controller = mActor->getCharacterController();
    if (isFinished()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (isFailed()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (controller) {
        m41(controller);
    }
}

bool PlayerTurnAndLookToObject::isChangeable() const {
    return false;
}

// NON_MATCHING: the original keeps the "DemoTurn" / "DemoTurnNatural" choice as branches (ours: csel) and loads the
// z component of `front` as an int before the x multiply.
void PlayerTurnAndLookToObject::m40() {
    auto* controller = mActor->getCharacterController();
    if (_d8) {
        setFinished();
        return;
    }
    _38.y = 0.0f;
    _38.normalize();
    sead::Vector3f front(mActor->getMtx().m[0][2], 0.0f, mActor->getMtx().m[2][2]);
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, _38, sead::Vector3f::ey);
    mActor->getASList()->x_6(6, 0, sead::Mathf::rad2deg(angle * axis.y));
    if (!static_cast<ksys::act::Player*>(mActor)->m188()) {
        const char* name;
        if (*mIsUseSlowTurn_d)
            name = "DemoTurnNatural";
        else
            name = "DemoTurn";
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe(name, true, -1.0f);
    }
    mActor->getASList()->sub_710115EFD0(0, true, false, 0.1f);
    if (controller) {
        controller->sub_7100F5EDD8(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

// NON_MATCHING: as m40, the z component of `front` is loaded as an int; mActor is loaded once for both branches.
void PlayerTurnAndLookToObject::m41(ksys::phys::CharacterController* controller) {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (static_cast<ksys::act::Player*>(mActor)->m188()) {
        ksys::util::Unk_7101EC6BAC angle(sead::Mathf::atan2Idx(_38.x, _38.z));
        const bool done = static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &angle, -1, -1);
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
        if (done)
            setFinished();
        return;
    }

    if (!_d9) {
        sead::Vector3f front(mActor->getMtx().m[0][2], 0.0f, mActor->getMtx().m[2][2]);
        front.normalize();
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, front, _38, sead::Vector3f::ey);
        const sead::Vector3f& velocity = mActor->getASList()->sub_710115D3B8();
        const f32 turn = angle * axis.y;
        if (sead::Mathf::abs(sead::Mathf::rad2deg(turn)) < _2c) {
            static_cast<ksys::act::Player*>(mActor)->sub_710086800C(turn);
            static_cast<ksys::act::Player*>(mActor)->_1c68 =
                static_cast<ksys::act::Player*>(mActor)->x_5();
            static_cast<ksys::act::Player*>(mActor)->actionCommon();
            _d9 = true;
        } else {
            static_cast<ksys::act::Player*>(mActor)->sub_710086800C(velocity.y);
            static_cast<ksys::act::Player*>(mActor)->_1c68 =
                static_cast<ksys::act::Player*>(mActor)->x_5();
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (isFinishedAS(0, 0)) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe(_e0.cstr(), true, -1.0f);
        setFinished();
    }
}

}  // namespace uking::action
