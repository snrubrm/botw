#include "Game/AI/AI/aiSimpleLiftable.h"

namespace uking::ai {

SimpleLiftable::SimpleLiftable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftable::~SimpleLiftable() = default;

void SimpleLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    m35();
}

bool SimpleLiftable::m36() {
    return isCurrentChild("通常");
}

}  // namespace uking::ai
