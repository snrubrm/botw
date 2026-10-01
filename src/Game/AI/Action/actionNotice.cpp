#include "Game/AI/Action/actionNotice.h"

namespace uking::action {

Notice::Notice(const InitArg& arg) : ActionWithAS(arg) {}

void Notice::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS("Notice", false, 0, 0, -1.0f);
}

}  // namespace uking::action
