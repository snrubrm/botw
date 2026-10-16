#include "Game/Actor/Behavior/behaviorNPCTerrorNeckControl.h"
#include "Game/Actor/actNPC.h"

namespace uking::behavior {

NPCTerrorNeckControl::NPCTerrorNeckControl(const InitArg& arg) : NeckControl(arg) {}

NPCTerrorNeckControl::~NPCTerrorNeckControl() = default;

bool NPCTerrorNeckControl::init_(sead::Heap* heap) {
    if (!NeckControl::init_(heap))
        return false;
    _38 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCTerrorNeckControl::calc() {
    NeckControl::calc();
}

void NPCTerrorNeckControl::enter() {
    NeckControl::enter();
}

void NPCTerrorNeckControl::leave() {
    NeckControl::leave();
}

void NPCTerrorNeckControl::loadParams() {
    NeckControl::loadParams();
}

void NPCTerrorNeckControl::m15(sead::Vector3f* out) {
    if (_38)
        out->set(_38->_103c);
}

}  // namespace uking::behavior
