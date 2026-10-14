#include "KingSystem/Sound/Actor/Action/actionEnvSeEmitPointInsectPlayAction.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

EnvSeEmitPointInsectPlayAction::EnvSeEmitPointInsectPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnvSeEmitPointInsectPlayAction::~EnvSeEmitPointInsectPlayAction() {
    if (_28) {
        uking::xlink::fade(*_28, -1);
        delete _28;
        _28 = nullptr;
    }
}

bool EnvSeEmitPointInsectPlayAction::init_(sead::Heap* heap) {
    _28 = new (heap) xlink2::HandleSLink;
    return true;
}

void EnvSeEmitPointInsectPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = -1;
    _20 = -1.0f;
    _24 = 0;
    _30.setNow();
    _38 = false;
}

void EnvSeEmitPointInsectPlayAction::leave_() {
    if (_28)
        uking::xlink::fade(*_28, -1);
}

void EnvSeEmitPointInsectPlayAction::loadParams_() {}

void EnvSeEmitPointInsectPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace ksys::snd
