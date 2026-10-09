#include "KingSystem/Physics/Constraint/physRackAndPinionCs.h"
#include "KingSystem/Physics/Constraint/physUnk_71024f6640.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RackAndPinionCs::~RackAndPinionCs() = default;
Unk_71024f6640::~Unk_71024f6640() = default;

u32 sub_7100F703FC(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1a0;
}

// The common callback lifetime follows the derived constraint families.
Unk_71012a6844::ItemA::ItemA(Constraint* constraint) : mConstraint(constraint) {}
Unk_71012a6844::ItemA::~ItemA() = default;

void Unk_71012a6844::ItemA::sub_7100F6EC20(sead::Vector3f*, sead::Vector3f*) const {}
void Unk_71012a6844::ItemA::sub_7100F6FF60(sead::Vector3f*, sead::Vector3f*) const {}

void Unk_71012a6844::ItemA::sub_7100F70C48(ItemA* item) {
    System::instance()->sub_7101216AB0(item);
    delete item;
}

}  // namespace ksys::phys
