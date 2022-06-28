#include "ms_game_msghandler.h"
#include "ms_logger.h"
#include "game_session.h"
#include "LinearMath/btQuaternion.h"

namespace msmessage
{
    namespace handler
    {
        void GameMsgHandler::Handle(int32 senderId, MessageBase *msg)
        {
            if (senderId == 0 || msg == NULL)
            {
                mLogError("unknown message!");
                return;
            }
            
            switch (msg->id)
            {
                case 2001:
                {
                    CSMove* csmove = reinterpret_cast<CSMove*>(msg);
                    Handle(senderId, *csmove);
                    break;
                }

                case 2003:
                {
                    CSJump* csjump = reinterpret_cast<CSJump*>(msg);
                    Handle(senderId, *csjump);
                    break;
                }

                case 2005:
                {
                    CSDash* csdash = reinterpret_cast<CSDash*>(msg);
                    Handle(senderId, *csdash);
                    break;
                }

                case 2008:
                {
                    CSPlayerRotate* csrotate = reinterpret_cast<CSPlayerRotate*>(msg);
                    auto player = owner->GetPlayer(csrotate->playerId);
                    btQuaternion rot(csrotate->rotation.x, csrotate->rotation.y, csrotate->rotation.z, csrotate->rotation.w);
                    player->SetRotation(rot);
                    break;
                }

                case 3001:
                {
                    break;
                }

                case 3003:
                {
                    break;
                }

                case 3004:
                {
                    break;
                }
            }
        }
    }
}