# 竞赛考场通用 Makefile (Linux 环境)
CXX = g++
STD = gnu++23

# 正式版：和OJ编译选项对齐，提交前用这个测试
CXXFLAGS_RELEASE = -O2 -std=$(STD) -Wall -Wextra -Wfatal-errors -pipe

# 调试版：带ASan地址消毒 + UB未定义行为检测，仅本地查错用
CXXFLAGS_DEBUG = -g -std=$(STD) -Wall -Wextra -Wfatal-errors -fsanitize=address,undefined -DLOCAL

# 模式规则：make x 自动编译 x.cpp → 可执行文件 x
%: %.cpp
	$(CXX) $(CXXFLAGS_RELEASE) $< -o $@

# 调试模式：make debug-x 生成带消毒器的调试版本
debug-%: %.cpp
	$(CXX) $(CXXFLAGS_DEBUG) $< -o $*

# 一键清理所有可执行文件、预编译头
.PHONY: clean
clean:
	rm -f $(basename $(wildcard *.cpp)) *.gch