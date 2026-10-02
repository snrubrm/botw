#include "Game/AI/Behavior/behaviorNPCTerrorNeckControl.h"
#include "Game/Actor/actNPC.h"

namespace uking::behavior {

NPCTerrorNeckControl::NPCTerrorNeckControl(const InitArg& arg) : NeckControl(arg) {}

NPCTerrorNeckControl::~NPCTerrorNeckControl() = default;

bool NPCTerrorNeckControl::m6(sead::Heap* heap) {
    if (!NeckControl::m6(heap))
        return false;
    _38 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCTerrorNeckControl::m7() {
    NeckControl::m7();
}

void NPCTerrorNeckControl::m8() {
    NeckControl::m8();
}

void NPCTerrorNeckControl::m9() {
    NeckControl::m9();
}

void NPCTerrorNeckControl::loadParams() {
    NeckControl::loadParams();
}

void NPCTerrorNeckControl::m15(sead::Vector3f* out) {
    if (_38)
        out->set(_38->_103c);
}

}  // namespace uking::behavior
