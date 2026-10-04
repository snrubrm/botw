#include "Game/AI/Action/actionEquipedWithScale.h"

namespace uking::action {

EquipedWithScale::EquipedWithScale(const InitArg& arg) : EquipedAction(arg) {}

EquipedWithScale::~EquipedWithScale() = default;

void EquipedWithScale::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
    if (auto* bind = sub_7100E14604())
        bind->_98 = 2;
}

}  // namespace uking::action
