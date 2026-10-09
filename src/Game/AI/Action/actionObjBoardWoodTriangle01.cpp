#include "Game/AI/Action/actionObjBoardWoodTriangle01.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"

// Full 0x71002ff594 applies an impulse from the actor's chemical motion.
void sub_71002FF594(ksys::act::Actor* actor);

namespace uking::action {

namespace {
// Placeholder name: the user data of message 0x80000c8 (sent by the OctaAir AI classes) when `_0` is 1.
struct Unk_80000c8_Payload {
    u32 _0;
    u32 _4;
    bool _8;
};
}  // namespace

// NON_MATCHING: the embedded message sender members remain unmodeled.
ObjBoardWoodTriangle01::ObjBoardWoodTriangle01(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ObjBoardWoodTriangle01::~ObjBoardWoodTriangle01() = default;

bool ObjBoardWoodTriangle01::init_(sead::Heap* heap) {
    mActor->mDrawDistanceFlags.set(2);
    return true;
}

void ObjBoardWoodTriangle01::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody())
        body->setUserTag(&_400);
    if (auto* chemical = mActor->sub_71011D8A44(0)) {
        _3f8 = chemical->_14c;
        chemical->_14c = 1.0f;
    }
    mActor->setFlag(static_cast<ksys::act::Actor::ActorFlag>(0x13), true);
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(0xc);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "LodArea"))
        body->addToWorld();
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    auto* link_data = object->getLinkData();
    for (s32 i = 0; i < link_data->mLinksToSelf.links.size(); ++i) {
        const auto& link = link_data->mLinksToSelf.links[i];
        if (link.type != ksys::map::MapLinkDefType::BAndSCs)
            continue;
        auto* linked_object = link.other_obj;
        if (!linked_object)
            continue;
        ksys::act::ActorConstDataAccess accessor;
        linked_object->getActorWithAccessor(accessor);
        if (accessor.isEnemyProfile())
            accessor.linkAcquire(_20.emplaceBack());
    }
}

void ObjBoardWoodTriangle01::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "LodArea"))
        body->removeFromWorld();
}

void ObjBoardWoodTriangle01::loadParams_() {}

void ObjBoardWoodTriangle01::calc_() {
    sub_710020D9B4();
    if (_460)
        return;
    int count = 0;
    for (int i = 0; i < _20.size(); ++i) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(_20.at(i), &accessor))
            count += accessor.isStateCalc();
    }
    if (count < 1) {
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->_14c = _3f8;
        _460 = true;
    }
    sub_71002FF594(mActor);
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
