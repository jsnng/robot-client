'''placeholder controller'''
from Client.Controllers.BaseController import BaseController
from Client.Shared.Action import Action
import asyncio

import logging

log = logging.getLogger()
log.setLevel(logging.NOTSET)

class DummyController(BaseController): 
    def __init__(self):
        super().__init__()

    async def do(self, action: Action):
        while True:
            await asyncio.sleep(1.)
