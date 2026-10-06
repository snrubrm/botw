#include "Game/AI/Action/actionForkGanonBeastAppearHolyWall.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkGanonBeastAppearHolyWall::ForkGanonBeastAppearHolyWall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastAppearHolyWall::~ForkGanonBeastAppearHolyWall() = default;

bool ForkGanonBeastAppearHolyWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastAppearHolyWall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonBeastAppearHolyWall::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastAppearHolyWall::loadParams_() {
    getStaticParam(&mShowDist_s, "ShowDist");
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mEffectYOffset_s, "EffectYOffset");
    getStaticParam(&mUiDist_s, "UiDist");
    getStaticParam(&mKeyName_s, "KeyName");
    getStaticParam(&mBasePos_s, "BasePos");
}

// NON_MATCHING: register allocation / spills only (the original spills the player y to the stack and keeps the
// BasePos pointer in a caller-saved register, loading base.y late as an integer)
void ForkGanonBeastAppearHolyWall::calc_() {
    const sead::Vector3f player_pos = getPlayerPosition();
    const sead::Vector3f& base_pos = *mBasePos_s;
    const f32 dx = player_pos.x - base_pos.x;
    const f32 dz = player_pos.z - base_pos.z;
    const f32 distance = sead::Vector2f(dx, dz).length();
    if (distance > *mUiDist_s)
        ui::showInfoOverlay(0x2e);
    const f32 show_dist = *mShowDist_s;
    const bool is_active = _58.sub_7101241B6C();
    if (distance > show_dist) {
        if (!is_active)
            xlinkSearchAndEmit(mActor, mKeyName_s.cstr(), 2, &_58);
        sead::Vector3f dir(dx, 0.0f, dz);
        dir.normalize();
        sead::Vector3f pos = base_pos;
        pos += dir * *mAppearDist_s;
        pos.y = player_pos.y + *mEffectYOffset_s;
        sead::Matrix34f mtx;
        ksys::util::sub_71011F00EC(&mtx, -dir, sead::Vector3f::ey, pos, false);
        _58.sub_7101241A44(mtx);
    } else if (is_active) {
        _58.fadeXLink();
    }
}

}  // namespace uking::action
