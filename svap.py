from os import system, listdir
from time import sleep

path = "/home/veter/Изображения/Обои/"
path_log = "/home/veter/.config/nitrogen/log.txt"
mont = 2
sle = 15

with open(path_log, "a") as log_file: 
    while True:
        list_dir = listdir(path)
        try:
            for i in list_dir:
                list_file = listdir(f"{path}{i}")
                try:
                    for j in range(mont):
                        system(f"nitrogen --head={j} --set-scaled {path}{i}/{list_file[j]}")
                except:
                    print(f"{path}{i}", file=log_file)
                sleep(sle)
        except:
            pass    


