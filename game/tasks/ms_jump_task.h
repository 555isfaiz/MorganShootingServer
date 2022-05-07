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
            int64 playerId_;
            int64 jumpStart_;

        public:
            void Execute() override;
            void OnFinished() override;

            JumpTask(GAMESESSION::GameSession* game, int64 playerId, int64 jumpStart);
            virtual ~JumpTask() {}
        };
    } // namespace gametasks
} // namespace msgame

#endif