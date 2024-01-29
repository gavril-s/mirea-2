import datetime
from enum import Enum


class Logger:
    class LogKey(Enum):
        CRE = 0  # создание экземпляра класса
        INF = 1  # изменение
        ERR = 2  # сработало исключение

    def log(key: LogKey, comment: str, filename: str = "log.txt"):
        with open(filename, "a+") as logfile:
            date = datetime.datetime.now().strftime("%d.%m.%Y %H:%M:%S")
            logfile.write(" --- ".join((key.name, date, comment)))
            logfile.write("\n")
