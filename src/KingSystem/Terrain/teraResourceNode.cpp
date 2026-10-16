#include "KingSystem/Terrain/teraResourceNode.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

Unk_710110d278* Unk_7101108460::getB() const {
    return mB;
}

Unk_710110cfd0* Unk_7101108460::getA() {
    return mA;
}

const Unk_710110cfd0* Unk_7101108460::getA() const {
    return mA;
}

u16 Unk_7101108460::sub_7101108614() const {
    return mB->_8->id;
}

bool Unk_7101108460::sub_7101108624() const {
    return mB->_a0 > sead::Mathf::epsilon();
}

}  // namespace ksys::tera
