#include "Game/AI/Action/actionSystemApplyEnvSetAction.h"
#include "Game/gameGraphics.h"

namespace uking::action {

SystemApplyEnvSetAction::SystemApplyEnvSetAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemApplyEnvSetAction::~SystemApplyEnvSetAction() = default;

void SystemApplyEnvSetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* graphics = Graphics::instance();
    if (graphics && !graphics->mModelScenes.isEmpty()) {
        if (auto* scene = graphics->mModelScenes.unsafeAt(0)) {
            auto& env = scene->mEnv;
            const sead::SafeString name = mEnvSetName_d.cstr();
            const int index = env.sub_7100C2859C(name, 0);
            if (index < 0) {
                setFailed();
            } else {
                env.sub_7100C286EC(index, true, 0);
                scene->mFlags |= 2;
                setFinished();
            }
            return;
        }
    }
    setFailed();
}

void SystemApplyEnvSetAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemApplyEnvSetAction::loadParams_() {
    getDynamicParam(&mEnvSetName_d, "EnvSetName");
}

void SystemApplyEnvSetAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
