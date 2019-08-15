import psutil
from flask_restful import Resource

class Usage(Resource):

    def get(self):
        _memory = psutil.virtual_memory()
        return {
            "cpu": psutil.cpu_percent(interval=1, percpu=True),
            "mem": {
                "total": _memory.total,
                "available": _memory.available,
                "free": _memory.free,
                "used": _memory.used
            },
            "swp": psutil.swap_memory().percent
        }