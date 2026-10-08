#include "Game/AI/Action/actionLookAtObject.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

LookAtObject::LookAtObject(const InitArg& arg) : LookAtObjectBase(arg) {}

LookAtObject::~LookAtObject() = default;

bool LookAtObject::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void LookAtObject::loadParams_() {
    LookAtObjectBase::loadParams_();
}

void LookAtObject::m33() {
    LookAtObjectBase::m33();
    --_30;
}

bool LookAtObject::oneShot_() {
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    switch (_30) {
    case 0:
        if (!m34(&link, &pos, _48, _58))
            _34 = 0;
        break;
    case 4:
        if (!m35(&link, &pos, _48, _58))
            _34 = 0;
        break;
    default:
        break;
    }
    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        switch (_34) {
        case 0:
            npc->sub_7100022E3C(_45);
            break;
        case 1:
            npc->sub_7100022D44(_45, 0, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
            break;
        default:
            break;
        }
    } else {
        setFailed();
    }
    return true;
}

}  // namespace uking::action
