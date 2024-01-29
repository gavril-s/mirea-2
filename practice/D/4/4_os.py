import sys
import platform
import os
import shutil
import glob
import subprocess
import time


def sort_tasks():
    path = os.path.join(os.getcwd(), "Ознакомительная практика")
    try:
        os.makedirs(os.path.join(path, "тема A"))
        os.makedirs(os.path.join(path, "тема B"))
    except Exception as e:
        print(e)

    for file in glob.glob("tasks/task_A*"):
        shutil.copy(file, os.path.join(path, "тема A", file[6:]))

    for file in glob.glob("tasks/task_B*"):
        shutil.copy(file, os.path.join(path, "тема B", file[6:]))


def run_tasks(foldername):
    print("folder тема A")
    for file in glob.glob(os.path.join(foldername, "тема A", "*")):
        print(">>>", "script", file)
        command = ["python", file]
        start = time.time()
        result = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        )
        finish = time.time()
        print(">>> >>> output", result.returncode, result.stdout, end="")
        print(">>> >>> time", finish - start, "s")
        print()

    print("folder тема B")
    for file in glob.glob(os.path.join(foldername, "тема B", "*")):
        print(">>>", "script", file)
        command = ["python", file]
        start = time.time()
        result = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        )
        finish = time.time()
        print(">>> >>> output", result.returncode, result.stdout, end="")
        print(">>> >>> time", finish - start, "s")
        print()


sort_tasks()
run_tasks(os.path.join(os.getcwd(), "Ознакомительная практика"))
