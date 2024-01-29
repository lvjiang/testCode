import threading, queue, time

q = queue.Queue()

def worker(name):
    while True:
        item = q.get()
        print(f'thread{name} Working on {item}')
        print(f'thread{name} Finished {item}')
        time.sleep(1)
        if item == 2:
            print('++++')
            continue

        q.task_done()
        
# turn-on the worker thread
threading.Thread(target=worker, daemon=False, args=(1,)).start()
threading.Thread(target=worker, daemon=False, args=(2,)).start()

# send thirty task requests to the worker
for item in range(10):
    q.put(item)
print('All task requests sent\n', end='')


# block until all tasks are done
q.join()
print('All work completed')

while True:
    pass
