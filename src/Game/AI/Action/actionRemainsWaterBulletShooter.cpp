#include "Game/AI/Action/actionRemainsWaterBulletShooter.h"
#include "Game/AI/aiUnk_7102419cb0.h"

namespace uking::action {

RemainsWaterBulletShooter::RemainsWaterBulletShooter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterBulletShooter::~RemainsWaterBulletShooter() = default;

bool RemainsWaterBulletShooter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterBulletShooter::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.mTimer.reset(0.0f);
    mFlags.set(Flag::Changeable);
    _a8 = 0;
    if (mRemainsWaterBattleInfo_a) {
        if (auto* info = sead::DynamicCast<Unk_7102419cb0>(
                *static_cast<Unk_71025afb58**>(mRemainsWaterBattleInfo_a))) {
            int count = 0;
            for (auto* ptr : info->_8) {
                if (ptr)
                    ++count;
            }
            _ac = count & 1;
            if (!count)
                setFailed();
            sub_71002311F0();
            return;
        }
    }
    _ac = false;
    setFailed();
    sub_71002311F0();
}

void RemainsWaterBulletShooter::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWaterBulletShooter::loadParams_() {
    getStaticParam(&mBulletType_s, "BulletType");
    getStaticParam(&mReloadCounter_s, "ReloadCounter");
    getStaticParam(&mOffsetAngle_s, "OffsetAngle");
    getStaticParam(&mUseRandRot_s, "UseRandRot");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mBaseShootParam_s, "BaseShootParam");
    getStaticParam(&mOffsetYParam_s, "OffsetYParam");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

void RemainsWaterBulletShooter::calc_() {
    if (isFinished() || isFailed())
        return;
    _60.sub_7100D3BCE4();
    sub_71002311F0();
}

}  // namespace uking::action
