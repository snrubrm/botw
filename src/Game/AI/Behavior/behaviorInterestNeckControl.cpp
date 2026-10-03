#include "Game/AI/Behavior/behaviorInterestNeckControl.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace uking::behavior {

InterestNeckControl::InterestNeckControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InterestNeckControl::~InterestNeckControl() = default;

// NON_MATCHING: the original stores the four -1.0f / 0 words as two 64-bit constants (integer-typed
// fields?); ours uses two `stp w, w` pairs
bool InterestNeckControl::m6(sead::Heap* heap) {
    auto* global = ksys::act::GlobalParameter::instance();
    _30 = global->getGlobalParam()->mNPCIgnorePlayerTime.ref();
    _34 = global->getGlobalParam()->mNPCCancelIgnorePlayerTime.ref();
    _40 = _30;
    _44 = _30;
    _48 = -1.0f;
    _4c = -1.0f;
    _50 = -1.0f;
    _54 = 0;
    return true;
}

// NON_MATCHING: the original zeroes the request in aligned 8 / 16 byte chunks from +0x10 (we start at +0xc); the
// request layout is only partly known
void InterestNeckControl::m8() {
    _3c = 0;
    if (_38 < 0) {
        if (auto* awareness = mActor->getAwareness()) {
            Unk_71023e26d8 request;
            if (auto* sensor = awareness->_260[0]) {
                if (sensor->m5(&request))
                    _38 = request._c;
            }
        }
    }
}

void InterestNeckControl::loadParams() {
    getStaticParam(&mIgnorePlayerByTimePass_s, "IgnorePlayerByTimePass");
}

void InterestNeckControl::m9() {
    auto* actor = mActor;
    if (!actor || actor->get1a0())
        return;
    if (auto* obj = actor->getMapObject()) {
        if (obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }
    sub_71005DB3EC(actor);
}

}  // namespace uking::behavior
