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
        {
            auto player = game->GetPlayer(playerId);
            player->SetJumpStart(jumpStart);
        }

        void JumpTask::Execute()
        {
            GAMESESSION::GameSession* g = reinterpret_cast<GAMESESSION::GameSession*>(context_);
            auto player = g->GetPlayer(playerId_);
            int64 now = msutils::GetNowMillSec();
            int64 jumpStart = player->GetJumpStart();
            int64 last = lastExec_ == 0 ? jumpStart : lastExec_;
            lastExec_ = now;
            auto position = player->GetPosition();

            // get new velocity
            float y_v = JUMP_INITIAL_V - G * (now - jumpStart) / 1000;

            // update position
            float y = position.y() + y_v * (now - last) / 1000;
            position.setY(y);
            player->SetPosition(position);

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
            player->SetJumpPhase(0);
            player->SetJumpStart(0);
        }
    } // namespace gametasks
} // namespace msgame
