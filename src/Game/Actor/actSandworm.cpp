#include "Game/Actor/actSandworm.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

Sandworm::Sandworm(const CreateArg& arg) : Enemy(arg) {
    _1c0 = 1;
}

Sandworm::~Sandworm() = default;

ksys::act::BaseProc* Sandworm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Sandworm(arg);
}

// NON_MATCHING: the original loads the vtable pointer separately in each branch (ours hoists the common load)
void Sandworm::sub_71002CDAE4(bool on) {
    if (auto* x = _1250) {
        if (auto* y = x->_18) {
            if (on)
                y->m0();
            else
                y->m1();
        }
    }
}

bool Sandworm::m81(const ksys::Message& message) {
    const auto& type = message.getType();
    if (type == 0x3000004) {
        if (_14cc != 2) {
            sub_7100720814(this, _14cc);
            _14cc = 2;
        }
    } else if (type == 0x3000003) {
        if (_14c8 != 2) {
            _14cc = _14c8;
            sub_71007208EC(this);
        }
    }
    return Enemy::m81(message);
}

void Sandworm::killWithDropsAndEffects(int a1) {
    sub_71002CDB48();
    Enemy::killWithDropsAndEffects(a1);
    incrementGiantOrSandwormDefeatCount();
}

void Sandworm::m56(sead::Vector3f* pos) {
    if (_1650 && _1650->isAddedToWorld())
        _1650->getCenterOfMassInWorld(pos);
    else
        x_18(pos);
}

void Sandworm::setNecklaceFlag(s32 index) {
    if (index >= 1 && ksys::act::hasTag(this, 0x12ad8456))
        Enemy::setNecklaceFlag(index + 1);
}

void Sandworm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

}  // namespace uking::act
