#include "KingSystem/Physics/Cloth/physClothWind.h"

namespace ksys::phys {

// NON_MATCHING: the original stores _3c and _40 separately (stp wzr, wzr); ours merges them.
ClothWind::ClothWind(ClothSet* set, s16 index) : ClothActionHandle(set, index) {
    mWind = sead::Vector3f::zero;
}

ClothWind::~ClothWind() = default;

}  // namespace ksys::phys
