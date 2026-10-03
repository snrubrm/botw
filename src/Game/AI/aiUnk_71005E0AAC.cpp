#include "Game/AI/aiUnk_71005E0AAC.h"
#include <cmath>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/CameraMgr.h"

// NON_MATCHING: the original keeps the Enemy-cast link selection as branches (the default link is only
// loaded on the else path) and orders the three fsub of the direction differently; ours selects with csel
bool sub_71005E0AAC(ksys::act::Actor* actor, bool a, f32 angle) {
    sead::Vector3f position;
    sead::Vector3f direction;
    ksys::act::BaseProcLink* link = nullptr;
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor))
        link = &static_cast<uking::act::Enemy*>(actor)->_c48._8;
    if (!link)
        link = &ksys::act::sUnk_71026505e0;
    if (!link->hasProc())
        return false;

    bool result;
    {
        ksys::act::acc::PlayerBase accessor;
        ksys::act::acquireActor(link, &accessor);
        result = false;
        if (accessor.isPlayerProfile()) {
            const bool m180 = accessor.m180();
            if (a ? (m180 || accessor.m181()) :
                    (m180 || accessor.m181() || accessor.x_29() || accessor.m179())) {
                f32 dot = -1.0f;
                if (ksys::sub_7100D8C6AC(&position) && ksys::sub_7100D8C7FC(&direction)) {
                    sead::Vector3f to_actor = actor->get454() - position;
                    to_actor.normalize();
                    dot = to_actor.dot(direction);
                }
                result = dot >= std::cos(angle);
            }
        }
    }
    return result;
}
