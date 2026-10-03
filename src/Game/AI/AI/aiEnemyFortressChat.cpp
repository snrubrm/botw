#include "Game/AI/AI/aiEnemyFortressChat.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyFortressChat::EnemyFortressChat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFortressChat::~EnemyFortressChat() = default;

bool EnemyFortressChat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFortressChat::enter_(ksys::act::ai::InlineParamPack* params) {
    _48.reset();
    sub_710038E110();
}

void EnemyFortressChat::sub_710038E110() {
    Unk_71025b1808* unit = nullptr;
    if (mRegistedActorUnit_a)
        unit = sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (unit) {
        auto* chosen = &ksys::act::getDummyBaseProcLink();
        u32 count = 0;
        for (auto& entry : unit->_8.mEntries) {
            if (entry.link.hasProcInCalcState() && !(entry.link == _48)) {
                if (sead::GlobalRandom::instance()->getU32(count) == 0)
                    chosen = &entry.link;
                ++count;
            }
        }
        _48 = *chosen;
    } else {
        _48.reset();
        setFailed();
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_48, "TargetActor", -1);
    changeChild("呼びかけ", &pack);
}

// NON_MATCHING: the original indexes the entries as `base + i * 0x18` in the loop (ours strength-reduces to
// a pointer increment)
void EnemyFortressChat::leave_() {
    if (isActorDeletedOrDeleting())
        return;
    if (auto* unit = sead::DynamicCast<Unk_71025b1808>(
            *static_cast<Unk_71025afb58**>(mRegistedActorUnit_a))) {
        for (int i = 0; i < 32; ++i)
            _58.sub_710070DCC0(&unit->_8.mEntries(i).link, true);
    }
}

void EnemyFortressChat::loadParams_() {
    getStaticParam(&mNextPer_s, "NextPer");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

}  // namespace uking::ai
