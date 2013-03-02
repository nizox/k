#include "scheduler.h"

namespace task {
    
scheduler::scheduler()
{
}

void
scheduler::run()
{
    while (1)
    {
        while (_tasks.empty() == false)
        {
            task t = _tasks.back();

            _tasks.pop_back();
            t();
        }
    }
}

} /* task */

