#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace ksys::act {

void Unk_7100d3bc4c::sub_7100D3BC4C(f32 rate) {
    f32 delta = VFR::instance()->getDeltaFrame();
    if (mActor && mActor->getLodState())
        delta += mActor->getLodState()->_40;
    mValue += delta * rate;
}

void Unk_7100d3bce4::sub_7100D3BCE4() {
    mTimer.previous_value = mTimer.value;
    f32 delta = VFR::instance()->getDeltaFrame();
    if (mActor && mActor->getLodState())
        delta += mActor->getLodState()->_40;
    mTimer.value += delta * mTimer.rate;
}

}  // namespace ksys::act
