#!/bin/bash

# 查找匹配的文件并将结果存储在result1变量中
qmlscene=$(find /home/shecannotsee/desktop/qt_project -type f -name "qmlscene" 2>/dev/null | head -n 1)

# 检查是否找到了结果
if [ -z "$qmlscene" ]; then
  echo "未找到匹配的文件，请检查路径和文件名。"
  exit 1
fi

# 接收参数p1
p1="$1"

# 执行qmlscene和p1
"$qmlscene" "$p1"
