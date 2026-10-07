#include "Game/AI/Behavior/behaviorPlayASWithBurnState.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::behavior {

PlayASWithBurnState::PlayASWithBurnState(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
PlayASWithBurnState::~PlayASWithBurnState() {
    ;
}

bool PlayASWithBurnState::m6(sead::Heap* heap) {
    return true;
}

void PlayASWithBurnState::m9() {}

void PlayASWithBurnState::loadParams() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOnWaitASName_s, "OnWaitASName");
    getStaticParam(&mOnToOffASName_s, "OnToOffASName");
    getStaticParam(&mOffToOnASName_s, "OffToOnASName");
}

// NON_MATCHING: the original tests `state == 1` before `state == 3` and compares the bytes with `uxtb`
void PlayASWithBurnState::sub_7100632B48(s8 state) {
    switch (state) {
    case 1:
        if (!mOffToOnASName_s.isEmpty())
            mActor->m107();
        break;
    case 3:
        if (!mOnToOffASName_s.isEmpty())
            mActor->m107();
        break;
    }

    if (_68 == state)
        return;

    switch (state) {
    case 0:
        _68 = 0;
        break;
    case 1:
        if (mOffToOnASName_s.isEmpty()) {
            _68 = 2;
        } else {
            _68 = 1;
            playAS(mOffToOnASName_s);
        }
        break;
    case 2:
        _68 = 2;
        playAS(mOnWaitASName_s);
        break;
    case 3:
        if (mOnToOffASName_s.isEmpty()) {
            _68 = 0;
        } else {
            _68 = 3;
            playAS(mOnToOffASName_s);
        }
        break;
    }
}

// NON_MATCHING: the original tests `_68` in the order 0, 3, 1 (chemical state 2) and reloads it for the final return
s8 PlayASWithBurnState::sub_7100632CD8() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 == 2) {
            if (_68 == 0)
                return 1;
            if (_68 == 3) {
                if (isASFinished())
                    return 1;
            } else if (_68 == 1) {
                if (isASFinished())
                    return 2;
            }
        } else {
            if (_68 == 1) {
                if (isASFinished())
                    return 3;
            } else if (_68 == 2) {
                return 3;
            } else if (_68 == 3) {
                if (isASFinished())
                    return 0;
            }
        }
    }
    return _68;
}

void PlayASWithBurnState::m8() {
    sub_7100632B48(sub_7100632CD8());
}

void PlayASWithBurnState::m7() {
    sub_7100632B48(sub_7100632CD8());
}

}  // namespace uking::behavior
