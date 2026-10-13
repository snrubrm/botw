#include "Game/gameEventMgrMiniGame.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

Unk_71024e80e0::~Unk_71024e80e0() = default;
SEAD_SINGLETON_DISPOSER_IMPL(Unk_71024e80e0)

void Unk_71024e80e0::init() { reset(); }
void Unk_71024e80e0::initBeforeStageGenB() { reset(); }

void Unk_71024e80e0::calc() {
    if (ksys::act::BaseProcMgr::instance()->isSpecialJobType(ksys::act::JobType::PreCalc) ||
        ksys::ui::sub_7100EDC4B8() || ksys::evt::Manager::instance()->hasActiveEvent())
        return;
    sub_7100E499EC();
}
