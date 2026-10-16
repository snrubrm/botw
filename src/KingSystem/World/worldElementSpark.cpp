#include "KingSystem/World/worldElementSpark.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
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

void ElementSpark::m33(bool a, bool fixed) {
    if (_48)
        _48->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

void ElementSpark::m35(f32 delta_frame) {
    mArg.life = sead::Mathf::clampMin(mArg.life - delta_frame, 0.0f);
    if (mArg.life <= 0.0f)
        x();
}
