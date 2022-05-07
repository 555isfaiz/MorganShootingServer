#include "ms_game_msghandler.h"
#include "game_session.h"

namespace msmessage
{
    namespace handler
    {
        void GameMsgHandler::Handle(int64 senderId, CSJump& msg)
        {
            owner->AddJumpTask(senderId, msg.jumpStart);
            auto scjump = new SCJump();
            scjump->playerId = senderId;
            std::vector<int32> ids = owner->GetPlayerIds(senderId);
            owner->SendMsg(ids, scjump);
            delete scjump;
        }
    }
}