# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 目标文件
TARGET = elevator

# 源文件
SRCS = main.c elevator.c

# 生成的目标文件
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译源文件生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 伪目标，避免与文件名冲突
.PHONY: all clean
