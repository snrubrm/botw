#include "aal/aalAuxBusMgr.h"
#include "aal/aalAuxBusRootFx.h"

namespace aal {

// 0x7100ba25fc (D1) / 0x7100ba2658 (D0)
AuxBusCtrl::~AuxBusCtrl() {
    mRoot->clearAuxBusDataCtrl();
    _68 = true;
    if (mRoot) {
        delete mRoot;
        mRoot = nullptr;
    }
}

// 0x7100ba2860
void AuxBusCtrl::setAuxBusDataCtrl(AuxBusDataCtrl* control) {
    mRoot->setAuxBusDataCtrl(control);
}

}  // namespace aal
