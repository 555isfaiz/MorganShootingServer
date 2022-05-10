#include "ms_game_msghandler.h"
#include "game_session.h"

namespace msmessage
{
    namespace handler
    {
        void GameMsgHandler::Handle(int32 senderId, CSJump& msg)
        {
            auto player = owner->GetPlayer(senderId);
            auto jumpPhase = player->GetJumpPhase();
            if (jumpPhase >= 2)
                return;

            player->SetJumpPhase(jumpPhase + 1);
            if (jumpPhase == 1)
                player->SetJumpStart(msg.jumpStart);
            else
                owner->AddJumpTask(senderId, msg.jumpStart);
                
            auto scjump = new SCJump();
            scjump->playerId = senderId;
            std::vector<int32> ids = owner->GetPlayerIds(senderId);
            owner->SendMsg(ids, scjump);
            delete scjump;
        }
    }
}