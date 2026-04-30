# CS61C 课程项目与实验 (Spring 2026)

UC Berkeley CS61C: Great Ideas in Computer Architecture (Machine Structures) — 涵盖 C 语言、RISC-V 汇编、CPU 设计、并行编程等内容。

## 项目概览

| 项目 | 主题 | 测试通过情况 | 完成度 |
|------|------|-------------|--------|
| **Project 1: snek** | C 语言贪吃蛇游戏 | 22/22 集成测试, 10/10 单元测试, 全部 custom 测试通过 | 100% |
| **Project 2: CS61Classify** | RISC-V 神经网络汇编 | 46/46 单元测试通过, 覆盖率部分(损失函数)未实现 | 90% |
| **Project 3: CS61CPU** | Logisim 五级流水线 CPU | Part A 13/13 通过, Part B 仅 3/28 通过 | 40% |

## 实验概览

| 实验 | 主题 | 状态 |
|------|------|------|
| **Lab 00** | 环境配置 (SSH, Git) | 完成 |
| **Lab 01** | C 语言基础 (指针/数组/结构体/字符串) | 完成 (6/6 编译通过) |
| **Lab 02** | GDB 调试 (断点/栈帧/内存检查) | 完成 (代码部分; ex3_commands.txt 为空) |
| **Lab 03** | RISC-V 汇编基础 (Calling Convention) | 完成 |
| **Lab 04** | RISC-V 与 C 互转 | 完成 |
| **Lab 05** | Logisim 时序电路 (FSM) | 电路文件已编写 (测试依赖 proj3 文件, 本地无法运行) |
| **Lab 06** | Logisim 流水线与数据冒险 | 电路文件已编写 (同上) |
| **Lab 07** | OpenMP 并行编程 (SIMD/多线程) | 完成 (所有测试通过, 加速比正确) |

## 各项目详情

### Project 1: snek (C 贪吃蛇)

用 C99 实现的贪吃蛇游戏。核心任务:
- 游戏状态管理与棋盘渲染
- 蛇移动逻辑 (方向更新/食物碰撞/墙体检测)
- 多蛇支持与碰撞判定
- 文件 I/O 读入棋盘/输出结果

```bash
cd sp26-proj1-starter
make snake && make run-integration-tests  # 22 项全部通过
make unit-tests                            # 10 项全部通过
make custom-tests                          # 全部通过
```

### Project 2: CS61Classify (RISC-V 神经网络)

用 RISC-V 汇编实现神经网络分类器。核心函数:
- `abs.s` — 绝对值
- `relu.s` — ReLU 激活函数
- `argmax.s` — 最大索引查找
- `dot.s` — 向量点积
- `matmul.s` — 矩阵乘法
- `read_matrix.s` / `write_matrix.s` — 文件 I/O
- `classify.s` — 主分类流程

```bash
cd sp26-proj2-starter
bash test.sh all       # 46 项全部通过
bash test.sh coverage  # 4 项失败 (损失函数未实现, 属于可选扩展)
```

> 未完成: 覆盖率部分的四个损失函数 (`abs_loss.s`, `zero_one_loss.s`, `squared_loss.s`, `initialize_zero.s`) 仍为 TODO 状态。

### Project 3: CS61CPU (五级流水线 RISC-V CPU)

用 Logisim Evolution 设计一个五级流水线 RISC-V CPU。分 Part A 和 Part B。

**Part A (完成):**
- ALU: 6/6 通过
- RegFile: 4/4 通过
- addi 集成测试: 3/3 通过

**Part B (未完成):**
- 分支比较器 (branch-comp): 0/3 — BrEq/BrLt 输出未定义 (U)
- 立即数生成器 (imm-gen): 2/6 — I-type 通过, B/J/S/U-type 失败
- 部分加载/存储 (partial-load/store): 0/7 全部失败
- 集成测试 (分支/立即数/跳转/lui/内存/程序): 1/11 通过 (仅 all-regs 通过)

```bash
cd sp26-proj3-starter
bash test.sh part_a   # 13/13 通过
bash test.sh part_b   # 3/28 通过
```

## 总结评价

| 维度 | 评分 | 说明 |
|------|------|------|
| C 语言编程 | ★★★★★ | Proj1 完整体现指针/内存管理/文件 I/O 能力 |
| RISC-V 汇编 | ★★★★☆ | Proj2 核心函数完成良好, 缺损失函数扩展 |
| CPU 设计 | ★★☆☆☆ | Part A 扎实, Part B 大部分电路尚需实现 |
| 并行编程 | ★★★★★ | Lab07 OpenMP 部分完整, 加速比显著 |
| 调试能力 | ★★★★☆ | Lab02 大部分完成, 部分文本答案未填 |

**总评**: 项目 1 和项目 2 核心部分完成度很高, 代码质量经全部本地测试验证。项目 3 Part B 是主要短板 — 分支比较器(BrEq/BrLt 输出未接线)、立即数生成器(B/J/S/U-type 位拼接有误)、部分加载/存储等子电路均需完善, 导致集成测试大面积失败。建议优先完成 branch-comp 和 imm-gen, 它们是后续集成测试通过的前提。
