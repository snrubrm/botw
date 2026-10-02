#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {

BoneHandle::BoneHandle() = default;

// NON_MATCHING: the original stores BoneHandleBase's vtable after ~BoneAccessKeyEx (see ~BoneHandleBase)
BoneHandle::~BoneHandle() = default;

bool BoneHandle::m3(gsys::Model* model, bool sorted) {
    _30.search(model, _20);
    return _30.isValid();
}

void BoneHandle::setName(const sead::SafeString& name) {
    if (_8)
        return;
    _20 = name;
    _30.getKey().reset();
}

}  // namespace ksys::act
