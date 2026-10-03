#include "Game/AI/Action/actionObjBoardWoodTriangle01.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

namespace {
// Placeholder name: the user data of message 0x80000c8 (sent by the OctaAir AI classes) when `_0` is 1.
struct Unk_80000c8_Payload {
    u32 _0;
    u32 _4;
    bool _8;
};
}  // namespace

ObjBoardWoodTriangle01::ObjBoardWoodTriangle01(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ObjBoardWoodTriangle01::~ObjBoardWoodTriangle01() = default;

bool ObjBoardWoodTriangle01::init_(sead::Heap* heap) {
    mActor->mDrawDistanceFlags.set(2);
    return true;
}

void ObjBoardWoodTriangle01::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ObjBoardWoodTriangle01::leave_() {
    ksys::act::ai::Action::leave_();
}

void ObjBoardWoodTriangle01::loadParams_() {}

void ObjBoardWoodTriangle01::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: the original selects between `flags | 0x40` and `flags & ~0x40` with a csel (one load of the
// flags); BitFlag32::change() branches.
bool ObjBoardWoodTriangle01::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x80000c8)
        return false;

    const auto* data = static_cast<const Unk_80000c8_Payload*>(message->getUserData());
    if (data && data->_0 == 1) {
        if (auto* lod = mActor->getLodState())
            lod->mFlags10.change(1 << 6, data->_8);
    }
    return true;
}

}  // namespace uking::action
