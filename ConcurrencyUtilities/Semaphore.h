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

class Semaphore {
public:
    /* Constructors */
    Semaphore();
    Semaphore(uint64_t nTokens);
    
    /* Acquire a token */
    void Acquire();
    
    /* Release one token */
    void Release();
    
    /* Release n tokens */
    void Release(uint64_t nTokens);
    
protected:
    std::mutex lockObject;
    std::condition_variable condvar;
    uint64_t tokens;
    uint64_t waitingThreads;
};

#endif /* defined(__ConcurrencyUtils__Semaphore__) */
