import os

def findLogFile() -> tuple[str, str]:

    current_dir = os.getcwd()

    log_dir = os.path.join(current_dir, "../logs")
    path: str = ""

    fn: str = ""
    
    for (root, _, files) in os.walk(log_dir):
        for f in files:
            if f == "sensor.log":
                fn = f 
                path = root
    
    return path, fn

def parseLine(line: str) -> float | None:
    if "[INFO]" not in line:
        return None
    
    temp_newline = line.split("[INFO] ")
    if len(temp_newline) < 2:
        return None
    temp = temp_newline[1].strip()

    try:
         return float(temp) 
    except ValueError:
         return None

def openLogFile(fn: str) -> list:
    content = []

    with open(fn, "r") as logfile:
        for index, line in enumerate(logfile):
            res: float | None = parseLine(line) 
            if res is not None:
                content.append(res)
            else: 
                print(f"[WARNING] Not valid input in line number {index}, skip")

    return content


def checkContent(c: list) -> bool: 
    if len(c) > 0:
        return True 

    return False 


if __name__ == "__main__":

    find_log_file_tuple: tuple[str, str] = findLogFile()
    path, filename = find_log_file_tuple
    
    abspath: str = os.path.join(path, filename)
    content_lfloat: list = openLogFile(abspath)
    
    if checkContent(content_lfloat):
        print("[INFO] Content of the log file is not empty")
    else: 
        print("[WARNING] Content of the log file is empty")
    
    parsedLine: float | None = parseLine("Mon Apr 13 10:04:50 2026 [INFO]")
    if parsedLine == None:
        print("[WARNING] Line doesn't contain [INFO]")
    else:
        print("[INFO] Correct value")


