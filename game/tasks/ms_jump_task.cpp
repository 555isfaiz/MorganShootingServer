#include "ms_jump_task.h"
#include "ms_message.h"
#include "game_params.h"
#include "ms_logger.h"

namespace msgame
{
    namespace gametasks
    {
        JumpTask::JumpTask(GAMESESSION::GameSession* game, int32 playerId, int64 jumpStart)
        : msutils::MSSimpleTask(game)
        , playerId_(playerId)
        , jumpStart_(jumpStart)
        {
            game->GetPlayer(playerId)->SetVelocity(btVector3(0, JUMP_INITIAL_V, 0));
        }

        void JumpTask::Execute()
        {
            int64 now = msutils::GetNowMillSec();
            int64 last = lastExec_ == 0 ? jumpStart_ : lastExec_;
            lastExec_ = now;
            GAMESESSION::GameSession* g = reinterpret_cast<GAMESESSION::GameSession*>(context_);
            auto player = g->GetPlayer(playerId_);
            auto v = player->GetVelocity();
            auto position = player->GetPosition();

            // update position
            float y = position.y() + v.y() * (now - last) / 1000;
            position.setY(y);
            player->SetPosition(position);

            // update velocity
            float y_v = v.y() - G * (now - last) / 1000;
            v.setY(y_v);
            player->SetVelocity(v);

            if (y <= INIT_ORIGIN_Y)
                finished_ = true;
        }

        void JumpTask::OnFinished()
        {
            GAMESESSION::GameSession* g = reinterpret_cast<GAMESESSION::GameSession*>(context_);
            auto player = g->GetPlayer(playerId_);
            auto position = player->GetPosition();

            // update position
            position.setY(INIT_ORIGIN_Y);
            player->SetPosition(position);
            player->SetVelocity(btVector3(0,0,0));
        }
    } // namespace gametasks
} // namespace msgame
