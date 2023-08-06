#pragma once

#include <Formats/Aliases/Primitives.h>
#include <shared_mutex>
#include <vector>
#include <algorithm>
#include <atomic>
#include <thread>

namespace TotkToolkit::Threading::Mutexes {

    /// <summary>
    /// Modified from https://stackoverflow.com/questions/36619715/a-shared-recursive-mutex-in-standard-c
    /// </summary>
    class SharedRecursive : public std::shared_mutex
    {
    public:
        void lock(void) {
            std::thread::id thisId = std::this_thread::get_id();
            if (mExclusiveOwner == thisId) {
                // recursive locking
                mExclusiveCount++;
            }
            else {
                // normal locking
                {
                    std::unique_lock<std::shared_mutex> lock(mSharedOwnersMutex);
                    std::vector<std::thread::id>::iterator it = std::find(mSharedOwners.begin(), mSharedOwners.end(), thisId);
                    if (it != mSharedOwners.end()) {
                        std::shared_mutex::unlock_shared();
                        mSharedOwners.erase(it);
                    }
                }

                std::shared_mutex::lock();
                mExclusiveOwner = thisId;
                mExclusiveCount = 1;
            }
        }
        void lock_shared(void) {
            std::thread::id thisId = std::this_thread::get_id();
            bool threadIsSharedOwner;
            {
                std::shared_lock<std::shared_mutex> lock(mSharedOwnersMutex);
                threadIsSharedOwner = std::find(mSharedOwners.begin(), mSharedOwners.end(), thisId) != mSharedOwners.end();
            }
            if (threadIsSharedOwner || mExclusiveOwner == thisId) {
                // recursive locking
            }
            else {
                // normal locking
                std::shared_mutex::lock_shared();
                std::unique_lock<std::shared_mutex> lock(mSharedOwnersMutex);
                mSharedOwners.push_back(thisId);
            }
        }
        void unlock(void) {
            if (mExclusiveCount > 1) {
                // recursive unlocking
                mExclusiveCount--;
            }
            else {
                // normal unlocking
                mExclusiveOwner = std::thread::id();
                mExclusiveCount = 0;
                std::shared_mutex::unlock();
            }
        }
        void unlock_shared(void) {
            std::thread::id thisId = std::this_thread::get_id();
            bool threadIsSharedOwner;
            std::vector<std::thread::id>::iterator it;
            {
                std::unique_lock<std::shared_mutex> lock(mSharedOwnersMutex);
                it = std::find(mSharedOwners.begin(), mSharedOwners.end(), thisId);
                threadIsSharedOwner = it != mSharedOwners.end();
                if (threadIsSharedOwner)
                    mSharedOwners.erase(it);
            }
            if (threadIsSharedOwner) {
                // normal unlocking
                std::shared_mutex::unlock_shared();
            }
        }

    private:
        std::atomic<std::thread::id> mExclusiveOwner;
        F_U32 mExclusiveCount;
        std::vector<std::thread::id> mSharedOwners; std::shared_mutex mSharedOwnersMutex;
    };
}