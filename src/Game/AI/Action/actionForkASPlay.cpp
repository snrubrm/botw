#include "Game/AI/Action/actionForkASPlay.h"

namespace uking::action {

ForkASPlay::ForkASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

ForkASPlay::~ForkASPlay() = default;

void ForkASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

const char* ForkASPlay::m32() {
    return mASName_s.cstr();
}

}  // namespace uking::action
