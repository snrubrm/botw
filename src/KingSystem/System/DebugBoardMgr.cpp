#include "KingSystem/System/DebugBoard.h"

DebugBoardMgr* DebugBoardMgr::sInstance;

// 0x710089baf4
ksys::IMessageBroker* DebugBoardMgr::getBroker0() {
    return &mBroker0;
}

// 0x710089bafc
ksys::IMessageBroker* DebugBoardMgr::getBroker1() {
    return &mBroker1;
}

// 0x710089bb08
ksys::IMessageBroker* DebugBoardMgr::getBroker2() {
    return &mBroker2;
}
