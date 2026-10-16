#include "KingSystem/World/worldElementSpark.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

ElementSpark* sub_71010C30E8(const ElementSparkCreateArg* arg) {
    auto* holder = Manager::instance()->getChemicalMgr()->_ae8;
    if (holder)
        return holder->sub_71010C74A0(arg);
    return nullptr;
}

}  // namespace ksys::world

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
ElementSpark::ElementSpark(const ElementSparkCreateArg& arg, sead::Heap* heap)
    : Unk_7102518688(ElementName(), heap, false) {
    mArg = arg;

    ElementName name;
    name.mName = "spark";
    if (mArg.actor && mArg.actor->getChemicalContainer())
        name._18 = mArg.actor->getChemicalContainer()->_68;
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
    mArg.actor = nullptr;
}

ElementSpark::~ElementSpark() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    mXLink.fadeXLink();
}

// NON_MATCHING: stack layout (the original reuses the SphereParam slot for the second matrix) and scheduling.
bool ElementSpark::m29(const ElementName& name, sead::Heap* heap) {
    sead::Matrix34f mtx;
    mtx.makeT(mArg.position);

    ksys::phys::SphereParam param;
    param.name = "ChemicalSpark(Sphere)";
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.radius = mArg.radius;
    param.motion_type = ksys::phys::MotionType::Keyframed;
    _48 = ksys::phys::SphereRigidBody::make(&param, heap);
    if (!_48)
        return false;

    _48->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    setRigidBody(_48, true);
    if (auto* actor = ksys::act::Reaction::instance()->_38) {
        sead::Matrix34f effect_mtx;
        effect_mtx.makeT(mArg.position);
        xlinkSearchAndEmit(actor, "Chemical_Flint", 2, &mXLink);
        if (mXLink.sub_7101241B6C())
            mXLink.sub_7101241A44(effect_mtx);
    }
    return true;
}

void ElementSpark::m33(bool a, bool fixed) {
    if (_48)
        _48->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

void ElementSpark::m35(f32 delta_frame) {
    mArg.life = sead::Mathf::clampMin(mArg.life - delta_frame, 0.0f);
    if (mArg.life <= 0.0f)
        x();
}
