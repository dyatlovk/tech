#include "ThreadPool.hpp"

#include "third_party/plog/Log.h"

namespace mtEngine
{
  ThreadPool::ThreadPool(uint32_t threadCount)
  {
    PLOGI << "Threads workers start...";
    workers.reserve(threadCount);

    for (std::size_t i = 0; i < threadCount; ++i)
    {
      workers.emplace_back(
          [this]
          {
            while (true)
            {
              std::function<void()> task;

              {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });

                if (stop && tasks.empty())
                  return;

                task = std::move(tasks.front());
                tasks.pop();
              }

              task();
            }
          });
    }
  }

  ThreadPool::~ThreadPool()
  {
    PLOGI << "Threads workers destroy...";
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      stop = true;
    }

    condition.notify_all();

    for (auto &worker : workers)
      worker.join();

    PLOGI << "Threads workers terminated";
  }

  void ThreadPool::Wait()
  {
    std::unique_lock<std::mutex> lock(queueMutex);

    condition.wait(lock, [this]() { return tasks.empty(); });
  }
} // namespace mtEngine
