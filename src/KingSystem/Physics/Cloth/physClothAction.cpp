#include "KingSystem/Physics/Cloth/physClothAction.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"

namespace ksys::phys {

ClothActionHandle::ClothActionHandle(ClothSet* set, s16 index)
    : mClothSet(set), mAction(nullptr), mIndex(index), mEnabled(false) {}

ClothActionHandle::~ClothActionHandle() {
    if (mAction && mClothSet) {
        if (mEnabled) {
            mClothSet->removeAction(this, mIndex);
            mEnabled = false;
        }
        mAction->removeReference();
        mClothSet = nullptr;
        mAction = nullptr;
    }
}

void ClothActionHandle::setEnabled(bool enabled) {
    if (mEnabled == enabled)
        return;
    if (mEnabled) {
        mClothSet->removeAction(this, mIndex);
        mEnabled = false;
    } else {
        mClothSet->addAction(this, mIndex);
        mEnabled = true;
    }
}

bool ClothActionHandle::initialize(sead::Heap* heap) {
    mAction = new Action(this);
    m2(heap);
    return mAction != nullptr;
}

hclAction* ClothActionHandle::getAction() const {
    return mAction;
}

const ClothParam* ClothActionHandle::getClothParam() const {
    return mClothSet->_18[mIndex].mClothParam;
}

void ClothActionHandle::m2(sead::Heap*) {}

void ClothActionHandle::Action::m5(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) {
    mOwner->m3(sim_cloth, output, timestep);
}

}  // namespace ksys::phys
