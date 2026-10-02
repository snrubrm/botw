#include "Game/AI/AI/aiAssassinCallSelect.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::ai {

AssassinCallSelect::AssassinCallSelect(const InitArg& arg) : EnemyCalledAppear(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
AssassinCallSelect::~AssassinCallSelect() { ; }

bool AssassinCallSelect::init_(sead::Heap* heap) {
    return EnemyCalledAppear::init_(heap);
}

void AssassinCallSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyCalledAppear::enter_(params);
}

void AssassinCallSelect::calc_() {
    EnemyCalledAppear::calc_();
}

void AssassinCallSelect::m34() {
    if (ksys::evt::Manager::instance()->isActiveEventNameEqualTo(mChangeDemoName_s.cstr(),
                                                                 mChangeDemoEPName_s.cstr())) {
        changeChild("変身デモ");
    } else {
        EnemyCalledAppear::m34();
    }
}

// NON_MATCHING: stack slot order (the original's event-name temporaries come from an inline helper
// shared with m34) and the boolean return is kept as branches
bool AssassinCallSelect::m35() {
    if (!isCurrentChild("変身デモ"))
        return false;
    if (ksys::evt::Manager::instance()->isActiveEventNameEqualTo(mChangeDemoName_s.cstr(),
                                                                 mChangeDemoEPName_s.cstr())) {
        return true;
    }
    return false;
}

void AssassinCallSelect::leave_() {
    EnemyCalledAppear::leave_();
}

void AssassinCallSelect::loadParams_() {
    EnemyCalledAppear::loadParams_();
    getStaticParam(&mChangeDemoName_s, "ChangeDemoName");
    getStaticParam(&mChangeDemoEPName_s, "ChangeDemoEPName");
}

}  // namespace uking::ai
