#include <stdlib.h>
#include "game_session.h"
#include "ms_logger.h"
#include "jniUtils.h"
#include "game_params.h"
#include "ms_jump_task.h"

namespace msgame
{
    namespace msgamesession
    {
        GameSession::GameSession(int32 sessionId)
        :sessionId_(sessionId)
        ,curPhase_(PHASE_PREPARE)
        {
            bt_collision_config = new btDefaultCollisionConfiguration();
            bt_collision_dispatcher = new btCollisionDispatcher(bt_collision_config);
            bt_overlap_pair_cache = new btDbvtBroadphase();
            bt_world = new btCollisionWorld(bt_collision_dispatcher, bt_overlap_pair_cache, bt_collision_config);
            msgHandler_ = new msmessage::handler::GameMsgHandler(this);
            createTime_ = msutils::GetNowMillSec();
        }

        void GameSession::Pulse()
        {
            bt_world->performDiscreteCollisionDetection();
            while (!oncePipe_.IsEmpty())
            {
                auto t = oncePipe_.Pop();
                t.Execute();
            }

            auto iter = longPipe_.begin();
            while (iter != longPipe_.end())
            {
                (*iter)->Execute();
                if ((*iter)->IsFinished())
                {
                    (*iter)->OnFinished();
                    auto ptr = (*iter);
                    iter = longPipe_.erase(iter);
                    delete ptr;
                    continue;
                }
                iter++;
            }
            
            PulseHuman();

            //SCGameSync   sync in the end of the pulse
            {
                std::vector<int32> ids;
                auto msg = new msmessage::SCGameSync;
                for (auto iter = players_.begin(); iter != players_.end(); iter++)
                {
                    ids.push_back(iter->first);
                    msg->players.push_back(iter->second->GetMsg());
                }
                msg->sessionId = sessionId_;
                SendMsg(ids, msg);
                delete msg;
            }
        }

        void GameSession::PulseHuman()
        {
            for (auto iter = players_.begin(); iter != players_.end(); iter++)
            {
                iter->second->Pulse();
            }
        }

        //deprecated
        void GameSession::AddPlayer(int32 id, std::string& name)
        {
            // if (curPhase != PHASE_PREPARE)
            // {
            //     mLogError("game started already, sessionId:"<<sessionId<<"playerId:"<<id);
            //     return;
            // }
            
            // if (players.count(id) != 0)
            // {
            //     mLogError("player already exist, sessionId:"<<sessionId<<"playerId:"<<id);
            //     return;
            // }
            
            // gameobject::Player* p = new gameobject::Player(id, name);
            // players.insert(std::pair<int32, gameobject::Player>(id, *p));
            // mLogInfo("player joined game! sessionId:"<<sessionId<<", playerId:"<<id<<", playerName:"<<name);
        }

        void GameSession::InitGame(std::vector<int32>& ids, std::vector<std::string>& names)
        {
            msmessage::SCJoinGame *msg = new msmessage::SCJoinGame;
            msg->sessionId = sessionId_;
            int32 sideOnes = 0;
            
            // int32 index[] = {0, 0, 0, 0};
            for (int32 i = 0; i < ids.size(); i++)
            {
                int32 id = ids.at(i);
                std::string name = names.at(i);

                int32 number = id % 2;
                
                GAMEOBJECT::Player *p = new GAMEOBJECT::Player(id, name, number);
                bt_world->addCollisionObject(p->GetCollisionObject());
                players_.insert(std::pair<int32, gameobject::Player*>(id, p));
                msg->players.push_back(p->GetMsg());
                mLogInfo("player joined game! sessionId:"<<sessionId_<<", playerId:"<<id<<", playerName:"<<name);
            }

            for (int32 i = 0; i < ids.size(); i++)
            {
                msg->mySide = ids[i] % 2;
                SendMsg(ids.at(i), msg);
            }

            delete msg;
        }

        std::vector<int32> GameSession::GetPlayerIds()
        {
            return GetPlayerIds(-1);
        }

        std::vector<int32> GameSession::GetPlayerIds(int32 exclude)
        {
            std::vector<int32> ids;
            for (auto pair : players_)
            {
                if (pair.first == exclude)
                {
                    continue;
                }
                
                ids.push_back(pair.first);
            }
            return ids;
        }

        void GameSession::RemovePlayer(int32 id)
        {
            msgame::gameobject::Player *player = players_[id];
            players_.erase(id);

            delete player;

            // sync to client
        }

        void GameSession::SendMsg(int32 id, msmessage::MessageBase *msg)
        {
            // TODO: should pack msgs before call jni methods to reduce expands
            obj_jniUtils.sendMsg(this, id, msg);
        }

        void GameSession::SendMsg(std::vector<int32>& ids, msmessage::MessageBase *msg)
        {
            obj_jniUtils.sendMsgMulti(this, ids, msg);
        }

        void GameSession::HandleMsg(int32 senderId, msmessage::MessageBase* msg)
        {
            msgHandler_->Handle(senderId, msg);
        }

        int32 GameSession::CalcMovePos(int32 senderId, btVector3 direction, int64 duration, btVector3& finalPos)
        {
            GAMEOBJECT::Player *player = GetPlayer(senderId);
            btVector3 posNow = player->GetPosition();

            float distance = MOVE_SPEED * duration / 1000;

            float dirLen = direction.length();
            btVector3 caledPos(distance / dirLen * direction.x() + posNow.x(), 
                                distance / dirLen * direction.y() + posNow.y(),
                                distance / dirLen * direction.z() + posNow.z());

            // check collide
            // int collideBefore = bt_world->getDispatcher()->getNumManifolds();
            // player->SetPosition(caledPos);
            // bt_world->performDiscreteCollisionDetection();
            // int collideAfter = bt_world->getDispatcher()->getNumManifolds();
            // mLogInfo("collide before: " << collideBefore << " collide after: " << collideAfter);
            // if (collideAfter > collideBefore)
            // {
            //     finalPos = posNow;
            //     return 1;
            // } 
            // else if (collideAfter == collideBefore)
            // {
            //     for (int i = 0; i < collideAfter; i++) 
            //     {
            //         btPersistentManifold *contactManifold = bt_world->getDispatcher()->getManifoldByIndexInternal(i);
            //         {
            //             const btCollisionObject *objA = contactManifold->getBody0();
            //             const btCollisionObject *objB = contactManifold->getBody1();
            //             if (reinterpret_cast<GAMEOBJECT::Player*>(objA->getUserPointer())->id() == senderId
            //                  || reinterpret_cast<GAMEOBJECT::Player*>(objB->getUserPointer())->id() == senderId)
            //             {
            //                 finalPos = posNow;
            //                 return 1;
            //             }
            //         }
            //     }
            // }
            
            finalPos = caledPos;
            return 0;
        }

        void GameSession::AddJumpTask(int32 playerId, int64 jumpStart)
        {
            GAMETASKS::JumpTask *task = new GAMETASKS::JumpTask(this, playerId, jumpStart);
            AddLongTask(task);
        }

        GameSession::~GameSession()
        {
            delete msgHandler_;
            delete bt_world;
            delete bt_overlap_pair_cache;
            delete bt_collision_dispatcher;
            delete bt_collision_config;
        }
    }
}