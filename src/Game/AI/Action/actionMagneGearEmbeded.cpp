#include "Game/AI/Action/actionMagneGearEmbeded.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace uking::action {

MagneGearEmbeded::MagneGearEmbeded(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearEmbeded::~MagneGearEmbeded() {
    if (_20) {
        ksys::phys::Constraint::destroy(_20);
        _20 = nullptr;
    }
    if (_28) {
        ksys::phys::Constraint::destroy(_28);
        _28 = nullptr;
    }
    if (_30) {
        ksys::phys::Constraint::destroy(_30);
        _30 = nullptr;
    }
    if (_38) {
        ksys::phys::Constraint::destroy(_38);
        _38 = nullptr;
    }
    if (_40) {
        ksys::phys::Constraint::destroy(_40);
        _40 = nullptr;
    }
    if (_48) {
        operator delete(_48);
        _48 = nullptr;
    }
}

bool MagneGearEmbeded::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MagneGearEmbeded::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MagneGearEmbeded::leave_() {
    ksys::act::ai::Action::leave_();
}

void MagneGearEmbeded::loadParams_() {}

void MagneGearEmbeded::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
