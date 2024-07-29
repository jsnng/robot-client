from multiprocessing import Queue
import logging

log = logging.getLogger()
log.setLevel(logging.NOTSET)

class BaseReceiver:
    def __init__(self, ip_addr='127.0.0.1', port=50514): # NOT IN USE
        self.ip_addr = ip_addr
        self.port = port 
        self.socket = None
        self.recv = Queue()

    def pipe(self):
        return self.recv

    def connect(): ...
    
    def send(self): ...

    def recieve(self): ...

    @staticmethod
    def add_cls_specific_arguments(parent):  # NOT IN USE
        parser = parent.add_argument_group('sender')
        parser.add_argument('--ip', type=str, default='127.0.0.1')
        parent.add_argument('--port', type=int, default=50514)
        return parent