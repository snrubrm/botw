#include "Game/AI/AI/aiGanonBeastWait.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GanonBeastWait::GanonBeastWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastWait::~GanonBeastWait() = default;

bool GanonBeastWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = static_cast<act::Enemy*>(mActor)) {
        const s32 time = enemy->_f28.sub_7100001AA4(1.0f);
        enemy->_e68 = ksys::Timer(time, time);
    }
    _40 = *mIsWeakPointAppearMode_a;
    changeChild("待機");
}

void GanonBeastWait::leave_() {
    sub_71005DB594(mActor, sead::Vector3f(0, 0, 35));
}

void GanonBeastWait::loadParams_() {
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

bool GanonBeastWait::m34() {
    return *mIsWeakPointAppearMode_a;
}

void GanonBeastWait::calc_() {
    auto* child = getCurrentChild();

    if (!_41 && _40 != *mIsWeakPointAppearMode_a) {
        if (*mIsWeakPointAppearMode_a)
            changeChild("弱点露出");
        else
            changeChild("復帰");
        _40 = *mIsWeakPointAppearMode_a;
        return;
    }

    if (!child->isFinished() && !child->isFailed()) {
        if (!child->isChangeable() || m34() || !isCurrentChild("待機"))
            return;

        auto* actor = mActor;
        if (!sead::IsDerivedFrom<act::Enemy>(actor))
            return;
        auto* enemy = static_cast<act::Enemy*>(actor);
        if (enemy->_e68.value <= sead::Mathf::epsilon()) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("レーザー発射", &params);
        }
    } else {
        if (isCurrentChild("レーザー発射") || isCurrentChild("復帰")) {
            if (auto* enemy = static_cast<act::Enemy*>(mActor)) {
                const s32 time = enemy->_f28.sub_7100001AA4(1.0f);
                enemy->_e68 = ksys::Timer(time, time);
            }
        }
        changeChild("待機");
    }
}

}  // namespace uking::ai
