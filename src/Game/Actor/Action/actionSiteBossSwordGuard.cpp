#include "Game/Actor/Action/actionSiteBossSwordGuard.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossSwordGuard::SiteBossSwordGuard(const InitArg& arg) : Guard(arg) {}

SiteBossSwordGuard::~SiteBossSwordGuard() = default;

bool SiteBossSwordGuard::init_(sead::Heap* heap) {
    return Guard::init_(heap);
}

void SiteBossSwordGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    Guard::enter_(params);

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_1558.isOnBit(5)) {
            if (auto* chemical = mActor->sub_71011D8A54("ShieldChemical")) {
                chemical->sub_7100D90D7C(false);
                chemical->sub_7100D91098(true);
                chemical->sub_7100D90AF4(true);
            }
        }
    }

    xlinkSearchAndEmit(mActor, "ShieldDamage", 2, nullptr);

    if (auto* as = mActor->getASList()) {
        if (auto* info = act::PlayerInfo::instance()) {
            ksys::act::acc::PlayerBase accessor;
            ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
            if (accessor.hasProc()) {
                ksys::act::ActorLinkConstDataAccess weapon_accessor;
                accessor.getWeapon(&weapon_accessor, 0);

                s32 value = 1;
                if (weapon_accessor.hasProc()) {
                    as->goLimpFromHeadShotMaybe(0x2c, weapon_accessor.getProfile(), 0);
                    if (!accessor.sub_7100009AA8(0))
                        value = accessor.m298_271();
                }

                const s32 count = accessor.m297();
                s32 clamped;
                if (count < 1)
                    clamped = 1;
                else
                    clamped = count > value ? value : count;

                sead::FormatFixedSafeString<16> name("%d", clamped);
                as->goLimpFromHeadShotMaybe(0x2f, name, 0);
            }
        }

        playAS("Shield_Reduce", false, 3, 0, -1.0f);
    }

    if (auto* cc = mActor->getCharacterController()) {
        Guard::enter_(params);
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Matrix34f mtx;
        ksys::util::sub_71011F0260(&mtx, _98, sead::Vector3f::ey, pos, false);
        cc->sub_7100F5FC8C(mtx);
    }
}

void SiteBossSwordGuard::leave_() {
    sead::DynamicCast<act::SiteBoss>(mActor);
    if (auto* chemical = mActor->sub_71011D8A54("ShieldChemical")) {
        chemical->sub_7100D90D7C(true);
        chemical->sub_7100D91098(false);
        chemical->sub_7100D90AF4(false);
    }
}

void SiteBossSwordGuard::loadParams_() {
    Guard::loadParams_();
}

void SiteBossSwordGuard::calc_() {
    Guard::calc_();
    const sead::Vector3f front = _98;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Matrix34f mtx;
    ksys::util::sub_71011F0260(&mtx, front, sead::Vector3f::ey, pos, false);
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FC8C(mtx);
}

}  // namespace uking::action
