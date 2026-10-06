#include "Game/AI/Action/actionNPCCheckHorseAssociated.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCCheckHorseAssociated::NPCCheckHorseAssociated(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCCheckHorseAssociated::~NPCCheckHorseAssociated() = default;

bool NPCCheckHorseAssociated::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm->setBool(false, "Horse_IsAssociated"))
        return false;
    auto& horse_link = ksys::act::PlayerInfo::instance()->getHorseLink();
    ksys::act::ActorConstDataAccess accessor;
    if (horse_link.hasProc() && ksys::act::acquireActor(&horse_link, &accessor)) {
        const sead::Vector3f horse_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const f32 dx = pos.x - horse_pos.x;
        const f32 dz = pos.z - horse_pos.z;
        if (sead::Mathf::sqrt(dx * dx + dz * dz) < 50.0f) {
            if (gdm->setBool(true, "Horse_IsAssociated"))
                return true;
        }
    }
    return false;
}

}  // namespace uking::action
