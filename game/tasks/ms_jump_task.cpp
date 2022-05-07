#include "ms_jump_task.h"
#include "ms_message.h"

namespace msgame
{
    namespace gametasks
    {
        JumpTask::JumpTask(GAMESESSION::GameSession* game, int64 playerId, int64 jumpStart)
        : msutils::MSSimpleTask(game)
        , playerId_(playerId)
        , jumpStart_(jumpStart)
        {
        }

        void JumpTask::Execute()
        {
        }

        void JumpTask::OnFinished()
        {
        }
    } // namespace gametasks
} // namespace msgame
