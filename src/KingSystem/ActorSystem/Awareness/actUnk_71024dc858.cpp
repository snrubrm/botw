#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace ksys::act {

// NON_MATCHING: store merging (the original merges _1c/_20 and _28-_34 into 64-bit stores)
Unk_71024dc858::Unk_71024dc858() = default;

Unk_71024dc858::~Unk_71024dc858() {
    mLink.reset();
}

Unk_71024dc858* sub_7100D78E30(const sead::ObjArray<Unk_71024dc858>* array, s32 idx) {
    return array->at(idx);
}

}  // namespace ksys::act
