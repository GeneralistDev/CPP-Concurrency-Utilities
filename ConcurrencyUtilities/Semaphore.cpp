//
//  Semaphore.cpp
//  ConcurrencyUtils
//
//  Created by Daniel Parker on 26/06/2014.
//  Copyright (c) 2014 Daniel Parker. All rights reserved.
//

#include "Semaphore.h"

/**
 *  Default Constructor, which sets the tokens to zero.
 */
Semaphore::Semaphore() {
    Semaphore(0);
}

/**
 *  Construct a semaphore with nTokens starting tokens.
 *  
 *  @param  n       The number of tokens to initialise the semaphore with.
 */
Semaphore::Semaphore(uint64_t n) {
    tokens = n;
}

/**
 *  Acquire a token. If no tokens are available, the thread will 
 *  block until release is called and the thread is woken up.
 */
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

/**
 *  Release a single token.
 */
void Semaphore::Release() {
    Release(1);
}

/**
 *  Release n tokens and pulse a single waiting thread.
 *
 *  @param  n   The number of tokens to release.
 */
void Semaphore::Release(uint64_t n) {
    std::unique_lock<std::mutex> lock(lockObject);
    
    tokens += n;
    if (waitingThreads > 0) {
        condvar.notify_one();
    }
}