#include "Game/Actor/Action/actionNPCSellApp.h"

namespace uking::action {

NPCSellApp::NPCSellApp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellApp::~NPCSellApp() = default;

bool NPCSellApp::oneShot_() {
    return true;
}

}  // namespace uking::action
