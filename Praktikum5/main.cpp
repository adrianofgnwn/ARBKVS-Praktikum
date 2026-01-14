#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// - - - Semaphore Class - - -
class Semaphore {
public: 
    Semaphore(int initial) : count_(initial) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(m_); // unique_lock enables unlock while sleeping and re-lock when waking up
        cv_.wait(lock, [this] { return count_ > 0; }); // cv_.wait(lock, CONDITION);
        /*
            If CONDITION is false:
            - unlocks the mutex
            - puts the thread to sleep
            - waits for a notification
            - re-locks the mutex
            - checks the condition again

            If CONDITION is true:
            - wait() returns immediately
        */

        --count_;
    }

    void release() {
        {
            std::lock_guard<std::mutex> lock(m_);
            ++count_;
        }
        cv_.notify_one(); // Wake one sleeping thread
    }

private:
    std::mutex m_;
    std::condition_variable cv_; // So threads sleep, doesn't waste CPU time and no busy-wait
    int count_; // Counter
};

// - - - Funktionen - - -
void lower_unsync() {
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void nums_unsync() {
    for (int i = 0; i <= 32; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;
}

void upper_unsync() {
    for (char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c;
    }
    std::cout << std::endl;
}

// Mutex Funktion
std::mutex cout_mutex; // Mutex declaration

void lower_mutex() {
    std::lock_guard<std::mutex> lock(cout_mutex);
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << c;
        
    }
    std::cout << std::endl;
}

void nums_mutex() {
    std::lock_guard<std::mutex> lock(cout_mutex);
    for (int i = 0; i <= 32; ++i) {
        std::cout << i;
    }
    std::cout << std::endl;
}

void upper_mutex() {
    std::lock_guard<std::mutex> lock(cout_mutex);
    for (char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c;
    
    }
    std::cout << std::endl;
}

// Semaphore Funktion
Semaphore sem(1); // Binary Semaphore (Mutex)

void lower_sem() {
    for (char c = 'a'; c <= 'z'; ++c) {
        sem.acquire();
        std::cout << c;
        sem.release();
    }
    std::cout << std::endl;
}

void nums_sem() {
    for (int i = 0; i <= 32; ++i) {
        sem.acquire();
        std::cout << i; 
        sem.release();
    }
    std::cout << std::endl;
}

void upper_sem() {
    for (char c = 'A'; c <= 'Z'; ++c) {
        sem.acquire();
        std::cout << c;
        sem.release();
    }
    std::cout << std::endl;
}

// - - - Main - - -
enum class Mode { Unsync = 1, Mutex = 2, Semaphore = 3 };

int main() {
    Mode mode = Mode::Semaphore;

    std::thread t1, t2, t3;

    switch (mode) {
        case Mode::Unsync:
            std::cout << "\nUnsynchronisiert\n";
            t1 = std::thread(lower_unsync);
            t2 = std::thread(nums_unsync);
            t3 = std::thread(upper_unsync);
            break;

        case Mode::Mutex:
            std::cout << "\nMit Mutex synchronisiert\n";
            t1 = std::thread(lower_mutex);
            t2 = std::thread(nums_mutex);
            t3 = std::thread(upper_mutex);
            break;

        case Mode::Semaphore:
            std::cout << "\nMit Semaphore(1) synchronisiert\n";
            t1 = std::thread(lower_sem);
            t2 = std::thread(nums_sem);
            t3 = std::thread(upper_sem);
            break;
    }

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Fertig." << std::endl;
    return 0;
}

/*
std::cout -> critical section (shared)
*/
