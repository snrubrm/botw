#include "Game/AI/AI/aiIceEnemyFeintBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

IceEnemyFeintBattle::IceEnemyFeintBattle(const InitArg& arg) : EnemyFeintBattle(arg) {}

IceEnemyFeintBattle::~IceEnemyFeintBattle() = default;

void IceEnemyFeintBattle::calc_() {
    auto* child = getCurrentChild();
    bool is_follow_up = false;
    if (child->isFinished() || child->isFailed())
        is_follow_up = isCurrentChild("追撃ち攻撃");

    child = getCurrentChild();
    if (is_follow_up) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        sub_7100381ED4();
        m37();
        return;
    }

    if (child->isChangeable() && isCurrentChild("戦闘準備")) {
        if (auto* link = sub_71005D9050(mActor)) {
            int state = 0;
            {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(link, &accessor);
                if (accessor.hasProc())
                    state = accessor.sub_7100D131D0(-1);
            }
            if (state == 1 && sub_7100382558()) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("追撃ち攻撃", &params);
                return;
            }
        }
    }
    EnemyFeintBattle::calc_();
}

void IceEnemyFeintBattle::loadParams_() {
    EnemyFeintBattle::loadParams_();
}

}  // namespace uking::ai
