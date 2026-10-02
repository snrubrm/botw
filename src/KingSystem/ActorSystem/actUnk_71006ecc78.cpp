#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"

namespace ksys::act {

bool Unk_71006ecc78::sub_71006EDA58() {
    if (auto* ragdoll = mActor->getPhysicsField70())
        return ragdoll->removeFromWorldAndResetLinks();
    return true;
}

void Unk_71006ecc78::sub_71006EE128(sead::Vector3f* out) const {
    *out = _8->_c4;
}

f32 Unk_71006ecc78::sub_71006EE148() const {
    return _8->_d4 / 30.0f;
}

u8 Unk_71006ecc78::sub_71006EE274() const {
    return _8->_dc;
}

}  // namespace ksys::act
