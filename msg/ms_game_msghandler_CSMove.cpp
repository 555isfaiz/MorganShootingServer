#include "ms_game_msghandler.h"
#include "game_session.h"
#include "ms_logger.h"
#include "ms_utils.h"
#include "game_params.h"

namespace msmessage
{
    namespace handler
    {
        void GameMsgHandler::Handle(int32 senderId, CSMove& msg)
        {
            //check move 

            //caculate new pos
            auto player = owner->GetPlayer(msg.playerId);
            btVector3 posBefore = player->GetPosition();
            btVector3 posCli;
            msutils::Msg2Vector3(msg.curPos, posCli);
            btVector3 direction;
            msutils::Msg2Vector3(msg.direction, direction);
            int64 now = msutils::GetNowMillSec();
            int64 deltaTime = now - msg.timeStamp;
            btVector3 finalPos;
            int32 checkRes = 0;
            auto scmove = new SCMove;

            // if ping is higher than 200ms
            if (deltaTime > 200)
            {
                //discard this movement
                finalPos = posBefore;
                scmove->result = 2;
            }
            else
            {
                int32 collideId = 0;
                
                btVector3 calPos;
                int32 collide = owner->CalcMovePos(senderId, direction, MOVE_DELTA, calPos);
                //pull back if the plane distance of calculated pos and client pos is bigger than 1
                if (collide || calPos.distance(posCli) > 1) //TBD
                {
                    finalPos = calPos;
                }
                else
                {
                    finalPos = posCli;
                }
            }
            
            // mLogInfo("pos from client, x:"<<msg.curPos.x<<" y:"<<msg.curPos.y<<" z:"<<msg.curPos.z<<", finalPos, x:"<<finalPos.x<<" y:"<<finalPos.y<<" z:"<<finalPos.z);
            player->SetPosition(finalPos); 

            // end:
            scmove->playerId = senderId;
            msutils::Vector32Msg(scmove->curPos, finalPos);
            scmove->direction.x = msg.direction.x;
            scmove->direction.y = msg.direction.y;
            scmove->direction.z = msg.direction.z;
            scmove->timeStamp = now;
            scmove->result = checkRes;
            std::vector<int32> ids = owner->GetPlayerIds();
            owner->SendMsg(ids, scmove);
            delete scmove;
        }
    }
}