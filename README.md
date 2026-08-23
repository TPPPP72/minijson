# Mini JSON Parser

一个极简的 JSON 解析器实现，通过**分步提交**的方式展示从词法分析到语法解析的完整过程，非常适合学习编译器/解析器的工作原理。

## 学习路径

本项目将 JSON 解析拆解为 **15 个循序渐进**的 commit，每一步都清晰可追踪：

### 第一阶段：基础框架 (commit 1-2)
- `db8eab7` - 初始化项目，配置构建和测试脚本
- `ff94cd9` - 定义 Token 结构，实现 Token 打印工具

### 第二阶段：词法分析 (commit 3-8)
- `2279892` - 实现整数和浮点数词法分析
- `29f6429` - 实现大括号 `{}` 和方括号 `[]` 词法分析
- `be857c1` - 测试脚本优化
- `9ba25a0` - 实现冒号 `:` 和逗号 `,` 词法分析
- `52a523e` - 实现字符串词法分析
- `eaa8310` - 实现布尔值 (`true`/`false`) 和 `null` 词法分析

### 第三阶段：语法解析 (commit 9-14)
- `2fad692` - 添加节点定义 (AST) 和打印工具
- `63ff7ee` - 测试脚本优化
- `ebae8c8` - 实现数字、布尔、null、字符串的解析器
- `e79e8c8` - 从文件读取 JSON 输入
- `0487838` - **实现 Pair 解析器**（键值对）
- `f5cf4b0` - **实现 Object 和 Array 解析器**

### 第四阶段：完整支持 (commit 15)
- `e24192d` - **支持嵌套对象和数组**（最终完整实现）

## 特性

- 支持 JSON 标准数据类型：Object, Array, String, Number, Boolean, Null
- 支持嵌套对象和数组（任意深度）
- 支持对象数组 `[{}, {}]` 和嵌套数组 `[[], []]`
- 支持混合类型数组 `[{}, []]`
- 完整的词法分析和递归下降解析
- 可视化 AST 结构

## ⚠️ 重要假设

**本项目假设所有输入 JSON 完全合法**，不包含任何错误处理或错误恢复机制。这意味着：
- 输入必须是格式良好的 JSON（括号匹配、引号闭合、逗号正确等）
- 遇到非法输入时，解析器行为未定义（可能崩溃或产生不可预测的结果）
- 本项目专注于**解析器的核心逻辑**，而非错误处理

这样的设计使得代码更简洁清晰，更适合学习目的。

## 架构

```
JSON 文本
    ↓
Lexer (词法分析) → Token 流
    ↓
Parser (语法分析) → AST (抽象语法树)
    ↓
NodeViewer → 可视化输出
```

### AST 节点结构

```
Node (基类)
├── ValueNode (String, Number, Boolean, Null)
├── ContainerNode (Object, Array)
│   └── child → Node* (链表)
└── PairNode (键值对)
    ├── key → ValueNode*
    └── value → Node*
```

## 快速开始

### 环境要求

- 支持 C++20 的编译器（如果使用非GCC编译器或GCC不在环境变量中需要自行修改构建脚本）
- Python 3.6+（用于运行测试脚本）

### 构建

```bash
python build.py
```

或直接使用编译命令：

```bash
g++ -std=c++20 -Iinclude main.cpp -o build/minijson.exe
```

### 使用方式

```bash
./minijson <json文件> <选项>
```

#### 选项说明

| 选项 | 说明 |
|------|------|
| `--dump-tokens` | 输出词法分析后的 Token 序列 |
| `--dump-ast` | 输出语法分析后的 AST（抽象语法树） |

#### 示例

```bash
# 输出 Token 序列
./minijson input.json --dump-tokens

# 输出 AST
./minijson input.json --dump-ast
```

## 测试用例

项目包含丰富的测试用例，覆盖各种 JSON 场景：

### 词法分析测试

| 文件 | 内容 | 测试目标 |
|------|------|----------|
| `input1.txt` | `123 1.23` | 整数和浮点数词法分析 |
| `input2.txt` | `{{[}]` | 大括号和方括号边界符号 |
| `input3.txt` | 包含冒号和逗号的对象/数组混合结构 | 冒号 `:` 和逗号 `,` 词法分析 |
| `input4.txt` | 完整的 JSON 对象（含字符串、数字、嵌套对象、数组） | 综合词法分析 |
| `input5.txt` | `true`/`false`/`null` | 布尔值和 null 词法分析 |

### 语法分析测试

| 文件 | 内容 | 测试目标 |
|------|------|----------|
| `input1.txt` | `"the test string"` | 字符串解析 |
| `input2.txt` | `1234` | 整数解析 |
| `input3.txt` | `123.4` | 浮点数解析 |
| `input4.txt` | `true` | 布尔值解析 |
| `input5.txt` | `null` | null 解析 |
| `input6.txt` | `"k" : "v"` | Pair（键值对）解析 |
| `input7.txt` | 包含多种类型的对象 | 简单对象解析 |
| `input8.txt` | `[1, 2, 3, 4]` | 数组解析 |
| `input9.txt` | 嵌套对象和数组 | 复杂嵌套解析 |
| `input10.txt` | 对象数组、嵌套数组、混合数组 | 高级嵌套结构解析 |

测试脚本会自动比对输出与预期结果：

```bash
python test.py
```
