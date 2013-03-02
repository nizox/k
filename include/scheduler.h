#pragma once
#ifndef SCHEDULER_B6W6MWS3
#define SCHEDULER_B6W6MWS3

#include "utility.h"
#include "vector.hpp"
#include "function.hpp"

namespace task {

using task = kl::function<int ()>;

class scheduler
{
 public:
    scheduler();
    scheduler(scheduler const &) = delete;
    scheduler & operator = (scheduler const &) = delete;

    void
    run();

    template <typename C>
    void
    post(C &&c)
    {
        this->_tasks.push_back(kl::move(c));
    }
 private:
    kl::vector<task> _tasks;
};

} /* taks */


#endif /* end of include guard: SCHEDULER_B6W6MWS3 */
