from datetime import datetime
from typing import NoReturn
from enum import Enum

# 定义日志级别枚举
class LOG_LEVEL(Enum):
    INFO = "INFO"
    ERROR = "ERROR"
    WARNING = "WARNING"

def record(level: LOG_LEVEL, message: str) -> NoReturn:
    """
    打印格式化后的日志信息到控制台
    :param message: 日志信息
    :param level: 日志级别, 默认是INFO
    """
    current_time: str = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    log_format: str = "{time} - {level} - {message}"
    
    # 格式化日志信息
    formatted_message: str = log_format.format(
        time=current_time, 
        level=level.value,  # 使用枚举的值作为日志级别
        message=message
    )
    
    # 打印日志信息
    print(formatted_message)

# 测试代码部分
if __name__ == "__main__":
    # 测试不同级别的日志打印
    record(LOG_LEVEL.INFO, "This is an info message")
    record(LOG_LEVEL.WARNING, "This is a warning message")
    record(LOG_LEVEL.ERROR, "This is an error message")
