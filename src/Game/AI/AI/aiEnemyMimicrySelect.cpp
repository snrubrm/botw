#include "Game/AI/AI/aiEnemyMimicrySelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapPlacementMgr.h"

bool sub_71005DCD84(s32* material, ksys::act::Actor* actor, f32 range, bool unused);

namespace uking::ai {

EnemyMimicrySelect::EnemyMimicrySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMimicrySelect::~EnemyMimicrySelect() = default;

bool EnemyMimicrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMimicrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0xff;
    if (*mIsMimicry_m)
        sub_71003988E0(params);
    else
        sub_7100398A34(params);
}

bool EnemyMimicrySelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyMimicrySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMimicrySelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("擬態")) {
            *mIsStartResetMimicry_a = true;
            sub_7100398A34(nullptr);
        } else if (isCurrentChild("通常")) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
        }
        return;
    }
    if (isCurrentChild("擬態")) {
        sub_71005DD34C(mActor, false);
        if (_50 == 0xff && ksys::map::PlacementMgr::instance()->isStaticCompoundReady(
                              mActor->getMtx().getTranslation(), false)) {
            s32 material = 0;
            if (sub_71005DCD84(&material, mActor, 1.5f, false)) {
                sub_71005DD27C(mActor, material, 1.0f);
                *mMimicryMaterial_a = material;
                _50 = 0;
            } else {
                _50 = 1;
                *mIsStartResetMimicry_a = true;
                sub_7100398A34(nullptr);
            }
        }
    }
}

void EnemyMimicrySelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
