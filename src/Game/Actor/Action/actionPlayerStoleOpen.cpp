#include "Game/Actor/Action/actionPlayerStoleOpen.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : BindPlayerNodeEx(arg) {}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    BindPlayerNodeBase::enter_(params);
    _e0 = 0;
    mActor->setScale(sead::Vector3f::zero);
    _38._98 = 0;
}

void PlayerStoleOpen::loadParams_() {
    BindPlayerNodeBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    BindPlayerNodeBase::calc_();
    _e0 = sead::Mathf::clampMax(_e0 + *mEnlargeSpd_s, 1.0f);
    mActor->setScale({_e0, _e0, _e0});
    auto& link = act::PlayerInfo::getSomeProcLink();
    mActor->x_57(sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr)));

    auto* player = ksys::act::ActorSystem::instance()->getPlayerLink();
    if (!player)
        return;
    const sead::Color4f color = player->m314();
    if (!(_e4 == color)) {
        Unk_710260af28::instance()->sub_7100F1E2F4(mActor->getModel(), color);
        _e4 = color;
    }
    mActor->sub_71011CCB1C(player->m315());
    mActor->x_3(player->m316());
    if (!player->m194())
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1);
}

}  // namespace uking::action
