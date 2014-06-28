//
//  Semaphore.cpp
//  ConcurrencyUtils
//
//  Created by Daniel Parker on 26/06/2014.
//  Copyright (c) 2014 Daniel Parker. All rights reserved.
//

#include "Semaphore.h"

/* Default constructor */
Semaphore::Semaphore() {
    Semaphore(0);
}

/* Construct with nTokens starting tokens */
Semaphore::Semaphore(uint64_t nTokens) {
    tokens = nTokens;
}

/* Acquire a token. Threads will wait until pulsed if there aren't any available */
void Semaphore::Acquire() {
    std::unique_lock<std::mutex> lock{lockObject};
    
    waitingThreads++;
    while (tokens == 0) {
        condvar.wait(lock);
    }
    waitingThreads--;
    tokens--;
    if (tokens > 0 && waitingThreads > 0) {
        condvar.notify_one();
    }
}

/* Release one token */
void Semaphore::Release() {
    Release(1);
}

/* Release nTokens tokens and pulse waiting threads */
void Semaphore::Release(uint64_t nTokens) {
    std::unique_lock<std::mutex> locker(lockObject);
    
    tokens++;
    if (waitingThreads > 0) {
        condvar.notify_one();
    }
}


