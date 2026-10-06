#include "Game/AI/Action/actionPlayerLookAtObject.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLookAtObject::PlayerLookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

PlayerLookAtObject::~PlayerLookAtObject() = default;

bool PlayerLookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void PlayerLookAtObject::m33() {
    LookAtObjectBase::m33();
    if (_30 == 4)
        _30 = 5;
}

bool PlayerLookAtObject::oneShot_() {
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    if (_30 == 0) {
        if (!m34(&link, &pos, _48, _58))
            _34 = 0;
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
    return true;
}

void PlayerLookAtObject::m37(ksys::act::BaseProcLink* link, const sead::Vector3f* pos) {
    switch (_30) {
    case 0:
        if (link)
            static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 1, &_68, link,
                                                                   &sead::Vector3f::zero);
        else
            static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 2, &sead::Vector3f::zero,
                                                                   nullptr, pos);
        break;
    case 1:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 2, &sead::Vector3f::zero,
                                                               nullptr, pos);
        break;
    case 2:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 3, &sead::Vector3f::zero,
                                                               nullptr, pos);
        break;
    case 3:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 1, &_68, link,
                                                               &sead::Vector3f::zero);
        break;
    }
}

void PlayerLookAtObject::m38() {
    if (static_cast<ksys::act::Player*>(mActor)->_ea8.hasProc())
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(
            _45, 1, &sead::Vector3f::zero, &static_cast<ksys::act::Player*>(mActor)->_ea8,
            &sead::Vector3f::zero);
}

void PlayerLookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

}  // namespace uking::action
