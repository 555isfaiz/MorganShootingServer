#ifndef _ms_jump_tast_
#define _ms_jump_tast_

#include "ms_simple_task.h"
#include "game_session.h"

#define GAMETASKS msgame::gametasks

namespace msgame
{
    namespace gametasks
    {
        class JumpTask : public msutils::MSSimpleTask
        {
        private:
            int32 playerId_;
            int64 lastExec_ = 0;

        public:
            void Execute() override;
            void OnFinished() override;

            JumpTask(GAMESESSION::GameSession* game, int32 playerId, int64 jumpStart);
            virtual ~JumpTask() {}
        };
    } // namespace gametasks
} // namespace msgame

#endif