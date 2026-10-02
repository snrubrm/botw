#include "Game/AI/AI/aiDuckRoot.h"

namespace uking::ai {

DuckRoot::DuckRoot(const InitArg& arg) : PreyRoot(arg) {}

DuckRoot::~DuckRoot() = default;

bool DuckRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void DuckRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
}

void DuckRoot::leave_() {
    PreyRoot::leave_();
}

void DuckRoot::loadParams_() {
    PreyRoot::loadParams_();
}

bool DuckRoot::m34() {
    return PreyRoot::m34();
}

bool DuckRoot::m35() {
    if (isCurrentChild("滝接触"))
        return false;
    return PreyRoot::m35();
}

bool DuckRoot::m37() {
    if (isCurrentChild("滝接触"))
        return false;
    return PreyRoot::m37();
}

}  // namespace uking::ai
