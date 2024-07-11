#include <iostream>
#include <pthread.h> // For POSIX threads and mutex

// Abstract Singleton class
class Singleton {
public:
    static Singleton* getInstance();
    // Helper function to initialize mutex
    static void initializeMutex();

    // Helper function to destroy mutex
    static void destroyMutex();
    // Example method
    void showMessage() {
        std::cout << "Hello from Singleton!" << std::endl;
    }

protected:
    Singleton() {} // Protected constructor to prevent direct instantiation
    Singleton(const Singleton&) = delete; // Disable copy constructor
    Singleton& operator=(const Singleton&) = delete; // Disable assignment operator

private:
    static Singleton* instance;
    static pthread_mutex_t mutex; // POSIX mutex

};

Singleton* Singleton::instance = nullptr;
pthread_mutex_t Singleton::mutex;

void Singleton::initializeMutex() {
    pthread_mutex_init(&mutex, nullptr);
}

void Singleton::destroyMutex() {
    pthread_mutex_destroy(&mutex);
}

Singleton* Singleton::getInstance() {
    if (instance == nullptr) {
        // Lock mutex
        pthread_mutex_lock(&mutex);

        // Double-check instance within critical section
        if (instance == nullptr) {
            instance = new Singleton();
        }

        // Unlock mutex
        pthread_mutex_unlock(&mutex);
    }
    return instance;
}

// Guard (Scope Mutex) class for managing mutex locks/unlocks
class Guard {
public:
    explicit Guard(pthread_mutex_t& mtx) : mutex(mtx) {
        pthread_mutex_lock(&mutex); // Lock mutex on initialization
    }

    ~Guard() {
        pthread_mutex_unlock(&mutex); // Unlock mutex on destruction
    }

private:
    pthread_mutex_t& mutex;
};

// Usage example
int main() {
    // Initialize mutex for Singleton access
    Singleton::initializeMutex();

    // Get Singleton instance
    Singleton* singleton = Singleton::getInstance();

    // Use Singleton instance
    singleton->showMessage();

    // Clean up: Destroy mutex (not needed for singleton instance destruction)
    Singleton::destroyMutex();

    return 0;
}


// int main() {
//     Singleton* singleton = Singleton::getInstance();
//     singleton->showMessage();

//     return 0;
// }
