#pragma once

#include "Game/UI/euiArcResourceMgr.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
namespace res {
class Handle;
}
namespace ui {

class ArcResourceMgr;

class ArcResource : public eui::ArcResourceMgr::ArcResource {
public:
    ArcResource(ArcResourceMgr* mgr, const sead::SafeString& name, u8* data, res::Handle* handle);
    ~ArcResource() override;

private:
    /* 0xa0 */ res::Handle* mHandle;
};
KSYS_CHECK_SIZE_NX150(ArcResource, 0xA8);

}  // namespace ui
}  // namespace ksys
