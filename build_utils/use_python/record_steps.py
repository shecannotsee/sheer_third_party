import configparser
from typing import NoReturn
from path_helper import check_file_exists

class step_file:
    def __init__(self, file_path: str) -> None:
        """
        初始化 IniFileHandler 类，加载 ini 文件
        :param file_path: ini 文件的路径
        """
        self.file_path: str = file_path
        # 检查文件是否存在, 不存在则创建文件
        check_file_exists(self.file_path)
        self.config: configparser.ConfigParser = configparser.ConfigParser()
        self.config.read(self.file_path)

    def get_value(self, section: str, key: str) -> str:
        """
        获取ini文件中指定节和键的值
        :param section: 节的名称
        :param key: 键的名称
        :return: 键的值, 如果没有找到, 返回空字符串
        """
        if self.config.has_section(section) and self.config.has_option(section, key):
            value: str = self.config.get(section, key)
            return value
        else:
            return {}

    def set_value(self, section: str, key: str, value: str) -> NoReturn:
        """
        设置ini文件中指定节和键的值
        :param section: 节的名称
        :param key: 键的名称
        :param value: 要设置的值
        """
        if not self.config.has_section(section):
            self.config.add_section(section)
        self.config.set(section, key, value)
        # 将更改保存到文件
        with open(self.file_path, 'w') as configfile:
            self.config.write(configfile)
