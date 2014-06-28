//
//  Semaphore.h
//  ConcurrencyUtils
//
//  Created by Daniel Parker on 26/06/2014.
//  Copyright (c) 2014 Daniel Parker. All rights reserved.
//

#ifndef __ConcurrencyUtils__Semaphore__
#define __ConcurrencyUtils__Semaphore__

#pragma GCC visibility push(default)

#include <iostream>
#include <mutex>
#include <condition_variable>

/**
 *  Semaphore concurrency utility, which can be used to control thread
 *  access permission.
 */
class Semaphore {
public:
    /**
     *  Default Constructor, which sets the tokens to zero.
     */
    Semaphore();
    
    /**
     *  Construct a semaphore with nTokens starting tokens.
     *
     *  @param  n       The number of tokens to initialise the semaphore with.
     */
    Semaphore(uint64_t nTokens);
    
    /**
     *  Acquire a token. If no tokens are available, the thread will
     *  block until release is called and the thread is woken up.
     */
    void Acquire();
    
    /**
     *  Release a single token.
     */
    void Release();
    
    /**
     *  Release n tokens and pulse a single waiting thread.
     *
     *  @param  n   The number of tokens to release.
     */
    void Release(uint64_t nTokens);
    
protected:
    /**
     *  An object to lock for access to class invariants.
     */
    std::mutex lockObject;
    
    /**
     *  Used to have threads wait, and to pulse threads.
     */
    std::condition_variable condvar;
    
    /**
     *  The tokens in this Semaphore.
     */
    uint64_t tokens;
    
    /**
     *  The number of threads that are trying to acquire.
     */
    uint64_t waitingThreads;
};

#endif /* defined(__ConcurrencyUtils__Semaphore__) */