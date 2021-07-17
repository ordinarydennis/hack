#include <cstdio>

#include "chat_server/chat_server.h"

int main() {

	ChatServer chatServer;

	chatServer.Init(11021);

	chatServer.Run();

	chatServer.Destory();

	return 0;
}




//#include "utils/tsqueue/tsqueue.h"
//int main() {
//
//    ThreadsafeQueue<int> q;
//    int num_elems = 0;
//
//    std::vector<std::thread> threads;
//    threads.emplace_back(FillQueue, 0, 10, std::ref(q));
//    threads.emplace_back(FillQueue, 10, 15, std::ref(q));
//    threads.emplace_back(FillQueue, 15, 30, std::ref(q));
//
//    std::thread flush(FlushQueue, std::ref(q), &num_elems);
//
//    cout << "Threads started, waiting for them to complete...\n";
//    flush.join();
//    std::for_each(threads.begin(), threads.end(),
//        std::mem_fn(&std::thread::join));
//
//    cout << "We processed " << num_elems << " elements" << endl;
//    cout << "After running the threads the Q has " << q.size() << " elements left" << endl;
//
//    for (auto f : flags) {
//        if (!f) {
//            cout << "ERROR: we missed one\n";
//        }
//    }
//    return EXIT_SUCCESS;
//
//    return 0;
//}