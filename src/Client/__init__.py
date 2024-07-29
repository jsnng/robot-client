from multiprocessing.managers import BaseManager, BaseProxy, MakeProxyType

class SharedResource:
    def __init__(self):
        self._action = None
        self._voltage = None
        self._current = None
    
    def get_action(self):
        return self._action
    
    def set_action(self, action):
        self._action = action

    def get_voltage(self):
        return self._voltage

    def set_voltage(self, voltage):
        self._voltage = voltage
    
    def get_current(self):
        return self._current
    
    def set_current(self, current):
        self._current = current
    
SharedResourceProxyBase = MakeProxyType('SharedResource', ('get_action', 'set_action', 'get_voltage', 'set_voltage', 'get_current', 'set_current'))
class SharedResourceProxy(SharedResourceProxyBase):
    def get_action(self):
        return self._callmethod('get_action')
    
    def set_action(self):
        return self._callmethod('set_action')
    
    def get_voltage(self):
        return self._callmethod('get_voltage')
    
    def set_voltage(self):
        return self._callmethod('set_voltage')
    
    def get_current(self):
        return self._callmethod('get_current')
    
    def set_current(self):
        return self._callmethod('set_current')