#pragma once

#include "Game/UI/euiArcResourceMgr.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class ExpHeap;
}

namespace ksys::ui {

class ArcResourceMgr : public eui::ArcResourceMgr {
public:
    ArcResourceMgr();
    ~ArcResourceMgr() override = default;

    void loadArchive(sead::Heap* heap, const sead::SafeString& path) override;
};
KSYS_CHECK_SIZE_NX150(ArcResourceMgr, 0x20);

}  // namespace ksys::ui
