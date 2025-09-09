from os import system, listdir
from time import sleep
from datetime import datetime

from conf import path, path_log, number_of_monitors, waiting_time

er = 0

with open(path_log, "a") as log_file: 
    print(f"Смена обоев запущена; Время {datetime.now()}", file=log_file)
    while er <= 25:
        try:
            list_dir = listdir(path)
        except:
            print(f"Ошибка при получении набора каталогов;Время {datetime.now()}", file=log_file)
            er += 1
            sleep(5)
            break
        er = 0
        for i in list_dir:
            list_file = listdir(f"{path}{i}")
            try:
                if len(list_file) < number_of_monitors:
                    print(f"Мониторов больше чем обоев. Везде поставлен первые обои; Путь к каталогу с нехваткой обоев:{path}{i};Время {datetime.now()}", file=log_file)
                    for j in range(number_of_monitors):
                        system(f"nitrogen --head={j} --set-scaled {path}{i}\\{list_file[0]}")
                elif len(list_file) < number_of_monitors:
                    print(f"Мониторов меньше чем обоев. Лишнии обои неучтены; Путь к каталогу с нехваткой обоев:{path}{i};Время {datetime.now()}", file=log_file)
                    for j in range(number_of_monitors):
                        system(f"nitrogen --head={j} --set-scaled {path}{i}\\{list_file[j]}")
                elif len(list_file) == number_of_monitors:
                    for j in range(number_of_monitors):
                        system(f"nitrogen --head={j} --set-scaled {path}{i}\\{list_file[j]}")
                else:
                    print(f"Неизвестная ошибка, код 1;Время {datetime.now()}", file=log_file)
            except:
                print(f"Неизвестная ошибка, код 2;Время {datetime.now()}", file=log_file)
            sleep(waiting_time)
    print(f"Смена обоев остановлена, много ошибок;Время {datetime.now()}", file=log_file)
        
