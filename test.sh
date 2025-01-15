#!/bin/bash
cd build && make && cd ../bin
# 定义测试数据 (将标准结果和输入字符串填入以下数组)
inputs=("../anbn.pda aaabbb" "../anbn.pda abb")
expected_outputs=("true" "false")

# 程序名称
program="./fla"

# 计数器
total_tests=${#inputs[@]}
passed_tests=0

# 遍历测试用例
for i in "${!inputs[@]}"; do
    input="${inputs[$i]}"
    expected_output="${expected_outputs[$i]}"

    # 执行程序并捕获输出
    actual_output=$($program $input)

    # 检查结果
    if [ "$actual_output" == "$expected_output" ]; then
        echo "Test $((i + 1)): Passed"
        ((passed_tests++))
    else
        echo "Test $((i + 1)): Failed"
        echo "  Input: $input"
        echo "  Expected: $expected_output"
        echo "  Got: $actual_output"
    fi
done

# 总结结果
echo
echo "Tests Passed: $passed_tests/$total_tests"
