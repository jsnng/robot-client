class BaseController:
    def __init__(self):
        pass

    def run(self, action):
        pass

    @staticmethod
    def add_cls_specific_arguments(parent):
        return parent